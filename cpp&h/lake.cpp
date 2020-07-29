// ==========================================================
//
// 湖[lake.cpp]
// Author : masayasu wakita
//
// ==========================================================
#include "lake.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "sound.h"
#include "character.h"
#include "spherecollision.h"

// ==========================================================
// 静的メンバー変数の初期化
// ==========================================================
LPDIRECT3DTEXTURE9 CLake::m_pTex = NULL;

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CLake::CLake() :CScene_THREE()
{
	m_fAnim = 0.0f;
}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CLake::~CLake()
{

}

// ==========================================================
// 弾の初期化
// ==========================================================
void CLake::Init(void)
{
	// オフセットタイプ設定
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// 色の設定
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// シーン3Dの初期化
	CScene_THREE::Init();
	// ビルボード
	CScene_THREE::SetBillboard(false);
	CScene_THREE::SetLighting(true);		// ライティング
	// テクスチャータイプ設定
	CScene_THREE::SetTexType(28);	// テクスチャー渡し
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_pos = GetPos();
}

// ==========================================================
// 終了
// ==========================================================
void CLake::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// 更新
// ==========================================================
void CLake::Update(void)
{
	m_fAnim += 0.0003f;
	SetTex(D3DXVECTOR2(0.0f + m_fAnim, 0.0f + m_fAnim), D3DXVECTOR2(1.0f + m_fAnim, 1.0f + m_fAnim));
	CScene_THREE::Update();
}

// ==========================================================
// 弾の描画
// ==========================================================
void CLake::Draw(void)
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
// 弾の生成
// ==========================================================
CLake *CLake::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLake *pLake = NULL;

	// シーン動的に確保
	pLake = new CLake();

	if (pLake != NULL)
	{// 湖が存在していたとき
		pLake->SetPos(pos);							// 位置設定
		pLake->SetSize(size);						// サイズ設定
		pLake->SetRot(D3DXVECTOR3(D3DX_PI / 2, 0.0, 0.0f));
		pLake->Init();								// 初期化
		pLake->ManageSetting(LAYER_3DOBJECT2);
		return pLake;
	}

	// 値を返す
	return NULL;
}

// ==========================================================
// テクスチャロード
// ==========================================================
HRESULT CLake::Load(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_pTex);
	return S_OK;
}

// ==========================================================
// 破棄
// ==========================================================
void CLake::Unload(void)
{
	// テクスチャ解放
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}