//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : Ryouma Inoue
//
//=============================================================================
#include "tutorial.h"			// �C���N���[�h�t�@�C��
#include "fade.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "manager.h"

//=============================================================================
//
// �R���X�g���N�^
//
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
//
// �f�X�g���N�^
//
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
//
// ����������
//
//=============================================================================
HRESULT CTutorial::Init()
{

	// ������
	return S_OK;
}

//=============================================================================
//
// �I������
//
//=============================================================================
void CTutorial::Uninit(void)
{
	// �S�Ă̊J��
	CScene::ReleaseAll();
}

//=============================================================================
//
// �X�V����
//
//=============================================================================
void CTutorial::Update(void)
{
	CFade *pFade = CManager::GetFade();

	// �t�F�[�h���Ă��Ȃ��Ƃ�
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// �Q�[���֑J��
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RETURN))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// �`���[�g���A����
				pFade->SetFade(CManager::MODE_SELECT);
			}
		}
	}
}

//=============================================================================
//
// �`�揈��
//
//=============================================================================
void CTutorial::Draw(void)
{

}

//=============================================================================
//
// �^�C�g���̐���
//
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	// �ϐ�
	CTutorial *pTutorial;

	// �������̊m��
	pTutorial = new CTutorial;

	// ������
	pTutorial->Init();

	return pTutorial;
}