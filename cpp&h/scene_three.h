// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3Dシーン処理の説明[scene_three.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SCENE_THREE_H_
#define _SCENE_THREE_H_	 // ファイル名を基準を決める

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CScene_THREE : public CScene
{
public:
	/* 列挙型 */
	typedef enum
	{
		OFFSET_TYPE_VERTICAL_CENTER = 0,	// オフセット縦の中心
		OFFSET_TYPE_VERTICAL_LEFT,			// オフセット縦の左から
		OFFSET_TYPE_VERTICAL_UNDER,			// オフセット縦の下から
		OFFSET_TYPE_SIDE_CENTER,			// オフセット横の中心から
		OFFSET_TYPE_MAX
	} OFFSET_TYPE;
	/* 関数 */
	CScene_THREE();
	~CScene_THREE();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 設定
	// 頂点座標
	void Set_Vtx_Pos(
		OFFSET_TYPE const &offsettype = OFFSET_TYPE_VERTICAL_CENTER,	// オフセットタイプ
		VERTEX_3D * pVtx = NULL											// 頂点情報
	);
	// 頂点カラー
	void Set_Vtx_Col(VERTEX_3D * pVtx = NULL);
	// サイズ
	void SetSize(D3DXVECTOR3 const &size)	{ m_size = size; };	
	// 位置
	void SetPos(D3DXVECTOR3 const &pos)		{ m_pos = pos; };	
	// 回転
	void SetRot(D3DXVECTOR3 const &rot)		{ m_rot = rot; };
	// 色
	void SetCol(D3DXCOLOR const &col)		{ m_col = col; };		
	// テクスチャー
	void SetTex(
		D3DXVECTOR2 const &first,									// 最短値
		D3DXVECTOR2 const &last										// 最長値
	);
	// テクスチャータイプ
	void SetTexType(
		int const & nTexType
	)
	{
		m_nTexType = nTexType;
	};
	// ビルボード状態
	void SetBillboard(bool const &bBillboard) 
		{ m_bBillboard = bBillboard; };	
	// Z軸状態
	void SetZEneble(bool const &bEneble)
	{
		m_bZEneble = bEneble;
	};
	// ライティング状態
	void SetLighting(bool const &bLight)
	{
		m_bLighting = bLight;
	};
	// αブレンド状態
	void SetAlphaBlend(bool const &bAlpha)
	{
		m_bAlpha = bAlpha;
	};
	// オフセットタイプ
	void SetOffsetType(OFFSET_TYPE const &type)
	{
		m_offsetType = type;
	};
	// 取得
	// サイズ
	D3DXVECTOR3 GetSize(void) const { return m_size; };		
	// 位置
	D3DXVECTOR3 GetPos(void) const	{ return m_pos; };		
	// 回転
	D3DXVECTOR3 GetRot(void) const	{ return m_rot; };	
	// テクスチャータイプ
	int const &GetTexType(void) const { return m_nTexType; };
	// シーン管理
	static CScene_THREE * Create(
		OFFSET_TYPE	const & type,									// タイプ
		D3DXVECTOR3 const & pos,									// 位置
		D3DXVECTOR3 const & size,									// サイズ
		int			const & nTexType,								// テクスチャータイプ
		D3DXVECTOR3	const & rot = D3DVECTOR3_ZERO,					// 角度
		bool		const & bBillboard = false,						// ビルボード
		bool		const & bZEneble = false,						// Zバッファ
		bool		const & bLighting = false,						// ライティング
		bool		const & bAlpha = false,							// アルファブレンド
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
	);

	// 個人管理
	static CScene_THREE * Create_Self(
		OFFSET_TYPE	const & type,									// タイプ
		D3DXVECTOR3 const & pos,									// 位置
		D3DXVECTOR3 const & size,									// サイズ
		int			const & nTexType,								// テクスチャータイプ
		D3DXVECTOR3	const & rot = D3DVECTOR3_ZERO,					// 角度
		bool		const & bBillboard = false,						// ビルボード
		bool		const & bZEneble = false,						// Zバッファ
		bool		const & bLighting = false,						// ライティング
		bool		const & bAlpha = false,							// アルファブレンド
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
	);
	// 個人管理
	static unique_ptr<CScene_THREE> Create_Uni(
		OFFSET_TYPE	const & type,									// タイプ
		D3DXVECTOR3 const & pos,									// 位置
		D3DXVECTOR3 const & size,									// サイズ
		int			const & nTexType,								// テクスチャータイプ
		D3DXVECTOR3	const & rot = D3DVECTOR3_ZERO,					// 角度
		bool		const & bBillboard = false,						// ビルボード
		bool		const & bZEneble = false,						// Zバッファ
		bool		const & bLighting = false,						// ライティング
		bool		const & bAlpha = false,							// アルファブレンド
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
	);

	float GetHeight(D3DXVECTOR3 pos);								// 高さ取得
protected:
private:
	/* 関数 */
	void Offset_Virtical_Center(VERTEX_3D *pVtx);					// オフセットが縦のセンター
	void Offset_Virtical_Left(VERTEX_3D *pVtx);						// オフセットが縦の左
	void Offset_Virtical_Under(VERTEX_3D *pVtx);					// オフセットが縦の下
	void Offset_Side_Center(VERTEX_3D *pVtx);						// オフセットが横のセンター
	/* 変数 */
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;												// 中心座標
	D3DXVECTOR3 m_OriginBlock;										// 初期配置
	D3DXVECTOR3 m_size;												// サイズ
	D3DXVECTOR3 m_rot;												// 角度
	D3DXMATRIX  m_mtxWorld;											// ワールドマトリックス
	D3DXCOLOR	m_col;												// カラー
	OFFSET_TYPE	m_offsetType;										// オフセットタイプ
	float m_fLengh;													// 長さ
	float m_fAngle;													// 角度
	bool m_bBillboard;												// ビルボード状態
	bool m_bZEneble;												// Z軸をなしにするかどうか
	bool m_bLighting;												// ライティングオンオフ
	bool m_bAlpha;													// αブレンド
	int m_nTexType;													// テクスチャータイプ
};

#endif