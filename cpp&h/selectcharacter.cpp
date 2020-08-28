// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター選択処理 [selectcharacter.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "selectcharacter.h"
/* 描画 */
#include "scene_two.h"
#include "ui_group.h"
#include "player.h"
#include "network.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_SELECTCHARA_POS	(D3DXVECTOR3(640.0f,360.0f,0.0f))	// キャラクター選択の位置
#define CHARACTER_SELECTCHARA_SIZE	(D3DXVECTOR2(1280.0f,720.0f))	// キャラクター選択のサイズ

#define CHARACTER_ICON_ORIGINPOS	(D3DXVECTOR3(250.0f,658.0f,0.0f))	// キャラクターアイコンの1番目の位置
#define CHARACTER_ICON_ORIGINPOS_X (250.0f)							// キャラクターアイコンの1番目のX位置
#define CHARACTER_ICON_ORIGINPOS_Y (658.0f)							// キャラクターアイコンの1番目のY位置
#define CHARACTER_ICON_SPACE		(250.0f)								// キャラクターアイコン同士の位置間隔
#define CHARACTER_ICON_SIZE			(85.0f)									// キャラクターアイコンのサイズ

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
	m_pSelectCharatUi = NULL;
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
	// 選択キャラクターUI生成
	m_pSelectCharatUi = CScene_TWO::Create(
		CScene_TWO::OFFSET_TYPE_CENTER,
		CHARACTER_SELECTCHARA_POS,
		CHARACTER_SELECTCHARA_SIZE);
	m_pSelectCharatUi->BindTexture(CTexture_manager::GetTexture(38));
	// 選択画面のUI生成
	CUi::LoadCreate(CUi::UITYPE_SELECTCHARACTER);
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
	// 選択キャラクターUIのNULLチェック
	// ->終了処理
	if (m_pSelectCharatUi != NULL)
	{
		// 終了処理
		//m_pSelectUi->Release();
		m_pSelectCharatUi = NULL;
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
			// 選択音2
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
		}
		// 右が入力されたら
		// ->キャラクター番号が加算
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_RIGHT))
		{
			CNetwork *pNetwork = CManager::GetNetwork();

			if (pNetwork != NULL)
			{
				m_CharacterType++;

				while (!pNetwork->CheckCharacterReady(m_CharacterType))
				{
					m_CharacterType++;
				}

				// 選択キャラクターUIのNULLチェック
				// ->テクスチャータイプ変更
				if (m_pSelectCharatUi != NULL)
				{
					m_pSelectCharatUi->BindTexture(CTexture_manager::GetTexture(38 + m_CharacterType));
				}
				// 選択音1
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND3);
			}
		}
		// 左が入力されたら
		// ->キャラクター番号が減算
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_LEFT))
		{
			CNetwork *pNetwork = CManager::GetNetwork();

			if (pNetwork != NULL)
			{
				m_CharacterType--;

				while (!pNetwork->CheckCharacterReady(m_CharacterType))
				{
					m_CharacterType--;
				}

				// 選択キャラクターUIのNULLチェック
				// ->テクスチャータイプ変更
				if (m_pSelectCharatUi != NULL)
				{
					m_pSelectCharatUi->BindTexture(CTexture_manager::GetTexture(38 + m_CharacterType));
				}
				// 選択音1
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND3);
			}
		}
		// 範囲設定
		if (m_CharacterType >= CPlayer::CHARACTER_PLAYERMAX)
		{
			m_CharacterType = 0;
			// 選択キャラクターUIのNULLチェック
			// ->テクスチャータイプ変更
			if (m_pSelectCharatUi != NULL)
			{
				m_pSelectCharatUi->BindTexture(CTexture_manager::GetTexture(38 + m_CharacterType));
			}
		}
		else if (m_CharacterType < 0)
		{
			m_CharacterType = CPlayer::CHARACTER_PLAYERMAX - 1;
			// 選択キャラクターUIのNULLチェック
			// ->テクスチャータイプ変更
			if (m_pSelectCharatUi != NULL)
			{
				m_pSelectCharatUi->BindTexture(CTexture_manager::GetTexture(38 + m_CharacterType));
			}
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
			// 選択音1
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
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
