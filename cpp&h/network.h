// ----------------------------------------------------------------------------------------------------
//
// �l�b�g���[�N�̐���[network.h]
// Author : masayasu wakita
//
// ----------------------------------------------------------------------------------------------------
#ifndef _NETWORK_H_
#define _NETWORK_H_	 // �t�@�C������������߂�

// ----------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------
#include "main.h"
#include "keyboard.h"

// ----------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------
#define SCRIPT_NETWORK "network.ini"
#define MAX_PLAYER 4

typedef enum
{
	NUM_KEY_W = 0,
	NUM_KEY_A,
	NUM_KEY_S,
	NUM_KEY_D,
	NUM_KEY_SPACE,
	NUM_KEY_M
} NUM_KEY;

typedef enum
{
	SOCKETTYPE_CLIENT = 0,
	SOCKETTYPE_GAME,
	SOCKETTYPE_MAX
} SOCKETTYPE;

// ----------------------------------------------------------------------------------------------------
//
// �\���̒�`
//
// ----------------------------------------------------------------------------------------------------
typedef struct
{
	//int m_nId = -1;										// ID�ԍ�
	int m_aKeyState[NUM_KEY_M] = {};				// �L�[�{�[�h�̃v���X���
} PLAYERSTATE;

// ----------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------
class CNetwork
{
public:
	/* �֐� */
	CNetwork();
	~CNetwork();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static HRESULT LoadConfiguration(void);

	HRESULT Build(void);
	HRESULT Connect(void);

	PLAYERSTATE GetKeystate(void);

	bool SendTCP(const char* data, int nSize);
	bool SendUDP(const char* data, int nSize);
	bool DataRecv(SOCKETTYPE type, char* data, int nSize);

	bool KeyData(void);
	SOCKET GetSocket(void) { return m_sockClient; }
	bool GetPressKeyboard(int nId, int nKey);
	bool GetTriggerKeyboard(int nId, int nKey);
	int GetId(void) { return m_nId; }
	float GetRot(const int &nId) { return m_fRot[nId]; }

	void StartUpdate(void);
	void StopUpdate(void);

	static int ConvertDecimalToBinary(int nValue);

private:
	SOCKET createServerSocket(unsigned short port);
	static void ConvertStringToFloat(char* text,const char* delimiter, float* pResult);

	SOCKET m_sockClient;								// �\�P�b�g(�N���C�A���g)
	SOCKET m_sockClientToServer;						// �\�P�b�g(UDP���M�p)
	SOCKET m_sockServerToClient;						// �\�P�b�g(UDP��M�p)

	struct sockaddr_in m_addrServer;					// �\�P�b�g�A�h���X(�T�[�o)�̏��(TCP����M)
	struct sockaddr_in m_addrClientToServer;			// �L�[���M�p�\�P�b�g(UDP���M�p)

	PLAYERSTATE keystate;
	fd_set m_readfds;

	int m_nId;
	float m_fRot[MAX_PLAYER];

	static char aIp[32];				// IP�A�h���X
	static int nPort;					// �|�[�g�ԍ�

	std::thread m_th;
	bool m_bUpdate;
};
#endif // !_NETWORK_H_