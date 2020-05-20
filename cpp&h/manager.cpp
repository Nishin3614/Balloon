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
CGame * CManager::m_game = NULL;						// �Q�[��
CManager::MODE CManager::m_mode = CManager::MODE_GAME;	// ���[�h
bool CManager::m_bWire = false;							// ���C���[

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
	/* ��� */
	// �Q�[���̐���
	m_game = new CGame;
	// ���[�h�̐ݒ�
	m_mode = STARTMODE;

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
	// �Q�[��
	if (m_game != NULL)
	{
		m_game->Uninit();
		delete m_game;
		m_game = NULL;
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
		// �Q�[��
	case MODE_GAME:
		m_game->Update();
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
		// �Q�[��
	case MODE_GAME:
		m_game->Uninit();
		break;
	default:
		break;
	}

	m_mode = mode;	// ���݂̃��[�h����

	// ���݂̃��[�h������
	switch (mode)
	{
		// �Q�[��
	case MODE_GAME:
		m_game->Init();
		break;
	default:
		break;
	}
}