// ------------------------------------------
//
// マネージャー処理の説明[manager.h]
// Author : Koki Nishiyama
//
// ------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_	 // ファイル名を忌Tを決める

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
#define ONEPLAYER_STAGE		(5)
#define DOUBLEPLAYER_STAGE	(5)
#define DERAY_TIME(X)		(X * 60)
#define MAX_PLAYER			(4)

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CFade;		// 画面遷移
class CGame;		// ゲーム
class CTitle;		// タイトル
class CTutorial;	// チュートリアル
class CResult;		// リザルト
class CRanking;		// ランキング
class CNetwork;		// ネットワーク
class CSelect;		// 選択画面
class CLoadScreen;	// 読み込み画面

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
		MODE_SELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	} MODE;
	/* 関数 */
	CManager();
	~CManager();
	HRESULT  Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE const mode);							// モード設定
	static CRenderer * GetRenderer(void) { return m_renderer; };	// レンダリングの誌�ﾘ�
	static CKeyboard * GetKeyboard(void) { return m_keyboard; };	// キーボードの誌�ﾘ�
	static CJoypad * GetJoy(void) { return m_joypad; };				// ジョイパッドの誌�ﾘ�
	static CMouse * GetMouse(void) { return m_mouse; };				// マウスの誌�ﾘ�
	static CKeyConfig * GetKeyConfig(void) { return m_keyconfig; };	// キー詳細の誌�ﾘ�
	static CSound * GetSound(void) { return m_sound; };				// サウンドの誌�ﾘ�
	static CFade * GetFade(void) { return m_fade; };				// 画面遷移の誌�ﾘ�
	static CGame * GetGame(void) { return m_game; };				// ゲームの誌�ﾘ�
	static CLoadScreen * GetLoadScreen(void) { return m_pLoadScreen; };	// 読み込み画面取得
	static MODE GetMode(void) { return m_mode; };					// モードの誌�ﾘ�
	static CNetwork * GetNetwork(void) { return m_pNetwork; }		// ネットワークの誌�ﾘ�
	static CSelect * GetSelect(void) { return m_select; };			// 選択画面の誌�ﾘ�

	// プレイヤー番号の取得
	static int const &GetPlayerID(void) { return m_nPlayerID; };	// プレイヤー番号
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
	static CSelect * m_select;				// 選択画面
	static CLoadScreen * m_pLoadScreen;		// 読み込み画面
	static CResult * m_result;				// リザルト
	static CRanking * m_ranking;			// ランキング
	static CNetwork * m_pNetwork;			// ネットワーク

	static MODE m_mode;						// モード
	static bool	m_bWire;					// ワイヤーモード
	static int m_nPlayerID;					// プレイヤー番号
};

#endif // !_MANAGER_H_