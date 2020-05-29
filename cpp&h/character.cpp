// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター処理 [character.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character.h"
#include "floor.h"
#include "input.h"
#include "collision.h"
#include "3Dparticle.h"
#include "camera.h"
#include "game.h"
#include "meshobit.h"
#include "ui.h"
#include "Extrusion.h"

#include "rectcollision.h"
#include "spherecollision.h"
#include "columncollision.h"
#include "circleshadow.h"
#include "stencilshadow.h"
#include "balloon.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_KEYMOVE (1)													// キー移動
#define CHARACTER_G (0.5f)														// 重力
#define CHARACTER_RESISTANCE (0.5f)												// 抵抗力
#define CHARACTER_STATUS_FILE ("data/LOAD/STATUS/status_manager_Character.csv")	// ファイル名
#define CIRCLESHADOW (true)														// 円形のシャドウにするかしないか

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MODEL_ALL	*CCharacter::m_modelAll[CHARACTER_MAX] = {};		// モデル全体の情報
CModel_info	*CCharacter::m_model_info[CHARACTER_MAX] = {};		// モデル情報
vector<int>	CCharacter::m_modelId[CHARACTER_MAX];				// モデル番号
D3DXVECTOR3	CCharacter::m_CharacterSize[CHARACTER_MAX] = {};	// キャラクターのサイズ
CCharacter::STATUS CCharacter::m_sStatus[CHARACTER_MAX] = {};	// キャラクターすべてのスタータス情報
int			CCharacter::m_NumParts[CHARACTER_MAX] = {};			// 動かすモデル数
int			CCharacter::m_NumModel[CHARACTER_MAX] = {};			// 最大モデル数
int			CCharacter::m_nCameraCharacter = 0;					// キャラクターに追尾するID

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// オーバーローバーコンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter::CCharacter() : CScene::CScene()
{
	m_pMeshobit = NULL;								// 軌跡
	m_pModel = NULL;								// モデル
	m_character = CHARACTER_PLAYER;					// キャラクター
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			// 位置
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 前の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 現在回転量
	m_rotLast = m_rot;								// 向きたい方向
	m_rotbetween = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転の差分
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// キャラクターのサイズ
	m_nMotiontypeOld = 0;							// 前回のモーションタイプ
	m_nMotiontype = 0;								// モーションタイプ
	m_keyinfoCnt = 0;								// キー情報のカウント
	m_nFrame = 0;									// フレームカウント
	m_nMotionFrame = 0;								// モーション一つののフレームカウント
	m_nMaxMotion = 0;								// 最大モーション数
	m_nIDWho = 0;									// 敵か味方か
	m_State = STATE_NORMAL;							// 現状のステータス
	m_nCntState = 0;								// カウントステータス
	m_fLength = 0;									// 攻撃の当たり範囲
	m_fAlpha = 1.0f;								// アルファ値
	m_bMotionCamera = false;						// モーションカメラの切り替え
	m_pStencilshadow = NULL;						// ステンシルシャドウ
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter::~CCharacter()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Init()
{
	// モデルのメモリ確保
	m_pModel = new CModel[m_NumParts[m_character]];

	// キャラクターの設定
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// キャラクター情報渡し
		m_pModel[nCntModel].Init();
		// モデルの情報を渡す
		m_pModel[nCntModel].BindModel(
			m_modelAll[m_character]->pModel_offset[nCntModel]
		);
		// モデルの番号設定
		m_pModel[nCntModel].SetModelId(m_modelId[m_character][nCntModel]);
		// シャドウon
		if (CIRCLESHADOW == false)
		{
			m_pModel[nCntModel].SetShadowMap(true);
		}
		// モーション設定
		m_pModel[nCntModel].BeginMotion(
			m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel],
			m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
		// すべての親以外
		if (nCntModel != 0)
		{
			// 親情報設定
			m_pModel[nCntModel].SetParentMtx(
				&m_pModel[m_modelAll[m_character]->pModel_offset[nCntModel].nParent].GetMatrix()
			);
		}
		// すべての親
		else
		{
			// 親情報設定
			m_pModel[nCntModel].SetParentMtx(
				&m_mtxWorld
			);
		}
	}
	// 敵か味方か
	if (m_character == CHARACTER_PLAYER)
	{
		m_nIDWho = 0;
	}
	else
	{
		m_nIDWho = 1;
	}

	// 軌跡の設定
	for (int nCntObit_Basic = 0; nCntObit_Basic < (signed)m_modelAll[m_character]->v_MeshObitLoad.size(); nCntObit_Basic++)
	{
		m_vec_pMeshObit.push_back(std::move(CMeshobit::Create_Self(
			m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).nLine,
			m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).BeginOffset,
			m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).EndOffset,
			(CMeshobit::TEX)m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).nTexType
		)));
	}

	// 攻撃当たり判定設定
	for (int nCntAttackCollision = 0; nCntAttackCollision < (signed)m_modelAll[m_character]->v_AttackCollision.size(); nCntAttackCollision++)
	{
		// 変数宣言
		D3DXVECTOR3 pos;
		// 当たり判定の位置の設定 
		D3DXVec3TransformCoord(
			&pos,
			&m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
			&m_pModel[m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).nParts].GetMatrix()
		);
		// 矩形の当たり判定
		if (m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_RectInfo)
		{
			// 矩形の当たり判定
			m_vec_AttackCollision.push_back(std::move(CRectCollision::Create_Self(
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_RectInfo->size
			)));
		}
		// 球の当たり判定
		else if (m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_SphereInfo)
		{
			// 球の当たり判定
			m_vec_AttackCollision.push_back(std::move(CSphereCollision::Create_Self(
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
				pos,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_SphereInfo->fRadius
			)));
		}
		// 円柱の当たり判定
		else if (m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_ColumnInfo)
		{
			// 円柱の当たり判定
			m_vec_AttackCollision.push_back(std::move(CColumnCollision::Create_Self(
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
				pos,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_ColumnInfo->fRadius,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_ColumnInfo->fVertical
			)));
		}
	}

	// キャラクター当たり判定設定
	if (m_modelAll[m_character]->pCharacterCollision != NULL)
	{
		m_pCharacterCollision = std::move(CRectCollision::Create_Self(
			m_modelAll[m_character]->pCharacterCollision->Offset,
			m_pos + m_modelAll[m_character]->pCharacterCollision->RectInfo->size
		));
	}
	// シャドウon
	if (CIRCLESHADOW == true)
	{
		D3DXVECTOR3 pos = m_pos;
		pos.y = 0;
		// ステンシルシャドウの生成
		m_pStencilshadow = CStencilshadow::Create(m_pos, D3DXVECTOR3(10.0f, 10000.0f, 10.0f));
	}

	// 風船生成
	m_pBalloon = CBalloon::Create(&m_mtxWorld);
	// ステータスの反映 //
	// 初期風船を持っている個数
	m_pBalloon->SetBiginBalloon(m_sStatus[m_character].nMaxBalloon);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Uninit(void)
{
	// ヌルチェック
	if (m_pModel != NULL)
	{
		delete[] m_pModel;
		m_pModel = NULL;
	}
	if (m_pCharacterCollision != NULL)
	{
		m_pCharacterCollision->Uninit();
		m_pCharacterCollision = NULL;
	}
	for (int nCntMotionObit = 0; nCntMotionObit < (signed)m_vec_pMeshObit.size(); nCntMotionObit++)
	{
		// 軌跡の終了処理
		m_vec_pMeshObit.at(nCntMotionObit)->Uninit();
	}
	// ステンシルシャドウの初期化
	if (m_pStencilshadow != NULL)
	{
		m_pStencilshadow = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Update(void)
{
	// カメラ追尾処理
	TrackCamera();
	// 通常時の更新処理
	Update_Normal();
	// 区域制限
	Limit();
	// 当たり判定処理
	Collision();
	// ステンシルシャドウの位置設定
	if (m_pStencilshadow != NULL)
	{
		// 位置取得
		D3DXVECTOR3 pos = m_pos;
		pos.y = -1000.0f;
		// ステンシルシャドウの位置設定
		m_pStencilshadow->SetPos(pos);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// それぞれの当たり判定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Collision(void)
{
	// 判定
	CCharacter * pCharacter;
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(LAYER_CHARACTER); nCntLayer++)
	{
		// キャラクター情報取得
		pCharacter = (CCharacter *)CScene::GetScene(LAYER_CHARACTER, nCntLayer);
		// キャラクター情報が入っていない場合
		// ->ループスキップ
		if (pCharacter == NULL) continue;
		// 現在のキャラクター情報と取得したキャラクター情報が同じ場合
		// ->ループスキップ
		else if (pCharacter == this) continue;
		// キャラクター同士の当たり判定処理
		else if (m_pCharacterCollision->CollisionDetection(pCharacter->GetCollision()))
		{
			// キャラクター同士当たっている
			// ->バウンド処理
			D3DXVECTOR3 rot = D3DVECTOR3_ZERO;
			D3DXVECTOR3 diffpos = D3DVECTOR3_ZERO;
			diffpos = pCharacter->m_pos - m_pos;
			// 相手から見てプレイヤーがいる角度
			rot.y = (atan2f(diffpos.x, diffpos.z));
			m_move.x = sinf(rot.y + D3DX_PI) * 2.5f;
			m_move.z = cosf(rot.y + D3DX_PI) * 2.5f;
		}
		// キャラクターと風船の当たり判定処理
		BalloonCollision(pCharacter->m_pBalloon);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船との当たり判定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::BalloonCollision(
	CBalloon * pBalloon	// 風船の情報
)
{
	// キャラクターと風船の当たり判定処理
	for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX; nCntBalloon++)
	{
		// 相手キャラクターの風船がNULLなら
		// ->関数を抜ける
		if (pBalloon->GetSceneX(nCntBalloon) == NULL) continue;
		// 相手キャラクターの風船のモデルがNULLなら
		// ->関数を抜ける
		else if (pBalloon->GetSceneX(nCntBalloon)->GetCollision() == NULL) continue;
		// 自キャラクターと相手のキャラクターの風船の判定
		else if (m_pCharacterCollision->CollisionDetection(
			pBalloon->GetSceneX(nCntBalloon)->GetCollision()))
		{

		}
	}
	// 直すこと
	// まだ当たった後の判定をとっただけ

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 通常時の更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Update_Normal(void)
{
	// 移動
	Move();
	// 高さ
	GetFloorHeight();
	// モーション
	Motion();
	// エフェクト情報更新
	Motion_Effect();
	// モデル更新
	ModelUpdate();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 次のモーション設定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::NextKeyMotion(void)
{
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// ヌルチェック
		if (&m_pModel[nCntModel] != NULL)
		{
			// モーション設定
			m_pModel[nCntModel].SetMotion(
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel],
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Move(void)
{
	// 現在回転差分
	m_rotbetween = m_rotLast - m_rot;

	// 限度調整
	m_rotbetween.x = CCalculation::Rot_One_Limit(m_rotbetween.x);
	m_rotbetween.y = CCalculation::Rot_One_Limit(m_rotbetween.y);
	m_rotbetween.z = CCalculation::Rot_One_Limit(m_rotbetween.z);

	// 回転移動
	m_rot += m_rotbetween * 0.1f;

	// 限度調整
	m_rot.x = CCalculation::Rot_One_Limit(m_rot.x);
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
	m_rot.z = CCalculation::Rot_One_Limit(m_rot.z);
	
	// 移動
	m_move.y -= 0.1f;
	if (m_nMotiontype != MOTIONTYPE_STANDUP)
	{
		m_pos.x += m_move.x;
		m_pos.z += m_move.z;
		m_pos.y += m_move.y;
	}
	// 当たり判定の更新
	m_pCharacterCollision->GetShape()->PassPos(m_pos);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モーション処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Motion(void)
{
	// フレームカウントアップ
	m_nFrame++;
	m_nMotionFrame++;
	// モーションタイプが変化
	// 初期化
	if (m_nMotiontype != m_nMotiontypeOld)
	{
		m_nFrame = 0;		// フレームキー情報のカウント
		m_nMotionFrame = 0;	// モーション一つのフレームカウント
		m_keyinfoCnt = 0;	// キー情報のカウント
		// 次のモーション設定
		NextKeyMotion();
	}
	// モーションの保存
	m_nMotiontypeOld = m_nMotiontype;
	// フレーム数が同じになったら
	if (m_nFrame >= m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame)
	{
		// 初期化
		m_nFrame = 0;	// フレーム
		// カウントアップ
		m_keyinfoCnt++;
		// モーションカメラの切り替えの初期化
		m_bMotionCamera = false;
		// キー情報が超えたら
		if (m_keyinfoCnt >= m_modelAll[m_character]->pMotion[m_nMotiontype].nNumKey)
		{
			// ループしないとき
			if (m_modelAll[m_character]->pMotion[m_nMotiontype].nLoop == 0)
			{
				m_nMotiontype = 0;	// モーションタイプ
			}
			// 初期化
			m_keyinfoCnt = 0;				// キー情報
			m_nMotionFrame = 0;				// モーション一つのフレームカウント
		}
		// 次のモーション設定
		NextKeyMotion();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モデルの更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::ModelUpdate(void)
{
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// ヌルチェック
		if (&m_pModel[nCntModel] != NULL)
		{
			// 更新
			m_pModel[nCntModel].Update();
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// カメラ追尾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::TrackCamera(void)
{
	if (m_character != CHARACTER_PLAYER)
	{
		return;
	}
	// モードがゲームとチュートリアルの場合
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// カメラの注視点設定
		CManager::GetRenderer()->GetCamera()->SetPosDestRPlayer(
			CCharacter::GetPos(),
			CCharacter::GetRot()
		);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 制限区域
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Limit(void)
{
	// xの制限
	if (m_pos.x < -950)
	{
		m_pos.x = -950;
	}
	if (m_pos.x > 950)
	{
		m_pos.x = 950;
	}
	// zの制限
	if (m_pos.z < -950)
	{
		m_pos.z = -950;
	}
	if (m_pos.z > 950)
	{
		m_pos.z = 950;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モーションエフェクト更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Motion_Effect(void)
{
	// 変数宣言
	D3DXVECTOR3 pos;
	for (int nCntMotionEffect = 0; nCntMotionEffect < (signed)m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.size(); nCntMotionEffect++)
	{
		// 開始時間外ならスキップ
		if (m_nFrame < m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nStart)
		{
			continue;
		}
		// 終了時間外ならスキップ
		else if (m_nFrame > m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nEnd)
		{
			continue;
		}
		// 時間内なら
		// 位置設定
		D3DXVec3TransformCoord(
			&pos,
			&m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).offset,
			CCharacter::GetMatrix(m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nKeyID)
		);
		// パーティクルの生成
		C3DParticle::Create(
			(C3DParticle::PARTICLE_OFFSET_ID)m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nParticleType,
			pos);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モーション軌跡更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Motion_Obit()
{
	for (int nCntMotionObit = 0; nCntMotionObit < (signed)m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.size(); nCntMotionObit++)
	{
		// 開始時間外ならスキップ
		if (m_nMotionFrame < m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nBeginFram)
		{
			continue;
		}
		// 終了時間外ならスキップ
		else if (m_nMotionFrame > m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nEndFram)
		{
			continue;
		}
		// 開始時に位置を初期に
		else if (m_nMotionFrame == m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nBeginFram)
		{
			m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->InitPos(*CCharacter::GetMatrix(m_modelAll[m_character]->v_MeshObitLoad.at(
				m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID).nPart));
		}
		// 軌跡の色の設定
		m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->SetCol(
			m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).BeginCol,
			m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).EndCol
		);
		// 軌跡の描画設定
		m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->DrawSet(*CCharacter::GetMatrix(m_modelAll[m_character]->v_MeshObitLoad.at(
			m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID).nPart));
		// 軌跡の描画
		m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->Draw();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モーションカメラの更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::MotionCamera(void)
{
	// 変数宣言
	// 情報取得
	static CCamera * pCamera = CManager::GetRenderer()->GetCamera();	// カメラ
	// モーションカメラの切り替えがOFFの場合
	if (!m_bMotionCamera)
	{
		// 要素があったら処理を行う
		if (m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera != NULL)
		{
			// カメラモーション設定
			pCamera->SetCamera_Motion(
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->offsetR + m_pos,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->rot + m_rot,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->fLength,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->fHeight,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->fIntertia
			);
			// モーションカメラの切り替え
			m_bMotionCamera = true;
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Draw(void)
{
	// 変数宣言
	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	// スケールを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	// 行列の積(1:ワールド行列 = 2:ワールド行列 * 3:回転行列)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxRot);


	// 位置を反映 //
	// 平行移動行列作成(オフセット)
	D3DXMatrixTranslation(&mtxTrans,	// 総合の入れ物
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// 行列の積(1:ワールド行列 = 2:ワールド行列 * 3:移動行列)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxTrans);					// 3


	// モデル
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// ヌルチェック
		if (&m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel].Draw();
		}
	}
	// モーション軌跡更新
	Motion_Obit();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 死んだときの処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Die(void)
{
	D3DXVECTOR3 ParticlePos;		// パーティクルが出る位置
	// パーティクルの位置(体の位置)
	ParticlePos = D3DXVECTOR3(
		CCharacter::GetMatrix(1)->_41,
		CCharacter::GetMatrix(1)->_42,
		CCharacter::GetMatrix(1)->_43
	);
	// パーティクル生成
	C3DParticle::Create(
		C3DParticle::OFFSET_ID_CROSSLINE,
		ParticlePos
	);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船を生成する処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::BalloonCreate(void)
{
	// 風船を生成する処理
	m_pBalloon->CreateBalloon();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// フィールドの高さを算出
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCharacter::GetFloorHeight(void)
{
	// 変数宣言
	CFloor * pFloor = NULL;	// 床
							// 情報取得
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		pFloor = (CFloor*)CScene::GetScene( CScene::LAYER_3DOBJECT, nCntLayer,CFloor());	// 床
		if (pFloor != NULL)
		{
			// 床の高さを代入
			if (m_pos.y < pFloor->GetHeight(m_pos))
			{
				m_pos.y = pFloor->GetHeight(m_pos);
				m_move.y = 0;
				return true;
			}
		}
	}
	return false;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モーションのフレーム情報取得処理
// 1)キャラクターID、2)モーションID、3)現在のキーカウント
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CCharacter::GetMaxFrame(
	CHARACTER character,	// キャラクター
	int nMotionID,			// モーションID
	int nNowKeyCnt			// 現在のキーカウント
)
{
	// モーション全体のフレーム数
	if (nNowKeyCnt == -1)
	{
		return m_modelAll[character]->pMotion[nMotionID].nAllFrame;
	}
	// 一つのキー間のフレーム数
	return m_modelAll[character]->pMotion[nMotionID].KeyInfo[nNowKeyCnt].nFrame;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// カメラ追尾処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CCharacter::GetCameraCharacter(void)
{
	return m_nCameraCharacter;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 重力処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::FagGravity(void)
{
	// 重力処理
	m_move.y -= 1.0f;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// モーション設定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::SetMotion(int const nMotiontype)
{
	// ループ状態の時
	if (m_modelAll[m_character]->pMotion[m_nMotiontype].nLoop == 1)
	{
		m_nMotiontype = nMotiontype;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 強制モーション設定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::ComplusionSetMotion(int const nMotiontype)
{
	m_nMotiontype = nMotiontype;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 回転取得処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 *CCharacter::GetPartsRot(int const nModelID)
{
	// モデルの行列情報取得
	if (nModelID >= 0 ||
		nModelID < m_NumParts[m_character])
	{
		return &m_pModel[nModelID].GetRot();
	}
	// キャラクターの行列情報取得
	else if (nModelID == -1)
	{
		return &m_rot;
	}
#ifdef _DEBUG
	CCalculation::Messanger("キャラクターのモデルの回転情報がありません");
#endif // _DEBUG
	// 指定されたIDがない場合
	return &m_rot;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 位置取得処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 *CCharacter::GetPartsPos(int const nModelID)
{
	// モデルの行列情報取得
	if (nModelID >= 0 ||
		nModelID < m_NumParts[m_character])
	{
		return &m_pModel[nModelID].GetPos();
	}
	// キャラクターの行列情報取得
	else if (nModelID == -1)
	{
		return &m_rot;
	}
#ifdef _DEBUG
	CCalculation::Messanger("キャラクターのモデルの回転情報がありません");
#endif // _DEBUG
	// 指定されたIDがない場合
	return &m_rot;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 行列取得処理
// -1はキャラクターの行列情報、0～はモデルの行列情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXMATRIX * CCharacter::GetMatrix(int const nModelID)
{
	// モデルの行列情報取得
	if(nModelID >= 0 ||
		nModelID < m_NumParts[m_character])
	{
		return &m_pModel[nModelID].GetMatrix();
	}
	// キャラクターの行列情報取得
	else if (nModelID == -1)
	{
		return &m_mtxWorld;
	}
#ifdef _DEBUG
	CCalculation::Messanger("キャラクターのモデルの行列情報がありません");
#endif // _DEBUG
	// 指定されたIDがない場合
	return &m_mtxWorld;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Load(
	CHARACTER const character,
	int const nMaxMotion,
	const char * file_name
)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	// モデルとモーション情報の生成
	m_modelAll[character] = new MODEL_ALL;
	// キャラクターのテキストデータの取得
	CModel_info::TextLoad(
		m_modelAll[character],					// モデル情報
		m_modelId[character],					// モデルファイル
		nMaxMotion,								// モーション数
		m_NumModel[character],					// 最大モデル数
		m_NumParts[character],					// 動かすモデル数
		file_name								// ファイル名
	);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ステータス情報読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CCharacter::LoadStatus(void)
{
	// 変数宣言
	vector<vector<string>> vsvec_Contens;	// ファイルの中身格納用
	// ファイルの中身を取得する
	vsvec_Contens = CCalculation::FileContens(CHARACTER_STATUS_FILE, ',');
	// 行ごとに回す
	for (int nCntLine = 0; nCntLine < (signed)vsvec_Contens.size(); nCntLine++)
	{
		// キャラクターが上限を超えていたら抜ける
		if (nCntLine >= CHARACTER_MAX)
		{
			break;
		}
		// 項目ごとに回す
		for (int nCntItem = 0; nCntItem < (signed)vsvec_Contens.at(nCntLine).size(); nCntItem++)
		{
			switch (nCntItem)
			{
				// 風船の個数
			case 0:
				m_sStatus[nCntLine].nMaxBalloon = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
				// 慣性力
			case 1:
				m_sStatus[nCntLine].nMaxInertia = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
				// ジャンプ力
			case 2:
				m_sStatus[nCntLine].nMaxJump = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
			default:
				break;
			}
		}
	}
	// vectorの多重配列開放
	vector<vector<string>>().swap(vsvec_Contens);
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだ情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::UnLoad(
	CHARACTER const character,
	int const nMaxMotion)
{
	// 変数宣言
	int	nCntMotion = 0;		// モーションカウント
	int	nCntKeySet = 0;		// フレーム数6

	// モデル・モーションの破棄
	CModel_info::TextUnload(m_modelAll[character], nMaxMotion);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
void CCharacter::Debug(void)
{
}
#endif // _DEBUG

