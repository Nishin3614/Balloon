// ------------------------------------------
//
// ƒ}ƒl[ƒWƒƒ[ˆ—‚Ìà–¾[manager.h]
// Author : Koki Nishiyama
//
// ------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_	 // ƒtƒ@ƒCƒ‹–¼‚ğŠõT‚ğŒˆ‚ß‚é

// ------------------------------------------
//
// ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
//
// ------------------------------------------
/* Šî–{ */
#include "main.h"
#include "Calculation.h"

/* •`‰æ */
#include "renderer.h"

/* “ü—ÍƒfƒoƒCƒX */
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "keyconfig.h"

/* ƒTƒEƒ“ƒh */
#include "sound.h"

/* ƒfƒoƒbƒO•\¦ */
#include "debugproc.h"

// ------------------------------------------
//
// ƒ}ƒNƒŠÖ”
//
// ------------------------------------------
#define ONEPLAYER_STAGE		(5)
#define DOUBLEPLAYER_STAGE	(5)
#define DERAY_TIME(X)		(X * 60)
#define MAX_PLAYER			(4)

// ------------------------------------------
//
// ‘O•ûéŒ¾
//
// ------------------------------------------
class CFade;		// ‰æ–Ê‘JˆÚ
class CGame;		// ƒQ[ƒ€
class CTitle;		// ƒ^ƒCƒgƒ‹
class CTutorial;	// ƒ`ƒ…[ƒgƒŠƒAƒ‹
class CResult;		// ƒŠƒUƒ‹ƒg
class CRanking;		// ƒ‰ƒ“ƒLƒ“ƒO
class CNetwork;		// ƒlƒbƒgƒ[ƒN
class CSelect;		// ‘I‘ğ‰æ–Ê
class CLoadScreen;	// “Ç‚İ‚İ‰æ–Ê

// ------------------------------------------
//
// ƒNƒ‰ƒX
//
// ------------------------------------------
class CManager
{
public:
	/* —ñ‹“Œ^ */
	// ƒ‚[ƒh
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
	/* ŠÖ” */
	CManager();
	~CManager();
	HRESULT  Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE const mode);							// ƒ‚[ƒhİ’è
	static CRenderer * GetRenderer(void) { return m_renderer; };	// ƒŒƒ“ƒ_ƒŠƒ“ƒO‚ÌûØ€
	static CKeyboard * GetKeyboard(void) { return m_keyboard; };	// ƒL[ƒ{[ƒh‚ÌûØ€
	static CJoypad * GetJoy(void) { return m_joypad; };				// ƒWƒ‡ƒCƒpƒbƒh‚ÌûØ€
	static CMouse * GetMouse(void) { return m_mouse; };				// ƒ}ƒEƒX‚ÌûØ€
	static CKeyConfig * GetKeyConfig(void) { return m_keyconfig; };	// ƒL[Ú×‚ÌûØ€
	static CSound * GetSound(void) { return m_sound; };				// ƒTƒEƒ“ƒh‚ÌûØ€
	static CFade * GetFade(void) { return m_fade; };				// ‰æ–Ê‘JˆÚ‚ÌûØ€
	static CGame * GetGame(void) { return m_game; };				// ƒQ[ƒ€‚ÌûØ€
	static CLoadScreen * GetLoadScreen(void) { return m_pLoadScreen; };	// “Ç‚İ‚İ‰æ–Êæ“¾
	static MODE GetMode(void) { return m_mode; };					// ƒ‚[ƒh‚ÌûØ€
	static CNetwork * GetNetwork(void) { return m_pNetwork; }		// ƒlƒbƒgƒ[ƒN‚ÌûØ€
	static CSelect * GetSelect(void) { return m_select; };			// ‘I‘ğ‰æ–Ê‚ÌûØ€

	// ƒvƒŒƒCƒ„[”Ô†‚Ìæ“¾
	static int const &GetPlayerID(void) { return m_nPlayerID; };	// ƒvƒŒƒCƒ„[”Ô†
protected:

private:
	// ƒQ[ƒ€‚ÉŒ‡‚©‚¹‚È‚¢‚à‚Ì
	static CRenderer * m_renderer;			// ƒŒƒ“ƒ_ƒŠƒ“ƒO
	static CSound * m_sound;				// ƒTƒEƒ“ƒh

											// “ü—ÍƒfƒoƒCƒX
	static CKeyboard * m_keyboard;			// ƒL[ƒ{[ƒh
	static CJoypad * m_joypad;				// ƒWƒ‡ƒCƒpƒbƒh
	static CMouse * m_mouse;				// ƒ}ƒEƒX
	static CKeyConfig * m_keyconfig;		// ƒL[Ú×

	// ‰æ–Ê
	static CFade * m_fade;					// ‰æ–Ê‘JˆÚ
	static CTitle * m_title;				// ƒ^ƒCƒgƒ‹
	static CTutorial * m_tutorial;			// ƒ`ƒ…[ƒgƒŠƒAƒ‹
	static CGame * m_game;					// ƒQ[ƒ€
	static CSelect * m_select;				// ‘I‘ğ‰æ–Ê
	static CLoadScreen * m_pLoadScreen;		// “Ç‚İ‚İ‰æ–Ê
	static CResult * m_result;				// ƒŠƒUƒ‹ƒg
	static CRanking * m_ranking;			// ƒ‰ƒ“ƒLƒ“ƒO
	static CNetwork * m_pNetwork;			// ƒlƒbƒgƒ[ƒN

	static MODE m_mode;						// ƒ‚[ƒh
	static bool	m_bWire;					// ƒƒCƒ„[ƒ‚[ƒh
	static int m_nPlayerID;					// ƒvƒŒƒCƒ„[”Ô†
};

#endif // !_MANAGER_H_