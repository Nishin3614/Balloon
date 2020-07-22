// ==========================================================
//
// プレイヤー(スピードアップ)処理 [speedUP.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "speedUP.h"
#include "manager.h"

// ==========================================================
//
// マクロ定義
//
// ==========================================================
#define INVISIBLE_FRONTFORCE (10)
#define INVISIBLE_G (0.5f)			// 重力
#define INVISIBLE_RESISTANCE (0.5f)// 抵抗力

// ==========================================================
//
// 静的変数宣言
//
// ==========================================================

// ==========================================================
// コンストラクタ処理
// ==========================================================
CSpeedUP::CSpeedUP() : CPlayer::CPlayer(CHARACTER_BALLOON1)
{
}

// ==========================================================
// デストラクタ処理
// ==========================================================
CSpeedUP::~CSpeedUP()
{
}

// ==========================================================
// 初期化処理
// ==========================================================
void CSpeedUP::Init(void)
{
	CPlayer::Init();

	// 状態の初期化
	m_bSpeedUP = false;
}

// ==========================================================
// 終了処理
// ==========================================================
void CSpeedUP::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// 更新処理
// ==========================================================
void CSpeedUP::Update(void)
{
	CPlayer::Update();
}

// ==========================================================
// 描画処理
// ==========================================================
void CSpeedUP::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// 死んだときの処理
// ==========================================================
void CSpeedUP::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// デバッグ表示
// ==========================================================
void CSpeedUP::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CSpeedUP::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ==========================================================
void CSpeedUP::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// 生成処理(シーン管理)
// ==========================================================
CSpeedUP * CSpeedUP::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CSpeedUP * pSpeedUP;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pSpeedUP = new CSpeedUP();
	// シーン管理設定
	pSpeedUP->ManageSetting(CScene::LAYER_CHARACTER);
	// 設定
	pSpeedUP->SetPlayerID(nPlayerID);
	pSpeedUP->SetPos(pos);
	pSpeedUP->SetRot(rot);
	pSpeedUP->SetRotDest(rot);
	// 初期化処理
	pSpeedUP->Init();
	// 生成したオブジェクトを返す
	return pSpeedUP;
}

// ==========================================================
// 生成処理(個人管理)
// ==========================================================
CSpeedUP * CSpeedUP::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CSpeedUP * pSpeedUP;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pSpeedUP = new CSpeedUP();
	// 設定
	pSpeedUP->SetPlayerID(nPlayerID);
	pSpeedUP->SetPos(pos);
	pSpeedUP->SetRot(rot);
	pSpeedUP->SetRotDest(rot);
	// 初期化処理
	pSpeedUP->Init();
	// 生成したオブジェクトを返す
	return pSpeedUP;
}

// ==========================================================
// リソース情報読み込み処理
// ==========================================================
HRESULT CSpeedUP::Load(void)
{
	return S_OK;
}

// ==========================================================
// 読み込んだリソース情報を破棄処理
// ==========================================================
void CSpeedUP::UnLoad(void)
{

}