// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Collision処理の説明[collision.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Collision.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define COLLISION_FILE "data/LOAD/collision.txt"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// グローバル変数
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCollision::CCollision() : CScene::CScene()
{
	// 初期化
	m_bCollision = false;
	m_nMyObjectId = 0;
	m_nOponentId = -1;
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCollision::Debug(void)
{
	// 変数宣言
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posold;

	// 情報代入 //
	// 位置情報取得
	if (GetShape()->Get_PPos() != NULL)
	{
		pos = *GetShape()->Get_PPos();
	}
	else
	{
		pos = GetShape()->Get_Pos();
	}
	// 過去の位置情報取得
	if (GetShape()->Get_PPosold() != NULL)
	{
		posold = *GetShape()->Get_PPosold();
	}
	else
	{
		posold = GetShape()->Get_Posold();
	}
	CDebugproc::Print("位置情報(%.1f,%.1f,%.1f)\n",
		pos.x,
		pos.y,
		pos.z
	);
	CDebugproc::Print("過去の位置情報(%.1f,%.1f,%.1f)\n",
		posold.x,
		posold.y,
		posold.z
	);

}

#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 形クラスの選択
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SelectShape(CShape * const shape)
{
	// クラス型比較 //
	// 矩形クラス
	if (shape->GetType() == CShape::SHAPETYPE_RECT)
	{
		return Judg((CRectShape*)shape);
	}
	// 球クラス
	else if (shape->GetType() == CShape::SHAPETYPE_SPHERE)
	{
		return Judg((CSphereShape*)shape);
	}
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定(指定)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(CCollision * collision)
{
	// 引数の当たり判定情報がNULLの場合
	// ->関数を抜ける
	if (collision == NULL)
	{
		return false;
	}
	// 変数宣言
	bool bJudg = false;	// 当たり判定状態
	// クラス型比較 //
	// 矩形クラス
	if (collision->GetShape()->GetType() == CShape::SHAPETYPE_RECT)
	{
		bJudg = Judg((CRectShape*)collision->GetShape());
	}
	// 球クラス
	else if (collision->GetShape()->GetType() == CShape::SHAPETYPE_SPHERE)
	{
		bJudg = Judg((CSphereShape*)collision->GetShape());
	}
	// 円柱クラス
	else if (collision->GetShape()->GetType() == CShape::SHAPETYPE_COLUMN)
	{
		bJudg = Judg((CColumnShape*)collision->GetShape());
	}
	// 判定がtrueなら
	// ->情報を保存
	if (bJudg ==  true)
	{
		// 相手の当たり判定状態をtrueへ
		collision->m_bCollision = true;
		// 相手の番号を代入
		collision->m_nOponentId = m_nMyObjectId;
		// シーン情報がNULLではないなら
		// ->当たった後の処理を行う
		if (m_pScene != NULL)
		{
			m_pScene->Scene_Collision(collision->m_nMyObjectId,collision->m_pScene);
		}
		// 相手のシーン情報がNULLではないなら
		// ->当たった後の処理を行う
		if (collision->m_pScene != NULL)
		{
			collision->m_pScene->Scene_Collision(m_nMyObjectId,m_pScene);
		}
	}
	// 当たり判定状態を返す
	return bJudg;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定(押し出し処理)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(
	CCollision * collision,
	D3DXVECTOR3 * pPos
)
{
	// 引数の当たり判定情報がNULLの場合
	// ->関数を抜ける
	if (collision == NULL)
	{
		return false;
	}
	// 変数宣言
	bool bJudg = false;	// 当たり判定状態
	// クラス型比較 //
	// 矩形クラス
	if (collision->GetShape()->GetType() == CShape::SHAPETYPE_RECT)
	{
		bJudg = Judg((CRectShape*)collision->GetShape(),pPos);
	}
	// 球クラス
	else if (collision->GetShape()->GetType() == CShape::SHAPETYPE_SPHERE)
	{

	}
	// 円柱クラス
	else if (collision->GetShape()->GetType() == CShape::SHAPETYPE_COLUMN)
	{

	}
	// 判定がtrueなら
	// ->情報を保存
	if (bJudg == true)
	{
		// 相手の当たり判定状態をtrueへ
		collision->m_bCollision = true;
		// 相手の番号を代入
		collision->m_nOponentId = m_nMyObjectId;
	}
	// 当たり判定状態を返す
	return bJudg;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定(指定オブジェクト)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(OBJTYPE const & obj)
{
	// 変数宣言
	CCollision * pCollision;	// 当たり判定情報
	bool bCollision = false;	// 当たり判定状態
	// 処理
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(LAYER_COLLISION); nCntLayer++)
	{
		// 当たり判定取得
		pCollision = (CCollision *)CScene::GetScene(LAYER_COLLISION, nCntLayer);
		// 当たり判定のNULLチェック
		// ->ループスキップ
		if (pCollision == NULL) continue;
		// 自分の当たり判定と取得した当たり判定が同じなら
		// ->ループスキップ
		else if (pCollision == this) continue;
		// 指定したオブジェクトではないなら
		// ->ループスキップ
		else if (pCollision->m_nMyObjectId != obj) continue;
		// 当たり判定をtrueにする
		bCollision |= this->CollisionDetection(pCollision);
	}
	// 当たり判定状態を返す
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定(管理している全体)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(void)
{
	// 変数宣言
	CCollision * pCollision;	// 当たり判定情報
	bool bCollision = false;	// 当たり判定状態
	// 処理
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(LAYER_COLLISION); nCntLayer++)
	{
		// 当たり判定取得
		pCollision = (CCollision *)CScene::GetScene(LAYER_COLLISION, nCntLayer);
		// 当たり判定のNULLチェック
		// ->ループスキップ
		if (pCollision == NULL) continue;
		// 自分の当たり判定と取得した当たり判定が同じなら
		// ->ループスキップ
		else if (pCollision == this) continue;
		// 当たり判定をtrueにする
		bCollision |= this->CollisionDetection(pCollision);
	}
	// 当たり判定状態を返す
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定状態の強制falseへ
// 当たった後の行動が起こった時に判定をfalseにする
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCollision::SetCollision(void)
{
	m_bCollision = false;
	m_nOponentId = -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形と矩形の判定
// pRectShapeA:矩形A
// pRectShapeB:矩形B
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndRect(
	CRectShape * const pRectShapeA,	// 矩形A
	CRectShape * const pRectShapeB	// 矩形B
)
{
	// 変数宣言
	D3DXVECTOR3 const &min_A = pRectShapeA->GetMin();
	D3DXVECTOR3 const &min_B = pRectShapeB->GetMin();
	D3DXVECTOR3 const &max_A = pRectShapeA->GetMax();
	D3DXVECTOR3 const &max_B = pRectShapeB->GetMax();
	D3DXVECTOR3 const &minOld_A = pRectShapeA->GetMinOld();
	D3DXVECTOR3 const &minOld_B = pRectShapeB->GetMinOld();
	D3DXVECTOR3 const &maxOld_A = pRectShapeA->GetMaxOld();
	D3DXVECTOR3 const &maxOld_B = pRectShapeB->GetMaxOld();
	D3DXVECTOR3 *pos_A = NULL;
	bool bCollision = false;
	// ポインター位置情報がNULLではないなら
	// ->位置情報に代入
	if (pRectShapeA->Get_PPos() != NULL)
	{
		pos_A = pRectShapeA->Get_PPos();
	}
	// 接触していないときはfalseを返す
	if (max_A.y > min_B.y &&
		min_A.y < max_B.y)
	{
		// 素材のZ範囲
		if (max_A.z > min_B.z&&
			min_A.z < max_B.z)
		{
			// 当たり判定(左)
			if (max_A.x > min_B.x &&
				maxOld_A.x <= min_B.x)
			{
				// 過去の位置情報AがNULLではないなら ||
				// 押し出し処理がありなら
				// ->押し出し処理
				if (pos_A != NULL ||
					pRectShapeA->GetPush())
				{
					// 素材状の左に
					pos_A->x = min_B.x - pRectShapeA->GetSize().x * 0.5f;
				}
				// 接触しているときはtrueを返す
				bCollision = true;
			}

			// 当たり判定(右)
			else if (min_A.x < max_B.x &&
				minOld_A.x >= max_B.x)
			{
				// 過去の位置情報AがNULLではないなら ||
				// 押し出し処理がありなら
				// ->押し出し処理
				if (pos_A != NULL ||
					pRectShapeA->GetPush())
				{
					// 素材状の左に
					pos_A->x = max_B.x + pRectShapeA->GetSize().x * 0.5f;
				}
				// 接触しているときはtrueを返す
				bCollision = true;
			}
		}
		// 素材のX範囲
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// 当たり判定(手前)
			if (max_A.z > min_B.z&&
				maxOld_A.z <= min_B.z)
			{
				// 過去の位置情報AがNULLではないなら ||
				// 押し出し処理がありなら
				// ->押し出し処理
				if (pos_A != NULL ||
					pRectShapeA->GetPush())
				{
					// 素材状の左に
					pos_A->z = min_B.z - pRectShapeA->GetSize().z * 0.5f;
				}
				// 接触しているときはtrueを返す
				bCollision = true;
			}

			// 当たり判定(奥)
			else if (min_A.z < max_B.z &&
				minOld_A.z >= max_B.z)
			{
				// 過去の位置情報AがNULLではないなら ||
				// 押し出し処理がありなら
				// ->押し出し処理
				if (pos_A != NULL ||
					pRectShapeA->GetPush())
				{
					// 素材状の左に
					pos_A->z = max_B.z +
						pRectShapeA->GetSize().z * 0.5f;
				}
				// 接触しているときはtrueを返す
				bCollision = true;
			}

		}
	}
	// 素材のZ範囲
	if (max_A.z > min_B.z&&
		min_A.z < max_B.z)
	{
		// 素材のX範囲
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// 当たり判定(下)
			if (max_A.y > min_B.y &&
				maxOld_A.y <= min_B.y)
			{
				// 過去の位置情報AがNULLではないなら ||
				// 押し出し処理がありなら
				// ->押し出し処理
				if (pos_A != NULL ||
					pRectShapeA->GetPush())
				{
					// 素材状の左に
					pos_A->y = min_B.y - pRectShapeA->GetSize().y;
				}
				// 接触しているときはtrueを返す
				bCollision = true;
			}

			// 当たり判定(上)
			else if (min_A.y < max_B.y&&
				minOld_A.y >= max_B.y)
			{
				// 過去の位置情報AがNULLではないなら ||
				// 押し出し処理がありなら
				// ->押し出し処理
				if (pos_A != NULL ||
					pRectShapeA->GetPush())
				{
					// 素材状の左に
					pos_A->y = max_B.y + 0.1f;
				}
				// 接触しているときはtrueを返す
				bCollision = true;
			}

		}
	}
	// 位置情報更新
	pRectShapeA->PassPos(D3DVECTOR3_ZERO);
	// 接触しているときはtrueを返す
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形と矩形の当たり判定
// pRectShapeA:矩形A
// pRectShapeB:矩形B
// pPos:位置ポインター(親元の位置)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndRect(
	CRectShape * pRectShapeA,		// 矩形A
	CRectShape * const pRectShapeB,	// 矩形B
	D3DXVECTOR3 * pPos				// 位置ポインター
)
{
	// 変数宣言
	bool bCollision = false;
	/*
	D3DXVECTOR3 const &min_A = pRectShapeA->GetMin();
	D3DXVECTOR3 const &min_B = pRectShapeB->GetMin();
	D3DXVECTOR3 const &max_A = pRectShapeA->GetMax();
	D3DXVECTOR3 const &max_B = pRectShapeB->GetMax();
	// 接触していないときはfalseを返す
	if (max_A.y > min_B.y &&
		min_A.y < max_B.y)
	{
		// 素材のZ範囲
		if (max_A.z > min_B.z&&
			min_A.z < max_B.z)
		{
			// 素材のZ範囲
			if (max_A.x > min_B.x&&
				min_A.x < max_B.x)
			{
				// 当たり判定(左)
				if (max_A.x > min_B.x)
				{
					// 素材状の左に
					pPos->x = min_B.x - pRectShapeA->GetSize().x * 0.6f;
					// 接触しているときはtrueを返す
					bCollision = true;
				}

				// 当たり判定(右)
				else if (min_A.x < max_B.x)
				{
					// 素材状の左に
					pPos->x = max_B.x + pRectShapeA->GetSize().x * 0.6f;
					// 接触しているときはtrueを返す
					bCollision = true;
				}
			}
		}
		// 素材のX範囲
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// 素材のX範囲
			if (max_A.z > min_B.z&&
				min_A.z < max_B.z)
			{

				// 当たり判定(手前)
				if (max_A.z > min_B.z)
				{
					// 素材状の左に
					pPos->z = min_B.z - pRectShapeA->GetSize().z * 0.6f;
					// 接触しているときはtrueを返す
					bCollision = true;
				}

				// 当たり判定(奥)
				else if (min_A.z < max_B.z)
				{
					// 素材状の左に
					pPos->z = max_B.z +
						pRectShapeA->GetSize().z * 0.6f + 0.1f;
					// 接触しているときはtrueを返す
					bCollision = true;
				}
			}
		}
	}
	// 素材のZ範囲
	if (max_A.z > min_B.z&&
		min_A.z < max_B.z)
	{
		// 素材のX範囲
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// 素材のX範囲
			if (max_A.y > min_B.y&&
				min_A.y < max_B.y)
			{
				// 当たり判定(下)
				if (max_A.y > min_B.y)
				{
					// 素材状の左に
					pPos->y = min_B.y - pRectShapeA->GetSize().y * 0.6f;
					// 接触しているときはtrueを返す
					bCollision = true;
				}

				// 当たり判定(上)
				else if (min_A.y < max_B.y)
				{
					// 素材状の左に
					pPos->y = max_B.y + pRectShapeA->GetSize().y * 0.6f;
					// 接触しているときはtrueを返す
					bCollision = true;
				}
			}
		}
	}
	// 当たり判定の更新
	pRectShapeA->PassPos(*pPos);
	*/


	// 接触していないときはfalseを返す
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形と球
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndSphere(CRectShape * const pRectShapeA, CSphereShape * const pSphereShapeB)
{
	// 変数宣言
	D3DXVECTOR3 ClosestPoint;	// ある座標の最も近い、ボックス上の座標
	D3DXVECTOR3 Pos_B;			// 位置
	// ポインター位置情報がある場合
	if (pSphereShapeB->Get_PPos() != NULL)
	{
		// 位置情報代入
		Pos_B = *pSphereShapeB->Get_PPos();
		// ある座標の最も近い、ボックス上の座標
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	// ない場合
	else
	{
		// 位置情報代入
		Pos_B = pSphereShapeB->Get_Pos();
		// ある座標の最も近い、ボックス上の座標
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	if (CCalculation::DiffPointSquare(Pos_B, ClosestPoint) <
		pSphereShapeB->GetRadius() * pSphereShapeB->GetRadius())
	{
		bool b = true;
	}
	// 距離が半径より短い場合true,それ以外falseを返す
	return
		CCalculation::DiffPointSquare(Pos_B,ClosestPoint) <
		pSphereShapeB->GetRadius() * pSphereShapeB->GetRadius();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形と球
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndSphere(CRectShape * const pRectShapeA, CSphereShape * const pSphereShapeB, D3DXVECTOR3 * pPos)
{
	// 変数宣言
	D3DXVECTOR3 ClosestPoint;	// ある座標の最も近い、ボックス上の座標
	D3DXVECTOR3 Pos_B;			// 位置
								// ポインター位置情報がある場合
	if (pSphereShapeB->Get_PPos() != NULL)
	{
		// 位置情報代入
		Pos_B = *pSphereShapeB->Get_PPos();
		// ある座標の最も近い、ボックス上の座標
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	// ない場合
	else
	{
		// 位置情報代入
		Pos_B = pSphereShapeB->Get_Pos();
		// ある座標の最も近い、ボックス上の座標
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	// 距離が半径より短い場合true,それ以外falseを返す
	return
		CCalculation::DiffPointSquare(Pos_B, ClosestPoint) <
		pSphereShapeB->GetRadius() * pSphereShapeB->GetRadius();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 矩形と円柱
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndColumn(CRectShape * const pRectShapeA, CColumnShape * const pColumnShapeB)
{
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 球と円柱
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SphereAndColumn(CSphereShape * const pSphereShapeA, CColumnShape * const pColumnShapeB)
{

	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 球と球
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SphereAndSphere(CSphereShape * const pSphereShapeA, CSphereShape * const pSphereShapeB)
{
	// 変数宣言
	D3DXVECTOR3 pos_A;
	D3DXVECTOR3 pos_B;
	// スフィアAのポイント位置情報がNULLではない場合
	// 位置情報代入
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_A = *pSphereShapeA->Get_PPos();
	}
	else
	{
		pos_A = pSphereShapeA->Get_Pos();
	}
	// スフィアBのポイント位置情報がNULLではない場合
	// 位置情報代入
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_B = *pSphereShapeB->Get_PPos();
	}
	else
	{
		pos_B = pSphereShapeB->Get_Pos();
	}

	return CCalculation::Collision_Sphere(
		pos_A + pSphereShapeA->GetOffset(),
		pSphereShapeA->GetRadius(),
		pos_B + pSphereShapeB->GetOffset(),
		pSphereShapeB->GetRadius()
	);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 球と球
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SphereAndSphere(CSphereShape * const pSphereShapeA, CSphereShape * const pSphereShapeB, D3DXVECTOR3 * pPos)
{
	// 変数宣言
	D3DXVECTOR3 pos_A;
	D3DXVECTOR3 pos_B;
	// スフィアAのポイント位置情報がNULLではない場合
	// 位置情報代入
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_A = *pSphereShapeA->Get_PPos();
	}
	else
	{
		pos_A = pSphereShapeA->Get_Pos();
	}
	// スフィアBのポイント位置情報がNULLではない場合
	// 位置情報代入
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_B = *pSphereShapeB->Get_PPos();
	}
	else
	{
		pos_B = pSphereShapeB->Get_Pos();
	}

	return CCalculation::Collision_Sphere(
		pos_A + pSphereShapeA->GetOffset(),
		pSphereShapeA->GetRadius(),
		pos_B + pSphereShapeB->GetOffset(),
		pSphereShapeB->GetRadius()
	);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 円柱と円柱
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::ColumnAndColumn(CColumnShape * const pColumnShapeA, CColumnShape * const pColumnShapeB)
{
	return false;
}
