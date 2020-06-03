// ----------------------------------------------------------------------------------------------------
//
// ネットワークキーボードの説明[networkKeyboard.h]
// Author : masayasu wakita
//
// ----------------------------------------------------------------------------------------------------
#ifndef _NETWORKKEYBOARD_H_
#define _NETWORKKEYBOARD_H_	 // ファイル名を基準を決める

// ----------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------
#include "network.h"

// ----------------------------------------------------------------------------------------------------
//
// クラス
//
// ----------------------------------------------------------------------------------------------------
class CNetworkKeyboard : public CNetwork
{
public:
	/* 関数 */
	CNetworkKeyboard();
	~CNetworkKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// キー入力情報
	bool GetTriggerKeyboard(int nID, int nKey);				// トリガー状態を取得
	bool GetReleaseKeyboard(int nID, int nKey);				// リピート状態を取得
	bool GetPressKeyboard(int nID, int nKey);				// プレス状態を取得

private:
	BYTE m_aKeyState[MAX_PLAYER][NUM_KEY_MAX] = {};				// プレス状態
	BYTE m_akeyStateTrigger[MAX_PLAYER][NUM_KEY_MAX] = {};		// トリガー状態
	BYTE m_akeyStateUp[MAX_PLAYER][NUM_KEY_MAX] = {};			// リリース状態
};
#endif // !_NETWORKKEYBOARD_H_