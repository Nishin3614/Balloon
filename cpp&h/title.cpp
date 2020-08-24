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
#include "2Deffect.h"
#include "3Dparticle.h"
#include "framework.h"

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
	// 2D�G�t�F�N�g�̐���
	C2DEffect::Create();
	// 3D�p�[�e�B�N������
	C3DParticle::Create(
		C3DParticle::PARTICLE_ID_BALLOON,
		//D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DVECTOR3_ZERO,
		true);

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
					// �`���[�g���A����
					pFade->SetFade(CManager::MODE_TUTORIAL);
				}
			}
		}
#ifdef _DEBUG
		// ���U���g��ʑJ��
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_9))
		{
			pFade->SetFade(CManager::MODE_RESULT);
		}
#endif // _DEBUG
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