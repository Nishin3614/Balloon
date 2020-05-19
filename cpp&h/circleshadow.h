// ----------------------------------------
//
// 円形キャラクター処理の説明[circleshadow.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _CIRCLESHADOW_H_
#define _CIRCLESHADOW_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_three.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define CIRCLESHADOW_HP (20)
#define CIRCLESHADOW_MP (50)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CCircleshadow : public CScene_THREE
{
public:
	/* 列挙型 */

	/* 関数 */
	CCircleshadow();
	~CCircleshadow();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// 作成(シーン継承あり)
	static CCircleshadow * Create(
		D3DXVECTOR3 const &pos,							// 位置
		D3DXVECTOR3 const &size							// サイズ
	);					// 作成
	static HRESULT Load(void);							// 読み込み
	static void UnLoad(void);							// 破棄
	// 設定 //

	// 取得 // 
protected:
private:
	/* 関数 */
	/* 変数 */
};
#endif