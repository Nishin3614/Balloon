//=============================================================================
//
// タイトルの処理 [title.h]
// Author : Ryouma Inoue
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

#define TITLE_BG_X (600.0f)				// タイトル位置
#define TITLE_BG_Y (300.0f)				// タイトル位置
#define TITLE_SIZE_X (450.0f)			// タイトルサイズ
#define TITLE_SIZE_Y (250.0f)			// タイトルサイズ
#define TITLEUI_POS_X (600.0f)			// タイトルUI位置
#define TITLEUI_POS_Y (600.0f)			// タイトルUI位置
#define TITLEUI_SIZE_X (300.0f)			// タイトルUIサイズ
#define TITLEUI_SIZE_Y (100.0f)			// タイトルUIサイズ

#define RESULT_TITLEUI_POS_X (1000.0f)			// リザルト用タイトルUI位置
#define RESULT_TITLEUI_POS_Y (600.0f)			// リザルト用タイトルUI位置
#define RESULT_TITLEUI_SIZE_X (200.0f)			// リザルト用タイトルUIサイズ
#define RESULT_TITLEUI_SIZE_Y (100.0f)			// リザルト用タイトルUIサイズ

#define PLAYER_POS_X (20.0f)			// プレイヤーの位置
#define PLAYER_POS_Y (20.0f)			// プレイヤーの位置
#define TITLE_WALL_POS_X (330.0f)		// 壁の位置
#define TITLE_WALL_POS_Y (100.0f)		// 壁の位置
#define TITLE_WALLF_POS_Y (50.0f)		// 壁の位置
#define TITLE_WALL_POS_Z (500.0f)		// 壁の位置

//=============================================================================
// 前方宣言	( ポインタだけなら使える )
//=============================================================================
class	CTitleUI;

//=============================================================================
// 管理クラス
//=============================================================================
class CTitle
{
public:

	CTitle();													// コンストラクタ
	~CTitle();													// デストラクタ

	HRESULT Init();												// 初期化
	void	Uninit(void);										// 終了
	void	Update(void);										// 更新
	void	Draw(void);											// 描画

	static  CTitle		*Create(void);							// タイトルの生成

private:
	CTitleUI *m_pTitleUI;										// タイトルUIへのポインタ
};
#endif
