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
#include "character_fish.h"
#include "speedUP.h"
#include "collision.h"
#include "item.h"
#include "PointCircle.h"
#include "solider.h"
#include "network.h"
#include "ui.h"

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
	CCharacter::InitStatic();
	/* �쐬 */
	// 3D�G�t�F�N�g�̐���
	C3DEffect::Create();
	// ���̐ݒ�
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		10000.0f);
	// 3D�}�b�v����
	CLake::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(2500.0f, 2500.0f, 0.0f));
	C3DMap::LoadScript("data/LOAD/MAPPING/rand.csv");
	C3DMap::LoadCreate(C3DMap::MAP_STAGE_1);
	CScene_X::LoadScrept("data/LOAD/MAPPING/object.csv");
	CSpeedUP::Create(0, D3DVECTOR3_ZERO);
	CItem::Create(0, D3DXVECTOR3(300.0f, 50.0f, 200.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	CPointCircle::Create(D3DXVECTOR3(-300.0f, 0.0f, 200.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f));
	CUi::LoadCreate(CUi::UITYPE_TUTORIALUI);
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
	// �����蔻�菈��
	CCollision::CollisionDetection();
	// �o���C�x���g����
	PopEvent();
	CFade *pFade = CManager::GetFade();
	CJoypad *pJoypad = CManager::GetJoy();
	CNetwork *pNetwork = CManager::GetNetwork();

	// �t�F�[�h���Ă��Ȃ��Ƃ�
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// �Q�[���֑J��
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RETURN))
		{
			if (pNetwork != NULL)
			{
				if (pNetwork->Connect() == S_OK)
				{

					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						// �I����ʂ�
						pFade->SetFade(CManager::MODE_SELECT);
					}
				}
			}
		}

		if (pJoypad != NULL)
		{
			if (pJoypad->GetTrigger(0, CJoypad::KEY_START))
			{
				if (pNetwork->Connect() == S_OK)
				{
					// �I����ʂ�
					pFade->SetFade(CManager::MODE_SELECT);
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

//=============================================================================
//
// �o���C�x���g����
//
//=============================================================================
void CTutorial::PopEvent(void)
{
	if (CItem::GetAllItem() == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CItem::Create(0, D3DXVECTOR3(300.0f, 50.0f, 200.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
		}
		nCntPop++;
	}
	if (CPointCircle::GetAllPointCircle() == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CPointCircle::Create(D3DXVECTOR3(-300.0f, 50.0f, 200.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		}
		nCntPop++;
	}
	if (CEnemy::GetAllEnemy() == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CSolider::Create(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
		}
		nCntPop++;
	}
	if (CSpeedUP::GetAll() == 0)
	{
		CSpeedUP::Create(0, D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	}
}
