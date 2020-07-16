// ==========================================================
//
// 複数の雷[thunderMulti.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
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
// 静的メンバー変数の初期化
// ==========================================================
CThunderMulti *CThunderMulti::m_pThunderMulti = NULL;
LPDIRECT3DTEXTURE9 CThunderMulti::m_pTex = NULL;

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CThunderMulti::CThunderMulti() :CScene_THREE()
{

}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CThunderMulti::~CThunderMulti()
{

}

// ==========================================================
// 初期化
// ==========================================================
void CThunderMulti::Init(void)
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
	// アニメーションカウンター初期化
	m_nCounterAnim = 0;
	// アニメーションパターン初期化
	m_nPatternAnim = 0;
	// 雷の状態を初期化
	m_bThunder = true;
	// ポジション取得
	m_pos = m_pThunderMulti->GetPos();
}

// ==========================================================
// 終了
// ==========================================================
void CThunderMulti::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// 更新
// ==========================================================
void CThunderMulti::Update(void)
{
	CScene_THREE::Update();

	// 距離計算用
	float fX_Difference;
	float fZ_Difference;
	float fDifference;
	// テクスチャ分割
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	m_nCounterAnim++;	// カウンター加算

						// 電撃テクスチャー
	if (m_nCounterAnim % 6 == 0)
	{
		m_nPatternAnim = (m_nPatternAnim + 1) % 6;

		CScene_THREE::SetAnimation(ANIM_TEX, 1.0f, 0.0f, m_nPatternAnim);
	}

	if (m_nPatternAnim == 5)
	{
		m_bThunder = false;
	}
}

// ==========================================================
// 描画
// ==========================================================
void CThunderMulti::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	if (m_bThunder == true)
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
CThunderMulti *CThunderMulti::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン動的に確保
	m_pThunderMulti = new CThunderMulti();

	// 位置設定
	m_pThunderMulti->SetPos(pos);

	// サイズ設定
	m_pThunderMulti->SetSize(size);

	// シーン初期化
	m_pThunderMulti->Init();

	m_pThunderMulti->ManageSetting(LAYER_3DOBJECT2);

	// 値を返す
	return m_pThunderMulti;
}

// ==========================================================
// 破棄
// ==========================================================
void CThunderMulti::Unload(void)
{
	// テクスチャ解放
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}