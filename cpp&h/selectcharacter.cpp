// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター選択処理 [selectcharacter.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "selectcharacter.h"
/* 描画 */
#include "speedUP.h"
#include "revival.h"
#include "invisible.h"
#include "attackUP.h"
#include "scene_two.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_ICON_ORIGINPOS (D3DXVECTOR3(250.0f,658.0f,0.0f))	// キャラクターアイコンの1番目の位置
#define CHARACTER_ICON_ORIGINPOS_X (250.0f)							// キャラクターアイコンの1番目のX位置
#define CHARACTER_ICON_ORIGINPOS_Y (658.0f)							// キャラクターアイコンの1番目のY位置
#define CHARACTER_ICON_SPACE (250.0f)								// キャラクターアイコン同士の位置間隔
#define CHARACTER_ICON_SIZE (85.0f)									// キャラクターアイコンのサイズ

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CSelectCharacter::m_SaveCharaType[MAX_PLAYER] = {};	// プレイヤーが選んだキャラクタータイプを保存


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelectCharacter::CSelectCharacter() : CScene::CScene()
{
	// 初期化
	m_pSpeedUP = NULL;
	m_pRevival = NULL;
	m_pInvisible = NULL;
	m_pAttackUP = NULL;
	m_pCheckUi = NULL;
	m_CharacterType = 0;
	m_PlayerID = 0;
	m_bReady = false;
	for (int nCntCharacter = 0; nCntCharacter < CCharacter::CHARACTER_PLAYERMAX; nCntCharacter++)
	{
		m_pSelectIcon[nCntCharacter] = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelectCharacter::~CSelectCharacter()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Init(void)
{
	// プレイヤー(スピードアップ)
	m_pSpeedUP = CSpeedUP::Create_Self(m_PlayerID, m_pos);
	// プレイヤー(復活)
	m_pRevival = CRevival::Create_Self(m_PlayerID, m_pos);
	// プレイヤー(透明)
	m_pInvisible = CInvisible::Create_Self(m_PlayerID, m_pos);
	// プレイヤー(アタックアップ)
	m_pAttackUP = CAttackUP::Create_Self(m_PlayerID, m_pos);
	// 選択UI生成
	m_pSelectUi = CScene_TWO::Create(
		CScene_TWO::OFFSET_TYPE_CENTER,
		CHARACTER_ICON_ORIGINPOS,
		D3DXVECTOR2(CHARACTER_ICON_SIZE, CHARACTER_ICON_SIZE));
	// 選択UIのNULLチェック
	// ->テクスチャー設定
	if (m_pSelectUi != NULL)
	{
		// テクスチャー設定
		m_pSelectUi->BindTexture(CTexture_manager::GetTexture(13));
	}

	// それぞれの選択アイコン
	for (int nCntCharacter = 0; nCntCharacter < CCharacter::CHARACTER_PLAYERMAX; nCntCharacter++)
	{
		// 選択アイコン生成
		m_pSelectIcon[nCntCharacter] = CScene_TWO::Create(
			CScene_TWO::OFFSET_TYPE_CENTER,
			D3DXVECTOR3(CHARACTER_ICON_ORIGINPOS_X * (nCntCharacter + 1), CHARACTER_ICON_ORIGINPOS_Y, 0.0f),
			D3DXVECTOR2(CHARACTER_ICON_SIZE, CHARACTER_ICON_SIZE));
		// テクスチャー未設定
		//
		m_pSelectIcon[nCntCharacter]->BindTexture(CTexture_manager::GetTexture(18));
		//
		// テクスチャー未設定
	}
	// 選択UIのNULLチェック
	// ->位置設定
	if (m_pSelectUi != NULL)
	{
		// 選択UIの位置設定
		m_pSelectUi->SetPosition(m_pSelectIcon[m_CharacterType]->GetPosition());
		m_pSelectUi->Set_Vtx_Pos();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Uninit(void)
{
	// プレイヤー(スピードアップ)がNULLではないなら
	// ->終了処理
	if (m_pSpeedUP != NULL)
	{
		m_pSpeedUP->Uninit();
		delete m_pSpeedUP;
		m_pSpeedUP = NULL;
	}
	// プレイヤー(復活)がNULLではないなら
	// ->終了処理
	if (m_pRevival != NULL)
	{
		m_pRevival->Uninit();
		delete m_pRevival;
		m_pRevival = NULL;
	}
	// プレイヤー(透明)がNULLではないなら
	// ->終了処理
	if (m_pInvisible != NULL)
	{
		m_pInvisible->Uninit();
		delete m_pInvisible;
		m_pInvisible = NULL;
	}
	// プレイヤー(アタックアップ)がNULLではないなら
	// ->終了処理
	if (m_pAttackUP != NULL)
	{
		m_pAttackUP->Uninit();
		delete m_pAttackUP;
		m_pAttackUP = NULL;
	}
	// 選択UIのNULLチェック
	// ->終了処理
	if (m_pSelectUi != NULL)
	{
		// 終了処理
		//m_pSelectUi->Release();
		m_pSelectUi = NULL;
	}
	// キャラクター確定UIのNULLチェック
	// ->終了処理
	if (m_pCheckUi != NULL)
	{
		// 終了処理
		//m_pSelectUi->Release();
		m_pCheckUi = NULL;
	}
	// それぞれの選択アイコン
	// ->終了処理
	for (int nCntCharacter = 0; nCntCharacter < CCharacter::CHARACTER_PLAYERMAX; nCntCharacter++)
	{
		// 選択アイコンがNULLではないなら
		// ->終了処理
		if (m_pSelectIcon[nCntCharacter] != NULL)
		{
			// 終了処理
			//m_pSelectIcon[nCntCharacter]->Release();
			m_pSelectIcon[nCntCharacter] = NULL;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Update(void)
{
	if (!m_bReady)
	{
		if (m_pCheckUi != NULL)
		{
			m_pCheckUi->Release();
			m_pCheckUi = NULL;
		}
		// 右が入力されたら
		// ->キャラクター番号が加算
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_RIGHT))
		{
			m_CharacterType++;
		}
		// 左が入力されたら
		// ->キャラクター番号が減算
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_LEFT))
		{
			m_CharacterType--;
		}
		// 範囲設定
		if (m_CharacterType >= CPlayer::CHARACTER_PLAYERMAX)
		{
			m_CharacterType = 0;
		}
		else if (m_CharacterType < 0)
		{
			m_CharacterType = CPlayer::CHARACTER_PLAYERMAX - 1;
		}
	}
	else
	{
		if (m_pCheckUi == NULL)
		{
			m_pCheckUi = CScene_TWO::Create(
				CScene_TWO::OFFSET_TYPE_CENTER,
				CHARACTER_ICON_ORIGINPOS,
				D3DXVECTOR2(CHARACTER_ICON_SIZE, CHARACTER_ICON_SIZE));
			// 選択UIのNULLチェック
			// ->テクスチャー設定
			if (m_pCheckUi != NULL)
			{
				// テクスチャー設定
				m_pCheckUi->BindTexture(CTexture_manager::GetTexture(27));
				// 選択UIの位置設定
				m_pCheckUi->SetPosition(m_pSelectIcon[m_CharacterType]->GetPosition());
				m_pCheckUi->Set_Vtx_Pos();
			}
		}
	}
#ifdef _DEBUG
	CDebugproc::Print("キャラクター選択:%d\n", m_CharacterType);
#endif // _DEBUG

	// 現在のキャラクター番号の保存
	m_SaveCharaType[m_PlayerID] = m_CharacterType;

	// プレイヤーの更新
	switch (m_CharacterType)
	{
		// プレイヤー(スピードアップ)
	case 0:
		// プレイヤー(スピードアップ)がNULLではないなら
		// ->更新処理
		if (m_pSpeedUP != NULL)
		{
			m_pSpeedUP->Update();
		}
		break;
		// プレイヤー(復活)
	case 1:
		// プレイヤー(復活)がNULLではないなら
		// ->更新処理
		if (m_pRevival != NULL)
		{
			m_pRevival->Update();
		}
		break;
		// プレイヤー(透明)
	case 2:
		// プレイヤー(透明)がNULLではないなら
		// ->更新処理
		if (m_pInvisible != NULL)
		{
			m_pInvisible->Update();
		}
		break;
	case 3:
		// プレイヤー(アタックアップ)がNULLではないなら
		// ->更新処理
		if (m_pAttackUP != NULL)
		{
			m_pAttackUP->Update();
		}
		break;
	default:
		break;
	}

	// 選択UIのNULLチェック
	// ->選択UIの位置設定
	if (m_pSelectUi != NULL)
	{
		// 選択UIの位置設定
		m_pSelectUi->SetPosition(m_pSelectIcon[m_CharacterType]->GetPosition());
		m_pSelectUi->Set_Vtx_Pos();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Draw(void)
{
	switch (m_CharacterType)
	{
		// プレイヤー(スピードアップ)
	case 0:
		// プレイヤー(スピードアップ)がNULLではないなら
		// ->描画処理
		if (m_pSpeedUP != NULL)
		{
			m_pSpeedUP->Draw();
		}
		break;
		// プレイヤー(復活)
	case 1:
		// プレイヤー(復活)がNULLではないなら
		// ->描画処理
		if (m_pRevival != NULL)
		{
			m_pRevival->Draw();
		}
		break;
		// プレイヤー(透明)
	case 2:
		// プレイヤー(透明)がNULLではないなら
		// ->描画処理
		if (m_pInvisible != NULL)
		{
			m_pInvisible->Draw();
		}
		break;
	case 3:
		// プレイヤー(アタックアップ)がNULLではないなら
		// ->更新処理
		if (m_pAttackUP != NULL)
		{
			m_pAttackUP->Draw();
		}
		break;
	default:
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelectCharacter * CSelectCharacter::Create(
	int const &nPlayerId,	// プレイヤーID
	D3DXVECTOR3 const &pos	// 位置
)
{
	// 変数宣言
	CSelectCharacter * pSelect_chara;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pSelect_chara = new CSelectCharacter;
	// プレイヤー番号設定
	pSelect_chara->m_PlayerID = nPlayerId;
	// 位置設定
	pSelect_chara->m_pos = pos;
	// 初期化処理
	pSelect_chara->Init();
	// シーン管理
	pSelect_chara->ManageSetting(CScene::LAYER_SELECTCHARACTER);
	// 生成したオブジェクトを返す
	return pSelect_chara;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 静的変数の初期化
// (選択画面の初期化時に関数を呼ぶ)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::InitStatic(void)
{
	for (int nCntSelectChara = 0; nCntSelectChara < MAX_PLAYER; nCntSelectChara++)
	{
		m_SaveCharaType[nCntSelectChara] = 0;
	}
}
