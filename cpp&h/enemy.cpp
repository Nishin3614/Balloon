// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 敵処理 [enemy.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "enemy.h"
#include "player.h"
#include "3Dparticle.h"
#include "game.h"
#include "circleshadow.h"
#include "camera.h"
#include "balloon_group.h"
#include "collision.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define ENEMY_KEYMOVE (1)
#define ENEMY_G (0.5f)			// 重力
#define ENEMY_RESISTANCE (0.5f)// 抵抗力
#define ENEMY_GRAVITY (0.1f)
#define ENEMY_AISTANDSTATEPOS	(450.0f)	// 通常状態になる位置
#define ENEMY_AIJUMPSTATEPOS	(20.0f)		// 通常状態になる位置

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CEnemy::m_nAllEnemy[TYPE_MAX] = {};		// 敵の総数

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// オーバーロードコンストラクタ(子供用)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CEnemy::CEnemy(CHARACTER const &character) : CCharacter_Balloon::CCharacter_Balloon(character)
{
	m_Type = TYPE_MOVE;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CEnemy::~CEnemy()
{
	m_nAllEnemy[m_Type]--;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Init(void)
{
	// 総数カウントアップ
	m_nAllEnemy[m_Type]++;
	// キャラクター初期化
	CCharacter_Balloon::Init();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// キャラクター終了処理
	CCharacter_Balloon::Uninit();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Update(void)
{
	// AIアクション処理
	Ai_Action();

	// 移動制限処理
	MoveRestriction();

	// キャラクターの重力加算処理
	CCharacter::AddGravity(ENEMY_GRAVITY);

	// キャラクター更新処理
	CCharacter_Balloon::Update();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// AIアクション処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Ai_Action(void)
{
	// タイプが動かないタイプなら
	if (m_Type == TYPE_STOP) return;
	// 出現している風船がすべて割られていたら
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() <= 0)
		{
			m_AI = AIACTION_BALLOON_NONE;
		}
		// 位置yが500超過なら
		else if (CCharacter::GetPos().y > ENEMY_AISTANDSTATEPOS)
		{
			m_AI = AIACTION_STAND;
		}
		// 着地状態なら
		else if (CCharacter::GetbLanding())
		{
			m_AI = AIACTION_JUMP;
		}
		// 位置yが10未満なら
		else if (CCharacter::GetPos().y < ENEMY_AIJUMPSTATEPOS)
		{
			m_AI = AIACTION_JUMP;
		}
	}
	switch (m_AI)
	{
		// 立っている状態(何もしていない)
	case AIACTION_STAND:
		break;
		// ジャンプ状態
	case AIACTION_JUMP:
		// AI行動_ジャンプ処理
		AiAction_Jump();
		break;
		// 出現している風船がすべて割られている状態
	case AIACTION_BALLOON_NONE:
		break;
	default:
		break;
	}
	// AI移動処理
	//Ai_Move();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// AI行動_ジャンプ状態
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::AiAction_Jump(void)
{
	// クーリングタイムが30超過なら
	if (m_Jump.nCoolTime > 10)
	{
		// 変数宣言
		D3DXVECTOR3 move = CCharacter::GetMove();	// 移動量
		// yの移動量を加算
		move.y += CCharacter::GetStatus().fMaxJump;
		// yの上限設定
		if (move.y > 10.0f)
		{
			move.y = 10.0f;
		}
		if (move.y < -5.0f)
		{
			move.y = -5.0f;
		}
		// 移動量設定
		CCharacter::SetMove(move);
		// 初期化
		m_Jump.nCoolTime = 0;	// クーリングタイム
	}
	// クーリングタイムアップ
	m_Jump.nCoolTime++;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動制限
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::MoveRestriction(void)
{
	D3DXVECTOR3 pos = GetPos();
	float fDifference = sqrtf(pos.x * pos.x + pos.z * pos.z);

	if (fDifference > 1200.0f)
	{// 今回もし当たっていたとき
		D3DXVECTOR3 save = pos - D3DXVECTOR3(0.0f, pos.y, 0.0f);
		D3DXVECTOR3 vec;
		D3DXVec3Normalize(&vec, &save);			//正規化する

		float y = pos.y;

		// 食い込んだ分を求める
		pos = vec * 1200.0f;

		pos.y = y;

		// 食い込んだ分だけ戻す
		SetPos(pos);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	// キャラクター描画処理
	CCharacter_Balloon::Draw();
}

#ifdef _DEBUG
//-------------------------------------------------------------------------------------------------------------
// デバッグ表示
//-------------------------------------------------------------------------------------------------------------
void CEnemy::Debug(void)
{
	CCharacter_Balloon::Debug();
}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CCharacter_Balloon::Scene_MyCollision(nObjType, pScene);
	// シーン情報がNULLなら
	// ->関数を抜ける
	if (pScene == NULL) return;
	// オブジェクトタイプがキャラクターなら
	else if (nObjType == CCollision::OBJTYPE_PLAYER)
	{
		// 死亡処理
		CCharacter_Balloon::BalloonNone();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CCharacter_Balloon::Scene_OpponentCollision(nObjType, pScene);
	// シーン情報がNULLなら
	// ->関数を抜ける
	if (pScene == NULL) return;
	// オブジェクトタイプがキャラクターなら
	else if (nObjType == CCollision::OBJTYPE_PLAYER)
	{
		// 死亡処理
		CCharacter_Balloon::BalloonNone();
	}
}

//-------------------------------------------------------------------------------------------------------------
// 死亡処理
//-------------------------------------------------------------------------------------------------------------
void CEnemy::Die(void)
{
	CDebugproc::Print("----敵情報----\n");
	CCharacter_Balloon::Die();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CEnemy::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだ情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEnemy::UnLoad(void)
{
}