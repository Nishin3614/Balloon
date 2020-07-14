//=============================================================================
//
// �l�b�g���[�N���� [network.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "network.h"
#include "debugproc.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "game.h"

bool m_aKeyState[MAX_PLAYER][NUM_KEY_M] = {};				//�L�[�{�[�h�̓��͏�񃏁[�N
bool m_aKeyStateOld[MAX_PLAYER][NUM_KEY_M] = {};			// �O�̃L�[�{�[�h���͏�񃏁[�N
bool m_aKeyStateTrigger[MAX_PLAYER][NUM_KEY_M] = {};		// Trigger

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
char CNetwork::aIp[32] = {};
int CNetwork::nPort = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNetwork::CNetwork()
{
	m_nId = -1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNetwork::~CNetwork()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CNetwork::Init(void)
{
	HRESULT hr;
	hr = Build();					// �\�P�b�g�̐���
	char debug[256];

	OutputDebugString("�N���C�A���g�\�z����\n");

	int ans = ConvertDecimalToBinary(100);
	sprintf(debug, "ans = %d\n", ans);
	OutputDebugString(debug);

	ans = 100 & 15;
	sprintf(debug, "ans = %d\n", ans);
	OutputDebugString(debug);

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_fRot[nCount] = 0.0f;
	}

	m_bUpdate = false;

	return hr;
}

//=============================================================================
// �I��
//=============================================================================
void CNetwork::Uninit(void)
{
	//�\�P�b�g(�N���C�A���g)�̊J��
	closesocket(m_sockClient);
}

//=============================================================================
// �X�V  if ( setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (const char *),  sizeof(param) )
//=============================================================================
void CNetwork::Update(void)
{
	DWORD dwCurrentTime;		// ���ݎ���
	DWORD dwExecLastTime;		// �Ō�ɏ�����������
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		// �V�X�e���������~���b�P�ʂŎ擾

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();		// �V�X�e���������~���b�P�ʂŎ擾

	while (m_bUpdate)
	{
		// DirectX�̏���
		dwCurrentTime = timeGetTime();		// �V�X�e���������擾

		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))		// 1/60�b���ƂɎ��s
		{
			dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

			OutputDebugString("�X�V�J�n");

			char debug[1024];
			int nError = -1;
			float fData[NUM_KEY_M + 1 + 3];
			char cDie[32];

			char cDataText[128];		//����
			char cPlayerData[MAX_PLAYER][128];		//��r

			OutputDebugString("���M�J�n\n");
			KeyData();
			OutputDebugString("���M����\n");

			fd_set readfds;
			FD_ZERO(&readfds);
			FD_SET(m_sockServerToClient, &readfds);

			struct timeval tv;

			// �w�肵���b���Ń^�C���A�E�g�����܂�
			tv.tv_sec = 0;
			tv.tv_usec = 0;

			nError = select(0, &readfds, NULL, NULL, &tv);
			if (nError == 0)
			{
				OutputDebugString("�^�C���A�E�g\n");
				continue;
			}

			if (FD_ISSET(m_sockServerToClient, &readfds))
			{
				OutputDebugString("��M�J�n\n");
				nError = recv(m_sockServerToClient, debug, sizeof(debug), 0);
				OutputDebugString("��M����\n");
			}

			if (nError == SOCKET_ERROR)
			{
				// �\�P�b�g�̍쐬�Ɏ��s�����Ƃ�
				char aError[64];
				sprintf(aError, "�T�[�o�[�ɐڑ����s!!\n �G���[�R�[�h : %d", WSAGetLastError());
				MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
			}
			else
			{
				sscanf(debug, "%s %s %s %s %s", &cDie, &cPlayerData[0], &cPlayerData[1], &cPlayerData[2], &cPlayerData[3]);

				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{
					ConvertStringToFloat(cPlayerData[nCount], ",", fData);

					for (int nCntkey = 0; nCntkey < NUM_KEY_M; nCntkey++)
					{
						m_aKeyStateOld[nCount][nCntkey] = m_aKeyState[nCount][nCntkey];
					}

					for (int nCntKey = 0; nCntKey < NUM_KEY_M; nCntKey++)
					{
						m_aKeyState[nCount][nCntKey] = fData[nCntKey];
					}

					for (int nCntKey = 0; nCntKey < NUM_KEY_M; nCntKey++)
					{
						m_aKeyStateTrigger[nCount][nCntKey] = (m_aKeyStateOld[nCount][nCntKey] ^ m_aKeyState[nCount][nCntKey]) & m_aKeyState[nCount][nCntKey];
					}
					m_fRot[nCount] = fData[NUM_KEY_M];

					m_playerPos[nCount] = D3DXVECTOR3(fData[NUM_KEY_M + 1], fData[NUM_KEY_M + 2], fData[NUM_KEY_M + 3]);
				}
			}
		}
	}
}

