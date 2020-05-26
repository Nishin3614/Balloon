// ----------------------------------------------------------------------------------------------------
//
// ColumnCollisionヘッダー処理の説明[columncollision.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------

#ifndef _COLUMNCOLLISION_H_
#define _COLUMNCOLLISION_H_	 // ファイル名を基準を決める

// ----------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------
#include "collision.h"

// ----------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------
#define COLUMNCOLLISION_MAX (128)

// ----------------------------------------------------------------------------------------------------
//
// ColumnCollision種類
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// 構造体定義
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 名前定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CColumnCollision : public CCollision
{
public:
	/* 列挙型 */
	/* 関数 */
	CColumnCollision();
	virtual ~CColumnCollision() {};
	virtual void Init(void) {};
	virtual void Uninit(void) {};
	virtual void Update(void) {};
	virtual void Draw(void) {};
#ifdef _DEBUG
	virtual void Debug(void) {};
#endif // _DEBUG
	CShape * const GetShape(void) { return m_pColumnShape.get(); };
	// 
	// 矩形クラスの当たり判定比較
	bool Judg(CRectShape * const RectShape);
	// 球クラスの当たり判定比較
	bool Judg(CSphereShape * const SphereShape);
	// 円柱クラスの当たり判定比較
	bool Judg(CColumnShape * const ColumnShape);
	// 設定
	// 作成処理(シーン管理)
	static CColumnCollision *Create(
		D3DXVECTOR3 const offset,
		D3DXVECTOR3 const &pos,
		float const &fRadius,
		float const &fVertical,
		OBJTYPE const &obj = OBJTYPE_ACTOR
	);
	// 作成処理(個人管理)
	static unique_ptr<CColumnCollision> Create_Self(
		D3DXVECTOR3 const offset,
		D3DXVECTOR3 const &pos,
		float const &fRadius,
		float const &fVertical,
		OBJTYPE const &obj = OBJTYPE_ACTOR
	);

protected:

private:
	// 変数宣言
	unique_ptr<CColumnShape> m_pColumnShape;	// 矩形
};

// ----------------------------------------------------------------------------------------------------
//
// プロトタイプ宣言
//
// ----------------------------------------------------------------------------------------------------

#endif