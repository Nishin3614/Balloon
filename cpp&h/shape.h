// ----------------------------------------------------------------------------------------------------
//
// Shapeヘッダー処理の説明[shape.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------

#ifndef _SHAPE_H_
#define _SHAPE_H_	 // ファイル名を基準を決める

// ----------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------
#include "main.h"
#include "Calculation.h"

// ----------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// Shape種類
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// 構造体定義
//
// ----------------------------------------------------------------------------------------------------

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
// 基底の形クラス
class CShape
{
public:
	/* 列挙型 */
	// 形の種類
	typedef enum
	{
		SHAPETYPE_RECT = 0,
		SHAPETYPE_SPHERE,
		SHAPETYPE_COLUMN,
		SHAPETYPE_MAX
	} SHAPETYPE;

	/* 関数 */
	CShape() {};
	virtual ~CShape() {};
	// 形の種類
	virtual SHAPETYPE GetType(void) const = 0;
	// 行列情報受け渡し
	// 1:行列情報
	virtual void PassMatrix(D3DXMATRIX const &mtx) = 0;
	// 位置と回転情報受け渡し
	// 1:位置情報,2:開店情報
	virtual void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	) = 0;
	// 位置情報受け渡し
	// 1:位置情報
	// 角度0の時
	virtual void PassPos(D3DXVECTOR3 const & pos) = 0;
	// 位置設定
	void SetOffset(D3DXVECTOR3 const &offset) { m_offset = offset; };
	// 位置取得
	D3DXVECTOR3 const &GetOffset(void) { return m_offset; };

protected:

private:
	D3DXVECTOR3 m_offset;	// オフセット座標
};

// 球のクラス
class CSphereShape : public CShape
{
public:
	/* 列挙型 */

	/* 関数 */
	CSphereShape() {};
	virtual ~CSphereShape() {};
	// 作成
	static unique_ptr<CSphereShape> Create(
		D3DXVECTOR3 const &offset,
		D3DXVECTOR3 const &pos,
		float const &radius
	);
	// 行列情報受け渡し
	// 1:行列情報
	void PassMatrix(D3DXMATRIX const &mtx);
	// 位置と回転情報受け渡し
	// 1:位置情報,2:開店情報
	void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	) {};
	// 位置情報受け渡し
	// 1:位置情報
	// 角度0の時
	void PassPos(D3DXVECTOR3 const & pos) { m_pos = pos; };
	// 設定 //
	// 半径設定
	void SetRadius(float const radius) { m_radius = radius; };
	// 位置設定
	void SetPos(D3DXVECTOR3 const &pos) { m_pos = pos; };

	// 取得 //
	// 形の種類取得
	SHAPETYPE GetType(void) const { return SHAPETYPE_SPHERE; };
	// 半径取得
	float GetRadius(void) const { return m_radius; };
	// 位置取得
	D3DXVECTOR3 const &GetPos(void) { return m_pos; };
protected:

private:
	D3DXVECTOR3 m_pos;
	float m_radius;
};

// 矩形のクラス
class CRectShape : public CShape
{
public:
	/* 列挙型 */

	/* 型宣言 */
	
	/* 関数 */
	CRectShape() 
	{
		m_size = D3DVECTOR3_ZERO;
		m_Min.x = m_Min.y = m_Min.z = FLT_MAX;
		m_Max.x = m_Max.y = m_Max.z = -FLT_MAX;
	};
	virtual ~CRectShape() {};
	// 最大座標値と最小座標値の計算
	// 1:行列情報
	void PassMatrix(D3DXMATRIX const &mtx);
	// 最大座標値と最小座標値の計算
	// 1:位置情報
	void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	);
	// 最大座標値と最小座標値の計算
	// 1:位置情報
	// 角度0の時
	void PassPos(D3DXVECTOR3 const & pos);
	// ある座標から最も近い、ボックス上の座標を返す
	D3DXVECTOR3 GetClosestpoint(D3DXVECTOR3 const &pos);
	// 作成
	static unique_ptr<CRectShape> Create(
		D3DXVECTOR3 const &offset,
		D3DXVECTOR3 const &size
	);
	// 設定 //
	// 半径設定
	void SetSize(D3DXVECTOR3 const size) { m_size = size; };
	// 取得 //
	// 形の種類取得
	SHAPETYPE GetType(void) const { return SHAPETYPE_RECT; };
	// 半径取得
	D3DXVECTOR3 GetSize(void) const { return m_size; };
	// 最大座標値取得
	D3DXVECTOR3 GetMax(void) const & { return m_Max; };
	// 最小座標値取得
	D3DXVECTOR3 GetMin(void) const & { return m_Min; };
protected:

private:
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_Min;
	D3DXVECTOR3 m_Max;
};

// 円柱のクラス
class CColumnShape : public CShape
{
public:
	/* 列挙型 */
	/* 関数 */
	CColumnShape() {};
	virtual ~CColumnShape() {};
	// 作成
	static unique_ptr<CColumnShape> Create(
		D3DXVECTOR3 const &offset,
		D3DXVECTOR3 const &pos,
		float const & fRadius,
		float const & fVertical
	);
	// 行列情報受け渡し
	// 1:行列情報
	// 未解決
	void PassMatrix(D3DXMATRIX const &mtx) {};
	// 位置と回転情報受け渡し
	// 1:位置情報,2:開店情報
	// 未解決
	void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	) {};
	// 位置情報受け渡し
	// 1:位置情報
	// 角度0の時
	void PassPos(D3DXVECTOR3 const & pos) { m_pos = pos; };
	// 設定 //
	// 位置設定
	void SetPos(D3DXVECTOR3 const &pos) { m_pos = pos; };
	// 半径設定
	void SetRadius(float const & fRadius) { m_fRadius = fRadius; };
	// 縦幅設定
	void SetVertical(float const & fVertical) { m_fVertical = fVertical; };
	// 取得 //
	// 形の種類取得
	SHAPETYPE GetType(void) const { return SHAPETYPE_COLUMN; };
	// 半径取得
	float GetRadius(void) const { return m_fRadius; };
	// 縦幅取得
	float GetVertical(void) const { return m_fVertical; };
	// 位置取得
	D3DXVECTOR3 const &GetPos(void) { return m_pos; };
protected:

private:
	D3DXVECTOR3 m_pos;
	float m_fRadius;
	float m_fVertical;
};

#endif