//=============================================================================
// �l�b�g���[�N�̐ݒ�f�[�^�ǂݍ���
//=============================================================================
HRESULT CNetwork::LoadConfiguration(void)
{
	FILE *pFile;
	char cReadText[128];		//����
	char cHeadText[128];		//��r
	char cDie[128];

	//�e�L�X�g�f�[�^���[�h
	pFile = fopen(SCRIPT_NETWORK, "r");

	if (pFile != NULL)
	{
		//�X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}

		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				//���s
				if (strcmp(cReadText, "\n") != 0)
				{
					if (strcmp(cHeadText, "IP") == 0)
					{//�p�[�c�����̂Ƃ�
						sscanf(cReadText, "%s %s %s", &cDie, &cDie, aIp);					//�p�[�c�̐����擾
					}
					else if (strcmp(cHeadText, "PORT") == 0)
					{//�p�[�c���f���̃A�h���X���̂Ƃ�
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nPort);					//�p�[�c�̐����擾
					}
				}
			}
		}

		//�t�@�C����
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "�l�b�g���[�N�̐ݒ�f�[�^�Ǎ����s�I", "�x���I", MB_ICONWARNING);
	}

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̓��͏�Ԃ̎擾
//=============================================================================
PLAYERSTATE CNetwork::GetKeystate(void)
{
	return keystate;
}

//=============================================================================
// ���M(TCP)
//=============================================================================
bool CNetwork::SendTCP(const char *data, int nSize)
{
	int nError;

	//�N���C�A���g�փf�[�^(ID)���M
	nError = send(m_sockClient, data, nSize, 0);
	if (nError < 0)
	{
		printf("���M�G���[ : %d\n", WSAGetLastError());
	}

	return false;
}

