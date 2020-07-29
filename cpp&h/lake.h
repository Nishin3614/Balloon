// ==========================================================
//
// 湖[lake.h]
// Author : masayasu wakita
//
// ==========================================================
#ifndef _LAKE_H_
#define _LAKE_H_

#include "main.h"
#include "scene_three.h"

#define	TEXTURE_BULLET	"data/TEXTURE/coin.png"			// 読み込むテクスチャファイル名

// ==========================================================
//
// クラスの定義
//
// ==========================================================
class CLake : public CScene_THREE
{
public:

	CLake();												// コンストラクタ
	~CLake();												// デストラクタ

	void Init(void);										// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画

	static CLake *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 生成
	static HRESULT Load(void);													// ロード
	static void Unload(void);													// アンロード

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	VERTEX_3D *m_pVtx;							// 頂点情報へのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス

	D3DXVECTOR3	m_vtxMin;						// 最小値
	D3DXVECTOR3	m_vtxMax;						// 最大値
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 回転
	D3DXVECTOR3 m_move;							// 移動量
	D3DXCOLOR m_col;							// 色
	float m_fAnim;								// アニメーション移動量
};
#endif