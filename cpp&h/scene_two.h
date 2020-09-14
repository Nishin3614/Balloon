// ----------------------------------------
//
// 2Dシーン処理の説明[scene_two.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _SCENE_TWO_H_
#define _SCENE_TWO_H_	 // ファイル名を基準を決める

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

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CScene_TWO : public CScene
{
public:
	/* 列挙型 */
	// オフセット
	typedef enum
	{
		OFFSET_TYPE_CENTER = 0,
		OFFSET_TYPE_LEFT,
		OFFSET_TYPE_MAX
	} OFFSET_TYPE;
	/* 関数 */
	CScene_TWO();
	~CScene_TWO();
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
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_OpponentCollision(
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

	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	// 頂点座標設定
	void Set_Vtx_Pos(
		OFFSET_TYPE const &offsettype = OFFSET_TYPE_CENTER,			// オフセットタイプ
		VERTEX_2D * pVtx = NULL										// 頂点情報
	);
	// 頂点カラー設定
	void Set_Vtx_Col(VERTEX_2D * pVtx = NULL);
	// 頂点カラー設定(右の色と左の色)
	void Set_Vtx_Col2(
		D3DXCOLOR const &col_r,		// 右の色
		D3DXCOLOR const &col_l,		// 左の色
		VERTEX_2D * pVtx = NULL);	// 2D頂点情報
									// 頂点カラー設定(上の色と下の色)
	void Set_Vtx_Col3(
		D3DXCOLOR const &col_o,		// 上の色
		D3DXCOLOR const &col_u,		// 下の色
		VERTEX_2D * pVtx = NULL);	// 2D頂点情報
	// オフセット設定
	void SetOffset(OFFSET_TYPE const &type) { m_offsetType = type; };
	// サイズ設定
	void SetSize(D3DXVECTOR2 const &size) { m_size = size; };
	// 位置設定
	void SetPosition(D3DXVECTOR3 const &pos) { m_pos = pos; };
	// 角度設定
	void SetRot(float const &frot) { m_rot = frot; };
	// 色設定
	void SetCol(
		D3DXCOLOR const &col) { m_col = col; };
	// テクスチャー設定
	void SetTex(
		D3DXVECTOR2 const &first = D3DXVECTOR2(0.0f,0.0f),			// 初期の配置
		D3DXVECTOR2 const &last = D3DXVECTOR2(1.0f, 1.0f)			// 最後の配置
	);
	void SetAnimation(float fTexX, float fTexY, float fTexY2, int nPatternAnim);					// アニメーションの設定
																									// テクスチャー設定
	void BindTexture(LPDIRECT3DTEXTURE9 const &p_Tex) { m_pTexture = p_Tex; };
	// サイズ取得
	D3DXVECTOR2 const GetSize(void) { return m_size; };
	// 位置取得
	D3DXVECTOR3 const GetPosition(void) { return m_pos; };
	// 色取得
	D3DXCOLOR const GetCol(void) { return m_col; };
	// 角度取得
	float const GetRot(void) { return m_rot; };
	// 長さ取得
	float const GetLengh(void) { return m_fLengh; };

	// 作成(シーン継承あり)
	static CScene_TWO * Create(
		OFFSET_TYPE	const & type,									// タイプ
		D3DXVECTOR3 const & pos,									// 位置
		D3DXVECTOR2 const & size,									// サイズ
		float		const & frot = 0.0f,							// 角度
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),	// 色
		CScene::LAYER	const & layer = CScene::LAYER_UI			// レイヤー
	);
	// 作成(シーン継承なし)
	static CScene_TWO * Create_Self(
		OFFSET_TYPE	const & type,									// タイプ
		D3DXVECTOR3 const & pos,									// 位置
		D3DXVECTOR2 const & size,									// サイズ
		float		const & frot = 0.0f,							// 角度
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
	);
	// unique_ptr作成(シーン継承なし)
	static std::unique_ptr<CScene_TWO> Creat_Unique(
		OFFSET_TYPE const & type,
		D3DXVECTOR3 const & pos,
		D3DXVECTOR2 const & size,
		float const & frot,
		D3DXCOLOR const & col
	);

protected:
	// 設定 //
private:
	/* 列挙型 */

	/* 構造体 */
	/* 関数 */
	void Offset_Center(VERTEX_2D *pVtx);	// オフセットがセンター
	void Offset_Left(VERTEX_2D *pVtx);		// オフセットが左

	/* 変数 */
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// 中心座標
	D3DXVECTOR2 m_size;						// サイズ
	D3DXCOLOR	m_col;						// カラー
	OFFSET_TYPE	m_offsetType;				// オフセットタイプ
	float m_rot;							// 角度
	float m_fLengh;							// 長さ
	float m_fAngle;							// 角度
};

#endif