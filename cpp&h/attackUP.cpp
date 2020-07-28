// ==========================================================
//
// �v���C���[(�A�^�b�N�A�b�v)���� [attackUP.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "attackUP.h"
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
CAttackUP::CAttackUP() : CPlayer::CPlayer(CHARACTER_BALLOON4)
{
}

// ==========================================================
// �f�X�g���N�^����
// ==========================================================
CAttackUP::~CAttackUP()
{
}

// ==========================================================
// ����������
// ==========================================================
void CAttackUP::Init(void)
{
	CPlayer::Init();

	// ��Ԃ̏�����
	m_bAttackUP = false;
}

// ==========================================================
// �I������
// ==========================================================
void CAttackUP::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// �X�V����
// ==========================================================
void CAttackUP::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// ��ԕω�
		m_bAttackUP = true;
	}
	else
	{
		// ��ԕω�
		m_bAttackUP = false;
	}
}

// ==========================================================
// �`�揈��
// ==========================================================
void CAttackUP::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// ���񂾂Ƃ��̏���
// ==========================================================
void CAttackUP::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// �f�o�b�O�\��
// ==========================================================
void CAttackUP::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CAttackUP::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CAttackUP::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// ��������(�V�[���Ǘ�)
// ==========================================================
CAttackUP * CAttackUP::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CAttackUP * pAttackUP;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pAttackUP = new CAttackUP();
	// �V�[���Ǘ��ݒ�
	pAttackUP->ManageSetting(CScene::LAYER_CHARACTER);
	// �ݒ�
	pAttackUP->SetPlayerID(nPlayerID);
	pAttackUP->SetPos(pos);
	pAttackUP->SetRot(rot);
	pAttackUP->SetRotDest(rot);
	// ����������
	pAttackUP->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pAttackUP;
}

// ==========================================================
// ��������(�l�Ǘ�)
// ==========================================================
CAttackUP * CAttackUP::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CAttackUP * pAttackUP;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pAttackUP = new CAttackUP();
	// �ݒ�
	pAttackUP->SetPlayerID(nPlayerID);
	pAttackUP->SetPos(pos);
	pAttackUP->SetRot(rot);
	pAttackUP->SetRotDest(rot);
	// ����������
	pAttackUP->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pAttackUP;
}

// ==========================================================
// ���\�[�X���ǂݍ��ݏ���
// ==========================================================
HRESULT CAttackUP::Load(void)
{
	return S_OK;
}

// ==========================================================
// �ǂݍ��񂾃��\�[�X����j������
// ==========================================================
void CAttackUP::UnLoad(void)
{

}