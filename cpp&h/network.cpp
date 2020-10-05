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
#include "joypad.h"
#include "score.h"
#include "fade.h"
#include "thunder.h"
#include "balloon_group.h"
#include "item.h"
#include "scoreUP.h"
#include "collision.h"
#include "PointCircle.h"
#include "select.h"
#include "BalloonNum.h"
#include "charRanking.h"

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
	m_bTimeout = false;

	m_selectBalloon.bCreate = false;
	m_selectBalloon.nId = -1;
	m_selectBalloon.nType = -1;

	// �����t���O�̏�����
	m_thunderEvent.bCreate = false;
	m_pointcircleEvent.bCreate = false;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_selectState[nCount].bReady = false;
		m_selectState[nCount].nType = -1;
		m_selectState[nCount].pBalloonNum = NULL;
	}
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

	OutputDebugString("�N���C�A���g�\�z����\n");

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_fRot[nCount] = 0.0f;
		m_bDie[nCount] = false;
		m_samplePos[nCount] = D3DXVECTOR3(250.0f * (nCount + 1), 600.0f, 0.0f);
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
	CloseTCP();

	// winsock2 �̏I������
	WSACleanup();
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

			int nError = -1;

			KeyData();

			fd_set readfds;
			FD_ZERO(&readfds);
			FD_SET(m_sockServerToClient, &readfds);
			FD_SET(m_sockClient, &readfds);

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

			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (FD_ISSET(m_sockServerToClient, &readfds))
				{// ��M
					// �L�[���͏��̍X�V
					UpdateUDP();
				}
			}

			if (FD_ISSET(m_sockClient, &readfds))
			{// ��M
				// �T�[�o�[�R�}���h�̍X�V
				UpdateTCP();
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
		//�T�[�o�[����f�[�^��M
		nError = recv(m_sockClient, data, nSize, 0);
		break;
	case SOCKETTYPE_GAME:
		//�T�[�o�[����f�[�^��M
		nError = recv(m_sockClientToServer, data, nSize, 0);
		break;
	}

	if (nError < 0)
	{
		sprintf(aError, "��M�G���[ : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
		return false;
	}

	return true;
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
	unsigned int nStartTime = 0;
	SOCKET sock;

	// �\�P�b�g�̏�����
	sock = socket(AF_INET, SOCK_STREAM, 0);

	//�T�[�o�ɐڑ�
	val = connect(sock, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));
	if (val == SOCKET_ERROR)
	{
		char aError[64];
		sprintf(aError, "�l�b�g���[�N�G���[!\nerror : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "�x��!", MB_ICONWARNING);
		return E_FAIL;
	}

	m_sockClient = sock;

	// ID�̎擾
	SendTCP("LOAD_ID", sizeof("LOAD_ID"));
	if (!DataRecv(SOCKETTYPE_CLIENT, (char*)&m_nId, sizeof(int)))
	{
		return E_FAIL;
	}

	// �V�[�h�l�̎擾
	SendTCP("SEED", sizeof("SEED"));
	if (!DataRecv(SOCKETTYPE_CLIENT, (char*)&nStartTime, sizeof(nStartTime)))
	{
		return E_FAIL;
	}

	srand(nStartTime);				// �����̎��ݒ�

#ifdef _DEBUG
	char debug[256];
	sprintf(debug, "ID = %d\n", m_nId);
	OutputDebugString(debug);
	sprintf(debug, "SEED = %d\n", nStartTime);
	OutputDebugString(debug);
#endif // _DEBUG

	StartUpdate();
	return S_OK;
}

