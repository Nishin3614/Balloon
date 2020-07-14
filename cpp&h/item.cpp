// ==========================================================
//
// アイテム[item.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
#include "item.h"
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
CItem *CItem::m_pItem = NULL;
LPDIRECT3DTEXTURE9 CItem::m_pTex = NULL;

// ==========================================================
// グローバル変数
// ==========================================================

// ==========================================================
//
// コンストラクタ
//
// ==========================================================
CItem::CItem() :CScene_THREE()
{
	m_pCollision = NULL;
}

// ==========================================================
//
// デストラクタ
//
// ==========================================================
CItem::~CItem()
{

}

// ==========================================================
// 弾の初期化
// ==========================================================
void CItem::Init(void)
{
	// オフセットタイプ設定
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// 色の設定
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// シーン3Dの初期化
	CScene_THREE::Init();
	m_pCollision = CSphereCollision::Create(50, D3DVECTOR3_ZERO, CCollision::OBJTYPE_ITEM, this,NULL, false,false, &m_pos);
	// ビルボード
	CScene_THREE::SetBillboard(true);
	CScene_THREE::SetLighting(true);		// ライティング
	// テクスチャータイプ設定
	CScene_THREE::SetTexType(21);	// テクスチャー渡し
	m_pos = m_pItem->GetPos();
}

// ==========================================================
// 終了
// ==========================================================
void CItem::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// 更新
// ==========================================================
void CItem::Update(void)
{
	CScene_THREE::Update();
}

// ==========================================================
// 弾の描画
// ==========================================================
void CItem::Draw(void)
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
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン動的に確保
	m_pItem = new CItem();

	// 位置設定
	m_pItem->SetPos(pos);

	// サイズ設定
	m_pItem->SetSize(size);

	// シーン初期化
	m_pItem->Init();

	m_pItem->ManageSetting(LAYER_3DOBJECT2);

	// 値を返す
	return m_pItem;
}

// ==========================================================
// テクスチャロード
// ==========================================================
HRESULT CItem::Load(void)
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
void CItem::Unload(void)
{
	// テクスチャ解放
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}

// ==========================================================
// 当たった後の処理
// 引数1:オブジェクトタイプ
// 引数2:相手のシーン情報
// ==========================================================
void CItem::Scene_Collision(int const & nObjType, CScene * pScene)
{
	// オブジェクトタイプがキャラクターなら
	if (nObjType == CCollision::OBJTYPE_CHARACTER)
	{
		Release();
		m_pCollision->Release();
		m_pCollision = NULL;
	}
}

// ==========================================================
// 当たり判定
// ==========================================================
bool CItem::ItemCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin)
{
	bool bCollide = false;

	if ((m_pos.x + m_vtxMin.x <= pPos->x + pVtxMax->x) &&
		(m_pos.x + m_vtxMax.x >= pPos->x + pVtxMin->x) &&
		(m_pos.z + m_vtxMin.z <= pPos->z + pVtxMax->z) &&
		(m_pos.z + m_vtxMax.z >= pPos->z + pVtxMin->z) &&
		(m_pos.y + m_vtxMin.y <= pPos->y + pVtxMax->y))
	{
		bCollide = true;
	}

	return bCollide;
}

