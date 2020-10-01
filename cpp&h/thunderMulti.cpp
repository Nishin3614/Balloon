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
int CThunderMulti::m_ThunderCnt = 0;							// 雷のカウント

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CThunderMulti::CThunderMulti() :CScene_THREE()
{
	m_ThunderCnt++;
}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CThunderMulti::~CThunderMulti()
{
	m_ThunderCnt--;
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
		Release();
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
	// 描画
	CScene_THREE::Draw();
}

// ==========================================================
// 生成
// ==========================================================
CThunderMulti *CThunderMulti::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CThunderMulti * pThunder = new CThunderMulti();

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
