// ----------------------------------------
//
// デバッグ用の当たり判定表示処理の説明[debugcollision.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _DEBUGCOLLISION_H_
#define _DEBUGCOLLISION_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define MAX_DEBUGCOLLISION (10)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CDebugcollision : public CScene
{
public:
	/* 列挙型 */
	typedef enum
	{
		COLLISIONTYPE_BOX = 0,
		COLLISIONTYPE_CICLE,
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;

	/* 関数 */
	CDebugcollision();
	~CDebugcollision();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 当たった後の処理
	// 引数1:オブジェクトタイプ
	// 引数2:相手のシーン情報
	virtual void Scene_Collision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	)
	{};
	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return m_ppos; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	static CDebugcollision * Create(
		D3DXVECTOR3 * pos,
		D3DXVECTOR3 * size,
		COLLISIONTYPE type
	);
protected:

private:
	void BoxCollision(void);


	D3DXVECTOR3 * m_ppos;
	D3DXVECTOR3 * m_size;
	COLLISIONTYPE m_type;
};

#endif