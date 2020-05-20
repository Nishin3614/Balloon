// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �V�[�������̐���[scene_load.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene_load.h"
/* �`�� */
#include "number.h"
#include "pause_ui.h"
#include "3Deffect.h"
#include "3Dparticle.h"
#include "floor.h"
#include "meshwall.h"
#include "meshdome.h"
#include "meshsphere.h"
#include "collision.h"
#include "camera.h"
#include "player.h"
#include "solider.h"
#include "circleshadow.h"
#include "time.h"
#include "fade.h"
#include "Extrusion.h"
#include "texture_manager.h"
#include "ui.h"
#include "scene_X.h"
#include "3Dmap.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CScene_load::CScene_load()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CScene_load::~CScene_load()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �V�[���e�q�쐬����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CScene_load::LoadAll(void)
{
	/* ----------�e�N�X�`���[�ǂݍ���---------- */
	// �e�N�X�`���[���
	if (!CTexture_manager::Load() == S_OK)
	{
		CCalculation::Messanger("�e�N�X�`���[���ǂݎ�莸�s");
	}
	// ���f���̏��
	if (!CScene_X::LoadModel() == S_OK)
	{
		CCalculation::Messanger("���f�����ǂݎ�莸�s");
	}
	/* UI */
	// UI
	if (!CUi::Load() == S_OK)
	{
		CCalculation::Messanger("UI�ǂݎ�莸�s");
	}
	// �|�[�YUI
	if (!CPause_ui::Load() == S_OK)
	{
		CCalculation::Messanger("�|�[�YUI�ǂݎ�莸�s");
	}
	// �t�F�[�h
	if (!CFade::Load() == S_OK)
	{
		CCalculation::Messanger("�t�F�[�h�ǂݎ�莸�s");
	}

	/* ���� */
	// 3Deffect
	if(!C3DEffect::Load()== S_OK)
	{
		CCalculation::Messanger("3D�G�t�F�N�g�ǂݎ�莸�s");
	}
	// 3Dparticle
	if(!C3DParticle::Load()== S_OK)
	{
		CCalculation::Messanger("3D�p�[�e�B�N���ǂݎ�莸�s");
	}
	/*
	/* �Q�[���ɕK�v�Ȃ��� */
	// �J����
	if (!CCamera::Load() == S_OK)
	{
		CCalculation::Messanger("�J�����ǂݎ�莸�s");
	}
	/* 2D�I�u�W�F�N�g */
	// �ԍ�
	if (!CNumber::Load() == S_OK)
	{
		CCalculation::Messanger("�ԍ��ǂݎ�莸�s");
	}

	/* 3D�I�u�W�F�N�g*/

	/* ���b�V�� */
	// ��
	if (!CFloor::Load() == S_OK)
	{
		CCalculation::Messanger("���ǂݎ�莸�s");
	}
	// ���b�V���h�[��
	if (!CMeshdome::Load() == S_OK)
	{
		CCalculation::Messanger("���b�V���h�[���ǂݎ�莸�s");
	}
	// ���b�V���X�t�B�A
	if (!CMeshsphere::Load() == S_OK)
	{
		CCalculation::Messanger("���b�V���X�t�B�A�ǂݎ�莸�s");
	}
	// ���b�V���E�H�[��
	if (!CMeshwall::Load() == S_OK)
	{
		CCalculation::Messanger("���b�V���E�H�[���ǂݎ�莸�s");
	}

	/* 3D���f��*/
	// �L�����N�^�[�X�e�[�^�X
	if (!CCharacter::LoadStatus() == S_OK)
	{
		CCalculation::Messanger("�L�����N�^�[�X�e�[�^�X���ǂݎ�莸�s");
	}
	// �v���C���[
	if(!CPlayer::Load()== S_OK)
	{
		CCalculation::Messanger("�v���C���[�ǂݎ�莸�s");
	}
	// ���m
	if (!CSolider::Load() == S_OK)
	{
		CCalculation::Messanger("���m�ǂݎ�莸�s");
	}
	// �~�`�V���h�E
	if (!CCircleshadow::Load() == S_OK)
	{
		CCalculation::Messanger("�~�`�V���h�E�ǂݎ�莸�s");
	}
	// 3D�}�b�v
	if (!C3DMap::Load() == S_OK)
	{
		CCalculation::Messanger("3D�}�b�v�ǂݎ�莸�s");
	}

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��񂾂��̂�j�����鏈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CScene_load::UnLoadAll(void)
{
	/* �ǂݍ��񂾂��̂̔j��*/
	// �ԍ�
	CTexture_manager::UnLoad();
	// �ԍ�
	CNumber::UnLoad();
	// UI
	CUi::UnLoad();
	// �|�[�YUI
	CPause_ui::UnLoad();
	// ��
	CFloor::UnLoad();
	// �v���C���[
	CPlayer::UnLoad();
	// 3Deffect
	C3DEffect::Unload();
	// 3Dparticle
	C3DParticle::Unload();
	// ���b�V���h�[��
	CMeshdome::UnLoad();
	// ���b�V���X�t�B�A
	CMeshsphere::Unload();
	// �~�`�V���h�E
	CCircleshadow::UnLoad();
	// ���b�V���E�H�[��
	CMeshwall::UnLoad();
	// �t�F�[�h
	CFade::UnLoad();
}