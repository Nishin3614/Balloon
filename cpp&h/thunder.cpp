// ==========================================================
//
// 雷[thunder.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
#include "thunder.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "sound.h"
#include "character.h"
#include "spherecollision.h"
#include "collision.h"
#include "character.h"
#include "3Dparticle.h"
#include "meshdome.h"

// ==========================================================
// 静的メンバー変数の初期化
// ==========================================================
CThunder *CThunder::m_pThunder = NULL;
LPDIRECT3DTEXTURE9 CThunder::m_pTex = NULL;

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CThunder::CThunder() :CScene_THREE()
{

}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CThunder::~CThunder()
{

}

// ==========================================================
// 初期化
// ==========================================================
void CThunder::Init(void)
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
	CScene_THREE::SetTexType(22);			// テクスチャー渡し
	// 範囲
	m_fDistance = MAX_DISTANCE;
	// ポジション取得
	m_pos = m_pThunder->GetPos();

	// メッシュドームの生成
	CMeshdome *pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_NORMAL,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// メッシュドームの使用状態
	pMeshDome->SetUse(true);
}

// ==========================================================
// 終了
// ==========================================================
void CThunder::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// 更新
// ==========================================================
void CThunder::Update(void)
{
	CScene_THREE::Update();

	// 距離計算用
	float fX_Difference;
	float fZ_Difference;
	float fDifference;

	/*
	g_aExplosion[nCntExplosion].nCounterAnim++;	// カウンター加算

												// 電撃テクスチャー
	if (g_aExplosion[nCntExplosion].type == EXPLOSIONTYPE_THUNDER)
	{
		// 当たり判定
		CollisionExplosion(nCntExplosion);
		if (g_aExplosion[nCntExplosion].nCounterAnim % 6 == 0)
		{
			// テクスチャ設定
			SetTexExplosion(pVtx,
				ANIMATION_SIX_FTEX * g_aExplosion[nCntExplosion].nPatternAnim,
				ANIMATION_SIX_FTEX + ANIMATION_SIX_FTEX * g_aExplosion[nCntExplosion].nPatternAnim);
			g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim++) % ANIMATION_SIX;	// 6枚パターン創造

																														// 爆発終了
			if (g_aExplosion[nCntExplosion].nPatternAnim % ANIMATION_SIX == 0)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
		}
	}
	*/

	for (int nCnt = 0; nCnt < CScene::GetMaxLayer(CScene::LAYER_CHARACTER); nCnt++)
	{
		// キャラクターへのポインタ
		CCharacter *pCharacter = (CCharacter*)CScene::GetScene(CScene::LAYER_CHARACTER, nCnt);

		if (pCharacter != NULL)
		{
			// キャラクターのポジション取得
			D3DXVECTOR3 charaPos = pCharacter->GetPos();

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
					C3DParticle::OFFSET_ID_CROSSLINE,
					charaPos
				);
				// キャラクター消滅
				pCharacter->Release();
			}
		}
	}
}

// ==========================================================
// 描画
// ==========================================================
void CThunder::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

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

// ==========================================================
// 生成
// ==========================================================
CThunder *CThunder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン動的に確保
	m_pThunder = new CThunder();

	// 位置設定
	m_pThunder->SetPos(pos);

	// サイズ設定
	m_pThunder->SetSize(size);

	// シーン初期化
	m_pThunder->Init();

	m_pThunder->ManageSetting(LAYER_3DOBJECT);

	// 値を返す
	return m_pThunder;
}

// ==========================================================
// 破棄
// ==========================================================
void CThunder::Unload(void)
{
	// テクスチャ解放
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}