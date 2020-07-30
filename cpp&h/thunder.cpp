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
CThunder *CThunder::m_pThunder = NULL;
LPDIRECT3DTEXTURE9 CThunder::m_pTex = NULL;

// ==========================================================
//
// �R���X�g���N�^
//
// ==========================================================
CThunder::CThunder() :CScene_THREE()
{

}

// ==========================================================
//
// �f�X�g���N�^
//
// ==========================================================
CThunder::~CThunder()
{

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
	// �|�W�V�����擾
	m_pos = m_pThunder->GetPos();
	// ���b�V���h�[���̐���
	m_pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_NORMAL,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
			CThunderMulti *pThunderMulti = CThunderMulti::Create(m_pos + D3DXVECTOR3(float(rand() % 81 - 40), float(rand() % 201 - 100), float(rand() % 81 - 40)),
				D3DXVECTOR3(100.0f, 500.0f, 0.0f));
		}

		if (m_nCntThunder % 20 == 0)
		{
			CThunderMulti *pThunderMulti = CThunderMulti::Create(m_pos + D3DXVECTOR3(float(rand() % 81 - 40), float(rand() % 201 - 100), float(rand() % 81 - 40)),
				D3DXVECTOR3(100.0f, 500.0f, 0.0f));
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

				// �O��̃|�W�V�����ݒ�
				m_posOld = m_pos;

				// �G�ƃv���C���[�̇]���W����
				fX_Difference = m_pos.x - charaPos.x;

				// �G�ƃv���C���[��Z���W����
				fZ_Difference = m_pos.z - charaPos.z;

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
					// �L�����N�^�[����
					pCharacter->Release();
				}
			}
		}
	}

	if (m_nCntDraw >= RELEASE_DRAW)
	{
		// ���b�V���h�[���̎g�p���
		m_pMeshDome->SetUse(false);
		Release();
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

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	}
}

// ==========================================================
// ����
// ==========================================================
CThunder *CThunder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[�����I�Ɋm��
	m_pThunder = new CThunder();

	// �ʒu�ݒ�
	m_pThunder->SetPos(pos);

	// �T�C�Y�ݒ�
	m_pThunder->SetSize(size);

	// �V�[��������
	m_pThunder->Init();

	m_pThunder->ManageSetting(LAYER_3DOBJECT2);

	// �l��Ԃ�
	return m_pThunder;
}

// ==========================================================
// �j��
// ==========================================================
void CThunder::Unload(void)
{
	// �e�N�X�`�����
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}