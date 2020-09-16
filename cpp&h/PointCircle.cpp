// ==========================================================
//
// ポイントサークル[PointCircle.cpp]
// Author : masayasu wakita
//
// ==========================================================
#include "PointCircle.h"
#include "meshdome.h"
#include "character.h"
#include "player.h"
#include "game.h"
#include "3Dparticle.h"
#include "item.h"
#include "score.h"

// ==========================================================
//
// マクロ定義
//
// ==========================================================
#define COUNT_DRAW (600)
#define RELEASE_DRAW (1200)

// ==========================================================
//
// 静的変数初期化
//
// ==========================================================
int CPointCircle::m_nAllPointCircle = 0;
bool CPointCircle::m_bPoint = false;

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CPointCircle::CPointCircle() : CScene_THREE()
{
	m_nAllPointCircle++;
}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CPointCircle::~CPointCircle()
{
	m_nAllPointCircle--;
}

// ==========================================================
// 初期化
// ==========================================================
void CPointCircle::Init(void)
{
	// オフセットタイプ設定
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// 色の設定
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// シーン3Dの初期化
	CScene_THREE::Init();
	// ビルボード
	CScene_THREE::SetBillboard(true);
	CScene_THREE::SetLighting(true);		// ライティング
											// テクスチャータイプ設定
	CScene_THREE::SetTexType(23);			// テクスチャー渡し
											// テクスチャ分割
	CScene_THREE::SetTex(D3DXVECTOR2(ANIM_TEX * 5, 0.0f), D3DXVECTOR2(ANIM_TEX + ANIM_TEX * 5, 1.0f));
	// 範囲
	m_fDistance = MAX_DISTANCE;
	// アニメーションカウンター初期化
	m_nCounterAnim = 0;
	// アニメーションパターン初期化
	m_nPatternAnim = 0;
	// 雷のカウント初期化
	m_nCntPoint = 0;
	// 雷の描画カウント初期化
	m_nCntDraw = 0;
	// 雷の状態を初期化
	m_bThunder = true;
	// ポジション取得
	m_pos = GetPos();
	// メッシュドームの生成
	m_pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE_Y, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_POINTCIRCLE,
		D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		false,
		LAYER_DOME);

	// メッシュドームの使用状態
	m_pMeshDome->SetUse(true);
}

// ==========================================================
// 終了
// ==========================================================
void CPointCircle::Uninit(void)
{
	if (m_pMeshDome != NULL)
	{
		m_pMeshDome->Release();
		m_pMeshDome = NULL;
	}
	CScene_THREE::Uninit();
}

// ==========================================================
// 更新
// ==========================================================
void CPointCircle::Update(void)
{
	CScene_THREE::Update();


	// 距離計算用
	float fX_Difference;
	float fZ_Difference;
	float fDifference;
	// テクスチャ分割
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	// カウンター加算
	m_nCounterAnim++;
	m_nCntDraw++;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// キャラクターへのポインタ
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			// キャラクターのポジション取得
			D3DXVECTOR3 charaPos = pPlayer->GetPos();

			// 前回のポジション設定
			m_posOld = m_pos;

			// 敵とプレイヤーのⅩ座標差分
			fX_Difference = m_pos.x - charaPos.x;

			// 敵とプレイヤーのZ座標差分
			fZ_Difference = m_pos.z - charaPos.z;

			// 敵とプレイヤーの一定距離
			fDifference = sqrtf(fX_Difference * fX_Difference + fZ_Difference * fZ_Difference);

			// プレイヤーが一定距離に近づいたら
			if (fDifference < m_fDistance)
			{
				// パーティクル生成
				C3DParticle::Create(
					C3DParticle::PARTICLE_ID_CROSSLINE,
					charaPos
				);

				if (nCount == CManager::GetNetwork()->GetId())
				{
					if (m_nCntPoint > 60)
					{
						m_bPoint = true;
						//CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
						m_nCntPoint = 0;
					}
					else
					{
						m_bPoint = false;
						m_nCntPoint++;
					}
				}
			}
		}
	}

	if (m_nCntDraw >= RELEASE_DRAW)
	{
		if (m_pMeshDome != NULL)
		{
			// メッシュドームの使用状態
			m_pMeshDome->SetUse(false);
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}
		Release();
	}
}

// ==========================================================
// 描画
// ==========================================================
void CPointCircle::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	if (m_bThunder == false)
	{
		// 描画
		CScene_THREE::Draw();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	}
}

// ==========================================================
// 生成
// ==========================================================
CPointCircle *CPointCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン動的に確保
	CPointCircle *pPointCircle = new CPointCircle();

	if (pPointCircle != NULL)
	{
		// 位置設定
		pPointCircle->SetPos(pos);

		// サイズ設定
		pPointCircle->SetSize(size);

		// シーン初期化
		pPointCircle->Init();

		pPointCircle->ManageSetting(LAYER_3DOBJECT2);

		return pPointCircle;
	}
	return NULL;
}

// ==========================================================
// 破棄
// ==========================================================
void CPointCircle::Unload(void)
{
}