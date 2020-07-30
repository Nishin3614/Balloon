// ==========================================================
//
// プレイヤー(スコアアップ)処理 [scoreUP.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "scoreUP.h"
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
bool CScoreUP::m_bScoreUP = false;

// ==========================================================
// コンストラクタ処理
// ==========================================================
CScoreUP::CScoreUP() : CPlayer::CPlayer(CHARACTER_BALLOON4)
{
}

// ==========================================================
// デストラクタ処理
// ==========================================================
CScoreUP::~CScoreUP()
{
}

// ==========================================================
// 初期化処理
// ==========================================================
void CScoreUP::Init(void)
{
	CPlayer::Init();

	// 状態の初期化
	m_bScoreUP = false;
}

// ==========================================================
// 終了処理
// ==========================================================
void CScoreUP::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// 更新処理
// ==========================================================
void CScoreUP::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// 状態変化
		m_bScoreUP = true;
	}
	else
	{
		// 状態変化
		m_bScoreUP = false;
	}
}

// ==========================================================
// 描画処理
// ==========================================================
void CScoreUP::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// 死んだときの処理
// ==========================================================
void CScoreUP::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// デバッグ表示
// ==========================================================
void CScoreUP::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CScoreUP::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CScoreUP::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// 生成処理(シーン管理)
// ==========================================================
CScoreUP * CScoreUP::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CScoreUP * pScoreUP;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pScoreUP = new CScoreUP();
	// シーン管理設定
	pScoreUP->ManageSetting(CScene::LAYER_CHARACTER);
	// 設定
	pScoreUP->SetPlayerID(nPlayerID);
	pScoreUP->SetPos(pos);
	pScoreUP->SetRot(rot);
	pScoreUP->SetRotDest(rot);
	// 初期化処理
	pScoreUP->Init();
	// 生成したオブジェクトを返す
	return pScoreUP;
}

// ==========================================================
// 生成処理(個人管理)
// ==========================================================
CScoreUP * CScoreUP::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CScoreUP * pScoreUP;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pScoreUP = new CScoreUP();
	// 設定
	pScoreUP->SetPlayerID(nPlayerID);
	pScoreUP->SetPos(pos);
	pScoreUP->SetRot(rot);
	pScoreUP->SetRotDest(rot);
	// 初期化処理
	pScoreUP->Init();
	// 生成したオブジェクトを返す
	return pScoreUP;
}

// ==========================================================
// リソース情報読み込み処理
// ==========================================================
HRESULT CScoreUP::Load(void)
{
	return S_OK;
}

// ==========================================================
// 読み込んだリソース情報を破棄処理
// ==========================================================
void CScoreUP::UnLoad(void)
{

}