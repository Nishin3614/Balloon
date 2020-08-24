// ==========================================================
//
// アイテム[item.h]
// Author:Ryouma Inoue
//
// ==========================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene_three.h"

#define MAX_BULLET_TEX (4)
#define MAX_BULLET (200)								// アイテムの最大数
#define BULLET_SIZE (100.0f)								// アイテムのサイズ
#define	TEXTURE_BULLET	"data/TEXTURE/coin.png"			// 読み込むテクスチャファイル名

// ==========================================================
//
// 前方宣言
//
// ==========================================================
class CCollision;

// ==========================================================
//
// クラスの定義
//
// ==========================================================
class CItem : public CScene_THREE
{
public:

	CItem();												// コンストラクタ
	~CItem();												// デストラクタ

	void Init(void);										// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画
	// 当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	);
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	);
	bool ItemCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin);				// 弾の当たり判定
	CCollision *GetCollision(void) { return m_pCollision; }

	static CItem *Create(const int nId, D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 生成
	static HRESULT Load(void);													// ロード
	static void Unload(void);													// アンロード

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	VERTEX_3D *m_pVtx;							// 頂点情報へのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス

	static CItem *m_pItem;

	D3DXVECTOR3	m_vtxMin;								// 最小値
	D3DXVECTOR3	m_vtxMax;								// 最大値
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_rot;									// 回転
	D3DXVECTOR3 m_move;									// 移動量
	D3DXCOLOR m_col;									// 色
	CCollision * m_pCollision;							// あたり判定情報
	int m_nCntEffect;
	int m_nId;											// コインのID

};
#endif