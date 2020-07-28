// ==========================================================
//
// プレイヤー(復活)処理 [revival.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "revival.h"
#include "manager.h"

// ==========================================================
//
// マクロ定義
//
// ==========================================================

// ==========================================================
//
// 静的変数宣言
//
// ==========================================================

// ==========================================================
// コンストラクタ処理
// ==========================================================
CRevival::CRevival() : CPlayer::CPlayer(CHARACTER_BALLOON2)
{
}

// ==========================================================
// デストラクタ処理
// ==========================================================
CRevival::~CRevival()
{
}

// ==========================================================
// 初期化処理
// ==========================================================
void CRevival::Init(void)
{
	CPlayer::Init();

	// 状態の初期化
	m_bRevival = false;
}

// ==========================================================
// 終了処理
// ==========================================================
void CRevival::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// 更新処理
// ==========================================================
void CRevival::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// 状態変化
		m_bRevival = true;

		CCharacter_Balloon::BalloonCreate();
	}
	else
	{
		// 状態変化
		m_bRevival = false;
	}
}

// ==========================================================
// 描画処理
// ==========================================================
void CRevival::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// 死んだときの処理
// ==========================================================
void CRevival::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// デバッグ表示
// ==========================================================
void CRevival::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CRevival::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CRevival::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// 生成処理(シーン管理)
// ==========================================================
CRevival * CRevival::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CRevival * pRevival;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pRevival = new CRevival();
	// シーン管理設定
	pRevival->ManageSetting(CScene::LAYER_CHARACTER);
	// 設定
	pRevival->SetPlayerID(nPlayerID);
	pRevival->SetPos(pos);
	pRevival->SetRot(rot);
	pRevival->SetRotDest(rot);
	// 初期化処理
	pRevival->Init();
	// 生成したオブジェクトを返す
	return pRevival;
}

// ==========================================================
// 生成処理(個人管理)
// ==========================================================
CRevival * CRevival::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CRevival * pRevival;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pRevival = new CRevival();
	// 設定
	pRevival->SetPlayerID(nPlayerID);
	pRevival->SetPos(pos);
	pRevival->SetRot(rot);
	pRevival->SetRotDest(rot);
	// 初期化処理
	pRevival->Init();
	// 生成したオブジェクトを返す
	return pRevival;
}

// ==========================================================
// リソース情報読み込み処理
// ==========================================================
HRESULT CRevival::Load(void)
{
	return S_OK;
}

// ==========================================================
// 読み込んだリソース情報を破棄処理
// ==========================================================
void CRevival::UnLoad(void)
{

}