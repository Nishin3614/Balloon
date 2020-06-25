// ------------------------------------------
//
// �l�b�g���[�N�L�[�{�[�h���� [networkKeyboard.cpp]
// Author : masayasu wakita
//
// ------------------------------------------
#include "networkKeyboard.h"

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CNetworkKeyboard::CNetworkKeyboard()
{

}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CNetworkKeyboard::~CNetworkKeyboard()
{

}

// ------------------------------------------
// ������
// ------------------------------------------
HRESULT CNetworkKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	return S_OK;
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CNetworkKeyboard::Uninit(void)
{

}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CNetworkKeyboard::Update(void)
{
	//// �ϐ��錾
	//BYTE aKeyState[MAX_PLAYER][NUM_KEY_MAX] = {};	// �L�[�{�[�h�̓��͏��
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
	//		// �g���K�[�E�����[�X���̍쐬
	//		m_akeyStateTrigger[nCntPlayer][nCntKey] = (m_aKeyState[nCntPlayer][nCntKey] & aKeyState[nCntPlayer][nCntKey]) ^ aKeyState[nCntPlayer][nCntKey];
	//		m_akeyStateUp[nCntPlayer][nCntKey] = m_aKeyState[nCntPlayer][nCntKey] ^ (m_aKeyState[nCntPlayer][nCntKey] & aKeyState[nCntPlayer][nCntKey]);
	//		m_aKeyState[nCntPlayer][nCntKey] = aKeyState[nCntPlayer][nCntKey];	//�L�[�v���X���ۑ�
	//	}
	//}
}

// ------------------------------------------
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
// ------------------------------------------
bool CNetworkKeyboard::GetTriggerKeyboard(int nID, int nKey)
{
	return(m_akeyStateTrigger[nID][nKey] & 0x80) ? true : false;
}

// ------------------------------------------
// �L�[�{�[�h�̃����[�X��Ԃ��擾
// ------------------------------------------
bool CNetworkKeyboard::GetReleaseKeyboard(int nID, int nKey)
{
	return(m_akeyStateUp[nID][nKey] & 0x80) ? true : false;
}

// ------------------------------------------
// �L�[�{�[�h�̃v���X��Ԃ��擾
// ------------------------------------------
bool CNetworkKeyboard::GetPressKeyboard(int nID, int nKey)
{
	return(m_aKeyState[nID][nKey] & 0x80) ? true : false;
}