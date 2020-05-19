// ----------------------------------------
//
// �o�b�O�O���E���h�h�[�������̐���[bgdome.cpp]
// Author : Koki Nishiyama
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "bgdome.h"
#include "meshdome.h"
#include "game.h"
#include "scene.h"
#include "debugproc.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define BGDOME_ROTMOVE (0.1f)				// �p�x�̈ړ���
#define BGDOME_SIZE (100.0f)				// �T�C�Y

// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CBgdome::CBgdome() : CScene()
{
	m_bUse = false;				// �g�p���
	m_CntFrame = 0;				// �J�E���g�t���[��
	m_nMaxFrame = 0;				// �ő�t���[��
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CBgdome::~CBgdome()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CBgdome::Init(void)
{
	/* �ϐ��̏����� */
	for (int nCntBgdome = 0; nCntBgdome < TYPE_MAX; nCntBgdome++)
	{
		m_aMeshdome[nCntBgdome] = CMeshdome::Create(
			m_pos,
			D3DXVECTOR3(500.0f, 500.0f, 500.0f),
			10,
			10
		);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CBgdome::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CBgdome::Update(void)
{
	if (m_bUse)
	{
		// �t���[���J�E���g�A�b�v
		m_CntFrame++;
		if (m_CntFrame >= m_nMaxFrame)
		{
			// �g�p���
			SetUse(false);
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CBgdome::Draw(void)
{
}

#ifdef _DEBUG
// ----------------------------------------
// �f�o�b�O�\������
// ----------------------------------------
void CBgdome::Debug(void)
{
}
#endif // _DEBUG
// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CBgdome::Load(void)
{
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CBgdome::UnLoad(void)
{
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CBgdome * CBgdome::Create(D3DXVECTOR3 const &pos)
{
	// �ϐ��錾
	CBgdome * pBgdome;		// �V�[��2D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pBgdome = new CBgdome();
	// �V�[���Ǘ��ݒ�
	pBgdome->ManageSetting(CScene::LAYER_3DOBJECT);
	// �ݒ�
	pBgdome->m_pos = pos;
	// ����������
	pBgdome->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pBgdome;
}

// ----------------------------------------
// �g�p��ԏ���
// ----------------------------------------
void CBgdome::SetUse(bool bUse)
{
	for (int nCntBgdome = 0; nCntBgdome < TYPE_MAX; nCntBgdome++)
	{
		m_aMeshdome[nCntBgdome]->SetUse(bUse);
	}
	m_bUse = bUse;
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CBgdome::SetPos(D3DXVECTOR3 const & pos)
{
	for (int nCntBgdome = 0; nCntBgdome < TYPE_MAX; nCntBgdome++)
	{
		m_aMeshdome[nCntBgdome]->SetPos(pos);
	}
}

// ----------------------------------------
// ��]�ݒ菈��
// ----------------------------------------
void CBgdome::SetRot(D3DXVECTOR3 const & rot)
{
	for (int nCntBgdome = 0; nCntBgdome < TYPE_MAX; nCntBgdome++)
	{
		m_aMeshdome[nCntBgdome]->SetRot(rot);
	}
}

// ----------------------------------------
// �ݒ菈��
// ----------------------------------------
void CBgdome::Set(
	D3DXVECTOR3 const & pos, 
	D3DXVECTOR3 const & rot, 
	int const & nFrame
)
{
	for (int nCntBgdome = 0; nCntBgdome < TYPE_MAX; nCntBgdome++)
	{
		m_aMeshdome[nCntBgdome]->SetPos(pos);
		m_aMeshdome[nCntBgdome]->SetRot(rot);
		m_aMeshdome[nCntBgdome]->SetUse(true);
	}
	m_CntFrame = 0;
	m_bUse = true;
	m_nMaxFrame = nFrame;
}