//=============================================================================
// ���M(UDP)
//=============================================================================
bool CNetwork::SendUDP(const char *data, int nSize)
{
	int nError;

	//�N���C�A���g�փf�[�^(ID)���M
	nError = sendto(m_sockClientToServer, data, nSize, 0, (struct sockaddr *)&m_addrClientToServer, sizeof(m_addrClientToServer));
	if (nError == SOCKET_ERROR)
	{
		char aError[256];
		memset(&aError, 0, sizeof(aError));
		sprintf(aError, "���M�G���[ : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
	}

	return false;
}

//=============================================================================
// ��M
//=============================================================================
bool CNetwork::DataRecv(SOCKETTYPE type, char *data, int nSize)
{
	int nError;
	char aError[256];

	switch (type)
	{
	case SOCKETTYPE_CLIENT:
		//�N���C�A���g�փf�[�^(ID)���M
		nError = recv(m_sockClient, data, nSize, 0);
		break;
	case SOCKETTYPE_GAME:
		//�N���C�A���g�փf�[�^(ID)���M
		nError = recv(m_sockClientToServer, data, nSize, 0);
		break;
	}

	if (nError < 0)
	{
		sprintf(aError, "��M�G���[ : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
		return false;
	}
	return false;
}

//=============================================================================
// �N���C�A���g�\�P�b�g�̍쐬
//=============================================================================
HRESULT CNetwork::Build(void)
{
	WSADATA wsaData;								//winsock�̏��
	int nError;										//�G���[�擾

	//winsock�̏�����
	nError = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (nError != 0)
	{
		switch (nError)
		{
		case WSASYSNOTREADY:
			MessageBox(NULL, "�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��܂���!", "�x���I", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAVERNOTSUPPORTED:
			MessageBox(NULL, "�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��܂���I", "�x���I", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAEINPROGRESS:
			MessageBox(NULL, "�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă��܂��I", "�x���I", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAEPROCLIM:
			MessageBox(NULL, "winsock�������ł���ő�v���Z�X���ɒB���܂����I", "�x���I", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAEFAULT:
			MessageBox(NULL, "�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂���܂���I", "�x���I", MB_ICONWARNING);
			return E_FAIL;
			break;
		}
	}

	// �\�P�b�g�쐬
	m_sockClient = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockClient == INVALID_SOCKET)
	{// �\�P�b�g�̍쐬�Ɏ��s�����Ƃ�
		char aError[64];
		sprintf(aError, "�\�P�b�g�̐����Ɏ��s!!\n �G���[�R�[�h : %d", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �\�P�b�g�쐬
	m_sockClientToServer = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sockClientToServer == INVALID_SOCKET)
	{// �\�P�b�g�̍쐬�Ɏ��s�����Ƃ�
		char aError[64];
		sprintf(aError, "�\�P�b�g�̐����Ɏ��s!!\n �G���[�R�[�h : %d", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	//�\�P�b�g�̐ݒ�
	m_addrServer.sin_family = AF_INET;
	m_addrServer.sin_port = htons(12345);
	m_addrServer.sin_addr.S_un.S_addr = inet_addr(aIp);

	bind(m_sockClientToServer, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));

	m_addrClientToServer.sin_family = AF_INET;
	m_addrClientToServer.sin_port = htons(10032);
	m_addrClientToServer.sin_addr.S_un.S_addr = inet_addr(aIp);

	// �\�P�b�g�쐬
	m_sockServerToClient = createServerSocket(nPort);

	return S_OK;
}

//=============================================================================
// �R�l�N�g
//=============================================================================
HRESULT CNetwork::Connect(void)
{
	int val = -1;
	char debug[256];

	//�T�[�o�ɐڑ�
	val = connect(m_sockClient, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));
	if (val == SOCKET_ERROR)
	{
		char aError[64];
		sprintf(aError, "�l�b�g���[�N�G���[!\nerror : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "�x��!", MB_ICONWARNING);
		return E_FAIL;
	}

	SendTCP("LOAD_ID", sizeof("LOAD_ID"));
	DataRecv(SOCKETTYPE_CLIENT, (char*)&m_nId, sizeof(int));

	sprintf(debug, "ID = %d\n", m_nId);
	OutputDebugString(debug);
	OutputDebugString("�T�[�o�Ƃ̐ڑ�����\n");
	return S_OK;
}

//=============================================================================
// �L�[�f�[�^
//=============================================================================
bool CNetwork::KeyData(void)
{
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CRenderer *pRenderer = CManager::GetRenderer();
	CCamera *pCamera = pRenderer->GetCamera();
	CPlayer *pPlayer = CGame::GetPlayer(m_nId);
	PLAYERSTATE state;

	D3DXVECTOR3 pos = pPlayer->GetPos();

	if (pPlayer != NULL)
	{
		if (pCamera != NULL)
		{
			D3DXVECTOR3 rot = pCamera->GetRot();

			memset(&state, 0, sizeof(PLAYERSTATE));
			CNetwork *pNetwork = CManager::GetNetwork();

			if (pKeyboard != NULL)
			{
				if (pNetwork != NULL)
				{
					char data[1024];

					sprintf(data, "SAVE_KEY %d %d %d %d %d %d %f %f %f %f", m_nId, pKeyboard->GetKeyboardPress(DIK_W), pKeyboard->GetKeyboardPress(DIK_A),
						pKeyboard->GetKeyboardPress(DIK_S), pKeyboard->GetKeyboardPress(DIK_D), pKeyboard->GetKeyboardPress(DIK_SPACE),		// �L�[���͏��
						rot.y,						// ��]
						pos.x, pos.y, pos.z);		// �ʒu
					pNetwork->SendUDP(data, sizeof("SAVE_KEY") + 1024);
				}
			}
		}
	}

	return false;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԏ擾
//=============================================================================
bool CNetwork::GetPressKeyboard(int nId, int nKey)
{
	return m_aKeyState[nId][nKey];
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԏ擾
//=============================================================================
bool CNetwork::GetTriggerKeyboard(int nId, int nKey)
{
	return m_aKeyStateTrigger[nId][nKey];
}

//=============================================================================
// �T�[�o�[�\�P�b�g���쐬����
//=============================================================================
SOCKET CNetwork::createServerSocket(unsigned short port)
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == SOCKET_ERROR)
	{// �\�P�b�g�̍쐬�Ɏ��s�����Ƃ�
		char aError[64];
		sprintf(aError, "�\�P�b�g�̐����Ɏ��s!!\n �G���[�R�[�h : %d", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
		return sock;
	}

	struct sockaddr_in adr;

	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	adr.sin_addr.S_un.S_addr = INADDR_ANY;  // �T�[�o���Ŋ��蓖�Ă��Ă��� IP �������Őݒ�

	if (SOCKET_ERROR == bind(sock, (struct sockaddr *)&adr, sizeof(adr)))
	{
		char aError[64];
		sprintf(aError, "�\�P�b�g�̐����Ɏ��s!!\n �G���[�R�[�h : %d", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
		return sock;
	}

	return sock;
}

//=============================================================================
// �`���ϊ�(float)�֐�
//=============================================================================
void CNetwork::ConvertStringToFloat(char* text, const char* delimiter, float* pResult)
{
	char* tp;
	char* ctx;
	int nTemp = 1;

	tp = strtok_s(text, delimiter, &ctx);
	pResult[0] = (float)atof(tp);

	while (tp = strtok_s(NULL, ",", &ctx))
	{
		pResult[nTemp++] = (float)atof(tp);
	}
}

//=============================================================================
// �X�V�J�n
//=============================================================================
void CNetwork::StartUpdate(void)
{
	if (!m_bUpdate)
	{// �X�V�t���O���܂�Ă����Ƃ�
		// �}���`�X���b�h�ɂčX�V�J�n
		m_bUpdate = true;								// �X�V�t���O�𗧂Ă�
		m_th = std::thread(&CNetwork::Update, this);	// �X���b�h�̍쐬
		m_th.detach();									// �X���b�h�̊Ǘ���؂藣��
	}
}

//=============================================================================
// �X�V��~
//=============================================================================
void CNetwork::StopUpdate(void)
{
	if (m_bUpdate)
	{// �X�V�t���O�������Ă�����
		m_bUpdate = false;
	}
}

//=============================================================================
// 2�i���ϊ�
//=============================================================================
int CNetwork::ConvertDecimalToBinary(int nValue) {
	int ans = 0;
	for (int nCount = 0; nValue > 0; nCount++)
	{
		ans = ans + (nValue % 2)*pow(10, nCount);
		nValue = nValue / 2;
	}
	return ans;
}