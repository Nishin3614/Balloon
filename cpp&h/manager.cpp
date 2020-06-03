// ----------------------------------------------------------------------------------------------------
//
// �}�l�[�W���[�����̐���[manager.cpp]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------
/* My */
#include "manager.h"

/* �`�� */
#include "scene.h"
#include "game.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "ranking.h"
#include "network.h"

// ----------------------------------------------------------------------------------------------------
//
// �}�N���֐�
//
// ----------------------------------------------------------------------------------------------------
#define STARTMODE (MODE_GAME)

// ----------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------------------------------------------------------------------
CRenderer *CManager::m_renderer = NULL;					// �����_���[
CKeyboard * CManager::m_keyboard = NULL;				// �L�[�{�[�h
CJoypad * CManager::m_joypad = NULL;					// �W���C�p�b�h
CMouse * CManager::m_mouse = NULL;						// �}�E�X
CKeyConfig * CManager::m_keyconfig = NULL;				// �L�[�ڍ�
CSound * CManager::m_sound = NULL;						// �T�E���h
CFade * CManager::m_fade = NULL;						// �t�F�[�h
CTitle * CManager::m_title = NULL;						// �^�C�g��
CTutorial * CManager::m_tutorial = NULL;				// �`���[�g���A��
CGame * CManager::m_game = NULL;						// �Q�[��
CResult * CManager::m_result = NULL;					// ���U���g
CRanking * CManager::m_ranking = NULL;					// �����L���O
CManager::MODE CManager::m_mode = CManager::MODE_GAME;	// ���[�h
bool CManager::m_bWire = false;							// ���C���[
CNetwork * CManager::m_pNetwork = NULL;					// �l�b�g���[�N

// ----------------------------------------------------------------------------------------------------
// �R���X�g���N�^
// ----------------------------------------------------------------------------------------------------
CManager::CManager()
{
}

// ----------------------------------------------------------------------------------------------------
// �f�X�g���N�^
// ----------------------------------------------------------------------------------------------------
CManager::~CManager()
{
}

// ----------------------------------------------------------------------------------------------------
// ����������
// ----------------------------------------------------------------------------------------------------
HRESULT CManager::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	/* �������̐��� */
	/* ���̓f�o�C�X */
	// �L�[�{�[�h�̐���
	m_keyboard = new CKeyboard;
	// �W���C�p�b�h�̐���
	m_joypad = new CJoypad;
	// �}�E�X�̐���
	m_mouse = new CMouse;
	// �L�[�ڍׂ̐���
	m_keyconfig = new CKeyConfig;
	/* �Q�[���Ɍ������Ȃ����� */
	// �T�E���h�̐���
	m_sound = new CSound;
	// �����_�����O�̐���
	m_renderer = new CRenderer;
	// �l�b�g���[�N�̐���
	m_pNetwork = new CNetwork;
	/* ��� */
	// �^�C�g���̐���
	m_title = new CTitle;
	// �`���[�g���A���̐���
	m_tutorial = new CTutorial;
	// �Q�[���̐���
	m_game = new CGame;
	// ���U���g�̐���
	m_result = new CResult;
	// ���U���g�̐���
	m_ranking = new CRanking;
	// ���[�h�̐ݒ�
	m_mode = STARTMODE;

	// �l�b�g���[�N�̐ݒ�f�[�^�ǂݍ���
	CNetwork::LoadConfiguration();

	/* ������ */
	// �L�[�{�[�h
	if (!m_keyboard->Init(hInstance, hWnd) == S_OK)
	{
		m_keyboard->Uninit();
		delete m_keyboard;
		m_keyboard = NULL;
	}
	// �W���C�p�b�h
	if (!m_joypad->Init(hInstance, hWnd) == S_OK)
	{
		m_joypad->Uninit();
		delete m_joypad;
		m_joypad = NULL;
	}
	// �}�E�X
	if (!m_mouse->Init(hInstance, hWnd) == S_OK)
	{
		m_mouse->Uninit();
		delete m_mouse;
		m_mouse = NULL;
	}
	// �L�[�ڍ�
	m_keyconfig->Init();
	// �T�E���h
	if (!m_sound->Init(hWnd) == S_OK)
	{
		m_sound->Uninit();
		delete m_sound;
		m_sound = NULL;
		return E_FAIL;
	}
	// �����_�����O
	if (!m_renderer->Init(hWnd, bWindow) == S_OK)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = NULL;
		return E_FAIL;
	}
	// �l�b�g���[�N
	if (!m_pNetwork->Init(hInstance, hWnd) == S_OK)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = NULL;
		return E_FAIL;
	}

	if (m_pNetwork != NULL)
	{
		m_pNetwork->Connect();
	}
	// ��ʑJ��
	m_fade = CFade::Create(STARTMODE);

	return S_OK;
}

