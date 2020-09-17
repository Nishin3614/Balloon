// ==========================================================
//
// 雷[thunder.h]
// Author:Ryouma Inoue
//
// ==========================================================
#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"
#include "scene_three.h"

// ==========================================================
// マクロ定義
// ==========================================================
#define	TEXTURE_THUNDER	"data/TEXTURE/coin.png"			// 読み込むテクスチャファイル名
#define	MAX_DISTANCE	(150)							// 距離
#define	MAX_DISTANCE_Y	(2000)							// 距離

// ==========================================================
//
// 前方宣言
//
// ==========================================================
class CMeshdome;

// ==========================================================
//
// クラスの定義
//
// ==========================================================
class CThunder : public CScene_THREE
{
public:

	CThunder();												// コンストラクタ
	~CThunder();											// デストラクタ

	void Init(void);										// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画

	static CThunder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 生成
	static void Unload(void);													// アンロード

private:
	CMeshdome *m_pMeshDome;								// メッシュドームへのポインタ

	D3DXVECTOR3 m_move;									// 移動量

	int	m_nCounterAnim;									// アニメーションカウンター
	int m_nPatternAnim;									// アニメーションパターン
	int m_nCntThunder;									// 雷のカウント
	int m_nCntDraw;										// 雷の描画カウント
	float m_fDistance;									// 距離
	bool m_bThunder;									// 雷の状態
};
#endif