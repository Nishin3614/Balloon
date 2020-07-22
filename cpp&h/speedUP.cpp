// ==========================================================
//
// �v���C���[(�X�s�[�h�A�b�v)���� [speedUP.cpp]
// Author : RYOUMA INOUE
//
// ==========================================================
#include "speedUP.h"
#include "manager.h"

// ==========================================================
//
// �}�N����`
//
// ==========================================================
#define INVISIBLE_FRONTFORCE (10)
#define INVISIBLE_G (0.5f)			// �d��
#define INVISIBLE_RESISTANCE (0.5f)// ��R��

// ==========================================================
//
// �ÓI�ϐ��錾
//
// ==========================================================

// ==========================================================
// �R���X�g���N�^����
// ==========================================================
CSpeedUP::CSpeedUP() : CPlayer::CPlayer(CHARACTER_BALLOON1)
{
}

// ==========================================================
// �f�X�g���N�^����
// ==========================================================
CSpeedUP::~CSpeedUP()
{
}

// ==========================================================
// ����������
// ==========================================================
void CSpeedUP::Init(void)
{
	CPlayer::Init();

	// ��Ԃ̏�����
	m_bSpeedUP = false;
}

// ==========================================================
// �I������
// ==========================================================
void CSpeedUP::Uninit(void)
{
	CPlayer::Uninit();
}

// ==========================================================
// �X�V����
// ==========================================================
void CSpeedUP::Update(void)
{
	CPlayer::Update();
}

// ==========================================================
// �`�揈��
// ==========================================================
void CSpeedUP::Draw(void)
{
	CPlayer::Draw();
}

// ==========================================================
// ���񂾂Ƃ��̏���
// ==========================================================
void CSpeedUP::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
// ==========================================================
// �f�o�b�O�\��
// ==========================================================
void CSpeedUP::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ==========================================================
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CSpeedUP::Scene_MyCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_MyCollision(nObjType, pScene);
}

// ==========================================================
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ==========================================================
void CSpeedUP::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_OpponentCollision(nObjType, pScene);
}

// ==========================================================
// ��������(�V�[���Ǘ�)
// ==========================================================
CSpeedUP * CSpeedUP::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CSpeedUP * pSpeedUP;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pSpeedUP = new CSpeedUP();
	// �V�[���Ǘ��ݒ�
	pSpeedUP->ManageSetting(CScene::LAYER_CHARACTER);
	// �ݒ�
	pSpeedUP->SetPlayerID(nPlayerID);
	pSpeedUP->SetPos(pos);
	pSpeedUP->SetRot(rot);
	pSpeedUP->SetRotDest(rot);
	// ����������
	pSpeedUP->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pSpeedUP;
}

// ==========================================================
// ��������(�l�Ǘ�)
// ==========================================================
CSpeedUP * CSpeedUP::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// �ϐ��錾
	CSpeedUP * pSpeedUP;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pSpeedUP = new CSpeedUP();
	// �ݒ�
	pSpeedUP->SetPlayerID(nPlayerID);
	pSpeedUP->SetPos(pos);
	pSpeedUP->SetRot(rot);
	pSpeedUP->SetRotDest(rot);
	// ����������
	pSpeedUP->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pSpeedUP;
}

// ==========================================================
// ���\�[�X���ǂݍ��ݏ���
// ==========================================================
HRESULT CSpeedUP::Load(void)
{
	return S_OK;
}

// ==========================================================
// �ǂݍ��񂾃��\�[�X����j������
// ==========================================================
void CSpeedUP::UnLoad(void)
{

}