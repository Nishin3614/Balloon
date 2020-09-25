// ==========================================================
//
// ��[thunder.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
#include "thunder.h"
#include "thunderMulti.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "sound.h"
#include "character.h"
#include "spherecollision.h"
#include "collision.h"
#include "character.h"
#include "3Dparticle.h"
#include "meshdome.h"
#include "ui_group.h"

// ==========================================================
//
// �}�N����`
//
// ==========================================================
#define COUNT_DRAW (600)
#define RELEASE_DRAW (1200)

// ==========================================================
// �ÓI�����o�[�ϐ��̏�����
// ==========================================================
int CThunder::m_nAllThunder = 0;

// ==========================================================
//
// �R���X�g���N�^
//
// ==========================================================
CThunder::CThunder() :CScene_THREE()
{
	m_nAllThunder++;
}

// ==========================================================
//
// �f�X�g���N�^
//
// ==========================================================
CThunder::~CThunder()
{
	m_nAllThunder--;
}

// ==========================================================
// ������
// ==========================================================
void CThunder::Init(void)
{
	// �I�t�Z�b�g�^�C�v�ݒ�
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// �F�̐ݒ�
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	// �r���{�[�h
	CScene_THREE::SetBillboard(true);
	CScene_THREE::SetLighting(true);		// ���C�e�B���O
	// �e�N�X�`���[�^�C�v�ݒ�
	CScene_THREE::SetTexType(23);			// �e�N�X�`���[�n��
	// �e�N�X�`������
	CScene_THREE::SetTex(D3DXVECTOR2(ANIM_TEX * 5, 0.0f), D3DXVECTOR2(ANIM_TEX + ANIM_TEX * 5, 1.0f));
	// �͈�
	m_fDistance = MAX_DISTANCE;
	// �A�j���[�V�����J�E���^�[������
	m_nCounterAnim = 0;
	// �A�j���[�V�����p�^�[��������
	m_nPatternAnim = 0;
	// ���̃J�E���g������
	m_nCntThunder = 0;
	// ���̕`��J�E���g������
	m_nCntDraw = 0;
	// ���̏�Ԃ�������
	m_bThunder = true;
	// ���b�V���h�[���̐���
	m_pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(CScene_THREE::GetPos().x, 0.0f, CScene_THREE::GetPos().z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE_Y, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_NORMAL,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		false,
		LAYER_DOME);

	// ���b�V���h�[���̎g�p���
	m_pMeshDome->SetUse(true);
}

// ==========================================================
// �I��
// ==========================================================
void CThunder::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// �X�V
// ==========================================================
void CThunder::Update(void)
{
	CScene_THREE::Update();

	// ���[�h���Q�[���Ȃ�
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �Q�[���̍X�V����
		Update_Game();
	}
	// ���[�h���`���[�g���A���Ȃ�
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// �`���[�g���A���̍X�V����
		Update_Tutorial();
	}

}

// ==========================================================
// �`��
// ==========================================================
void CThunder::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	if (m_bThunder == false)
	{
		// �`��
		CScene_THREE::Draw();
	}
}

// ==========================================================
// ����
// ==========================================================
CThunder *CThunder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[�����I�Ɋm��
	CThunder * pThunder = new CThunder();

	// �ʒu�ݒ�
	pThunder->SetPos(pos);

	// �T�C�Y�ݒ�
	pThunder->SetSize(size);

	// �V�[��������
	pThunder->Init();

	pThunder->ManageSetting(LAYER_3DOBJECT2);

	// �l��Ԃ�
	return pThunder;
}

// ==========================================================
// �j��
// ==========================================================
void CThunder::Unload(void)
{
}