//=============================================================================
// �L�[�f�[�^
//=============================================================================
bool CNetwork::KeyData(void)
{
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CJoypad *pJoypad = CManager::GetJoy();
	CRenderer *pRenderer = CManager::GetRenderer();
	CCamera *pCamera = pRenderer->GetCamera();
	CPlayer *pPlayer = CGame::GetPlayer(m_nId);
	CGame *pGame = CManager::GetGame();
	CScore *pScore = pGame->GetScore();
	PLAYERSTATE state;
	memset(&state, 0, sizeof(PLAYERSTATE));
	CNetwork *pNetwork = CManager::GetNetwork();
	int stick_H, stick_V;

	if (pPlayer == NULL)
	{
		return false;
	}

	if (pCamera == NULL)
	{
		return false;
	}

	if (pKeyboard == NULL)
	{
		return false;
	}

	if (pGame == NULL)
	{
		return false;
	}

	if (pScore == NULL)
	{
		return false;
	}

	if (pJoypad == NULL)
	{
		stick_H = 0;
		stick_V = 0;
	}

	D3DXVECTOR3 pos = pPlayer->GetPos();

	if (pNetwork != NULL)
	{
		D3DXVECTOR3 rot = CGame::GetPlayer(m_nId)->GetRotDest();

		char data[1024];
		bool aKeyState[NUM_KEY_M] = {};

		if (pJoypad != NULL)
		{
			pJoypad->GetStickLeft(0, stick_H, stick_V);

			if (pKeyboard->GetKeyboardPress(DIK_SPACE) || pJoypad->GetPress(0, CJoypad::KEY_A) || pJoypad->GetPress(0, CJoypad::KEY_X))
			{
				aKeyState[NUM_KEY_SPACE] = true;
			}
		}
		else
		{
			if (pKeyboard->GetKeyboardPress(DIK_SPACE))
			{
				aKeyState[NUM_KEY_SPACE] = true;
			}
		}

		int nScore;
		nScore = pScore->GetNowScore();

		// ID, W�L�[, A�L�[, S�L�[, D�L�[, SPACE�L�[, �X�e�B�b�NH, �X�e�B�b�NV, ��]���, �ʒuX, �ʒuY, �ʒuZ, �X�R�A
		sprintf(data, "SAVE_KEY %d %d %d %d %d %d %d %d %f %f %f %f %d", m_nId, pKeyboard->GetKeyboardPress(DIK_W), pKeyboard->GetKeyboardPress(DIK_A),
			pKeyboard->GetKeyboardPress(DIK_S), pKeyboard->GetKeyboardPress(DIK_D), aKeyState[NUM_KEY_SPACE],		// �L�[���͏��
			stick_H,					// �X�e�B�b�NH
			stick_V,					// �X�e�B�b�NV
			rot.y,						// ��]
			pos.x, pos.y, pos.z,		// �ʒu
			nScore						// �X�R�A
		);
		pNetwork->SendUDP(data, sizeof("SAVE_KEY") + 1024);
	}

	return true;
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
// �L�����N�^�[���g�p�\���ǂ���
//=============================================================================
bool CNetwork::CheckCharacterReady(int nIndex)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_selectState[nCount].bReady)
		{
			if (m_selectState[nCount].nType == nIndex)
			{
				return false;
			}
		}
	}
	return true;
}

//=============================================================================
// �N���G�C�g����
//=============================================================================
void CNetwork::Create(void)
{
	if (m_thunderEvent.bCreate)
	{// ���T�[�N���쐬����
		CThunder::Create(m_thunderEvent.pos, D3DXVECTOR3(100.0f, 500.0f, 0.0f));
		m_thunderEvent.bCreate = false;
	}
	if (m_pointcircleEvent.bCreate)
	{// �|�C���g�T�[�N���쐬����
		CPointCircle::Create(m_pointcircleEvent.pos, D3DXVECTOR3(100.0f, 500.0f, 0.0f));
		m_pointcircleEvent.bCreate = false;
	}

	if (m_selectBalloon.bCreate)
	{
		if (m_selectState[m_selectBalloon.nId].pBalloonNum == NULL)
		{// �I�𒆃v���C���[�\��UI�����݂��Ă��Ȃ��Ƃ�
		 // UI�̍쐬
			m_selectState[m_selectBalloon.nId].pBalloonNum = CBalloonNum::Create(m_selectBalloon.nId);

			if (m_selectState[m_selectBalloon.nId].pBalloonNum != NULL)
			{
				m_selectState[m_selectBalloon.nId].pBalloonNum->SetPosition(m_samplePos[m_selectBalloon.nType]);
				m_selectState[m_selectBalloon.nId].pBalloonNum->Init();
			}
		}
		else
		{// �I�𒆃v���C���[�\��UI�����݂��Ă����Ƃ�
			m_selectState[m_selectBalloon.nId].pBalloonNum->Release();		// �J������
			m_selectState[m_selectBalloon.nId].pBalloonNum = NULL;

			// UI�̍쐬
			m_selectState[m_selectBalloon.nId].pBalloonNum = CBalloonNum::Create(m_selectBalloon.nId);

			if (m_selectState[m_selectBalloon.nId].pBalloonNum != NULL)
			{
				m_selectState[m_selectBalloon.nId].pBalloonNum->SetPosition(m_samplePos[m_selectBalloon.nType]);
				m_selectState[m_selectBalloon.nId].pBalloonNum->Init();
			}
		}

		m_selectBalloon.bCreate = false;
	}
}

