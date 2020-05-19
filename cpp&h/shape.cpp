#include "shape.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形の最大座標値と最小座標値の計算
// 1:行列情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRectShape::PassMatrix(
	D3DXMATRIX const &mtx
)
{
	// 最小座標値の設定
	D3DXVec3TransformCoord(&m_Min, &(this->GetOffset() - m_size), &mtx);
	// 最大座標値の設定
	D3DXVec3TransformCoord(&m_Max, &(this->GetOffset() + m_size), &mtx);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形の最大座標値と最小座標値の計算
// 1:位置情報,2:回転情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRectShape::PassPos(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot)
{
	// 変数宣言
	D3DXMATRIX mtx;
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtx,
		rot.y,
		rot.x,
		rot.z);
	// 最小座標値の設定
	D3DXVec3TransformCoord(&m_Min, &(pos + this->GetOffset() - m_size), &mtx);
	// 最大座標値の設定
	D3DXVec3TransformCoord(&m_Max, &(pos + this->GetOffset() + m_size), &mtx);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形の最大座標値と最小座標値の計算
// 軸方向が平面(角度0)の時
// 1:位置情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRectShape::PassPos(D3DXVECTOR3 const & pos)
{
	// 最大座標値の計算
	m_Max = pos + this->GetOffset() + m_size * 0.5f;
	// 最小座標値の計算
	m_Min = pos + this->GetOffset() - m_size * 0.5f;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ある座標から最も近い、ボックス上の座標を返す
// 1:位置情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 CRectShape::GetClosestpoint(D3DXVECTOR3 const & pos)
{
	// 変数宣言
	D3DXVECTOR3 r_pos;	// ボックス上の座標
	// ある座標がボックスの最小座標値より低い場合
	if (pos.x < m_Min.x)
	{
		// 最小座標値を代入
		r_pos.x = m_Min.x;
	}
	// ある座標がボックスの最大座標値より低い場合
	else if (pos.x > m_Max.x)
	{
		// 最大座標値を代入
		r_pos.x = m_Max.x;
	}
	// それ以外
	else
	{
		// ある座標を代入
		r_pos.x = pos.x;
	}

	// ある座標がボックスの最小座標値より低い場合
	if (pos.y < m_Min.y)
	{
		// 最小座標値を代入
		r_pos.y = m_Min.y;
	}
	// ある座標がボックスの最大座標値より低い場合
	else if (pos.y > m_Max.y)
	{
		// 最大座標値を代入
		r_pos.y = m_Max.y;
	}
	// それ以外
	else
	{
		// ある座標を代入
		r_pos.y = pos.y;
	}

	// ある座標がボックスの最小座標値より低い場合
	if (pos.z < m_Min.z)
	{
		// 最小座標値を代入
		r_pos.z = m_Min.z;
	}
	// ある座標がボックスの最大座標値より低い場合
	else if (pos.z > m_Max.z)
	{
		// 最大座標値を代入
		r_pos.z = m_Max.z;
	}
	// それ以外
	else
	{
		// ある座標を代入
		r_pos.z = pos.z;
	}
	return r_pos;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形クラスの作成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unique_ptr<CRectShape> CRectShape::Create(
	D3DXVECTOR3 const &offset,
	D3DXVECTOR3 const &size
)
{
	// 変数宣言
	unique_ptr<CRectShape> pRect(new CRectShape);
	// 半径の設定
	pRect->SetSize(size);
	// オフセットの設定
	pRect->SetOffset(offset);
	return pRect;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 球クラスの作成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unique_ptr<CSphereShape> CSphereShape::Create(
	D3DXVECTOR3 const &offset,
	D3DXVECTOR3 const &pos,
	float const & radius
)
{
	// 変数宣言
	unique_ptr<CSphereShape> pSphere(new CSphereShape);
	// オフセットの設定
	pSphere->SetOffset(offset);
	// 位置設定
	pSphere->SetPos(pos);
	// 半径の設定
	pSphere->SetRadius(radius);
	return pSphere;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 行列情報受け渡し
// 1:行列情報
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereShape::PassMatrix(D3DXMATRIX const & mtx)
{
	// 最大座標値の設定
	D3DXVec3TransformCoord(&m_pos, &this->GetOffset(), &mtx);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 円柱クラスの作成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unique_ptr<CColumnShape> CColumnShape::Create(
	D3DXVECTOR3 const &offset,
	D3DXVECTOR3 const &pos,
	float const & fRadius,
	float const & fVertical
)
{
	// 変数宣言
	unique_ptr<CColumnShape> pColum(new CColumnShape);
	// オフセットの設定
	pColum->SetOffset(offset);
	// 位置設定
	pColum->SetPos(pos);
	// 半径の設定
	pColum->SetRadius(fRadius);
	// 縦幅の設定
	pColum->SetVertical(fVertical);
	return pColum;
}
