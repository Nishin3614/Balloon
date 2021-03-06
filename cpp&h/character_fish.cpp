// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 魚キャラクター処理 [character_fish.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character_fish.h"
#include "player.h"
#include "3Dparticle.h"
#include "game.h"
#include "circleshadow.h"
#include "camera.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_FISH_GRAVITY	(0.05f)							// 魚にかかる重力
#define CHARACTER_FISH_MOVE		(D3DXVECTOR3(0.0f,7.0f,0.0f))	// 魚の移動量
#define CHARACTER_FISH_YPOS		(-150.0f)						// 位置y

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// オーバーロードコンストラクタ(子供用)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter_Fish::CCharacter_Fish() : CCharacter::CCharacter(CCharacter::CHARACTER_FISH)
{
	// 移動量設定
	CCharacter::SetMove(CHARACTER_FISH_MOVE);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter_Fish::~CCharacter_Fish()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Init(void)
{
	// キャラクター初期化
	CCharacter::Init();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Uninit(void)
{
	// キャラクター終了処理
	CCharacter::Uninit();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Update(void)
{
	// AIアクション処理
	Ai_Action();
	// キャラクターの重力加算処理
	CCharacter::AddGravity(CHARACTER_FISH_GRAVITY);
	// キャラクター更新処理
	CCharacter::Update();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// AIアクション処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Ai_Action(void)
{
	// キャラクターが一定の距離未満なら
	if (CCharacter::GetPos().y < CHARACTER_FISH_YPOS)
	{
		// 死亡処理
		Die();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Draw(void)
{
	// キャラクター描画処理
	CCharacter::Draw();
}

#ifdef _DEBUG
//-------------------------------------------------------------------------------------------------------------
// デバッグ表示
//-------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Debug(void)
{
	CCharacter::Debug();
}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CCharacter::Scene_MyCollision(nObjType, pScene);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CCharacter::Scene_OpponentCollision(nObjType, pScene);
}

//-------------------------------------------------------------------------------------------------------------
// 死亡処理
//-------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::Die(void)
{
	CCharacter::Die();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成(シーン管理)処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter_Fish * CCharacter_Fish::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot)
{
	// 変数宣言
	CCharacter_Fish * pCharacter_Fish;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pCharacter_Fish = new CCharacter_Fish();
	// シーン管理設定
	pCharacter_Fish->ManageSetting(CScene::LAYER_CHARACTER);
	// 設定
	pCharacter_Fish->SetPos(D3DXVECTOR3(pos.x,CHARACTER_FISH_YPOS,pos.z));
	pCharacter_Fish->SetRot(rot);
	pCharacter_Fish->SetRotDest(rot);
	// 初期化処理
	pCharacter_Fish->Init();
	// 設定
	// 生成したオブジェクトを返す
	return pCharacter_Fish;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成(個人管理)処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter_Fish * CCharacter_Fish::Create_Self(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot)
{
	// 変数宣言
	CCharacter_Fish * pCharacter_Fish;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pCharacter_Fish = new CCharacter_Fish();
	// 設定
	pCharacter_Fish->SetPos(pos);
	pCharacter_Fish->SetRot(rot);
	pCharacter_Fish->SetRotDest(rot);
	// 初期化処理
	pCharacter_Fish->Init();
	// 設定
	// 生成したオブジェクトを返す
	return pCharacter_Fish;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CCharacter_Fish::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだ情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter_Fish::UnLoad(void)
{
}