// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 風船グループ処理の説明[balloon_group.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "balloon_group.h"
#include "p_thunder.h"
#include "3Dparticle.h"
#include "selectcharacter.h"
#include "spherecollision.h"
#include "circleshadow.h"
#include "network.h"
#include "game.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BALLOON_GROUP_Y				(60.0f)								// 位置y
#define BALLOON_GROUP_RADIUS		(30.0f)								// 半径
#define BALLOON_OFFSET_POS			(D3DXVECTOR3(0.0f,100.0f,0.0f))		// オフセット位置
#define BALLOON_COLLISION_RADIUS	(35.0f)								// あたり判定の半径
#define BALLOON_INVINCIBLE			(DERAY_TIME(3))						// 無敵カウント

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::CBalloon_group() : CScene::CScene()
{
	// 初期化
	m_nPopBalloon_group = 2;
	m_nBringBalloon_group = 0;
	m_pPos = NULL;
	m_offsetPos = BALLOON_OFFSET_POS;
	m_Corepos = D3DVECTOR3_ZERO;
	m_fAngleBalloon_group = 0;
	m_pCollision = NULL;
	m_pMtx = NULL;
	m_nActorId = -1;
	m_nCntInvincible = BALLOON_INVINCIBLE;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::~CBalloon_group()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Init(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Uninit(void)
{
	// 終了処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
	}
	// 当たり判定情報の開放
	if (m_pCollision != NULL)
	{
		m_pCollision->CompulsionScene();
		m_pCollision->Release();
		m_pCollision = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Update(void)
{
	// 最終的な位置情報の更新
	m_Corepos = *m_pPos + m_offsetPos;
	// 風船の更新処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// 無敵カウントが規定数ごとに点滅
		if (m_nCntInvincible >= BALLOON_INVINCIBLE)
		{
			m_apBalloon[nCntBalloon_group]->SetModelAlpha(1.0f);
		}
		else if (m_nCntInvincible % 10 == 0)
		{
			m_apBalloon[nCntBalloon_group]->SetModelAlpha(1.0f);
		}
		else if (m_nCntInvincible % 5 == 0)
		{
			m_apBalloon[nCntBalloon_group]->SetModelAlpha(0.0f);
		}
		// 更新
		m_apBalloon[nCntBalloon_group]->Update();
	}
	/*
	// プレイヤー情報
	for (int nCntPlayer = 0; nCntPlayer < CScene::GetMaxLayer(CScene::LAYER_CHARACTER); nCntPlayer++)
	{
		CPlayer * pPlayer = (CPlayer *)CScene::GetScene(CScene::LAYER_CHARACTER, nCntPlayer);
		if (pPlayer == NULL) continue;
		else if (pPlayer->GetPlayerID == CManager::GetNetwork()->GetId())
		{

		}
	}
	*/
	// 当たり判定がNULLではないなら
	// 更新
	if (m_pCollision != NULL)
	{
		// 位置情報の更新(行列渡し)
		m_pCollision->GetShape()->PassMatrix(*m_pMtx);
		// 更新
		m_pCollision->Update();
		if (m_nCntInvincible <= BALLOON_INVINCIBLE)
		{
			// 無敵カウントアップ
			m_nCntInvincible++;
		}
		return;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Draw(void)
{
	// 風船の更新処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// 描画
		m_apBalloon[nCntBalloon_group]->Draw();
	}
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Debug(void)
{
	//CDebugproc::Print("所持している風船グループの数[%d]\n", m_nBringBalloon_group);
	//CDebugproc::Print("出現している風船グループの数[%d]\n", m_nPopBalloon_group);
	//CDebugproc::Print("風船グループ[%d]pos(%.1f,%.1f,%.1f)\n",m_nActorId,m_pPos->x, m_pPos->y, m_pPos->z);
}
#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Scene_MyCollision(
	int const &nObjType,	// オブジェクトタイプ
	CScene * pScene			// 相手のシーン情報
)
{
	// 相手のオブジェクトタイプがキャラクターなら
	if (nObjType == CCollision::OBJTYPE_PLAYER ||
		nObjType == CCollision::OBJTYPE_ENEMY)
	{
		if (m_nActorId == CManager::GetNetwork()->GetId())
		{
			// 無敵カウントが規定カウントを越していなかったら
			// ->関数を抜ける
			if (m_nCntInvincible < BALLOON_INVINCIBLE) return;
			// 風船割れる処理
			CrackBalloon();
			CManager::GetNetwork()->SendTCP("HIT", sizeof("HIT"));
			// 無敵カウント初期化
			m_nCntInvincible = 0;
		}
		else if (m_nActorId == -1)
		{
			// 無敵カウントが規定カウントを越していなかったら
			// ->関数を抜ける
			if (m_nCntInvincible < BALLOON_INVINCIBLE) return;
			// 風船割れる処理
			CrackBalloon();
			CManager::GetNetwork()->SendTCP("HIT", sizeof("HIT"));
			// 無敵カウント初期化
			m_nCntInvincible = 0;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Scene_OpponentCollision(
	int const &nObjType,	// オブジェクトタイプ
	CScene * pScene			// 相手のシーン情報
)
{
	// 相手のオブジェクトタイプがキャラクターなら
	if (nObjType == CCollision::OBJTYPE_PLAYER ||
		nObjType == CCollision::OBJTYPE_ENEMY)
	{
		if (m_nActorId == CManager::GetNetwork()->GetId())
		{
			// 無敵カウントが規定カウントを越していなかったら
			// ->関数を抜ける
 			if (m_nCntInvincible < BALLOON_INVINCIBLE) return;
			// 風船割れる処理
			CrackBalloon();
			CManager::GetNetwork()->SendTCP("HIT", sizeof("HIT"));
			// 無敵カウント初期化
			m_nCntInvincible = 0;
		}
		else if (m_nActorId == -1)
		{
			// 無敵カウントが規定カウントを越していなかったら
			// ->関数を抜ける
			if (m_nCntInvincible < BALLOON_INVINCIBLE) return;
			// 風船割れる処理
			CrackBalloon();
			CManager::GetNetwork()->SendTCP("HIT", sizeof("HIT"));
			// 無敵カウント初期化
			m_nCntInvincible = 0;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 位置情報設定
// pPos:位置情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetPPos(
	D3DXVECTOR3 * pPos	// 位置情報
)
{
	// 位置情報のポインターを代入する
	m_pPos = pPos;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 外に出して置ける風船グループの最大個数を設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetPopMaxBalloom(
	int const & nPopMaxBaloon,
	int const & nObjType,
	CScene * pParent
)
{
	// 最大出現数を代入
	m_nMaxPopBalloon_group = nPopMaxBaloon;
	// 角度
	m_fAngleBalloon_group = D3DX_PI / m_nMaxPopBalloon_group * 2;
	// 初期設定
	for (int nCntBalloon_group = 0; nCntBalloon_group < m_nMaxPopBalloon_group; nCntBalloon_group++)
	{
		//風船グループ生成
		m_apBalloon.push_back(CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
			m_pPos,
			D3DVECTOR3_ZERO,
			0
		));
		//// 当たり判定設定(球)
		//m_apBalloon[nCntBalloon_group]->SetCollision(
		//	CShape::SHAPETYPE_SPHERE,
		//	nObjType,
		//	false,
		//	true,
		//	pParent,
		//	BALLOON_OFFSET_POS
		//);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船グループを生成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CreateBalloon_group(
	int const & nObjType,
	CScene * pParent
)
{
	// 風船グループ生成処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] != NULL) continue;
		// 変数宣言
		D3DXVECTOR3 offsetpos;	// オフセット位置
		// オフセット位置の設定
		offsetpos = D3DXVECTOR3(
			sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
			BALLOON_GROUP_Y,
			cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS);
		// 風船生成
		m_apBalloon[nCntBalloon_group] = CBalloon::Create_Self(
			offsetpos,
			m_pPos,
			D3DVECTOR3_ZERO,
			0
		);
		// 持っている風船グループの個数を減らす
		m_nBringBalloon_group--;
		// 出現している風船グループの個数を増やす
		m_nPopBalloon_group++;
		// エフェクトを用意するならここ
		// 当たり判定の使用状態をtrueに
		m_pCollision->SetUse(true);
		// バルーン復活のパーティクル生成
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON4SKILL, offsetpos + *m_pPos);
		// 生成処理が終了したら
		// ->関数を抜ける
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// あたり判定を強制的に削除
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CollisionDelete(void)
{
	// 当たり判定情報の開放
	if (m_pCollision != NULL)
	{
		m_pCollision->CompulsionScene();
		m_pCollision->Release();
		m_pCollision = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船情報取得処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon * CBalloon_group::GetBalloon(int const & nBalloon_group)
{
	// 0 < nBalloon_group <= BALLOON_GROUP_MAXなら
	// ->関数を抜ける
	if (nBalloon_group < 0 || nBalloon_group >= (signed)m_apBalloon.size())
	{
#ifdef _DEBUG
		CCalculation::Messanger("CBalloon_group::GetSceneX->上限越え");
#endif // _DEBUG
		return NULL;
	}
	// 風船の情報を返す
	return m_apBalloon[nBalloon_group];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group * CBalloon_group::Create(
	D3DXVECTOR3 *pPos,					// 位置情報
	D3DXMATRIX	*pMtx,					// 行列情報
	int const &nPopMaxBalloon_group,	// 最大風船グループ数
	int const &nObjType,				// オブジェクトタイプ
	CScene * pParent					// 親情報
)
{
	// 変数宣言
	CBalloon_group * pBalloon_group;		// シーン3Dクラス
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pBalloon_group = new CBalloon_group();
	// シーン管理設定
	pBalloon_group->ManageSetting(CScene::LAYER_3DOBJECT);
	// 初期化処理
	pBalloon_group->Init();
	// 位置情報設定
	pBalloon_group->SetPPos(pPos);
	// 外に出して置ける風船グループの最大個数を設定
	pBalloon_group->SetPopMaxBalloom(
		nPopMaxBalloon_group,
		nObjType,
		pParent
	);
	// 出現している風船グループの個数に代入する
	pBalloon_group->m_nPopBalloon_group = nPopMaxBalloon_group;
	// 行列情報設定
	pBalloon_group->m_pMtx = pMtx;
	// あたり判定の設定
	pBalloon_group->SetCollision(nObjType, pParent);
	// 生成したオブジェクトを返す
	return pBalloon_group;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// リソース情報読み込む設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CBalloon_group::Load(void)
{
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだリソース情報を開放する
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::UnLoad(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// あたり判定情報設定処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetCollision(
	int const &nObjType,				// オブジェクトタイプ
	CScene * pParent					// 親情報
)
{
	// あたり判定生成
	m_pCollision = CSphereCollision::Create(
		BALLOON_COLLISION_RADIUS,
		D3DVECTOR3_ZERO,
		(CCollision::OBJTYPE)nObjType,
		this,
		pParent,
		false,
		true,
		&m_Corepos
	);
	// 位置情報の更新(行列渡し)
	m_pCollision->GetShape()->PassMatrix(*m_pMtx);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船が割れる処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CrackBalloon(
	int const &nCrackBalloon	// 割れる風船数
)
{
	// 変数宣言
	int nCntCrack = nCrackBalloon;	// 割れた風船カウント
	// 風船ループ
	for (int nCntBalloon = 0; nCntBalloon < (signed)m_apBalloon.size(); nCntBalloon++)
	{
		// 当たり判定状態がNULLなら
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon] == NULL)
		{
			continue;
		}
		// 風船が割れる音1
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_BALLOONBREAK1);
		// 風船割れた時のパーティクル生成
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOONBREAK, m_apBalloon[nCntBalloon]->GetPos());
		// 風船の終了処理
		m_apBalloon[nCntBalloon]->Uninit();
		// 風船の開放
		delete m_apBalloon[nCntBalloon];
		m_apBalloon[nCntBalloon] = NULL;
		// 出現している風船グループの個数を減らす
		m_nPopBalloon_group--;
		// 割れる風船数カウントを減らす
		nCntCrack--;
		// 全ての風船が割れていたら
		if (nCntBalloon == (signed)m_apBalloon.size() - 1)
		{
			// 当たり判定の使用状態をfalseに
			m_pCollision->SetUse(false);
		}
		// 割れる風船数カウントが0以下なら
		// ->ループを抜ける
		if (nCntCrack <= 0)
		{
			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船グループが割れる処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::BreakBalloon_group(int const &nCntBalloon_group)
{
	// 当たり判定状態がtrueなら
	// ->開放
	if (m_apBalloon[nCntBalloon_group]->GetBalloonCollision())
	{
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
		// 出現している風船グループの個数を減らす
		m_nPopBalloon_group--;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 雷で風船を割らせる処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Thunder_BreakBalloon_group(void)
{
	// 風船を割らせる処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// 終了処理
		m_apBalloon[nCntBalloon_group]->Uninit();
		// 風船の開放
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
		// 出現している風船グループの個数を増やす
		m_nPopBalloon_group--;
		// 一つ風船を割ったら関数を抜ける
		return;
	}
}