// ==========================================================
// �`���[�g���A���̍X�V����
// ==========================================================
void CThunder::Update_Tutorial(void)
{
	// �����v�Z�p
	float fX_Difference;
	float fZ_Difference;
	float fDifference;
	// �e�N�X�`������
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	// �J�E���^�[���Z
	m_nCounterAnim++;
	m_nCntThunder++;
	m_nCntDraw++;


	if (m_nCntDraw >= COUNT_DRAW)
	{
		if (m_nCntThunder % 50 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 200.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// ����1
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER1);
		}

		if (m_nCntThunder % 20 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// ����2
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER2);
		}

		//// �d���e�N�X�`���[
		//if (m_nCounterAnim % 6 == 0)
		//{
		//	m_nPatternAnim = (m_nPatternAnim + 1) % 6;

		//		CScene_THREE::SetAnimation(ANIM_TEX, 1.0f, 0.0f, m_nPatternAnim);
		//}
		//
		//if (m_nPatternAnim == 5)
		//{
		//	m_bThunder = false;
		//
		//}
		for (int nCnt = 0; nCnt < CScene::GetMaxLayer(CScene::LAYER_CHARACTER); nCnt++)
		{
			// �L�����N�^�[�ւ̃|�C���^
			CCharacter *pCharacter = (CCharacter*)CScene::GetScene(CScene::LAYER_CHARACTER, nCnt);

			if (pCharacter != NULL)
			{
				// �L�����N�^�[�̃|�W�V�����擾
				D3DXVECTOR3 charaPos = pCharacter->GetPos();
				// �G�ƃv���C���[�̇]���W����
				fX_Difference = CScene_THREE::GetPos().x - charaPos.x;

				// �G�ƃv���C���[��Z���W����
				fZ_Difference = CScene_THREE::GetPos().z - charaPos.z;

				// �G�ƃv���C���[�̈�苗��
				fDifference = sqrtf(fX_Difference * fX_Difference + fZ_Difference * fZ_Difference);

				// �v���C���[����苗���ɋ߂Â�����
				if (fDifference < m_fDistance)
				{
					// �p�[�e�B�N������
					C3DParticle::Create(
						C3DParticle::PARTICLE_ID_CROSSLINE,
						charaPos
					);
					// ���ʉ�2
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_KERSPLASH2);
					// �L�����N�^�[����
					pCharacter->Die();
				}
			}
		}
	}
}

// ==========================================================
// �Q�[���̍X�V����
// ==========================================================
void CThunder::Update_Game(void)
{
	// �����v�Z�p
	float fX_Difference;
	float fZ_Difference;
	float fDifference;
	// �e�N�X�`������
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	// �J�E���^�[���Z
	m_nCounterAnim++;
	m_nCntThunder++;
	m_nCntDraw++;


	if (m_nCntDraw >= COUNT_DRAW)
	{
		if (m_nCntThunder % 50 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 200.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// ����1
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER1);
		}

		if (m_nCntThunder % 20 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(CScene_THREE::GetPos() + D3DXVECTOR3(float(rand() % 41 - 20), 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 1000.0f, 0.0f));
			// ����2
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_THUNDER2);
		}

		//// �d���e�N�X�`���[
		//if (m_nCounterAnim % 6 == 0)
		//{
		//	m_nPatternAnim = (m_nPatternAnim + 1) % 6;

		//		CScene_THREE::SetAnimation(ANIM_TEX, 1.0f, 0.0f, m_nPatternAnim);
		//}
		//
		//if (m_nPatternAnim == 5)
		//{
		//	m_bThunder = false;
		//
		//}
		for (int nCnt = 0; nCnt < CScene::GetMaxLayer(CScene::LAYER_CHARACTER); nCnt++)
		{
			// �L�����N�^�[�ւ̃|�C���^
			CCharacter *pCharacter = (CCharacter*)CScene::GetScene(CScene::LAYER_CHARACTER, nCnt);

			if (pCharacter != NULL)
			{
				// �L�����N�^�[�̃|�W�V�����擾
				D3DXVECTOR3 charaPos = pCharacter->GetPos();
				// �G�ƃv���C���[�̇]���W����
				fX_Difference = CScene_THREE::GetPos().x - charaPos.x;

				// �G�ƃv���C���[��Z���W����
				fZ_Difference = CScene_THREE::GetPos().z - charaPos.z;

				// �G�ƃv���C���[�̈�苗��
				fDifference = sqrtf(fX_Difference * fX_Difference + fZ_Difference * fZ_Difference);

				// �v���C���[����苗���ɋ߂Â�����
				if (fDifference < m_fDistance)
				{
					// �p�[�e�B�N������
					C3DParticle::Create(
						C3DParticle::PARTICLE_ID_CROSSLINE,
						charaPos
					);
					// ���ʉ�2
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_KERSPLASH2);
					// �L�����N�^�[����
					pCharacter->Die();
				}
			}
		}
	}

	if (m_nCntDraw >= RELEASE_DRAW)
	{
		// ���b�V���h�[����NULL�`�F�b�N
		if (m_pMeshDome != NULL)
		{
			// ���b�V���h�[���̎g�p���
			m_pMeshDome->SetUse(false);
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}
		Release();
	}
}
