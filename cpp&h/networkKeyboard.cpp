// ------------------------------------------
//
// ネットワークキーボード処理 [networkKeyboard.cpp]
// Author : masayasu wakita
//
// ------------------------------------------
#include "networkKeyboard.h"

// ------------------------------------------
// コンストラクタ
// ------------------------------------------
CNetworkKeyboard::CNetworkKeyboard()
{

}

// ------------------------------------------
// デストラクタ
// ------------------------------------------
CNetworkKeyboard::~CNetworkKeyboard()
{

}

// ------------------------------------------
// 初期化
// ------------------------------------------
HRESULT CNetworkKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	return S_OK;
}

// ------------------------------------------
// 終了
// ------------------------------------------
void CNetworkKeyboard::Uninit(void)
{

}

// ------------------------------------------
// 更新
// ------------------------------------------
void CNetworkKeyboard::Update(void)
{
	//// 変数宣言
	//BYTE aKeyState[MAX_PLAYER][NUM_KEY_MAX] = {};	// キーボードの入力情報
	//KEYSTATE keystate = GetKeystate();

	//for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	//{
	//	*aKeyState[nCount] = *keystate.m_aKeyState[nCount];
	//}

	//int nCntKey;

	//for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	//{
	//	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	//	{
	//		// トリガー・リリース情報の作成
	//		m_akeyStateTrigger[nCntPlayer][nCntKey] = (m_aKeyState[nCntPlayer][nCntKey] & aKeyState[nCntPlayer][nCntKey]) ^ aKeyState[nCntPlayer][nCntKey];
	//		m_akeyStateUp[nCntPlayer][nCntKey] = m_aKeyState[nCntPlayer][nCntKey] ^ (m_aKeyState[nCntPlayer][nCntKey] & aKeyState[nCntPlayer][nCntKey]);
	//		m_aKeyState[nCntPlayer][nCntKey] = aKeyState[nCntPlayer][nCntKey];	//キープレス情報保存
	//	}
	//}
}

// ------------------------------------------
// キーボードのトリガー状態を取得
// ------------------------------------------
bool CNetworkKeyboard::GetTriggerKeyboard(int nID, int nKey)
{
	return(m_akeyStateTrigger[nID][nKey] & 0x80) ? true : false;
}

// ------------------------------------------
// キーボードのリリース状態を取得
// ------------------------------------------
bool CNetworkKeyboard::GetReleaseKeyboard(int nID, int nKey)
{
	return(m_akeyStateUp[nID][nKey] & 0x80) ? true : false;
}

// ------------------------------------------
// キーボードのプレス状態を取得
// ------------------------------------------
bool CNetworkKeyboard::GetPressKeyboard(int nID, int nKey)
{
	return(m_aKeyState[nID][nKey] & 0x80) ? true : false;
}