// ==========================================================
//
// プレイヤー(透明)処理 [invisible.h]
// Author : RYOUMA INOUE
//
// ==========================================================
#ifndef _INVISIBLE_H_
#define _INVISIBLE_H_

#define _CRT_SECURE_NO_WARNINGS

// ==========================================================
// インクルードファイル
// ==========================================================
#include "player.h"

// ==========================================================
// 前方宣言
// ==========================================================


// ==========================================================
// クラス
// ==========================================================
class CInvisible : public CPlayer
{
public:
	// ---------モーションタイプ---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CPlayer::MOTIONTYPE_MAX
	} MOTIONTYPE;
	/* 関数 */
	CInvisible();
	~CInvisible();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// プレイヤーが死んだときの関数
	void Die(void);
#ifdef _DEBUG
	void Debug(void);
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
	// 生成処理(シーン管理)
	static CInvisible * Create(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);			// 作成
				// 生成処理(個人管理)
	static CInvisible * Create_Self(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);
	static HRESULT Load(void);			// 読み込み
	static void UnLoad(void);			// UnLoadする
	// 透明かどうかの取得処理
	bool const &GetInvisible(void) { return m_bInvisible; };
protected:
private:
	/* 構造体 */
	/* 関数 */

	/* 変数 */
	bool m_bInvisible;					// 透明かどうか
};
#endif
