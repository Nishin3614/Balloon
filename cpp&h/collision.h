// ----------------------------------------------------------------------------------------------------
//
// Collisionヘッダー処理の説明[calculation.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------

#ifndef _COLLISION_H_
#define _COLLISION_H_	 // ファイル名を基準を決める

// ----------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------
#include "scene.h"
#include "shape.h"

// ----------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------
#define COLLISION_MAX (128)

// ----------------------------------------------------------------------------------------------------
//
// Collision種類
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
class CCollision : public CScene
{
public:
	/* 列挙型 */
	// 当たり判定の形
	typedef enum
	{
		COLLISIONTYPE_SQUARE = 0,
		COLLISIONTYPE_CIRCLE,
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;
	// オブジェクトカテゴリー
	typedef enum
	{
		OBJTYPE_CHARACTER = 0,
		OBJTYPE_BALLOON,
		OBJTYPE_ACTOR,
		OBJTYPE_MAX
	} OBJTYPE;
	/* 関数 */
	CCollision();
	virtual ~CCollision() {};
	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
#ifdef _DEBUG
	virtual void Debug(void) = 0;
#endif // _DEBUG
	// 判定の有無
	// 矩形クラスの当たり判定比較
	virtual bool Judg(CRectShape * const RectShape) = 0;
	// 矩形クラスの当たり判定比較(押し出し処理)
	virtual bool Judg(CRectShape * const RectShape,D3DXVECTOR3 * pPos) = 0;
	// 球クラスの当たり判定比較
	virtual bool Judg(CSphereShape * const SphereShape) = 0;
	// 円柱クラスの当たり判定比較
	virtual bool Judg(CColumnShape * const ColumnShape) = 0;
	// 形クラスの当たり判定
	bool SelectShape(CShape * const shape);
	// 当たり判定同士の判定(指定)
	bool CollisionDetection(CCollision * collision);
	// 当たり判定同士の判定(押し出し処理)
	bool CollisionDetection(
		CCollision * collision,
		D3DXVECTOR3 * pPos);
	// 当たり判定同士の判定(指定オブジェクト)
	bool CollisionDetection(OBJTYPE const &obj);
	// 当たり判定同士の判定(全体)
	bool CollisionDetection(void);
	// 形別の当たり判定の区別

	// 当たり判定状態の強制falseへ
	// 当たった後の行動が起こった時に判定をfalseにする
	void SetCollision(void);
	// 当たり判定状態の取得
	bool &GetbCollision(void) { return m_bCollision; };
	// 自分のオブジェクト番号設定
	void SetObjectID(OBJTYPE const &obj) { m_nMyObjectId = obj; };
	// 形を取得
	virtual CShape * const GetShape(void) = 0;

	// 矩形と矩形の当たり判定
	// pRectShapeA:矩形A
	// pRectShapeB:矩形B
	static bool RectAndRect(
		CRectShape * const pRectShapeA,	// 矩形A
		CRectShape * const pRectShapeB	// 矩形B
	);
	// 矩形と矩形の当たり判定
	// pRectShapeA:矩形A
	// pRectShapeB:矩形B
	// pPos:位置ポインター(親元の位置)
	static bool RectAndRect(
		CRectShape * const pRectShapeA,	// 矩形A
		CRectShape * const pRectShapeB,	// 矩形B
		D3DXVECTOR3 * pPos				// 位置ポインター
	);
	// 矩形と球の当たり判定
	static bool RectAndSphere(
		CRectShape * const pRectShapeA,		// 矩形A
		CSphereShape * const pSphereShapeB	// 球B
	);
	// 矩形と円柱の当たり判定
	static bool RectAndColumn(
		CRectShape * const pRectShapeA,		// 矩形A
		CColumnShape * const pColumnShapeB	// 円柱B
	);
	// 球と円柱の当たり判定
	static bool SphereAndColumn(
		CSphereShape * const pSphereShapeA,	// 球A
		CColumnShape * const pColumnShapeB	// 円柱B
	);
	// 球と球の当たり判定
	static bool SphereAndSphere(
		CSphereShape * const pSphereShapeA,	// 球A
		CSphereShape * const pSphereShapeB	// 球B
	);
	// 円柱と円柱の当たり判定
	static bool ColumnAndColumn(
		CColumnShape * const pColumnShapeA,	// 円柱A
		CColumnShape * const pColumnShapeB	// 円柱B
	);
protected:

private:
	/* 変数 */
	bool m_bCollision;						// 当たり判定状態
	int m_nMyObjectId;						// オブジェクト番号
	int m_nOponentId;						// 当たった時の相手
};

// ----------------------------------------------------------------------------------------------------
//
// プロトタイプ宣言
//
// ----------------------------------------------------------------------------------------------------

#endif