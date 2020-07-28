// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// モデル処理 [player.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "player.h"
#include "input.h"
#include "camera.h"
#include "balloon_group.h"
#include "ui.h"
#include "network.h"
#include "manager.h"
#include "fade.h"
#include "collision.h"
#include "game.h"
#include "score.h"
#include "joypad.h"
#include "character_fish.h"
#include "2Dgauge.h"
#include "rank.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int	CPlayer::m_All = 0;					// 総数

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::CPlayer(CHARACTER const &character) : CCharacter_Balloon::CCharacter_Balloon(character)
{
	m_p2DMPGauge = NULL;			// MPゲージ
	m_pRank = NULL;					// 現在順位
	m_posold = D3DVECTOR3_ZERO;		// 前の位置
	m_nCntState = 0;				// ステートカウント
	m_All++;						// 総数
	m_nCntFishApponent = 0;			// 魚出現カウント
	m_nMP = 0;						// MP
	m_bMPMax = false;				// MPが最大かどうか
	m_bResetMP = false;				// MPをリセット
	m_nRank = -1;					// ランキングの初期化
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Init(void)
{
	// 変数宣言
	CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク
	const int nId = pNetwork->GetId();				// 自分のIDを取得
	// バルーンキャラクター初期化
	CCharacter_Balloon::Init();
	// 変数宣言
	D3DXVECTOR3 pos;	// ゲージの配置用

	// 移動量代入
	m_fMoveNow = CCharacter::GetStatus().fMaxMove;

	// カメラの初期化
	// カメラの注視点設定
	CManager::GetRenderer()->GetCamera()->SetPosR(
		CCharacter::GetPos() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		CCharacter::GetRot() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f)
	);
	// モードがゲームなら
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// キャラクター自体のプレイヤー番号とコントロールしているプレイヤー番号が同じなら
		// ->ゲージ生成
		if (m_nPlayerID == nId)
		{
			// MPゲージの生成
			m_p2DMPGauge = C2DGauge::Create(
				PLAYER_UI_MP_POS,
				D3DXVECTOR2(500.0f, 25.0f),
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
			);
			// MPゲージの変化定数を設定
			m_p2DMPGauge->SetConstance((float)PLAYER_MPMAX);
			// MPゲージの変化定数を設定
			m_p2DMPGauge->BeginGauge((float)m_nMP);
			// MPゲージのメインカラー設定
			m_p2DMPGauge->SetMainCol(
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
		}

		m_pRank = CRank::Create();

		if (m_pRank != NULL)
		{
			m_pRank->SetPos(m_pos);
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	// キャラクターの終了処理
	CCharacter_Balloon::Uninit();
	// MPゲージの開放
	if (m_p2DMPGauge != NULL)
	{
		m_p2DMPGauge = NULL;
	}
	if (m_pRank != NULL)
	{
		m_pRank = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	const int nId = pNetwork->GetId();

	// モーション設定
	CCharacter::SetMotion(MOTIONTYPE_NEUTRAL);
	// 選択画面以外なら
	if (CManager::GetMode() != CManager::MODE_SELECT)
	{
		// キャラクター自体のプレイヤー番号とコントロールしているプレイヤー番号が同じなら
		// ->行動処理
		if (m_nPlayerID == nId)
		{
			// 自キャラの行動処理
			MyAction(m_nPlayerID);
		}
		// それ以外のキャラクターの処理
		else
		{
			// 他キャラの行動処理
			OtherAction();
		}
	}

	// キャラクター更新
	CCharacter_Balloon::Update();

	/* プロトタイプ用 */
	// キャラクターの区域宣言
	if (CManager::GetPlayerID() != m_nPlayerID)
	{
		CCharacter::Limit();
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_pRank != NULL)
		{
			if (m_nRank != pNetwork->GetRank(m_nPlayerID))
			{
				m_nRank = pNetwork->GetRank(m_nPlayerID);
				m_pRank->SetAnimation(1.0f / 4, 1.0f, 0.0f, m_nRank - 1);
			}
		}

		if (pNetwork != NULL)
		{
			if (pNetwork->GetDie(m_nPlayerID))
			{
				OtherDie();
			}
		}

		if (m_pRank != NULL)
		{
			m_pRank->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 120.0f, m_pos.z));
		}
	}
#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_8))
	{
		CCharacter_Balloon::Thunder_BreakBalloon();
	}
#endif // _DEBUG

	// 魚出現処理
	FishApponent();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 自キャラ行動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyAction(const int &nId)
{
	// 自キャラの移動処理
	MyMove();
	// 風船を膨らませる
	if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_BALLOONCREATE))
	{
		// 風船を生成する処理
		CCharacter_Balloon::BalloonCreate();
	}
	// カメラの処理
	Camera();
	// MP上げ処理(マイフレーム)
	MpUp(MPUP_EVERY);
	// MPゲージの変化定数を設定
	m_p2DMPGauge->ChangeGauge((float)m_nMP);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyMove(void)
{
	// 変数宣言
	D3DXVECTOR3 move, rot;			// 移動量、回転
	bool bMove = false;				// 移動状態
	float fRot;						// 回転

	// 情報取得
	rot = CCharacter::GetRotDest();								// 目的回転量
	move = CCharacter::GetMove();								// 移動量
	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// カメラ回転
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CJoypad *pJoypad = CManager::GetJoy();

	// 移動 //
	/* ジョイパッド */
	// パッド用 //
	int nValueH, nValueV;	// ゲームパッドのスティック情報の取得用
	float fMove;			// 移動速度
	float fAngle;			// スティック角度の計算用変数
	fAngle = 0.0f;			// 角度

	if (CManager::GetJoy() != NULL)
	{
		// ゲームパッドのスティック情報を取得
		CManager::GetJoy()->GetStickLeft(0, nValueH, nValueV);

		// プレイヤー移動
		// ゲームパッド移動
		if (nValueH != 0 || nValueV != 0)
		{
			// 角度の計算
			fAngle = atan2f((float)nValueH, (float)nValueV);

			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}
			// 速度の計算
			if (abs(nValueH) > abs(nValueV))
			{
				fMove = (abs(nValueH) * m_fMoveNow) / 1024.0f;
			}
			else
			{
				fMove = (abs(nValueV) * m_fMoveNow) / 1024.0f;
			}
			rot.y = fAngle + fRot;

			// スティックの角度によってプレイヤー移動
			move.x -= sinf(fAngle + fRot) * (fMove);
			move.z -= cosf(fAngle + fRot) * (fMove);
			// 移動状態on
			bMove = true;
		}
	}

	/* キーボード */
	// 左
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		// 移動状態on
		bMove = true;
		// 奥
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = -D3DX_PI * 0.25f + fRot;

			move.x += sinf(D3DX_PI * 0.75f + fRot) * m_fMoveNow;
			move.z += cosf(D3DX_PI * 0.75f + fRot) * m_fMoveNow;
		}
		// 手前
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = -D3DX_PI * 0.75f + fRot;

			move.x += sinf(D3DX_PI * 0.25f + fRot) * m_fMoveNow;
			move.z += cosf(D3DX_PI * 0.25f + fRot) * m_fMoveNow;
		}
		// 左
		else
		{
			rot.y = -D3DX_PI * 0.5f + fRot;
			move.x += sinf(D3DX_PI * 0.5f + fRot) * m_fMoveNow;
			move.z += cosf(D3DX_PI * 0.5f + fRot) * m_fMoveNow;
		}
	}
	// 右
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		// 移動状態on
		bMove = true;

		// 奥
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = D3DX_PI * 0.25f + fRot;

			move.x += sinf(-D3DX_PI * 0.75f + fRot) * m_fMoveNow;
			move.z += cosf(-D3DX_PI * 0.75f + fRot) * m_fMoveNow;
		}
		// 手前
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = D3DX_PI * 0.75f + fRot;

			move.x += sinf(-D3DX_PI * 0.25f + fRot) * m_fMoveNow;
			move.z += cosf(-D3DX_PI * 0.25f + fRot) * m_fMoveNow;
		}
		// 右
		else
		{
			rot.y = D3DX_PI * 0.5f + fRot;

			move.x += sinf(-D3DX_PI * 0.5f + fRot) * m_fMoveNow;
			move.z += cosf(-D3DX_PI * 0.5f + fRot) * m_fMoveNow;
		}
	}
	// 奥に行く
	else if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		// 移動状態on
		bMove = true;
		rot.y = D3DX_PI * 0.0f + fRot;
		move.x += sinf(-D3DX_PI * 1.0f + fRot) * m_fMoveNow;
		move.z += cosf(-D3DX_PI * 1.0f + fRot) * m_fMoveNow;
	}
	// 手前に行く
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		// 移動状態on
		bMove = true;
		rot.y = D3DX_PI * 1.0f + fRot;
		move.x += sinf(D3DX_PI * 0.0f + fRot) * m_fMoveNow;
		move.z += cosf(D3DX_PI * 0.0f + fRot) * m_fMoveNow;
	}
	// 風船がNULLではないなら
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		// 風船があるなら
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
		{
			// 宙に浮く
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// 移動量yが0未満なら
				if (move.y < 0.0f)
				{
					move.y = 0.0f;
				}
				move.y += CCharacter::GetStatus().fMaxJump;
			}
			else
			{
				if (pJoypad != NULL)
				{
					// 宙に浮く
					if (pJoypad->GetTrigger(0, CJoypad::KEY_A) || pJoypad->GetTrigger(0, CJoypad::KEY_X))
					{
						// 移動量yが0未満なら
						if (move.y < 0.0f)
						{
							move.y = 0.0f;
						}
						move.y += CCharacter::GetStatus().fMaxJump;
					}
				}
			}
		}
	}
	// 移動状態なら
	if (bMove == true)
	{
		CCharacter::SetMotion(MOTIONTYPE_MOVE);
	}
	// yの上限設定
	if (move.y > 10.0f)
	{
		move.y = 10.0f;
	}
	if (move.y < -5.0f)
	{
		move.y = -5.0f;
	}
	CCharacter::SetMove(move);
	CCharacter::SetRotDest(rot);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// カメラ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Camera(void)
{
	// カメラ上のプレイヤー位置・回転情報の設定
	CCamera * pCamera = CManager::GetRenderer()->GetCamera();
	pCamera->SetPosDestRPlayer(
		CCharacter::GetPos(),
		CCharacter::GetRot()
	);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// MPアップ状態
//	nMpUp	: MP上げ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MpUp(
	int const &nMpUp	// MP上げ
)
{
	if (m_bResetMP == false)
	{
		// MPを上げる
		m_nMP += nMpUp;
		// 上限を超えたら最大MP分代入
		if (m_nMP > PLAYER_MPMAX)
		{
			m_nMP = PLAYER_MPMAX;
		}
		// MPがマックスだったら
		if (m_nMP == PLAYER_MPMAX)
		{
			// リセット開始
			m_bResetMP = true;
			// 状態変化
			m_bMPMax = true;
		}
	}
	else
	{
		// MPを上げる
		m_nMP -= 100;
		// MPがマックスだったら
		if (m_nMP == 0)
		{
			// MP状態の初期化
			m_bMPMax = false;
			// リセット終了
			m_bResetMP = false;
		}
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 他キャラ行動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::OtherAction(void)
{
	// 他キャラの移動処理
	OtherMove();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 魚出現処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::FishApponent(void)
{
	// プレイヤーの位置が指定した位置以下なら
	if (CCharacter::GetPos().y >= FISH_APPONENTPOS)
	{
		// 出現カウント
		if (m_nCntFishApponent == FISH_APPONENTTIME)
		{
			// 魚生成
			CCharacter_Fish::Create(CCharacter::GetPos());
			// 魚出現カウント初期化処理
			m_nCntFishApponent = 0;
		}
		// 魚出現カウントアップ
		m_nCntFishApponent++;
	}
	// それ以外
	else
	{
		// 魚出現カウント初期化処理
		m_nCntFishApponent = 0;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 他キャラ移動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::OtherMove(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	// 変数宣言
	D3DXVECTOR3 move, rot;			// 移動量、回転
	bool bMove = false;				// 移動状態
	float fRot;						// 回転
	// 情報取得
	rot = CCharacter::GetRotDest();								// 目的回転量
	move = CCharacter::GetMove();								// 移動量
	// サーバー側からカメラの回転情報を取得する
	fRot = pNetwork->GetRot(m_nPlayerID);	// カメラ回転
	// 移動 //
	/* ジョイパッド */
	// パッド用 //
	int nValueH, nValueV;	// ゲームパッドのスティック情報の取得用
	float fMove;			// 移動速度
	float fAngle;			// スティック角度の計算用変数
	fAngle = 0.0f;			// 角度

	if (CManager::GetJoy() != NULL)
	{
		// ゲームパッドのスティック情報を取得
		CManager::GetJoy()->GetStickLeft(0, nValueH, nValueV);

		/* プレイヤー移動 */
		// ゲームパッド移動
		if (nValueH != 0 || nValueV != 0)
		{
			// 角度の計算
			fAngle = atan2f((float)nValueH, (float)nValueV);

			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}
			// 速度の計算
			if (abs(nValueH) > abs(nValueV))
			{
				fMove = (abs(nValueH) * CCharacter::GetStatus().fMaxMove) / 1024.0f;
			}
			else
			{
				fMove = (abs(nValueV) * CCharacter::GetStatus().fMaxMove) / 1024.0f;
			}
			rot.y = fAngle + fRot;

			// スティックの角度によってプレイヤー移動
			move.x -= sinf(fAngle + fRot) * (fMove);
			move.z -= cosf(fAngle + fRot) * (fMove);
			// 移動状態on
			bMove = true;
		}
	}
	/* キーボード */
	// 左
	if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_A))
	{
		// 移動状態on
		bMove = true;
		// 奥
		if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
		{
			rot.y = -D3DX_PI * 0.25f + fRot;

			move.x += sinf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// 手前
		else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
		{
			rot.y = -D3DX_PI * 0.75f + fRot;

			move.x += sinf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// 左
		else
		{
			rot.y = -D3DX_PI * 0.5f + fRot;
			move.x += sinf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
	}
	// 右
	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_D))
	{
		// 移動状態on
		bMove = true;

		// 奥
		if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
		{
			rot.y = D3DX_PI * 0.25f + fRot;

			move.x += sinf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// 手前
		else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
		{
			rot.y = D3DX_PI * 0.75f + fRot;

			move.x += sinf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// 右
		else
		{
			rot.y = D3DX_PI * 0.5f + fRot;

			move.x += sinf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
	}
	// 奥に行く
	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	{
		// 移動状態on
		bMove = true;
		rot.y = D3DX_PI * 0.0f + fRot;
		move.x += sinf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
		move.z += cosf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	}
	// 手前に行く
	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	{
		// 移動状態on
		bMove = true;
		rot.y = D3DX_PI * 1.0f + fRot;
		move.x += sinf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
		move.z += cosf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	}
	// 風船がNULLではないなら
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
		{
			// 宙に浮く
			if (pNetwork->GetTriggerKeyboard(m_nPlayerID, NUM_KEY_SPACE))
			{
				move.y += CCharacter::GetStatus().fMaxJump;
			}
		}
	}
	// 移動状態なら
	if (bMove == true)
	{
		CCharacter::SetMotion(MOTIONTYPE_MOVE);
	}
	//CCharacter::SetMove(move);
	CCharacter::SetRotDest(rot);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	// キャラクター描画
	CCharacter_Balloon::Draw();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 死亡処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Die(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	char aDie[64];
	sprintf(aDie, "DIE %d", pNetwork->GetId());
	pNetwork->SendTCP(aDie, sizeof(aDie));

	if (m_pRank != NULL)
	{
		m_pRank->Release();
		m_pRank = NULL;
	}

	// 死亡処理
	CCharacter_Balloon::Die();
	// コントロールする自キャラの場合
	if (m_nPlayerID == CManager::GetPlayerID())
	{
		OutputDebugString("あうとー！");
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 人形の死亡処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::OtherDie(void)
{
	// 死亡処理
	CCharacter_Balloon::Die();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	// バルーンキャラクターの当たった後の処理
	CCharacter_Balloon::Scene_MyCollision(nObjType, pScene);
	// シーン情報がNULLなら
	// ->関数を抜ける
	if (pScene == NULL) return;
	// オブジェクトタイプがアイテムなら
	else if (nObjType == CCollision::OBJTYPE_ITEM)
	{
		// 変数宣言
		// ネットワーク情報取得
		CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報
		// プレイヤーのスコア加算追加
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_COIN);
		}
	}
	// オブジェクトタイプがプレイヤー風船なら ||
	// オブジェクトタイプが敵風船なら ||
	else if (nObjType == CCollision::OBJTYPE_PLAYER_BALLOON ||
		nObjType == CCollision::OBJTYPE_ENEMY_BALLOON)
	{
		// 変数宣言
		// ネットワーク情報取得
		CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報
		// プレイヤーのスコア加算追加
		if (m_nPlayerID == pNetwork->GetId())
		{
			// スコア加算処理
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON);
			// MP上げ処理(風船)
			MpUp(MPUP_BREAKBALLOON);
		}
	}
	// オブジェクトタイプがプレイヤーなら
	else if (nObjType == CCollision::OBJTYPE_PLAYER)
	{
		// やること
		// スコア加算とMP加算の場所
		// ここではない
		// 自分が死んだ時ではなく、相手が死んだときに加算


		// 変数宣言
		// ネットワーク情報取得
		CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報
		// 死亡処理
		BalloonNone();
		// プレイヤーのスコア加算追加
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_PLAYER);
			// MP上げ処理(プレイヤー)
			MpUp(MPUP_PLAYER_KNOCKDOWN);
		}
	}
	// オブジェクトタイプが敵なら
	else if (nObjType == CCollision::OBJTYPE_ENEMY)
	{
		// 変数宣言
		// ネットワーク情報取得
		CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報
		// 死亡処理
		BalloonNone();
		// プレイヤーのスコア加算追加
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_ENEMY);
			// MP上げ処理(敵)
			MpUp(MPUP_ENEMY_KNOCKDOWN);
		}
	}
	// オブジェクトタイプがアイテムなら
	else if (nObjType == CCollision::OBJTYPE_FISH)
	{
		// 死亡
		Die();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	// バルーンキャラクターの相手に当てられた後の処理
	CCharacter_Balloon::Scene_OpponentCollision(nObjType, pScene);
	// シーン情報がNULLなら
	// ->関数を抜ける
	if (pScene == NULL) return;
	// オブジェクトタイプがアイテムなら
	else if (nObjType == CCollision::OBJTYPE_FISH)
	{
		// 死亡
		Die();
	}
	// オブジェクトタイプが敵なら
	else if (nObjType == CCollision::OBJTYPE_ENEMY)
	{
		// 変数宣言
		// ネットワーク情報取得
		CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報
		// プレイヤーのスコア加算追加
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_COIN);
		}
		// 死亡処理
		BalloonNone();
	}
}

#ifdef _DEBUG
//-------------------------------------------------------------------------------------------------------------
// デバッグ表示
//-------------------------------------------------------------------------------------------------------------
void CPlayer::Debug(void)
{
	if (m_nPlayerID == 0)
	{
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_R))
		{
			CCharacter::SetPos(D3DVECTOR3_ZERO);
		}
	}
	// MP全回復
	if (CManager::GetKeyboard()->GetKeyboardTrigger(TESTPLAY_NUMBER3))
	{
		// MP全回復
		m_nMP = PLAYER_MPMAX;
		// MPゲージのNULLチェック
		if (m_p2DMPGauge != NULL)
		{
			// ゲージを変える
			m_p2DMPGauge->ChangeGauge((float)m_nMP);
		}
	}
	CDebugproc::Print("-----プレイヤー番号[%d]-----\n", m_nPlayerID);
	// キャラクターデバッグ
	CCharacter_Balloon::Debug();


}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// リソース情報読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CPlayer::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだリソース情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::UnLoad(void)
{
}
