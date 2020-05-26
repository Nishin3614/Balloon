// ------------------------------------------
//
// マネージャー処理の説明[manager.h]
// Author : Koki Nishiyama
//
// ------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_	 // ファイル名を基準を決める

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
/* 基本 */
#include "main.h"
#include "Calculation.h"

/* 描画 */
#include "renderer.h"

/* 入力デバイス */
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "keyconfig.h"

/* サウンド */
#include "sound.h"

/* デバッグ表示 */
#include "debugproc.h"

// ------------------------------------------
//
// マクロ関数
//
// ------------------------------------------
#define ONEPLAYER_STAGE (5)
#define DOUBLEPLAYER_STAGE (5)
#define DERAY_TIME(X) (X * 60)

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CFade;		// 画面遷移
class CGame;		// ゲーム
class CTitle;		// タイトル
class CTutorial;	// チュートリアル

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CManager
{
public:
	/* 列挙型 */
	// モード
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_MAX
	} MODE;
	/* 関数 */
	CManager();
	~CManager();
	HRESULT  Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE const mode);								// モード設定
	static CRenderer * GetRenderer(void) { return m_renderer; };		// レンダリングの取得
	static CKeyboard * GetKeyboard(void) { return m_keyboard; };		// キーボードの取得
	static CJoypad * GetJoy(void) { return m_joypad; };		// ジョイパッドの取得
	static CMouse * GetMouse(void) { return m_mouse; };		// マウスの取得
	static CKeyConfig * GetKeyConfig(void) { return m_keyconfig; };	// キー詳細の取得
	static CSound * GetSound(void) { return m_sound; };		// サウンドの取得
	static CFade * GetFade(void) { return m_fade; };			// 画面遷移の取得
	static CGame * GetGame(void) { return m_game; };			// ゲームの取得
	static MODE GetMode(void) { return m_mode; };			// モードの取得
protected:

private:
	// ゲームに欠かせないもの
	static CRenderer * m_renderer;			// レンダリング
	static CSound * m_sound;				// サウンド

											// 入力デバイス
	static CKeyboard * m_keyboard;			// キーボード
	static CJoypad * m_joypad;				// ジョイパッド
	static CMouse * m_mouse;				// マウス
	static CKeyConfig * m_keyconfig;		// キー詳細

											// 画面
	static CFade * m_fade;					// 画面遷移
	static CTitle * m_title;				// タイトル
	static CTutorial * m_tutorial;			// チュートリアル
	static CGame * m_game;					// ゲーム

	static MODE m_mode;						// モード
	static bool	m_bWire;					// ワイヤーモード
};

#endif // !_MANAGER_H_