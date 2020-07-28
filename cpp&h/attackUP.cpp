// ==========================================================
//
// プレイヤー(アタックアップ)処理 [attackUP.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "attackUP.h"
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
CAttackUP::CAttackUP() : CPlayer::CPlayer(CHARACTER_BALLOON4)
{
}

// ==========================================================
// デストラクタ処理
// ==========================================================
CAttackUP::~CAttackUP()
{
}

// ==========================================================
// 初期化処理
// ==========================================================
void CAttackUP::Init(void)
{
	CPlayer::Init();

	// 状態の初期化
	m_bAttackUP = false;
}

// ==========================================================
// 終了処理
// ==========================================================
void CAttackUP::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// 更新処理
// ==========================================================
void CAttackUP::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// 状態変化
		m_bAttackUP = true;
	}
	else
	{
		// 状態変化
		m_bAttackUP = false;
	}
}

// ==========================================================
// 描画処理
// ==========================================================
void CAttackUP::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// 死んだときの処理
// ==========================================================
void CAttackUP::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// デバッグ表示
// ==========================================================
void CAttackUP::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CAttackUP::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CAttackUP::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// 生成処理(シーン管理)
// ==========================================================
CAttackUP * CAttackUP::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CAttackUP * pAttackUP;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pAttackUP = new CAttackUP();
	// シーン管理設定
	pAttackUP->ManageSetting(CScene::LAYER_CHARACTER);
	// 設定
	pAttackUP->SetPlayerID(nPlayerID);
	pAttackUP->SetPos(pos);
	pAttackUP->SetRot(rot);
	pAttackUP->SetRotDest(rot);
	// 初期化処理
	pAttackUP->Init();
	// 生成したオブジェクトを返す
	return pAttackUP;
}

// ==========================================================
// 生成処理(個人管理)
// ==========================================================
CAttackUP * CAttackUP::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CAttackUP * pAttackUP;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pAttackUP = new CAttackUP();
	// 設定
	pAttackUP->SetPlayerID(nPlayerID);
	pAttackUP->SetPos(pos);
	pAttackUP->SetRot(rot);
	pAttackUP->SetRotDest(rot);
	// 初期化処理
	pAttackUP->Init();
	// 生成したオブジェクトを返す
	return pAttackUP;
}

// ==========================================================
// リソース情報読み込み処理
// ==========================================================
HRESULT CAttackUP::Load(void)
{
	return S_OK;
}

// ==========================================================
// 読み込んだリソース情報を破棄処理
// ==========================================================
void CAttackUP::UnLoad(void)
{

}