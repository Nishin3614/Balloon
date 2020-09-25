// ----------------------------------------
//
// フレームワーク処理の説明[framework.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_two.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CFramework : public CScene_TWO
{
public:
	/* 列挙型 */

	/* 関数 */
	CFramework();
	~CFramework();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
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

	// 作成(シーン継承あり)
	static CFramework * Create(void);
	// 作成(シーン継承なし)
	static CFramework * Create_Self(void);
	// unique_ptr作成(シーン継承なし)
	static std::unique_ptr<CFramework> Creat_Unique(void);
	// 使用状態設定
	void SetUse(bool const &bUse) { m_bUse = bUse; };
	// 使用状態取得
	bool const &GetUse(void) { return m_bUse; };
protected:
	// 設定 //
private:
	/* 変数 */
	bool m_bUse;	// 使用状態
};

#endif