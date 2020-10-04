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
#include "scoreUP.h"
#include "invisible.h"
#include "framework.h"
#include "ui_group.h"
#include "meshdome.h"
#include "item.h"
#include "thundercloud.h"
#include "PointCircle.h"
#include "3Dparticle.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PLAYER_GRAVITY (0.1f)
#define PLAYER_UPMOVELIMIT		(10.0f)	// プレイヤーの上昇移動量制限
#define PLAYER_UNDERMOVELIMIT	(5.0f)	// プレイヤーの下降移動量制限

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int	CPlayer::m_All = 0;					// 総数
bool CPlayer::m_bDie[MAX_PLAYER] = {};
CMeshdome *CPlayer::m_pMeshDome = NULL;	// 移動上限警告表示用

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::CPlayer(CHARACTER const &character) : CCharacter_Balloon::CCharacter_Balloon(character)
{
	m_p2DMPGauge = NULL;			// MPゲージ
	m_pRank = NULL;					// 現在順位
	m_nCloudCount = 0;				// 雲が出現するまでのカウンタ
	m_posold = D3DVECTOR3_ZERO;		// 前の位置
	m_nCntState = 0;				// ステートカウント
	m_All++;						// 総数
	m_nMP = 0;						// MP
	m_bMPMax = false;				// MPが最大かどうか
	m_bResetMP = false;				// MPをリセット
	m_nRank = -1;					// ランキングの初期化
	m_pFramework = NULL;			// フレームワーク情報
	for (int nCntFishApponent = 0; nCntFishApponent < MAX_FISHAPPONENT; nCntFishApponent++)
	{
		m_nCntFishApponent[nCntFishApponent] = 0;			// 魚出現カウント
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	m_All--;						// 総数
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
	m_fMoveAdd = CCharacter::GetStatus().fMaxMove * 0.1f;
	m_fMoveNow = CCharacter::GetStatus().fMaxMove;

	// カメラの初期化
	// カメラの注視点設定
	CManager::GetRenderer()->GetCamera()->SetPosR(
		CCharacter::GetPos() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		CCharacter::GetRot() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f)
	);
	// ドームのNULLチェック
	if (m_pMeshDome == NULL)
	{
		// メッシュドームの生成
		m_pMeshDome = CMeshdome::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1300, 2000, 1300),
			10,
			10,
			CMeshdome::TYPE_WARNING,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			false,
			LAYER_BGDOME);

		if (m_pMeshDome != NULL)
		{
			// メッシュドームの使用状態
			m_pMeshDome->SetUse(false);
			m_pMeshDome->SetDrawBack(true);
		}
	}
	// モードがゲームなら
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// キャラクター自体のプレイヤー番号とコントロールしているプレイヤー番号が同じなら
		// ->ゲージ生成
		if (m_nPlayerID == nId)
		{
			// キャラクター2
			if (GetCharacter() == CHARACTER_BALLOON2)
			{
				// MPゲージの生成
				m_p2DMPGauge = C2DGauge::Create(
					PLAYER_UI_MP_POS,
					D3DXVECTOR2(480.0f, 25.0f),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
					GetCharacter()
				);

			}
			// キャラクター4
			else if (GetCharacter() == CHARACTER_BALLOON4)
			{
				// MPゲージの生成
				m_p2DMPGauge = C2DGauge::Create(
					PLAYER_UI_MP_POS,
					D3DXVECTOR2(470.0f, 25.0f),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
					GetCharacter()
				);
			}
			else
			{
				// MPゲージの生成
				m_p2DMPGauge = C2DGauge::Create(
					PLAYER_UI_MP_POS,
					D3DXVECTOR2(500.0f, 25.0f),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
					GetCharacter()
				);
			}
			// MPゲージの変化定数を設定
			m_p2DMPGauge->SetConstance((float)CCharacter::GetStatus().nMaxMp);
			// MPゲージの変化定数を設定
			m_p2DMPGauge->BeginGauge((float)m_nMP);
			// MPゲージのメインカラー設定
			m_p2DMPGauge->SetMainCol(
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
			// フレームワークの生成
			m_pFramework = CFramework::Create();
		}

		m_pRank = CRank::Create();

		if (m_pRank != NULL)
		{
			m_pRank->SetPos(m_pos);
		}

		m_bDie[m_nPlayerID] = false;
		CCharacter_Balloon::GetBalloon()->SetID(m_nPlayerID);

	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// MPゲージの生成
		m_p2DMPGauge = C2DGauge::Create(
			PLAYER_UI_MP_POS,
			D3DXVECTOR2(500.0f, 25.0f),
			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
			GetCharacter()
		);
		// MPゲージの変化定数を設定
		m_p2DMPGauge->SetConstance((float)CCharacter::GetStatus().nMaxMp);
		// MPゲージの変化定数を設定
		m_p2DMPGauge->BeginGauge((float)m_nMP);
		// MPゲージのメインカラー設定
		m_p2DMPGauge->SetMainCol(
			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
			D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
		// フレームワークの生成
		m_pFramework = CFramework::Create();
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
		m_p2DMPGauge->Release();
		m_p2DMPGauge = NULL;
	}
	// ランク情報の開放
	if (m_pRank != NULL)
	{
		m_pRank->Release();
		m_pRank = NULL;
	}
	// フレームワーク情報の開放
	if (m_pFramework != NULL)
	{
		m_pFramework->Release();
		m_pFramework = NULL;
	}
	// メッシュドームの開放
	if (m_pMeshDome != NULL)
	{
		m_pMeshDome->Release();
		m_pMeshDome = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	const int nId = pNetwork->GetId();

	//CDebugproc::Print("[%d]回転量 : %f\n", m_nPlayerID, GetRot().y);
	CDebugproc::Print("[%d]位置 : %f\n", m_nPlayerID, m_pos.y);

	// 選択画面以外なら
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// キャラクター自体のプレイヤー番号とコントロールしているプレイヤー番号が同じなら
		// ->行動処理
		if (m_nPlayerID == nId)
		{
			// 自キャラの行動処理
			MyAction(m_nPlayerID);
			Skill_Particle();
		}
		// それ以外のキャラクターの処理
		else
		{
			// 他キャラの行動処理
			OtherAction();
		}
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// 自キャラの行動処理
		MyAction(m_nPlayerID);
		Skill_Particle();
	}
	// モーション設定処理
	StatusMotion();

	// キャラクター更新
	CCharacter_Balloon::Update();

	/* プロトタイプ用 */
	// キャラクターの区域宣言
	if (CManager::GetPlayerID() != m_nPlayerID)
	{
		CCharacter::Limit();
	}

	if (m_pos.y > 900.0f)
	{
		if (m_nCloudCount > 10)
		{
			for (int nCount = 0; nCount < 5; nCount++)
			{
				D3DXVECTOR3 pos = CCharacter_Balloon::GetBalloon()->GetCorePos();
				CThunderCloud::Create(pos);
				m_nCloudCount = 0;
			}
		}
		else
		{
			m_nCloudCount++;
		}
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

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// キャラクター情報取得
			CCharacter::CHARACTER character = CCharacter::GetCharacter();

			// プレイヤーのスコア加算追加
			if (m_nPlayerID == pNetwork->GetId())
			{
				if (CPointCircle::GetPoint() == true)
				{
					// キャラクターが一致したら
					if (character != CCharacter::CHARACTER_BALLOON2)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
					// キャラクターが一致したら
					if (character == CCharacter::CHARACTER_BALLOON2)
					{
						// 状態
						if (CScoreUP::GetScoreUP() == true)
						{
							CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
						}
						else
						{
							CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
						}
					}
				}
			}
		}

	}

	if (m_pos.y <= -60.0f)
	{
		// 風船割れた時のパーティクル生成
		C3DParticle::Create(C3DParticle::PARTICLE_ID_WATER, m_pos);
	}
