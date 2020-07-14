// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター選択処理 [selectcharacter.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "selectcharacter.h"
/* 描画 */
#include "p_thunder.h"
#include "p_zombie.h"
#include "scene_two.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_ICON_FIXEDPOS (400.0f)

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
	m_pThunder = NULL;
	m_pZombie = NULL;
	m_CharacterType = 0;
	m_PlayerID = 0;
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
	// プレイヤー(雷)
	m_pThunder = CP_thunder::Create_Self(m_PlayerID, m_pos);
	// プレイヤー(ゾンビ)
	m_pZombie = CP_zombie::Create_Self(m_PlayerID, m_pos);
	// 選択UI生成
	m_pSelectUi = CScene_TWO::Create(
		CScene_TWO::OFFSET_TYPE_CENTER,
		D3DXVECTOR3(CHARACTER_ICON_FIXEDPOS, 600.0f, 0.0f),
		D3DXVECTOR2(150.0f, 150.0f));
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
			D3DXVECTOR3(CHARACTER_ICON_FIXEDPOS * (nCntCharacter + 1), 600.0f, 0.0f),
			D3DXVECTOR2(100.0f, 100.0f));
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
	// プレイヤー(雷)がNULLではないなら
	// ->終了処理
	if (m_pThunder != NULL)
	{
		m_pThunder->Uninit();
		delete m_pThunder;
		m_pThunder = NULL;
	}
	// プレイヤー(ゾンビ)がNULLではないなら
	// ->終了処理
	if (m_pZombie != NULL)
	{
		m_pZombie->Uninit();
		delete m_pZombie;
		m_pZombie = NULL;
	}
	// 選択UIのNULLチェック
	// ->終了処理
	if (m_pSelectUi != NULL)
	{
		// 終了処理
		//m_pSelectUi->Release();
		m_pSelectUi = NULL;
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
#ifdef _DEBUG
	CDebugproc::Print("キャラクター選択:%d\n", m_CharacterType);
#endif // _DEBUG

	// 現在のキャラクター番号の保存
	m_SaveCharaType[m_PlayerID] = m_CharacterType;

	// プレイヤーの更新
	switch (m_CharacterType)
	{
		// プレイヤー(雷)
	case 0:
		// プレイヤー(雷)がNULLではないなら
		// ->更新処理
		if (m_pThunder != NULL)
		{
			m_pThunder->Update();
		}
		break;
		// プレイヤー(ゾンビ)
	case 1:
		// プレイヤー(ゾンビ)がNULLではないなら
		// ->更新処理
		if (m_pZombie != NULL)
		{
			m_pZombie->Update();
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
		// プレイヤー(雷)
	case 0:
		// プレイヤー(雷)がNULLではないなら
		// ->描画処理
		if (m_pThunder != NULL)
		{
			m_pThunder->Draw();
		}
		break;
		// プレイヤー(ゾンビ)
	case 1:
		// プレイヤー(ゾンビ)がNULLではないなら
		// ->描画処理
		if (m_pZombie != NULL)
		{
			m_pZombie->Draw();
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
