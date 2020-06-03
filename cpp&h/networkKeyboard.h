// ----------------------------------------------------------------------------------------------------
//
// �l�b�g���[�N�L�[�{�[�h�̐���[networkKeyboard.h]
// Author : masayasu wakita
//
// ----------------------------------------------------------------------------------------------------
#ifndef _NETWORKKEYBOARD_H_
#define _NETWORKKEYBOARD_H_	 // �t�@�C������������߂�

// ----------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------
#include "network.h"

// ----------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------
class CNetworkKeyboard : public CNetwork
{
public:
	/* �֐� */
	CNetworkKeyboard();
	~CNetworkKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �L�[���͏��
	bool GetTriggerKeyboard(int nID, int nKey);				// �g���K�[��Ԃ��擾
	bool GetReleaseKeyboard(int nID, int nKey);				// ���s�[�g��Ԃ��擾
	bool GetPressKeyboard(int nID, int nKey);				// �v���X��Ԃ��擾

private:
	BYTE m_aKeyState[MAX_PLAYER][NUM_KEY_MAX] = {};				// �v���X���
	BYTE m_akeyStateTrigger[MAX_PLAYER][NUM_KEY_MAX] = {};		// �g���K�[���
	BYTE m_akeyStateUp[MAX_PLAYER][NUM_KEY_MAX] = {};			// �����[�X���
};
#endif // !_NETWORKKEYBOARD_H_