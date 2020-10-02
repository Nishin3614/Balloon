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
#ifdef _DEBUG
	void Debug(void) {};
#endif // _DEBUG
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
	static int &GetAllThunder(void) { return m_nAllThunder; };			// ポイントサークルの総数取得
	static CThunder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 生成
	static void Unload(void);													// アンロード

private:
	/* 関数 */
	// チュートリアルの更新処理
	void Update_Tutorial(void);
	// ゲームの更新処理
	void Update_Game(void);
	/* 変数 */
	static int m_nAllThunder;						// ポイントサークルの総数
	CMeshdome *m_pMeshDome;								// メッシュドームへのポインタ


	int	m_nCounterAnim;									// アニメーションカウンター
	int m_nPatternAnim;									// アニメーションパターン
	int m_nCntThunder;									// 雷のカウント
	int m_nCntDraw;										// 雷の描画カウント
	float m_fDistance;									// 距離
};
#endif