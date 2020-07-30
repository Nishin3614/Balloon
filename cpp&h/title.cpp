//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : Ryouma Inoue
//
//=============================================================================
#include "title.h"			// �C���N���[�h�t�@�C��
#include "fade.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "manager.h"
#include "ui.h"
#include "network.h"

//=============================================================================
//
// �R���X�g���N�^
//
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//
// �f�X�g���N�^
//
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//
// ����������
//
//=============================================================================
HRESULT CTitle::Init()
{
	// UI����
	CUi::LoadCreate(CUi::UITYPE_TITLEUI_NAME);
	// ������
	return S_OK;
}

//=============================================================================
//
// �I������
//
//=============================================================================
void CTitle::Uninit(void)
{
	// �S�Ă̊J��
	CScene::ReleaseAll();
}

//=============================================================================
//
// �X�V����
//
//=============================================================================
void CTitle::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CNetwork *pNetwork = CManager::GetNetwork();
	CJoypad *pJoypad = CManager::GetJoy();

	// �t�F�[�h���Ă��Ȃ��Ƃ�
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// �Q�[���֑J��
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			if (pNetwork != NULL)
			{
				if (pNetwork->Connect() == S_OK)
				{
					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						// �`���[�g���A����
						pFade->SetFade(CManager::MODE_TUTORIAL);
					}
				}
			}
		}

		if (pJoypad != NULL)
		{
			if (pJoypad->GetTrigger(0, CJoypad::KEY_START) || pJoypad->GetTrigger(0, CJoypad::KEY_A))
			{
				if (pNetwork->Connect() == S_OK)
				{
					pFade->SetFade(CManager::MODE_TUTORIAL);
				}
			}
		}
	}
}

//=============================================================================
//
// �`�揈��
//
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
//
// �^�C�g���̐���
//
//=============================================================================
CTitle * CTitle::Create(void)
{
	// �ϐ�
	CTitle *pTitle;

	// �������̊m��
	pTitle = new CTitle;

	// ������
	pTitle->Init();

	return pTitle;
}