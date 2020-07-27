// ==========================================================
//
// �v���C���[(����)���� [invisible.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "invisible.h"
#include "manager.h"
#include "character.h"

// ==========================================================
//
// �}�N����`
//
// ==========================================================
#define INVISIBLE (0.3f)

// ==========================================================
//
// �ÓI�ϐ��錾
//
// ==========================================================

// ==========================================================
// �R���X�g���N�^����
// ==========================================================
CInvisible::CInvisible() : CPlayer::CPlayer(CHARACTER_BALLOON3)
{
}

// ==========================================================
// �f�X�g���N�^����
// ==========================================================
CInvisible::~CInvisible()
{
}

// ==========================================================
// ����������
// ==========================================================
void CInvisible::Init(void)
{
	CPlayer::Init();

	// ��Ԃ̏�����
	m_bInvisible = false;
}

// ==========================================================
// �I������
// ==========================================================
void CInvisible::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// �X�V����
// ==========================================================
void CInvisible::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// ��ԕω�
		m_bInvisible = true;
	}
	else
	{
		// ��ԕω�
		m_bInvisible = false;
	}
}

// ==========================================================
// �`�揈��
// ==========================================================
void CInvisible::Draw(void)
{
	CPlayer::Draw();

	if (m_bInvisible == true)
	{
		CCharacter::SetAlpha(INVISIBLE);
	}
	else
	{
		CCharacter::SetAlpha(1.0f);
	}
}

// ==========================================================
// ���񂾂Ƃ��̏���
// ==========================================================
void CInvisible::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// �f�o�b�O�\��
// ==========================================================
void CInvisible::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CInvisible::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CInvisible::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// ��������(�V�[���Ǘ�)
// ==========================================================
CInvisible * CInvisible::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CInvisible * pInvisible;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pInvisible = new CInvisible();
	// �V�[���Ǘ��ݒ�
	pInvisible->ManageSetting(CScene::LAYER_CHARACTER);
	// �ݒ�
	pInvisible->SetPlayerID(nPlayerID);
	pInvisible->SetPos(pos);
	pInvisible->SetRot(rot);
	pInvisible->SetRotDest(rot);
	// ����������
	pInvisible->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pInvisible;
}

// ==========================================================
// ��������(�l�Ǘ�)
// ==========================================================
CInvisible * CInvisible::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CInvisible * pInvisible;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pInvisible = new CInvisible();
	// �ݒ�
	pInvisible->SetPlayerID(nPlayerID);
	pInvisible->SetPos(pos);
	pInvisible->SetRot(rot);
	pInvisible->SetRotDest(rot);
	// ����������
	pInvisible->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pInvisible;
}

// ==========================================================
// ���\�[�X���ǂݍ��ݏ���
// ==========================================================
HRESULT CInvisible::Load(void)
{
	return S_OK;
}

// ==========================================================
// �ǂݍ��񂾃��\�[�X����j������
// ==========================================================
void CInvisible::UnLoad(void)
{

}