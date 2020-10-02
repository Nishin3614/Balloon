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
#define	ANIM_TEX		(1.0f / 8.0f)					// アニメーションテクスチャ

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
	// 当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 自分から当たらなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_NoMyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 生成
	static CThunderMulti *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 生成
private:
	static int m_ThunderCnt;							// 雷のカウント

	int	m_nCounterAnim;									// アニメーションカウンター
	int m_nPatternAnim;									// アニメーションパターン
	float m_fDistance;									// 距離
};
#endif