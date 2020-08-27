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

#define ITME_STATUS_FILE	("data/LOAD/STATUS/status_manager_Item.csv")	// アイテムステータスパス
// ==========================================================
// 静的メンバー変数の初期化
// ==========================================================
CItem *CItem::m_pItem = NULL;
LPDIRECT3DTEXTURE9 CItem::m_pTex = NULL;
CItem::STATUS	CItem::m_sStatus = {};					// アイテムのスタータス情報

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
	m_pCollision = CSphereCollision::Create(
		50,
		D3DVECTOR3_ZERO,
		CCollision::OBJTYPE_ITEM,
		this,
		NULL,
		false,
		false,
		&CScene_THREE::GetPos());
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
	// あたり判定のNULLチェック
	if (m_pCollision != NULL)
	{
		m_pCollision->Release();
		m_pCollision = NULL;
	}

	CScene_THREE::Uninit();
}

// ==========================================================
// 更新
// ==========================================================
void CItem::Update(void)
{
	// あたり判定のNULLチェック
	if (m_pCollision != NULL)
	{
		m_pCollision->GetShape()->PassPos(D3DVECTOR3_ZERO);
	}

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
CItem *CItem::Create(const int nId, D3DXVECTOR3 pos, D3DXVECTOR3 size)
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

	// IDの設定
	m_pItem->m_nId = nId;

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
	// ステータス読み込み
	LoadStatus();
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

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ステータス情報読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CItem::LoadStatus(void)
{
	// 変数宣言
	std::vector<std::vector<std::string>> vsvec_Contens;	// ファイルの中身格納用
															// ファイルの中身を取得する
	vsvec_Contens = CCalculation::FileContens(ITME_STATUS_FILE, ',');
	// 行ごとに回す
	for (int nCntLine = 0; nCntLine < (signed)vsvec_Contens.size(); nCntLine++)
	{
		// 項目ごとに回す
		for (int nCntItem = 0; nCntItem < (signed)vsvec_Contens.at(nCntLine).size(); nCntItem++)
		{
			switch (nCntItem)
			{
				// スコアポイント
			case 0:
				m_sStatus.nScorePoint = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
				// MPアップ
			case 1:
				m_sStatus.nMpUp = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
			default:
				break;
			}
		}
	}
	// std::vectorの多重配列開放
	std::vector<std::vector<std::string>>().swap(vsvec_Contens);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たった後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CItem::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork == NULL)
	{
		return;
	}

	// オブジェクトタイプがキャラクターなら
	if (nObjType == CCollision::OBJTYPE_PLAYER)
	{
		char aDie[64];
		sprintf(aDie, "GET_COIN %d", m_nId);
		pNetwork->SendTCP(aDie, sizeof(aDie));
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 相手に当てられた後の処理
//	nObjType	: オブジェクトタイプ
//	pScene		: 相手のシーン情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CItem::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork == NULL)
	{
		return;
	}

	// オブジェクトタイプがキャラクターなら
	if (nObjType == CCollision::OBJTYPE_PLAYER)
	{
		char aDie[64];
		sprintf(aDie, "GET_COIN %d", m_nId);
		pNetwork->SendTCP(aDie, sizeof(aDie));
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

