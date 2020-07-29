// ==========================================================
//
// ��[lake.cpp]
// Author : masayasu wakita
//
// ==========================================================
#include "lake.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "sound.h"
#include "character.h"
#include "spherecollision.h"

// ==========================================================
// �ÓI�����o�[�ϐ��̏�����
// ==========================================================
LPDIRECT3DTEXTURE9 CLake::m_pTex = NULL;

// ==========================================================
//
// �R���X�g���N�^
//
// ==========================================================
CLake::CLake() :CScene_THREE()
{
	m_fAnim = 0.0f;
}

// ==========================================================
//
// �f�X�g���N�^
//
// ==========================================================
CLake::~CLake()
{

}

// ==========================================================
// �e�̏�����
// ==========================================================
void CLake::Init(void)
{
	// �I�t�Z�b�g�^�C�v�ݒ�
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// �F�̐ݒ�
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	// �r���{�[�h
	CScene_THREE::SetBillboard(false);
	CScene_THREE::SetLighting(true);		// ���C�e�B���O
	// �e�N�X�`���[�^�C�v�ݒ�
	CScene_THREE::SetTexType(28);	// �e�N�X�`���[�n��
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_pos = GetPos();
}

// ==========================================================
// �I��
// ==========================================================
void CLake::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// �X�V
// ==========================================================
void CLake::Update(void)
{
	m_fAnim += 0.0003f;
	SetTex(D3DXVECTOR2(0.0f + m_fAnim, 0.0f + m_fAnim), D3DXVECTOR2(1.0f + m_fAnim, 1.0f + m_fAnim));
	CScene_THREE::Update();
}

// ==========================================================
// �e�̕`��
// ==========================================================
void CLake::Draw(void)
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
// �e�̐���
// ==========================================================
CLake *CLake::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLake *pLake = NULL;

	// �V�[�����I�Ɋm��
	pLake = new CLake();

	if (pLake != NULL)
	{// �΂����݂��Ă����Ƃ�
		pLake->SetPos(pos);							// �ʒu�ݒ�
		pLake->SetSize(size);						// �T�C�Y�ݒ�
		pLake->SetRot(D3DXVECTOR3(D3DX_PI / 2, 0.0, 0.0f));
		pLake->Init();								// ������
		pLake->ManageSetting(LAYER_3DOBJECT2);
		return pLake;
	}

	// �l��Ԃ�
	return NULL;
}

// ==========================================================
// �e�N�X�`�����[�h
// ==========================================================
HRESULT CLake::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_pTex);
	return S_OK;
}

// ==========================================================
// �j��
// ==========================================================
void CLake::Unload(void)
{
	// �e�N�X�`�����
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}