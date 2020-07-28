// ==========================================================
//
// �v���C���[(����)���� [revival.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "revival.h"
#include "manager.h"

// ==========================================================
//
// �}�N����`
//
// ==========================================================

// ==========================================================
//
// �ÓI�ϐ��錾
//
// ==========================================================

// ==========================================================
// �R���X�g���N�^����
// ==========================================================
CRevival::CRevival() : CPlayer::CPlayer(CHARACTER_BALLOON2)
{
}

// ==========================================================
// �f�X�g���N�^����
// ==========================================================
CRevival::~CRevival()
{
}

// ==========================================================
// ����������
// ==========================================================
void CRevival::Init(void)
{
	CPlayer::Init();

	// ��Ԃ̏�����
	m_bRevival = false;
}

// ==========================================================
// �I������
// ==========================================================
void CRevival::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// �X�V����
// ==========================================================
void CRevival::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// ��ԕω�
		m_bRevival = true;

		CCharacter_Balloon::BalloonCreate();
	}
	else
	{
		// ��ԕω�
		m_bRevival = false;
	}
}

// ==========================================================
// �`�揈��
// ==========================================================
void CRevival::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// ���񂾂Ƃ��̏���
// ==========================================================
void CRevival::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// �f�o�b�O�\��
// ==========================================================
void CRevival::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CRevival::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CRevival::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// ��������(�V�[���Ǘ�)
// ==========================================================
CRevival * CRevival::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CRevival * pRevival;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pRevival = new CRevival();
	// �V�[���Ǘ��ݒ�
	pRevival->ManageSetting(CScene::LAYER_CHARACTER);
	// �ݒ�
	pRevival->SetPlayerID(nPlayerID);
	pRevival->SetPos(pos);
	pRevival->SetRot(rot);
	pRevival->SetRotDest(rot);
	// ����������
	pRevival->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pRevival;
}

// ==========================================================
// ��������(�l�Ǘ�)
// ==========================================================
CRevival * CRevival::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CRevival * pRevival;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pRevival = new CRevival();
	// �ݒ�
	pRevival->SetPlayerID(nPlayerID);
	pRevival->SetPos(pos);
	pRevival->SetRot(rot);
	pRevival->SetRotDest(rot);
	// ����������
	pRevival->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pRevival;
}

// ==========================================================
// ���\�[�X���ǂݍ��ݏ���
// ==========================================================
HRESULT CRevival::Load(void)
{
	return S_OK;
}

// ==========================================================
// �ǂݍ��񂾃��\�[�X����j������
// ==========================================================
void CRevival::UnLoad(void)
{

}