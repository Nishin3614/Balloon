// ==========================================================
//
// �v���C���[(�X�R�A�A�b�v)���� [scoreUP.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "scoreUP.h"
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
bool CScoreUP::m_bScoreUP = false;

// ==========================================================
// �R���X�g���N�^����
// ==========================================================
CScoreUP::CScoreUP() : CPlayer::CPlayer(CHARACTER_BALLOON4)
{
}

// ==========================================================
// �f�X�g���N�^����
// ==========================================================
CScoreUP::~CScoreUP()
{
}

// ==========================================================
// ����������
// ==========================================================
void CScoreUP::Init(void)
{
	CPlayer::Init();

	// ��Ԃ̏�����
	m_bScoreUP = false;
}

// ==========================================================
// �I������
// ==========================================================
void CScoreUP::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// �X�V����
// ==========================================================
void CScoreUP::Update(void)
{
	CPlayer::Update();

	if (CPlayer::GetMPMax() == true)
	{
		// ��ԕω�
		m_bScoreUP = true;
	}
	else
	{
		// ��ԕω�
		m_bScoreUP = false;
	}
}

// ==========================================================
// �`�揈��
// ==========================================================
void CScoreUP::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// ���񂾂Ƃ��̏���
// ==========================================================
void CScoreUP::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// �f�o�b�O�\��
// ==========================================================
void CScoreUP::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CScoreUP::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CScoreUP::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// ��������(�V�[���Ǘ�)
// ==========================================================
CScoreUP * CScoreUP::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CScoreUP * pScoreUP;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pScoreUP = new CScoreUP();
	// �V�[���Ǘ��ݒ�
	pScoreUP->ManageSetting(CScene::LAYER_CHARACTER);
	// �ݒ�
	pScoreUP->SetPlayerID(nPlayerID);
	pScoreUP->SetPos(pos);
	pScoreUP->SetRot(rot);
	pScoreUP->SetRotDest(rot);
	// ����������
	pScoreUP->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pScoreUP;
}

// ==========================================================
// ��������(�l�Ǘ�)
// ==========================================================
CScoreUP * CScoreUP::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CScoreUP * pScoreUP;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pScoreUP = new CScoreUP();
	// �ݒ�
	pScoreUP->SetPlayerID(nPlayerID);
	pScoreUP->SetPos(pos);
	pScoreUP->SetRot(rot);
	pScoreUP->SetRotDest(rot);
	// ����������
	pScoreUP->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pScoreUP;
}

// ==========================================================
// ���\�[�X���ǂݍ��ݏ���
// ==========================================================
HRESULT CScoreUP::Load(void)
{
	return S_OK;
}

// ==========================================================
// �ǂݍ��񂾃��\�[�X����j������
// ==========================================================
void CScoreUP::UnLoad(void)
{

}