//=============================================================================
// �R�C���̃f�[�^�x�[�X�����Z�b�g
//=============================================================================
void CNetwork::ResetCoin(void)
{
	for (int nCount = 0; nCount < MAX_COIN; nCount++)
	{
		m_apItem[nCount] = CItem::Create(nCount, D3DXVECTOR3(0.0f, -1000.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

		if (m_apItem[nCount] != NULL)
		{
			m_apItem[nCount]->SetDrawState(false);
		}
	}
}

//=============================================================================
// �L�����N�^�[�I����Ԃ̍X�V
//=============================================================================
void CNetwork::UpdateCharacterState(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	char aData[256], aDie[64];
	int nType[MAX_PLAYER];
	memset(&aData, 0, sizeof(aData));

	if (pNetwork != NULL)
	{
		pNetwork->SendTCP("CHARACTERSELECT_STATE", sizeof("CHARACTERSELECT_STATE"));
		if (!pNetwork->DataRecv(SOCKETTYPE_CLIENT, aData, sizeof(aData)))
		{
			return;
		}

		sscanf(aData, "%s %d %d %d %d", &aDie , &nType[0], &nType[1], &nType[2], &nType[3]);

		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (nType[nCount] == -1)
			{
				continue;
			}

			m_selectState[nCount].bReady = true;
			m_selectState[nCount].nType = nType[nCount];

			if (m_selectState[nCount].pBalloonNum == NULL)
			{// �I�𒆃v���C���[�\��UI�����݂��Ă��Ȃ��Ƃ�
			 // UI�̍쐬
				m_selectState[nCount].pBalloonNum = CBalloonNum::Create(nCount);

				if (m_selectState[nCount].pBalloonNum != NULL)
				{
					m_selectState[nCount].pBalloonNum->SetPosition(m_samplePos[nType[nCount]]);
					m_selectState[nCount].pBalloonNum->Init();
				}
			}
		}
	}
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
// UDP���瑗���Ă�����̐���(�L�[���)
//=============================================================================
bool CNetwork::UpdateUDP(void)
{
	char aData[1024];
	float fData[RECVDATA_MAX];
	char cPlayerData[MAX_PLAYER][128];		//��r
	char cDie[32];

	int nError = -1;
	nError = recv(m_sockServerToClient, aData, sizeof(aData), 0);

	if (nError == SOCKET_ERROR)
	{
		// �\�P�b�g�̍쐬�Ɏ��s�����Ƃ�
		char aError[64];
		sprintf(aError, "�T�[�o�[�ɐڑ����s!!\n �G���[�R�[�h : %d", WSAGetLastError());
		MessageBox(NULL, aError, "�x���I", MB_ICONWARNING);
	}
	else
	{
		sscanf(aData, "%s %s %s %s %s", &cDie, &cPlayerData[0], &cPlayerData[1], &cPlayerData[2], &cPlayerData[3]);

		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			ConvertStringToFloat(cPlayerData[nCount], ",", fData);

			for (int nCntkey = 0; nCntkey < NUM_KEY_M; nCntkey++)
			{
				m_aKeyStateOld[nCount][nCntkey] = m_aKeyState[nCount][nCntkey];
			}

			for (int nCntKey = 0; nCntKey < NUM_KEY_M; nCntKey++)
			{
				//m_aKeyState[nCount][nCntKey] = fData[nCntKey];
				m_aKeyState[nCount][nCntKey] = (fData[nCntKey] == 0) ? true : false;
			}

			for (int nCntKey = 0; nCntKey < NUM_KEY_M; nCntKey++)
			{
				m_aKeyStateTrigger[nCount][nCntKey] = (m_aKeyStateOld[nCount][nCntKey] ^ m_aKeyState[nCount][nCntKey]) & m_aKeyState[nCount][nCntKey];
			}
			// ��]�ʂ̑��
			m_fRot[nCount] = fData[RECVDATA_ROT];

			// �ʒu�̑��
			m_playerPos[nCount] = D3DXVECTOR3(fData[RECVDATA_POS_X], fData[RECVDATA_POS_Y], fData[RECVDATA_POS_Z]);

			// �����N�̑��
			m_nRank[nCount] = (int)fData[RECVDATA_RANK];

			m_nStick[STICKTYPE_H] = (int)fData[RECVDATA_STICK_H];
			m_nStick[STICKTYPE_V] = (int)fData[RECVDATA_STICK_V];
		}
	}

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (nCount != m_nId)
		{
			CPlayer *pPlayer = CGame::GetPlayer(nCount);		// �v���C���[�̎擾

			if (pPlayer != NULL)
			{
				pPlayer->SetPos(m_playerPos[nCount]);				// �ʒu�̎擾
				pPlayer->SetRotDest(D3DXVECTOR3(0.0f, m_fRot[nCount], 0.0f));
			}
		}
	}

	return true;
}

