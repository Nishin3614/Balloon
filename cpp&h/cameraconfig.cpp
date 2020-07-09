// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// カメラ設定処理の説明[cameraconfig.cpp]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 描画 */
#include "cameraconfig.h"
#include "pause.h"
#include "fade.h"
#include "game.h"
#include "ui.h"
#include "pause_ui.h"
#include "camera.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CAMERACONFIG_TEXANIM (0.5f)
#define CCTA CAMERACONFIG_TEXANIM
#define CAMERACONFIG_NUMBER_TEXANIM (0.1f)
#define CCBTA CAMERACONFIG_NUMBER_TEXANIM

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// グローバル変数
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 選択
int CCameraconfig::m_nSelect = 0;
bool CCameraconfig::m_bConfig = false;						// 設定状態
int CCameraconfig::m_nSpeed = 3;							// カメラスピード
D3DXVECTOR2 CCameraconfig::m_AddSpeed = { 0.01f,-0.01f };		// カメラスピード加算

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCameraconfig::CCameraconfig()
{
	m_nSelect = 0;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCameraconfig::~CCameraconfig()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Init(void)
{
	// 背景の生成
	m_BgUi = std::move(CUi::LoadCreate_Self(CUi::UITYPE_SETTINGUI_BG));
	// 選択UIの生成
	m_uni_SelectUi = std::move(CScene_TWO::Creat_Unique(
		CScene_TWO::OFFSET_TYPE_CENTER,
		D3DVECTOR3_ZERO,
		{95.0f,60.0f},
		0.0f,
		{ 1.0f,1.0f,1.0f,1.0f }
	));
	// テクスチャー設定
	m_uni_SelectUi->BindTexture(CTexture_manager::GetTexture(69));
	// UIの生成
	m_Ui = std::move(CUi::LoadCreate_Self(
		CUi::UITYPE_SETTINGUI_SELECT
	));
	// テクスチャーアニメーション設定
	SetTexAnim();
	// 選択UIの位置更新
	m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
	m_uni_SelectUi->Set_Vtx_Pos();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Uninit(void)
{
	// 背景の終了処理
	for (int nCntUi = 0; nCntUi < (signed)m_BgUi.size(); nCntUi++)
	{
		m_BgUi[nCntUi]->Uninit();
	}
	// 選択UIの終了処理
	if (m_uni_SelectUi != NULL)
	{
		m_uni_SelectUi->Uninit();
	}
	// PauseUIの終了処理
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Uninit();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Update(void)
{
	/* ジョイパッド */
	if (CManager::GetJoy() != NULL)
	{
		// スティックの下方向に傾けたとき |
		// 下矢印が押されたとき |
		// ->次の項目へ
		if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_DOWN) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_DOWN))
		{
			m_nSelect++;
			// 上限超えたら
			if (m_nSelect >= CAMERACONFIG_MAX)
			{
				m_nSelect = CAMERACONFIG_UPDOWN;
			}
			// 選択UIの位置更新
			m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
			m_uni_SelectUi->Set_Vtx_Pos();
			// カーソル音
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
		}
		// スティックの上方向に傾けたとき |
		// 上矢印が押されたとき |
		// ->前の項目へ
		else if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_UP) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_UP))
		{
			m_nSelect--;
			// 下限超えたら
			if (m_nSelect < CAMERACONFIG_UPDOWN)
			{
				m_nSelect = CAMERACONFIG_RESET;
			}
			// 選択UIの位置更新
			m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
			m_uni_SelectUi->Set_Vtx_Pos();
			// カーソル音
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
		}
		// Bボタンを押したら |
		// ->選択している項目の処理
		if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_B))
		{
			Select();
		}
		// 右スティックを倒したら |
		// 右矢印を押したら
		// ->カメラの速度が上がる
		else if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_RIGHT) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_RIGHT))
		{
			// カメラの速さ設定
			if (m_nSelect == CAMERACONFIG_SPEED)
			{
				if (m_nSpeed < 9)
				{
					D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
					RotSpeed.x += m_AddSpeed.x;
					RotSpeed.y += m_AddSpeed.y;
					m_nSpeed++;
					// エンター音
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
				}
			}
			// テクスチャーアニメーション設定
			SetTexAnim();
		}
		// 左スティックを倒したら |
		// 左矢印を押したら
		// ->カメラの速度が下がる
		else if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_LEFT) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_LEFT))
		{
			// カメラの速さ設定
			if (m_nSelect == CAMERACONFIG_SPEED)
			{
				if (m_nSpeed > 1)
				{
					D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
					RotSpeed.x -= m_AddSpeed.x;
					RotSpeed.y -= m_AddSpeed.y;
					m_nSpeed--;
					// エンター音
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
				}
			}
			// テクスチャーアニメーション設定
			SetTexAnim();
		}
		// Aボタンを押したら |
		// ->戻る
		else if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_A))
		{
			// ポーズのカメラ設定状態をfalseに
			m_bConfig = false;
			// 選択番号を初期化する
			m_nSelect = CCameraconfig::CAMERACONFIG_UPDOWN;
		}
	}
	/* キーボード */
	// 下矢印を押したら |
	// Sボタンを押したら |
	// ->次の項目へ
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_DOWN) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_S))
	{
		m_nSelect++;
		// 上限超えたら
		if (m_nSelect >= CAMERACONFIG_MAX)
		{
			m_nSelect = CAMERACONFIG_UPDOWN;
		}
		// 選択UIの位置更新
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
		// カーソル音
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
	}
	// 上矢印を押したら |
	// Wボタンを押したら |
	// ->前の項目へ
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_UP) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_W))
	{
		m_nSelect--;
		// 下限超えたら
		if (m_nSelect < CAMERACONFIG_UPDOWN)
		{
			m_nSelect = CAMERACONFIG_RESET;
		}
		// 選択UIの位置更新
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
		// カーソル音
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
	}
	// エンター押したら |
	// ->選択している項目の処理
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
	{
		Select();
	}
	// 右を押したら
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RIGHT) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_D))
	{
		// カメラの速さ設定
		if (m_nSelect == CAMERACONFIG_SPEED)
		{
			if (m_nSpeed < 9)
			{
				D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
				RotSpeed.x += m_AddSpeed.x;
				RotSpeed.y += m_AddSpeed.y;
				m_nSpeed++;
				// エンター音
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
			}
		}
		// テクスチャーアニメーション設定
		SetTexAnim();
	}
	// 左を押したら
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_LEFT) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_A))
	{
		// カメラの速さ設定
		if (m_nSelect == CAMERACONFIG_SPEED)
		{
			if (m_nSpeed > 1)
			{
				D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
				RotSpeed.x -= m_AddSpeed.x;
				RotSpeed.y -= m_AddSpeed.y;
				m_nSpeed--;
				// エンター音
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
			}
		}
		// テクスチャーアニメーション設定
		SetTexAnim();
	}
	// BackSpaceを押したら |
	// ->戻る
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_BACKSPACE))
	{
		// ポーズのカメラ設定状態をfalseに
		m_bConfig = false;
		// 選択番号を初期化する
		m_nSelect = CCameraconfig::CAMERACONFIG_UPDOWN;
		// 選択UIの位置更新
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
		// エンター音
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	}
	/* 各UIの更新処理 */
	// 背景の更新処理
	for (int nCntUi = 0; nCntUi < (signed)m_BgUi.size(); nCntUi++)
	{
		m_BgUi[nCntUi]->Update();
	}
	// 選択UIの更新処理
	if (m_uni_SelectUi != NULL)
	{
		m_uni_SelectUi->Update();
	}
	// UIの更新処理
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Update();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Draw(void)
{
	// 背景の更新処理
	for (int nCntUi = 0; nCntUi < (signed)m_BgUi.size(); nCntUi++)
	{
		m_BgUi[nCntUi]->Draw();
	}
	// 選択UIの描画処理
	if (m_uni_SelectUi != NULL)
	{
		m_uni_SelectUi->Draw();
	}
	// UIの描画処理
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Draw();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 全体の初期化
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::SelfInit(void)
{
	// 選択初期化
	m_nSelect = 0;
}

#ifdef _DEBUG
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Debug(void)
{
}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CCameraconfig::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::UnLoad(void)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::unique_ptr<CCameraconfig> CCameraconfig::Create_Self(void)
{
	// 変数宣言
	std::unique_ptr<CCameraconfig> pCameraconfig(new CCameraconfig);
	// 初期化処理
	pCameraconfig->Init();
	// 生成したオブジェクトを返す
	return pCameraconfig;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 選択処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Select(void)
{
	// エンター音
	CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();

	// カメラ上下設定
	if (m_nSelect == CAMERACONFIG_UPDOWN)
	{
		RotSpeed.x *= -1;
		m_AddSpeed.x *= -1;
	}
	// カメラ左右設定
	else if (m_nSelect == CAMERACONFIG_LEFTRIGHT)
	{
		RotSpeed.y *= -1;
		m_AddSpeed.y *= -1;
	}
	// カメラの速さ設定
	else if (m_nSelect == CAMERACONFIG_SPEED)
	{
		if (m_nSpeed < 9)
		{
			RotSpeed.x += m_AddSpeed.x;
			RotSpeed.y += m_AddSpeed.y;
			m_nSpeed++;
		}
	}
	// 戻る
	else if (m_nSelect == CAMERACONFIG_BACK)
	{
		// ポーズのカメラ設定状態をfalseに
		m_bConfig = false;
		// 選択番号を初期化する
		m_nSelect = CCameraconfig::CAMERACONFIG_UPDOWN;
		// 選択UIの位置更新
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
	}
	// すべてのカメラ情報を前の状態に戻す
	else if (m_nSelect == CAMERACONFIG_RESET)
	{
		// すべてのカメラ情報をもとの状態に戻す
		CManager::GetRenderer()->GetCamera()->SetCameraInfo();
		m_nSpeed = 3;					// カメラスピード
		m_AddSpeed = { 0.01f,-0.01f };	// カメラスピード加算
	}
	// テクスチャーアニメーション設定
	SetTexAnim();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// テクスチャーアニメーション設定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::SetTexAnim(void)
{
	// yのカメラの回転スピードが-なら
	if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().x > 0)
	{
		// UIのテクスチャーアニメーション設定
		m_Ui[CAMERACONFIG_UPDOWN]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_NORMAL }, { 1.0f,CCTA + CCTA * TEX_NORMAL });
	}
	// yのカメラの回転スピードが+なら
	else if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().x < 0)
	{
		// UIのテクスチャーアニメーション設定
		m_Ui[CAMERACONFIG_UPDOWN]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_INVERSION }, { 1.0f,CCTA + CCTA * TEX_INVERSION });
	}
	// xのカメラの回転スピードが-なら
	if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().y > 0)
	{
		// UIのテクスチャーアニメーション設定
		m_Ui[CAMERACONFIG_LEFTRIGHT]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_INVERSION }, { 1.0f,CCTA + CCTA * TEX_INVERSION });
	}
	// xのカメラの回転スピードが+なら
	else if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().y < 0)
	{
		// UIのテクスチャーアニメーション設定
		m_Ui[CAMERACONFIG_LEFTRIGHT]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_NORMAL }, { 1.0f,CCTA + CCTA * TEX_NORMAL });
	}
	// カメラスピードの変化
	m_Ui[CAMERACONFIG_SPEED]->GetScene_Two()->SetTex({ CCBTA * m_nSpeed,0.0f }, { CCBTA + CCBTA * m_nSpeed,1.0f });
}
