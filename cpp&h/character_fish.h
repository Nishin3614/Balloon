// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 魚キャラクター処理 [character_fish.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _CHARACTER_FISH_H_
#define _CHARACTER_FISH_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 前方宣言
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// クラス
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCharacter_Fish : public CCharacter
{
public:
	/* 関数 */
	// 自分自身用
	CCharacter_Fish();
	virtual ~CCharacter_Fish();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
#ifdef _DEBUG
	virtual void Debug(void);
#endif // _DEBUG
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
	// 自分から当たらなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_NoMyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};

	// 魚キャラクターが死んだときの関数
	virtual void Die(void);
	// 生成処理(シーン管理)
	//	pos	: 位置
	//	rot	: 回転
	static CCharacter_Fish * Create(
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);			// 作成
				// 生成処理(個人管理)
	static CCharacter_Fish * Create_Self(
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);
	static HRESULT Load(void);								// 読み込み
	static void UnLoad(void);								// UnLoadする

protected:
	/* 列挙型 */
	/* 変数 */
	// 行動
private:
	/* 関数 */
	// AIアクション処理
	void Ai_Action(void);
	/* 変数 */
};
#endif
