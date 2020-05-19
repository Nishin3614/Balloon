// ------------------------------------------
//
// ポーズヘッダー処理 [pause.h]
// Author : KOKI NISHIYAMA
//
// ------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// マクロ定義
//
// ------------------------------------------

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CPause_ui;
class CPause_bg;

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CPause
{
public:
	/* 関数 */
	CPause();
	~CPause();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SelfInit(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
protected:
private:
	unique_ptr<CPause_ui> m_uni_Pause_ui;	// ポーズUI
};
#endif
