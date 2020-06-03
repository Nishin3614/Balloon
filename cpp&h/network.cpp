// ------------------------------------------
//
// �l�b�g���[�N���� [network.cpp]
// Author : masayasu wakita
//
// ------------------------------------------
#include "network.h"
#include "keyboard.h"

// ------------------------------------------
// �ÓI�����o�ϐ�
// ------------------------------------------
char CNetwork::aIp[32] = {};
int CNetwork::nPort = 0;

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CNetwork::CNetwork()
{

}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CNetwork::~CNetwork()
{

}

// ------------------------------------------
// ������
// ------------------------------------------
HRESULT CNetwork::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	hr = Build();					// �\�P�b�g�̐���
	OutputDebugString("�N���C�A���g�\�z����\n");

	return hr;
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CNetwork::Uninit(void)
{
	//�\�P�b�g(�N���C�A���g)�̊J��
	closesocket(m_sockClient);
}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CNetwork::Update(void)
{
	//send(m_sockClient, "LOAD", sizeof("LOAD"), 0);
	//recv(m_sockClient, (char*)&keystate, sizeof(KEYSTATE), 0);
}

// ------------------------------------------
// �l�b�g���[�N�̐ݒ�f�[�^�ǂݍ���
// ------------------------------------------
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

// ------------------------------------------
// �L�[�{�[�h�̓��͏�Ԃ̎擾
// -----------------------------------------
KEYSTATE CNetwork::GetKeystate(void)
{
	return keystate;
}

// ------------------------------------------
// �N���C�A���g�\�P�b�g�̍쐬
// -----------------------------------------
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

	//�\�P�b�g�̐ݒ�
	m_addrServer.sin_family = AF_INET;
	m_addrServer.sin_port = htons(nPort);
	m_addrServer.sin_addr.S_un.S_addr = inet_addr(aIp);
	return S_OK;
}

// ------------------------------------------
// �R�l�N�g
// ------------------------------------------
HRESULT CNetwork::Connect(void)
{
	int val = -1;

	//�T�[�o�ɐڑ�
	val = connect(m_sockClient, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));
	if (val == SOCKET_ERROR)
	{
		char aError[64];
		sprintf(aError, "�l�b�g���[�N�G���[!\nerror : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "�x��!", MB_ICONWARNING);
		return E_FAIL;
	}

	OutputDebugString("�T�[�o�Ƃ̐ڑ�����\n");
	return S_OK;
}