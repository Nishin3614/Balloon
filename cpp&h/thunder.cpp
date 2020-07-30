// ==========================================================
//
// 雷[thunder.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
#include "thunder.h"
#include "thunderMulti.h"
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
//
// マクロ定義
//
// ==========================================================
#define COUNT_DRAW (600)
#define RELEASE_DRAW (1200)

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
	m_nCntThunder = 0;
	// 雷の描画カウント初期化
	m_nCntDraw = 0;
	// 雷の状態を初期化
	m_bThunder = true;
	// ポジション取得
	m_pos = m_pThunder->GetPos();
	// メッシュドームの生成
	m_pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_NORMAL,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// メッシュドームの使用状態
	m_pMeshDome->SetUse(true);
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
	// テクスチャ分割
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	// カウンター加算
	m_nCounterAnim++;
	m_nCntThunder++;
	m_nCntDraw++;


	if (m_nCntDraw >= COUNT_DRAW)
	{
		if (m_nCntThunder % 50 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(m_pos + D3DXVECTOR3(float(rand() % 81 - 40), float(rand() % 201 - 100), float(rand() % 81 - 40)),
				D3DXVECTOR3(100.0f, 500.0f, 0.0f));
		}

		if (m_nCntThunder % 20 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(m_pos + D3DXVECTOR3(float(rand() % 81 - 40), float(rand() % 201 - 100), float(rand() % 81 - 40)),
				D3DXVECTOR3(100.0f, 500.0f, 0.0f));
		}

		//// 電撃テクスチャー
		//if (m_nCounterAnim % 6 == 0)
		//{
		//	m_nPatternAnim = (m_nPatternAnim + 1) % 6;

	 //		CScene_THREE::SetAnimation(ANIM_TEX, 1.0f, 0.0f, m_nPatternAnim);
		//}
		//
		//if (m_nPatternAnim == 5)
		//{
		//	m_bThunder = false;
		//
		//}
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
						C3DParticle::PARTICLE_ID_CROSSLINE,
						charaPos
					);
					// キャラクター消滅
					pCharacter->Release();
				}
			}
		}
	}

	if (m_nCntDraw >= RELEASE_DRAW)
	{
		// メッシュドームの使用状態
		m_pMeshDome->SetUse(false);
		Release();
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

	m_pThunder->ManageSetting(LAYER_3DOBJECT2);

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