//=============================================================================
// �T�[�o�[���߂̏���
//=============================================================================
bool CNetwork::UpdateTCP(void)
{
	char aFunc[256];
	int nError;

	char cDataText[128];		//����
	char cHeadText[128];		//��r

	memset(cDataText, 0, 128);
	memset(cHeadText, 0, 128);

	memset(aFunc, 0, 256);
	nError = recv(m_sockClient, &aFunc[0], 256, 0);

	sscanf(aFunc, "%s %s", &cHeadText, &cDataText);
	OutputDebugString(aFunc);

	// �ڑ��m�F
	if (WSAGetLastError() == WSAEWOULDBLOCK)
	{
		printf("�܂����Ȃ�");
	}
	else if (nError == 0 || nError == -1) {
		//�ؒf������
		printf("�T�[�o�[�ƒʐM�ؒf!!!\n");
		closesocket(m_sockClient);
		m_sockClient = NULL;
		return false;
	}

	//���[�h��������
	if (strcmp(cHeadText, "KILL") == 0)
	{
		char aDie[64];
		int nDeath = -1;		// �N��?
		int nKill = -1;			// �N��?

		sscanf(aFunc, "%s %d %d", &aDie, &nDeath, &nKill);

		if (!m_bDie[nDeath])
		{
			CPlayer *pPlayer = CGame::GetPlayer(nDeath);

			if (pPlayer != NULL)
			{
				pPlayer->Die();
			}

			m_bDie[nDeath] = true;

			if (m_nId == nKill)
			{// �������L���[�������Ƃ�
				pPlayer = CGame::GetPlayer(m_nId);
				if (pPlayer != NULL)
				{
					pPlayer->MpUp(CCharacter::GetStatus(pPlayer->GetCharacter()).nMaxMpUp_KnockDown);
				}
			}
		}
	}
	else if (strcmp(cHeadText, "GAME_END") == 0)
	{
		char aDie[64];
		int nRank[MAX_PLAYER] = {};

		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ��Ƃ�
			sscanf(aFunc, "%s %d %d %d %d", &aDie, &nRank[0], &nRank[1], &nRank[2], &nRank[3]);

			// �`���[�g���A����
			CCharRanking::SetRank(nRank);
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);
		}
	}
	else if (strcmp(cHeadText, "GAME_START") == 0)
	{
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ��Ƃ�
			// ������
			for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
			{
				m_selectState[nCount].bReady = false;
				m_selectState[nCount].nType = -1;
			}

			// �`���[�g���A����
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
	}
	else if (strcmp(cHeadText, "CHARACTER_SELECT") == 0)
	{
		int nId;			// �v���C���[ID
		int nType;			// �L�����N�^�[�̎��
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d %d", &aDie, &nId, &nType);

		m_selectState[nId].bReady = true;
		m_selectState[nId].nType = nType;

		m_selectBalloon.nId = nId;
		m_selectBalloon.nType = nType;
		m_selectBalloon.bCreate = true;

		if (m_nId == nId)
		{
			CSelect *pSelect = CManager::GetSelect();
			pSelect->SetReady(true);
		}
	}
	else if (strcmp(cHeadText, "CHARACTER_CANCEL") == 0)
	{
		int nId;
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d", &aDie, &nId);

		m_selectState[nId].bReady = false;
		m_selectState[nId].nType = -1;

		if (m_selectState[nId].pBalloonNum != NULL)
		{
			m_selectState[nId].pBalloonNum->Release();
			m_selectState[nId].pBalloonNum = NULL;
		}

		if (m_nId == nId)
		{
			CSelect *pSelect = CManager::GetSelect();
			pSelect->SetReady(false);
		}
	}
	else if (strcmp(cHeadText, "HIT") == 0)
	{
		int nId;
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d", &aDie, &nId);
		OutputDebugString(aFunc);

		// �v���C���[�擾
		CPlayer *pPlayer = CGame::GetPlayer(nId);
		if (pPlayer != NULL)
		{
			// ���D�j��
			pPlayer->GetBalloon()->CrackBalloon();
		}
	}
	else if (strcmp(cHeadText, "SET_COIN") == 0)
	{
		int nId;
		int nMaxCoin = 0;
		D3DXVECTOR3 pos;

		std::string Data = aFunc;
		std::vector<std::string> vsvec_Contens;		// �e�L�X�g�f�[�^�i�[�p
		std::vector<std::string> vsvec_Data;		// �e�L�X�g�f�[�^�i�[�p

		vsvec_Contens = CCalculation::split(Data, ' ');

		nMaxCoin = atoi(vsvec_Contens[1].c_str());

		for (int nCount = 0; nCount < nMaxCoin; nCount++)
		{
			// ��񐮗�
			vsvec_Data = CCalculation::split(vsvec_Contens[nCount + 2], ',');
			nId = atoi(vsvec_Data[0].c_str());
			pos.x = (float)atof(vsvec_Data[1].c_str());
			pos.y = (float)atof(vsvec_Data[2].c_str());
			pos.z = (float)atof(vsvec_Data[3].c_str());

			if (m_apItem[nId] != NULL)
			{
				m_apItem[nId]->SetPos(pos);
				m_apItem[nId]->SetDrawState(true);
			}
			else
			{
				m_apItem[nId] = CItem::Create(nId, pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			}
		}
	}
	else if (strcmp(cHeadText, "DELETE_COIN") == 0)
	{
		int nCoinId;
		int nPlayerId;
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d %d", &aDie, &nCoinId, &nPlayerId);

		if (m_nId == nPlayerId)
		{
			CPlayer *pPlayer = CGame::GetPlayer(m_nId);

			// �v���C���[�̃X�R�A���Z�ǉ�
			if (pPlayer != NULL)
			{
				// �L�����N�^�[����v������
				if (pPlayer->GetCharacter() != CCharacter::CHARACTER_BALLOON4)
				{
					CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
				}
				// �L�����N�^�[����v������
				if (pPlayer->GetCharacter() == CCharacter::CHARACTER_BALLOON4)
				{
					// ���
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
				}

				CManager::GetSound()->PlaySound(CSound::LABEL_SE_POINTGET1);
			}
		}

		if (m_apItem[nCoinId] != NULL)
		{
			m_apItem[nCoinId]->SetPos(D3DXVECTOR3(0.0f, -1000.0f, 0.0f));
			m_apItem[nCoinId]->SetDrawState(false);
		}
	}
	else if (strcmp(cHeadText, "RECOVERY") == 0)
	{
		int nId;
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d", &aDie, &nId);
		OutputDebugString(aFunc);

		// �v���C���[�擾
		CPlayer *pPlayer = CGame::GetPlayer(nId);
		if (pPlayer != NULL)
		{
			// ���D�j��
			pPlayer->BalloonCreate();
		}
	}
	else if (strcmp(cHeadText, "START_SP") == 0)
	{
		int nId;
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d", &aDie, &nId);
		CPlayer *pPlayer = CGame::GetPlayer(nId);

		if (pPlayer != NULL)
		{// �v���C���[�����݂��Ă����Ƃ�
			pPlayer->SetMPMax(true);				// �K�E�Z�g�p
		}
	}
	else if (strcmp(cHeadText, "STOP_SP") == 0)
	{
		int nId;
		char aDie[64];

		// ��񐮗�
		sscanf(aFunc, "%s %d", &aDie, &nId);
		CPlayer *pPlayer = CGame::GetPlayer(nId);

		if (pPlayer != NULL)
		{// �v���C���[�����݂��Ă����Ƃ�
			pPlayer->SetMPMax(false);				// �K�E�Z����
		}
	}
	else if (strcmp(cHeadText, "THUNDER") == 0)
	{
		char aDie[64];
		D3DXVECTOR3 pos;

		// ������
		sscanf(aFunc, "%s %f %f %f", &aDie, &pos.x, &pos.y, &pos.z);
		m_thunderEvent.pos = pos;
		m_thunderEvent.bCreate = true;
	}
	else if (strcmp(cHeadText, "POINTCIRCLE") == 0)
	{
		char aDie[64];
		D3DXVECTOR3 pos;

		// �|�C���g�T�[�N������
		sscanf(aFunc, "%s %f %f %f", &aDie, &pos.x, &pos.y, &pos.z);
		m_pointcircleEvent.pos = pos;
		m_pointcircleEvent.bCreate = true;
	}

	return true;
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
// �ʐM�ؒf
//=============================================================================
void CNetwork::CloseTCP(void)
{
	closesocket(m_sockClient);
}