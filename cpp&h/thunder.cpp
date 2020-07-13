// ==========================================================
//
// ��[thunder.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
#include "thunder.h"
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
	CScene_THREE::SetTexType(22);			// �e�N�X�`���[�n��
	// �͈�
	m_fDistance = MAX_DISTANCE;
	// �|�W�V�����擾
	m_pos = m_pThunder->GetPos();

	// ���b�V���h�[���̐���
	CMeshdome *pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_NORMAL,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���b�V���h�[���̎g�p���
	pMeshDome->SetUse(true);
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

	/*
	g_aExplosion[nCntExplosion].nCounterAnim++;	// �J�E���^�[���Z

												// �d���e�N�X�`���[
	if (g_aExplosion[nCntExplosion].type == EXPLOSIONTYPE_THUNDER)
	{
		// �����蔻��
		CollisionExplosion(nCntExplosion);
		if (g_aExplosion[nCntExplosion].nCounterAnim % 6 == 0)
		{
			// �e�N�X�`���ݒ�
			SetTexExplosion(pVtx,
				ANIMATION_SIX_FTEX * g_aExplosion[nCntExplosion].nPatternAnim,
				ANIMATION_SIX_FTEX + ANIMATION_SIX_FTEX * g_aExplosion[nCntExplosion].nPatternAnim);
			g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim++) % ANIMATION_SIX;	// 6���p�^�[���n��

																														// �����I��
			if (g_aExplosion[nCntExplosion].nPatternAnim % ANIMATION_SIX == 0)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
		}
	}
	*/

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
					C3DParticle::OFFSET_ID_CROSSLINE,
					charaPos
				);
				// �L�����N�^�[����
				pCharacter->Release();
			}
		}
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

	m_pThunder->ManageSetting(LAYER_3DOBJECT);

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