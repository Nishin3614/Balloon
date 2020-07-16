// ==========================================================
//
// 複数の雷[thunderMulti.h]
// Author:Ryouma Inoue
//
// ==========================================================
#ifndef _THUNDERMULTI_H_
#define _THUNDERMULTI_H_

#include "main.h"
#include "scene_three.h"

// ==========================================================
// マクロ定義
// ==========================================================
#define	ANIM_TEX		(1.0f / 6.0f)					// アニメーションテクスチャ

// ==========================================================
//
// クラスの定義
//
// ==========================================================
class CThunderMulti : public CScene_THREE
{
public:

	CThunderMulti();										// コンストラクタ
	~CThunderMulti();										// デストラクタ

	void Init(void);										// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画

	static CThunderMulti *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 生成
	static void Unload(void);													// アンロード

private:
	static LPDIRECT3DTEXTURE9 m_pTex;					// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;			// 頂点バッファへのポインタ
	VERTEX_3D *m_pVtx;									// 頂点情報へのポインタ
	D3DXMATRIX m_mtxWorld;								// ワールドマトリックス

	static CThunderMulti *m_pThunderMulti;

	D3DXVECTOR3	m_vtxMin;								// 最小値
	D3DXVECTOR3	m_vtxMax;								// 最大値
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_posOld;								// 前回の位置
	D3DXVECTOR3 m_rot;									// 回転
	D3DXVECTOR3 m_move;									// 移動量
	D3DXCOLOR m_col;									// 色

	int	m_nCounterAnim;									// アニメーションカウンター
	int m_nPatternAnim;									// アニメーションパターン
	float m_fDistance;									// 距離
	bool m_bThunder;									// 雷の状態
};
#endif