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
#include "ui_group.h"

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
int CThunder::m_nAllThunder = 0;

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CThunder::CThunder() :CScene_THREE()
{
	m_nAllThunder++;
}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CThunder::~CThunder()
{
	m_nAllThunder--;
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
	// メッシュドームの生成
	m_pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(CScene_THREE::GetPos().x, 0.0f, CScene_THREE::GetPos().z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE_Y, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_NORMAL,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		false,
		LAYER_DOME);

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

	// モードがゲームなら
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ゲームの更新処理
		Update_Game();
	}
	// モードがチュートリアルなら
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// チュートリアルの更新処理
		Update_Tutorial();
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
	}
}

// ==========================================================
// 生成
// ==========================================================
CThunder *CThunder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン動的に確保
	CThunder * pThunder = new CThunder();

	// 位置設定
	pThunder->SetPos(pos);

	// サイズ設定
	pThunder->SetSize(size);

	// シーン初期化
	pThunder->Init();

	pThunder->ManageSetting(LAYER_3DOBJECT2);

	// 値を返す
	return pThunder;
}

// ==========================================================
// 破棄
// ==========================================================
void CThunder::Unload(void)
{
}

// ==========================================================
// チュートリアルの更新処理
// ==========================================================
void CThunder::Update_Tutorial(void)
{
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
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 200.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// 雷音1
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER1);
		}

		if (m_nCntThunder % 20 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// 雷音2
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER2);
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
				// 敵とプレイヤーのⅩ座標差分
				fX_Difference = CScene_THREE::GetPos().x - charaPos.x;

				// 敵とプレイヤーのZ座標差分
				fZ_Difference = CScene_THREE::GetPos().z - charaPos.z;

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
					// 死ぬ音2
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_KERSPLASH2);
					// キャラクター消滅
					pCharacter->Die();
				}
			}
		}
	}
}

// ==========================================================
// ゲームの更新処理
// ==========================================================
void CThunder::Update_Game(void)
{
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
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 200.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// 雷音1
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER1);
		}

		if (m_nCntThunder % 20 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// 雷音2
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER2);
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
				// 敵とプレイヤーのⅩ座標差分
				fX_Difference = CScene_THREE::GetPos().x - charaPos.x;

				// 敵とプレイヤーのZ座標差分
				fZ_Difference = CScene_THREE::GetPos().z - charaPos.z;

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
					// 死ぬ音2
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_KERSPLASH2);
					// キャラクター消滅
					pCharacter->Die();
				}
			}
		}
	}

	if (m_nCntDraw >= RELEASE_DRAW)
	{
		// メッシュドームのNULLチェック
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