// ----------------------------------------------------------------------------------------------------
// �I������
// ----------------------------------------------------------------------------------------------------
void CManager::Uninit(void)
{
	/* �������̔j�� */
	// ���̓f�o�C�X
	CInput::ReleaseAll();
	// �L�[�{�[�h
	if (m_keyboard != NULL)
	{
		m_keyboard->Uninit();
		delete m_keyboard;
		m_keyboard = NULL;
	}
	// �W���C�p�b�h
	if (m_joypad != NULL)
	{
		m_joypad->Uninit();
		delete m_joypad;
		m_joypad = NULL;
	}
	// �}�E�X
	if (m_mouse != NULL)
	{
		m_mouse->Uninit();
		delete m_mouse;
		m_mouse = NULL;
	}
	// �L�[�ڍ�
	if (m_keyconfig != NULL)
	{
		m_keyconfig->Uninit();
		delete m_keyconfig;
		m_keyconfig = NULL;
	}
	// �T�E���h
	if (m_sound != NULL)
	{
		m_sound->Uninit();
		delete m_sound;
		m_sound = NULL;
	}
	// �����_�����O
	if (m_renderer != NULL)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = NULL;
	}
	// ��ʑJ��
	if (m_fade != NULL)
	{
		m_fade->Uninit();
		delete m_fade;
		m_fade = NULL;
	}
	// �^�C�g��
	if (m_title != NULL)
	{
		m_title->Uninit();
		delete m_title;
		m_title = NULL;
	}
	// �`���[�g���A��
	if (m_tutorial != NULL)
	{
		m_tutorial->Uninit();
		delete m_tutorial;
		m_tutorial = NULL;
	}
	// �Q�[��
	if (m_game != NULL)
	{
		m_game->Uninit();
		delete m_game;
		m_game = NULL;
	}
	// ���U���g
	if (m_result != NULL)
	{
		m_result->Uninit();
		delete m_result;
		m_result = NULL;
	}
	// ���U���g
	if (m_ranking != NULL)
	{
		m_ranking->Uninit();
		delete m_ranking;
		m_ranking = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------
// �X�V����
// ----------------------------------------------------------------------------------------------------
void CManager::Update(void)
{
	// ���̓f�o�C�X�̃{�^����������Ă��邩���ۂ̏�����
	CInput::InitState();
	// �L�[�{�[�h
	if (m_keyboard != NULL)
	{
		m_keyboard->Update();
	}
	// �W���C�p�b�h
	if (m_joypad != NULL)
	{
		m_joypad->Update();
	}
	// �}�E�X
	if (m_mouse != NULL)
	{
		m_mouse->Update();
	}
	// �����_�����O
	m_renderer->Update();

	// �O�̃��[�h�I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		m_title->Update();
		break;
		// �`���[�g���A��
	case MODE_TUTORIAL:
		m_tutorial->Update();
		break;
		// �Q�[��
	case MODE_GAME:
		m_game->Update();
		break;
		// ���U���g
	case MODE_RESULT:
		m_result->Update();
		break;
		// �����L���O
	case MODE_RANKING:
		m_ranking->Update();
		break;
	default:
		break;
	}

	// ��ʑJ��
	m_fade->Update();
}

// ----------------------------------------------------------------------------------------------------
//
// �`��֐�
//
// ----------------------------------------------------------------------------------------------------
void CManager::Draw(void)
{
	// �����_�����O
	m_renderer->Draw();
}

// ----------------------------------------------------------------------------------------------------
// ���[�h�ݒ�֐�
// ----------------------------------------------------------------------------------------------------
void CManager::SetMode(MODE const mode)
{
	// �O�̃��[�h�I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		m_title->Uninit();
		break;
		// �`���[�g���A��
	case MODE_TUTORIAL:
		m_tutorial->Uninit();
		break;
		// �Q�[��
	case MODE_GAME:
		m_game->Uninit();
		break;
		// ���U���g
	case MODE_RESULT:
		m_result->Uninit();
		break;
		// �����L���O
	case MODE_RANKING:
		m_ranking->Uninit();
		break;
	default:
		break;
	}

	m_mode = mode;	// ���݂̃��[�h����

					// ���݂̃��[�h������
	switch (mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		m_title->Init();
		break;
		// �`���[�g���A��
	case MODE_TUTORIAL:
		m_tutorial->Init();
		break;
		// �Q�[��
	case MODE_GAME:
		m_game->Init();
		break;
		// ���U���g
	case MODE_RESULT:
		m_result->Init();
		break;
		// �����L���O
	case MODE_RANKING:
		m_ranking->Init();
		break;
	default:
		break;
	}
}