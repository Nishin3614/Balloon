// ==========================================================
//
// �A�C�e��[item.cpp]
// Author:Ryouma Inoue
//
// ==========================================================
#include "item.h"
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
CItem *CItem::m_pItem = NULL;
LPDIRECT3DTEXTURE9 CItem::m_pTex = NULL;

// ==========================================================
// �O���[�o���ϐ�
// ==========================================================

// ==========================================================
//
// �R���X�g���N�^
//
// ==========================================================
CItem::CItem() :CScene_THREE()
{
	m_pCollision = NULL;
}

// ==========================================================
//
// �f�X�g���N�^
//
// ==========================================================
CItem::~CItem()
{

}

// ==========================================================
// �e�̏�����
// ==========================================================
void CItem::Init(void)
{
	// �I�t�Z�b�g�^�C�v�ݒ�
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// �F�̐ݒ�
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	m_pCollision = CSphereCollision::Create(50, D3DVECTOR3_ZERO, CCollision::OBJTYPE_ITEM, this,NULL, false,false, &m_pos);
	// �r���{�[�h
	CScene_THREE::SetBillboard(true);
	CScene_THREE::SetLighting(true);		// ���C�e�B���O
	// �e�N�X�`���[�^�C�v�ݒ�
	CScene_THREE::SetTexType(21);	// �e�N�X�`���[�n��
	m_pos = m_pItem->GetPos();
}

// ==========================================================
// �I��
// ==========================================================
void CItem::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ==========================================================
// �X�V
// ==========================================================
void CItem::Update(void)
{
	CScene_THREE::Update();
}

// ==========================================================
// �e�̕`��
// ==========================================================
void CItem::Draw(void)
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
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[�����I�Ɋm��
	m_pItem = new CItem();

	// �ʒu�ݒ�
	m_pItem->SetPos(pos);

	// �T�C�Y�ݒ�
	m_pItem->SetSize(size);

	// �V�[��������
	m_pItem->Init();

	m_pItem->ManageSetting(LAYER_3DOBJECT2);

	// �l��Ԃ�
	return m_pItem;
}

// ==========================================================
// �e�N�X�`�����[�h
// ==========================================================
HRESULT CItem::Load(void)
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
void CItem::Unload(void)
{
	// �e�N�X�`�����
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}

// ==========================================================
// ����������̏���
// ����1:�I�u�W�F�N�g�^�C�v
// ����2:����̃V�[�����
// ==========================================================
void CItem::Scene_Collision(int const & nObjType, CScene * pScene)
{
	// �I�u�W�F�N�g�^�C�v���L�����N�^�[�Ȃ�
	if (nObjType == CCollision::OBJTYPE_CHARACTER)
	{
		Release();
		m_pCollision->Release();
		m_pCollision = NULL;
	}
}

// ==========================================================
// �����蔻��
// ==========================================================
bool CItem::ItemCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin)
{
	bool bCollide = false;

	if ((m_pos.x + m_vtxMin.x <= pPos->x + pVtxMax->x) &&
		(m_pos.x + m_vtxMax.x >= pPos->x + pVtxMin->x) &&
		(m_pos.z + m_vtxMin.z <= pPos->z + pVtxMax->z) &&
		(m_pos.z + m_vtxMax.z >= pPos->z + pVtxMin->z) &&
		(m_pos.y + m_vtxMin.y <= pPos->y + pVtxMax->y))
	{
		bCollide = true;
	}

	return bCollide;
}