#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_8))
	{
		CCharacter_Balloon::Thunder_BreakBalloon();
	}
#endif // _DEBUG
	//// 魚出現処理
	//FishApponent();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 自キャラ行動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyAction(const int &nId)
{
	// 自キャラの移動処理
	MyMove();

	//// 風船を膨らませる
	//if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_BALLOONCREATE))
	//{
	//	// 風船を生成する処理
	//	CCharacter_Balloon::BalloonCreate();
	//}
	// MP上げ処理(マイフレーム)
	MpUp(CCharacter::GetStatus().nMaxMpUp_Every);
	// カメラの更新
	Camera();
	// MPゲージの変化定数を設定
	if (m_p2DMPGauge != NULL)
	{
		m_p2DMPGauge->ChangeGauge((float)m_nMP);
	}
	D3DXVECTOR3 pos = GetPos();
	float fDifference = sqrtf(pos.x * pos.x + pos.z * pos.z);

	if (fDifference > 1000.0f)
	{
		if (m_pMeshDome != NULL)
		{
			if (!m_pMeshDome->GetUse())
			{
				m_pMeshDome->SetUse(true);
			}
		}
	}
	else
	{
		if (m_pMeshDome != NULL)
		{
			if (m_pMeshDome->GetUse())
			{
				m_pMeshDome->SetUse(false);
			}
		}
	}

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
// スキルによるパーティクル処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Skill_Particle(void)
{
	// MPがマックス状態ではないとき
	// ->関数を抜ける
	if (!m_bMPMax) return;
	// キャラクターによるパーティクル処理
	switch (CCharacter::GetCharacter())
	{
		// キャラクターバルーン1
	case CCharacter::CHARACTER_BALLOON1:
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON1SKILL, CCharacter::GetPos());
		break;
		// キャラクターバルーン2
	case CCharacter::CHARACTER_BALLOON2:
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON2SKILL, CCharacter::GetPos());
		break;
	default:
		break;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyMove(void)
{
	// 変数宣言
	D3DXVECTOR3 move, rot;			// 移動量、回転
	D3DXVECTOR3 vec;				// ベクトル
	float fRot;						// 回転

	// 情報取得
	rot = CCharacter::GetRotDest();								// 目的回転量
	move = CCharacter::GetMove();								// 移動量
	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// カメラ回転
	vec = CCharacter::GetDirectionVec();						// ベクトル
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CJoypad *pJoypad = CManager::GetJoy();

	// 移動 //
	/* キーボード */
	// 左
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		// 移動状態on
		CCharacter::SetbMove(true);
		// 奥
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = -D3DX_PI * 0.25f + fRot;
			vec = D3DXVECTOR3(sinf(D3DX_PI * 0.75f + fRot), 0.0f, cosf(D3DX_PI * 0.75f + fRot));
			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// 着地状態なら
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// 手前
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = -D3DX_PI * 0.75f + fRot;
			vec = D3DXVECTOR3(sinf(D3DX_PI * 0.25f + fRot), 0.0f, cosf(D3DX_PI * 0.25f + fRot));
			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// 着地状態なら
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// 左
		else
		{
			rot.y = -D3DX_PI * 0.5f + fRot;
			vec = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + fRot), 0.0f, cosf(D3DX_PI * 0.5f + fRot));
			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// 着地状態なら
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
	}
	// 右
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		// 移動状態on
		CCharacter::SetbMove(true);

		// 奥
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = D3DX_PI * 0.25f + fRot;
			vec = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f + fRot), 0.0f, cosf(-D3DX_PI * 0.75f + fRot));

			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// 着地状態なら
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// 手前
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = D3DX_PI * 0.75f + fRot;
			vec = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f + fRot), 0.0f, cosf(-D3DX_PI * 0.25f + fRot));

			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// 着地状態なら
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// 右
		else
		{
			rot.y = D3DX_PI * 0.5f + fRot;
			vec = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f + fRot), 0.0f, cosf(-D3DX_PI * 0.5f + fRot));

			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// 着地状態なら
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
	}
	// 奥に行く
	else if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		// 移動状態on
		CCharacter::SetbMove(true);
		rot.y = D3DX_PI * 0.0f + fRot;
		vec = D3DXVECTOR3(sinf(-D3DX_PI * 1.0f + fRot), 0.0f, cosf(-D3DX_PI * 1.0f + fRot));
		// 着地状態ではないなら
		if (!CCharacter::GetbLanding())
		{
			move.x += vec.x * m_fMoveAdd;
			move.z += vec.z * m_fMoveAdd;
		}
		// 着地状態なら
		else
		{
			move.x += vec.x * m_fMoveNow;
			move.z += vec.z * m_fMoveNow;
		}
	}
	// 手前に行く
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		// 移動状態on
		CCharacter::SetbMove(true);
		rot.y = D3DX_PI * 1.0f + fRot;
		vec = D3DXVECTOR3(sinf(D3DX_PI * 0.0f + fRot), 0.0f, cosf(D3DX_PI * 0.0f + fRot));
		// 着地状態ではないなら
		if (!CCharacter::GetbLanding())
		{
			move.x += vec.x * m_fMoveAdd;
			move.z += vec.z * m_fMoveAdd;
		}
		// 着地状態なら
		else
		{
			move.x += vec.x * m_fMoveNow;
			move.z += vec.z * m_fMoveNow;
		}
	}
	// それ以外
	else
	{
		// 移動状態off
		CCharacter::SetbMove(false);
	}

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
			// 着地状態ではないなら
			if (!CCharacter::GetbLanding())
			{
				// 速度の計算
				if (abs(nValueH) > abs(nValueV))
				{
					fMove = (abs(nValueH) * m_fMoveAdd) / 1024.0f;
				}
				else
				{
					fMove = (abs(nValueV) * m_fMoveAdd) / 1024.0f;
				}
			}
			// 着地状態なら
			else
			{
				// 速度の計算
				if (abs(nValueH) > abs(nValueV))
				{
					fMove = (abs(nValueH) * m_fMoveNow) / 1024.0f;
				}
				else
				{
					fMove = (abs(nValueV) * m_fMoveNow) / 1024.0f;
				}
			}
			rot.y = fAngle + fRot;
			vec = D3DXVECTOR3(sinf(fAngle + fRot), 0.0f, cosf(fAngle + fRot));
			// スティックの角度によってプレイヤー移動
			move.x -= sinf(fAngle + fRot) * (fMove);
			move.z -= cosf(fAngle + fRot) * (fMove);
			// 移動状態on
			CCharacter::SetbMove(true);
		}
	}
	if (vec.x < 0)
	{
		vec.x *= -1;
	}
	if (vec.z < 0)
	{
		vec.z *= -1;
	}
	CCharacter::SetDirectionVec(vec);
	// 風船がNULLではないなら
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		// 風船があるなら
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
		{
			// 宙に浮く
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				move.y += CCharacter::GetStatus().fMaxJump;
			}
			else
			{
				if (pJoypad != NULL)
				{
					// 宙に浮く
					if (pJoypad->GetTrigger(0, CJoypad::KEY_RIGHT_1))
					{
						move.y += CCharacter::GetStatus().fMaxJump;
					}
				}
			}
		}
	}
	// yの上限設定
	if (move.y > PLAYER_UPMOVELIMIT)
	{
		move.y = PLAYER_UPMOVELIMIT;
	}
	if (move.y < -PLAYER_UNDERMOVELIMIT)
	{
		move.y = -PLAYER_UNDERMOVELIMIT;
	}
	CCharacter::SetMove(move);

	// キャラクターの重力加算処理
	CCharacter::AddGravity(PLAYER_GRAVITY);
	CCharacter::SetRotDest(rot);

	//if (pKeyboard->GetKeyboardTrigger(DIK_C))
	//{
	//	CGame::GetPlayer(1)->SetRotDest(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	//}
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
	// キャラクター情報取得
	CCharacter::CHARACTER character = CCharacter::GetCharacter();

	if (m_bResetMP == false)
	{
		// MPを上げる
		m_nMP += nMpUp;
		// 上限を超えたら最大MP分代入
		if (m_nMP > CCharacter::GetStatus().nMaxMp)
		{
			m_nMP = CCharacter::GetStatus().nMaxMp;
		}
		// MPがマックスだったら
		if (m_nMP == CCharacter::GetStatus().nMaxMp)
		{
			// リセット開始
			m_bResetMP = true;
			// サーバーに報告
			CNetwork *pNetwork = CManager::GetNetwork();
			pNetwork->SendTCP("START_SP", sizeof("START_SP"));

			// 状態変化
			m_bMPMax = true;
			// フレームワーク情報のNULLチェック
			if (m_pFramework != NULL)
			{
				// フレームワーク情報の使用状態設定
				m_pFramework->SetUse(true);
			}
			// キャラクターによるパーティクル処理
			switch (CCharacter::GetCharacter())
			{
				// キャラクターバルーン3
			case CCharacter::CHARACTER_BALLOON3:
				C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON3SKILL, CCharacter::GetPos());
				break;
			}
		}
	}
	else
	{
		// MPを下げる
		m_nMP -= CCharacter::GetStatus().nMaxMpDown;

		// MPがマックスだったら
		if (m_nMP == 0)
		{
			// MP状態の初期化
			m_bMPMax = false;

			// サーバーに報告
			CNetwork *pNetwork = CManager::GetNetwork();
			pNetwork->SendTCP("STOP_SP", sizeof("STOP_SP"));

			// リセット終了
			m_bResetMP = false;
			// フレームワーク情報のNULLチェック
			if (m_pFramework != NULL)
			{
				// フレームワーク情報の使用状態設定
				m_pFramework->SetUse(false);
			}
		}
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ゲージ初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::GaugeStatusInit(void)
{
	m_nMP = 0;						// MP
	// ぬるちぇ
	if (m_p2DMPGauge != NULL)
	{
		// MPゲージの変化定数を設定
		m_p2DMPGauge->SetConstance((float)CCharacter::GetStatus().nMaxMp);
		// MPゲージの変化定数を設定
		m_p2DMPGauge->BeginGauge((float)m_nMP);
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
// 魚が出現
//	nFishApponent	: 魚の出現番号
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::FishApponent(
	int const &nFishApponent	// 魚の出現番号
)
{
	// モードがチュートリアルなら
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// 出現カウント
		if (m_nCntFishApponent[nFishApponent] == FISH_APPONENTTIME)
		{
			// 魚生成
			CCharacter_Fish::Create(CCharacter::GetPos());
			// 魚出現カウント初期化処理
			m_nCntFishApponent[nFishApponent] = 0;
		}
		// 魚出現カウントアップ
		m_nCntFishApponent[nFishApponent]++;
	}
	// それ以外なら
	else
	{
		// 変数宣言
		CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報取得
		const int nId = pNetwork->GetId();				// 自分のクライアント番号
		// 自キャラ以外なら
		// 関数を抜ける
		if (m_nPlayerID != nId)
		{
			return;
		}
		// 出現カウント
		if (m_nCntFishApponent[nFishApponent] == FISH_APPONENTTIME)
		{
			// 魚生成
			CCharacter_Fish::Create(CCharacter::GetPos());
			// 魚出現カウント初期化処理
			m_nCntFishApponent[nFishApponent] = 0;
		}
		// 魚出現カウントアップ
		m_nCntFishApponent[nFishApponent]++;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 状態によってのモーション設定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::StatusMotion(void)
{
	// 勝利モーション

	// ジャンプ中
	if (!CCharacter::GetbLanding())
	{
		SetMotion(MOTIONTYPE_JAMP);
	}
	// 移動中
	else if (CCharacter::GetbMove())
	{
		// モーション設定(移動)
		SetMotion(MOTIONTYPE_MOVE);
	}
	// 待機
	else
	{
		SetMotion(MOTIONTYPE_NEUTRAL);
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
	float fRot = 0.0f;						// 回転
	// 情報取得
	rot = CCharacter::GetRotDest();								// 目的回転量
	move = CCharacter::GetMove();								// 移動量
	// 移動 //
	/* ジョイパッド */
	// パッド用 //

	/* キーボード */
	//// 左
	//if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_A))
	//{
	//	// 移動状態on
	//	CCharacter::SetbMove(true);
	//	// 奥
	//	if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	//	{
	//		rot.y = -D3DX_PI * 0.25f + fRot;

	//		move.x += sinf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// 手前
	//	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	//	{
	//		rot.y = -D3DX_PI * 0.75f + fRot;

	//		move.x += sinf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// 左
	//	else
	//	{
	//		rot.y = -D3DX_PI * 0.5f + fRot;
	//		move.x += sinf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//}
	//// 右
	//else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_D))
	//{
	//	// 移動状態on
	//	CCharacter::SetbMove(true);

	//	// 奥
	//	if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	//	{
	//		rot.y = D3DX_PI * 0.25f + fRot;

	//		move.x += sinf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// 手前
	//	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	//	{
	//		rot.y = D3DX_PI * 0.75f + fRot;

	//		move.x += sinf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// 右
	//	else
	//	{
	//		rot.y = D3DX_PI * 0.5f + fRot;

	//		move.x += sinf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//}
	//// 奥に行く
	//else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	//{
	//	// 移動状態on
	//	CCharacter::SetbMove(true);
	//	rot.y = D3DX_PI * 0.0f + fRot;
	//	move.x += sinf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	move.z += cosf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//}
	//// 手前に行く
	//else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	//{
	//	// 移動状態on
	//	CCharacter::SetbMove(true);
	//	rot.y = D3DX_PI * 1.0f + fRot;
	//	move.x += sinf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	move.z += cosf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//}
	//// それ以外
	//else
	//{
	//	// 移動状態off
	//	CCharacter::SetbMove(false);
	//}
	//// 風船がNULLではないなら
	//if (CCharacter_Balloon::GetBalloon() != NULL)
	//{
	//	if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
	//	{
	//		// 宙に浮く
	//		if (pNetwork->GetTriggerKeyboard(m_nPlayerID, NUM_KEY_SPACE))
	//		{
	//			move.y += CCharacter::GetStatus().fMaxJump;
	//		}
	//	}
	//}

	// サーバー側からカメラの回転情報を取得する
	rot.y = pNetwork->GetRot(m_nPlayerID);	// カメラ回転

	//	// 回転をセット
	//CCharacter::SetRotDest(rot);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	// 変数宣言
	CNetwork *pNetwork = CManager::GetNetwork();			// ネットワーク情報
	// プレイヤー番号がクライアント側で管理しているプレイヤー番号なら
	if (m_nPlayerID == pNetwork->GetId())
	{
		// キャラクター描画
		CCharacter_Balloon::Draw();
		// 関数を抜ける
		return;
	}
	// それ以外なら
	// 変数宣言
	CInvisible * pInvisible = NULL;								// 透明化キャラクター情報
	static char const * cClassName = typeid(CInvisible).name();	// クラス名
	bool		bInvisible = false;								// 透明かどうか
	// クラス名が同じなら(CInvisible)
	if (typeid(*this).name() == cClassName)
	{
		// 指定のクラスにダウンキャストする
		pInvisible = (CInvisible *)this;
		// 透明かどうかがfalseなら
		if (!pInvisible->GetInvisible())
		{
			// キャラクターバルーン描画処理
			CCharacter_Balloon::Draw();
		}
		return;
	}
	// 他のクラス名なら
	else
	{
		// キャラクターバルーン描画処理
		CCharacter_Balloon::Draw();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 死亡処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Die(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_nPlayerID == CManager::GetNetwork()->GetId())
		{
			CNetwork *pNetwork = CManager::GetNetwork();
			pNetwork->SendTCP("DIE", sizeof("DIE"));
			OutputDebugString("死亡宣告");
		}

		// MPゲージの開放
		if (m_p2DMPGauge != NULL)
		{
			m_p2DMPGauge->Release();
			m_p2DMPGauge = NULL;
		}
		// ランク情報の開放
		if (m_pRank != NULL)
		{
			m_pRank->Release();
			m_pRank = NULL;
		}
		// フレームワーク情報の開放
		if (m_pFramework != NULL)
		{
			m_pFramework->SetUse(false);
			m_pFramework->Release();
			m_pFramework = NULL;
		}
		// メッシュドームの開放
		if (m_pMeshDome != NULL)
		{
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}

		// 死亡処理
		CCharacter_Balloon::Die();
		// コントロールする自キャラの場合
		if (m_nPlayerID == CManager::GetNetwork()->GetId())
		{
			m_bDie[m_nPlayerID] = true;			// 死亡フラグを立てる
			CUi_group::Create(CUi::UITYPE_DIE);
		}
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// 死亡処理
		CCharacter_Balloon::Die();
		// MPゲージの開放
		if (m_p2DMPGauge != NULL)
		{
			m_p2DMPGauge->Release();
			m_p2DMPGauge = NULL;
		}
		// ランク情報の開放
		if (m_pRank != NULL)
		{
			m_pRank->Release();
			m_pRank = NULL;
		}
		// フレームワーク情報の開放
		if (m_pFramework != NULL)
		{
			m_pFramework->SetUse(false);
			m_pFramework->Release();
			m_pFramework = NULL;
		}
		// メッシュドームの開放
		if (m_pMeshDome != NULL)
		{
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}
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

	printf("えぐいて");

	// キャラクター情報取得
	CCharacter::CHARACTER character = CCharacter::GetCharacter();
	// 変数宣言
	// ネットワーク情報取得
	CNetwork *pNetwork = CManager::GetNetwork();	// ネットワーク情報
	// バルーンキャラクターの当たった後の処理
	CCharacter_Balloon::Scene_MyCollision(nObjType, pScene);
	// オブジェクトタイプがアイテムなら
	if (nObjType == CCollision::OBJTYPE_ITEM)
	{
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// プレイヤーのスコア加算追加
			if (m_nPlayerID == pNetwork->GetId())
			{
				// キャラクターが一致したら
				if (character != CCharacter::CHARACTER_BALLOON2)
				{
					CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
				}
				// キャラクターが一致したら
				if (character == CCharacter::CHARACTER_BALLOON2)
				{
					// 状態
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
				}
				// MP上げ処理(風船)
				MpUp(CItem::GetStatus().nMpUp);
			}
		}
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			// MP上げ処理(風船)
			MpUp(CItem::GetStatus().nMpUp);
		}
	}
	// オブジェクトタイプがプレイヤー風船なら ||
	// オブジェクトタイプが敵風船なら ||
	else if (nObjType == CCollision::OBJTYPE_PLAYER_BALLOON ||
		nObjType == CCollision::OBJTYPE_ENEMY_BALLOON)
	{
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// プレイヤーのスコア加算追加
			if (m_nPlayerID == pNetwork->GetId())
			{
				// キャラクターが一致したら
				if (character != CCharacter::CHARACTER_BALLOON2)
				{
					// スコア加算処理
					CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON);
				}
				// キャラクターが一致したら
				if (character == CCharacter::CHARACTER_BALLOON2)
				{
					// 状態
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON);
					}
				}
				// MP上げ処理(風船)
				MpUp(MPUP_BREAKBALLOON);
			}
		}
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
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


		// プレイヤーのスコア加算追加
		if (m_nPlayerID == pNetwork->GetId())
		{
			// 死亡処理
			BalloonNone();



			// この処理をどこで行うか不明
			//CManager::GetGame()->GetScore()->AddScore(SCORETYPE_PLAYER);
			// MP上げ処理(プレイヤー)
			//MpUp(MPUP_PLAYER_KNOCKDOWN);
		}
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
			// 死亡処理
			BalloonNone();


			// この処理をどこで行うか不明
			//CManager::GetGame()->GetScore()->AddScore(SCORETYPE_ENEMY);
			// MP上げ処理(敵)
			//MpUp(MPUP_ENEMY_KNOCKDOWN);
		}
	}
	// オブジェクトタイプが魚なら
	else if (nObjType == CCollision::OBJTYPE_FISH)
	{
		Die();
	}
	// オブジェクトタイプが出現魚1なら
	else if (nObjType == CCollision::OBJTYPE_APPEFISH1)
	{
		FishApponent(0);
	}
	// オブジェクトタイプが出現魚2なら
	else if (nObjType == CCollision::OBJTYPE_APPEFISH2)
	{
		FishApponent(1);
	}
	// オブジェクトタイプが出現魚3なら
	else if (nObjType == CCollision::OBJTYPE_APPEFISH3)
	{
		FishApponent(2);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	// キャラクター情報取得
	CCharacter::CHARACTER character = CCharacter::GetCharacter();

	// バルーンキャラクターの相手に当てられた後の処理
	CCharacter_Balloon::Scene_OpponentCollision(nObjType, pScene);

	printf("えぐいて");

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
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				// キャラクターが一致したら
				if (character != CCharacter::CHARACTER_BALLOON2)
				{
					CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
				}
				// キャラクターが一致したら
				if (character == CCharacter::CHARACTER_BALLOON2)
				{
					// 状態
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
				}
			}
		}
		// 死亡処理
		BalloonNone();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 自分から当たらなかった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_NoMyCollision(int const & nObjType, CScene * pScene)
{
	// オブジェクトタイプが出現魚1なら
	if (nObjType == CCollision::OBJTYPE_APPEFISH1)
	{
		m_nCntFishApponent[0] = 0;
	}
	// オブジェクトタイプが出現魚2なら
	else if (nObjType == CCollision::OBJTYPE_APPEFISH2)
	{
		m_nCntFishApponent[1] = 0;
	}
	// オブジェクトタイプが出現魚3なら
	else if (nObjType == CCollision::OBJTYPE_APPEFISH3)
	{
		m_nCntFishApponent[2] = 0;
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられなかった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_NoOpponentCollision(int const & nObjType, CScene * pScene)
{

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
		m_nMP = CCharacter::GetStatus().nMaxMp;
		// MPゲージのNULLチェック
		if (m_p2DMPGauge != NULL)
		{
			// ゲージを変える
			m_p2DMPGauge->ChangeGauge((float)m_nMP);
		}
	}
	//CDebugproc::Print("-----プレイヤー番号[%d]-----\n", m_nPlayerID);
	// キャラクターデバッグ
	CCharacter_Balloon::Debug();
	// 現在のスピードを表示
	CDebugproc::Print("現在のスピード(%.3f)\n", m_fMoveNow);

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
