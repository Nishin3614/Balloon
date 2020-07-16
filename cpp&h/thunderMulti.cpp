// ==========================================================
//
// �����̗�[thunderMulti.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
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
// �ÓI�����o�[�ϐ��̏�����
// ==========================================================
CThunderMulti *CThunderMulti::m_pThunderMulti = NULL;
LPDIRECT3DTEXTURE9 CThunderMulti::m_pTex = NULL;

// ==========================================================
//
// �R���X�g���N�^
//
// ==========================================================
CThunderMulti::CThunderMulti() :CScene_THREE()
{

}

// ==========================================================
//
// �f�X�g���N�^
//
// ==========================================================
CThunderMulti::~CThunderMulti()
{

}

// ==========================================================
// ������
// ==========================================================
void CThunderMulti::Init(void)
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
	// �A�j���[�V�����J�E���^�[������
	m_nCounterAnim = 0;
	// �A�j���[�V�����p�^�[��������
	m_nPatternAnim = 0;
	// ���̏�Ԃ�������
	m_bThunder = true;
	// �|�W�V�����擾
	m_pos = m_pThunderMulti->GetPos();
}

// ==========================================================
// �I��
// ==========================================================
void CThunderMulti::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// �X�V
// ==========================================================
void CThunderMulti::Update(void)
{
	CScene_THREE::Update();

	// �����v�Z�p
	float fX_Difference;
	float fZ_Difference;
	float fDifference;
	// �e�N�X�`������
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	m_nCounterAnim++;	// �J�E���^�[���Z

						// �d���e�N�X�`���[
	if (m_nCounterAnim % 6 == 0)
	{
		m_nPatternAnim = (m_nPatternAnim + 1) % 6;

		CScene_THREE::SetAnimation(ANIM_TEX, 1.0f, 0.0f, m_nPatternAnim);
	}

	if (m_nPatternAnim == 5)
	{
		m_bThunder = false;
	}
}

// ==========================================================
// �`��
// ==========================================================
void CThunderMulti::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	if (m_bThunder == true)
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
CThunderMulti *CThunderMulti::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[�����I�Ɋm��
	m_pThunderMulti = new CThunderMulti();

	// �ʒu�ݒ�
	m_pThunderMulti->SetPos(pos);

	// �T�C�Y�ݒ�
	m_pThunderMulti->SetSize(size);

	// �V�[��������
	m_pThunderMulti->Init();

	m_pThunderMulti->ManageSetting(LAYER_3DOBJECT2);

	// �l��Ԃ�
	return m_pThunderMulti;
}

// ==========================================================
// �j��
// ==========================================================
void CThunderMulti::Unload(void)
{
	// �e�N�X�`�����
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}