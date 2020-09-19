// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���D�O���[�v�����̐���[balloon_group.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "balloon_group.h"
#include "p_thunder.h"
#include "3Dparticle.h"
#include "selectcharacter.h"
#include "spherecollision.h"
#include "circleshadow.h"
#include "network.h"
#include "game.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BALLOON_GROUP_Y				(60.0f)								// �ʒuy
#define BALLOON_GROUP_RADIUS		(30.0f)								// ���a
#define BALLOON_OFFSET_POS			(D3DXVECTOR3(0.0f,100.0f,0.0f))		// �I�t�Z�b�g�ʒu
#define BALLOON_COLLISION_RADIUS	(35.0f)								// �����蔻��̔��a
#define BALLOON_INVINCIBLE			(DERAY_TIME(3))						// ���G�J�E���g

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::CBalloon_group() : CScene::CScene()
{
	// ������
	m_nPopBalloon_group = 2;
	m_nBringBalloon_group = 0;
	m_pPos = NULL;
	m_offsetPos = BALLOON_OFFSET_POS;
	m_Corepos = D3DVECTOR3_ZERO;
	m_fAngleBalloon_group = 0;
	m_pCollision = NULL;
	m_pMtx = NULL;
	m_nActorId = -1;
	m_nCntInvincible = BALLOON_INVINCIBLE;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::~CBalloon_group()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Init(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Uninit(void)
{
	// �I������
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
	}
	// �����蔻����̊J��
	if (m_pCollision != NULL)
	{
		m_pCollision->CompulsionScene();
		m_pCollision->Release();
		m_pCollision = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Update(void)
{
	// �ŏI�I�Ȉʒu���̍X�V
	m_Corepos = *m_pPos + m_offsetPos;
	// ���D�̍X�V����
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// ���G�J�E���g���K�萔���Ƃɓ_��
		if (m_nCntInvincible >= BALLOON_INVINCIBLE)
		{
			m_apBalloon[nCntBalloon_group]->SetModelAlpha(1.0f);
		}
		else if (m_nCntInvincible % 10 == 0)
		{
			m_apBalloon[nCntBalloon_group]->SetModelAlpha(1.0f);
		}
		else if (m_nCntInvincible % 5 == 0)
		{
			m_apBalloon[nCntBalloon_group]->SetModelAlpha(0.0f);
		}
		// �X�V
		m_apBalloon[nCntBalloon_group]->Update();
	}
	/*
	// �v���C���[���
	for (int nCntPlayer = 0; nCntPlayer < CScene::GetMaxLayer(CScene::LAYER_CHARACTER); nCntPlayer++)
	{
		CPlayer * pPlayer = (CPlayer *)CScene::GetScene(CScene::LAYER_CHARACTER, nCntPlayer);
		if (pPlayer == NULL) continue;
		else if (pPlayer->GetPlayerID == CManager::GetNetwork()->GetId())
		{

		}
	}
	*/
	// �����蔻�肪NULL�ł͂Ȃ��Ȃ�
	// �X�V
	if (m_pCollision != NULL)
	{
		// �ʒu���̍X�V(�s��n��)
		m_pCollision->GetShape()->PassMatrix(*m_pMtx);
		// �X�V
		m_pCollision->Update();
		if (m_nCntInvincible <= BALLOON_INVINCIBLE)
		{
			// ���G�J�E���g�A�b�v
			m_nCntInvincible++;
		}
		return;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�揈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Draw(void)
{
	// ���D�̍X�V����
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// �`��
		m_apBalloon[nCntBalloon_group]->Draw();
	}
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O�\��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Debug(void)
{
	//CDebugproc::Print("�������Ă��镗�D�O���[�v�̐�[%d]\n", m_nBringBalloon_group);
	//CDebugproc::Print("�o�����Ă��镗�D�O���[�v�̐�[%d]\n", m_nPopBalloon_group);
	//CDebugproc::Print("���D�O���[�v[%d]pos(%.1f,%.1f,%.1f)\n",m_nActorId,m_pPos->x, m_pPos->y, m_pPos->z);
}
#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Scene_MyCollision(
	int const &nObjType,	// �I�u�W�F�N�g�^�C�v
	CScene * pScene			// ����̃V�[�����
)
{
	// ����̃I�u�W�F�N�g�^�C�v���L�����N�^�[�Ȃ�
	if (nObjType == CCollision::OBJTYPE_PLAYER ||
		nObjType == CCollision::OBJTYPE_ENEMY)
	{
		if (m_nActorId == CManager::GetNetwork()->GetId())
		{
			// ���D����鏈��
			CrackBalloon();
			CManager::GetNetwork()->SendTCP("HIT", sizeof("HIT"));
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Scene_OpponentCollision(
	int const &nObjType,	// �I�u�W�F�N�g�^�C�v
	CScene * pScene			// ����̃V�[�����
)
{
	// ����̃I�u�W�F�N�g�^�C�v���L�����N�^�[�Ȃ�
	if (nObjType == CCollision::OBJTYPE_PLAYER ||
		nObjType == CCollision::OBJTYPE_ENEMY)
	{
		if (m_nActorId == CManager::GetNetwork()->GetId())
		{
			// ���G�J�E���g���K��J�E���g���z���Ă��Ȃ�������
			// ->�֐��𔲂���
 			if (m_nCntInvincible < BALLOON_INVINCIBLE) return;
			// ���D����鏈��
			CrackBalloon();
			CManager::GetNetwork()->SendTCP("HIT", sizeof("HIT"));
			// ���G�J�E���g������
			m_nCntInvincible = 0;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ʒu���ݒ�
// pPos:�ʒu���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetPPos(
	D3DXVECTOR3 * pPos	// �ʒu���
)
{
	// �ʒu���̃|�C���^�[��������
	m_pPos = pPos;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O�ɏo���Ēu���镗�D�O���[�v�̍ő����ݒ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetPopMaxBalloom(
	int const & nPopMaxBaloon,
	int const & nObjType,
	CScene * pParent
)
{
	// �ő�o��������
	m_nMaxPopBalloon_group = nPopMaxBaloon;
	// �p�x
	m_fAngleBalloon_group = D3DX_PI / m_nMaxPopBalloon_group * 2;
	// �����ݒ�
	for (int nCntBalloon_group = 0; nCntBalloon_group < m_nMaxPopBalloon_group; nCntBalloon_group++)
	{
		//���D�O���[�v����
		m_apBalloon.push_back(CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
			m_pPos,
			D3DVECTOR3_ZERO,
			0
		));
		//// �����蔻��ݒ�(��)
		//m_apBalloon[nCntBalloon_group]->SetCollision(
		//	CShape::SHAPETYPE_SPHERE,
		//	nObjType,
		//	false,
		//	true,
		//	pParent,
		//	BALLOON_OFFSET_POS
		//);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D�O���[�v�𐶐�����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CreateBalloon_group(
	int const & nObjType,
	CScene * pParent
)
{
	// ���D�O���[�v��������
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] != NULL) continue;
		// ���D����
		m_apBalloon[nCntBalloon_group] = CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
			m_pPos,
			D3DVECTOR3_ZERO,
			0
		);
		// �����Ă��镗�D�O���[�v�̌������炷
		m_nBringBalloon_group--;
		// �o�����Ă��镗�D�O���[�v�̌��𑝂₷
		m_nPopBalloon_group++;
		// �G�t�F�N�g��p�ӂ���Ȃ炱��
		// �����蔻��̎g�p��Ԃ�true��
		m_pCollision->SetUse(true);

		// �����������I��������
		// ->�֐��𔲂���
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻��������I�ɍ폜
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CollisionDelete(void)
{
	// �����蔻����̊J��
	if (m_pCollision != NULL)
	{
		m_pCollision->CompulsionScene();
		m_pCollision->Release();
		m_pCollision = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D���擾����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon * CBalloon_group::GetBalloon(int const & nBalloon_group)
{
	// 0 < nBalloon_group <= BALLOON_GROUP_MAX�Ȃ�
	// ->�֐��𔲂���
	if (nBalloon_group < 0 || nBalloon_group >= (signed)m_apBalloon.size())
	{
#ifdef _DEBUG
		CCalculation::Messanger("CBalloon_group::GetSceneX->����z��");
#endif // _DEBUG
		return NULL;
	}
	// ���D�̏���Ԃ�
	return m_apBalloon[nBalloon_group];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �쐬����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group * CBalloon_group::Create(
	D3DXVECTOR3 *pPos,					// �ʒu���
	D3DXMATRIX	*pMtx,					// �s����
	int const &nPopMaxBalloon_group,	// �ő啗�D�O���[�v��
	int const &nObjType,				// �I�u�W�F�N�g�^�C�v
	CScene * pParent					// �e���
)
{
	// �ϐ��錾
	CBalloon_group * pBalloon_group;		// �V�[��3D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pBalloon_group = new CBalloon_group();
	// �V�[���Ǘ��ݒ�
	pBalloon_group->ManageSetting(CScene::LAYER_3DOBJECT);
	// ����������
	pBalloon_group->Init();
	// �ʒu���ݒ�
	pBalloon_group->SetPPos(pPos);
	// �O�ɏo���Ēu���镗�D�O���[�v�̍ő����ݒ�
	pBalloon_group->SetPopMaxBalloom(
		nPopMaxBalloon_group,
		nObjType,
		pParent
	);
	// �o�����Ă��镗�D�O���[�v�̌��ɑ������
	pBalloon_group->m_nPopBalloon_group = nPopMaxBalloon_group;
	// �s����ݒ�
	pBalloon_group->m_pMtx = pMtx;
	// �����蔻��̐ݒ�
	pBalloon_group->SetCollision(nObjType, pParent);
	// ���������I�u�W�F�N�g��Ԃ�
	return pBalloon_group;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���\�[�X���ǂݍ��ސݒ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CBalloon_group::Load(void)
{
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��񂾃��\�[�X�����J������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::UnLoad(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻����ݒ菈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetCollision(
	int const &nObjType,				// �I�u�W�F�N�g�^�C�v
	CScene * pParent					// �e���
)
{
	// �����蔻�萶��
	m_pCollision = CSphereCollision::Create(
		BALLOON_COLLISION_RADIUS,
		D3DVECTOR3_ZERO,
		(CCollision::OBJTYPE)nObjType,
		this,
		pParent,
		false,
		true,
		&m_Corepos
	);
	// �ʒu���̍X�V(�s��n��)
	m_pCollision->GetShape()->PassMatrix(*m_pMtx);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D������鏈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CrackBalloon(
	int const &nCrackBalloon	// ����镗�D��
)
{
	// �ϐ��錾
	int nCntCrack = nCrackBalloon;	// ���ꂽ���D�J�E���g
	// ���D���[�v
	for (int nCntBalloon = 0; nCntBalloon < (signed)m_apBalloon.size(); nCntBalloon++)
	{
		// �����蔻���Ԃ�NULL�Ȃ�
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon] == NULL)
		{
			continue;
		}
		// ���D������鉹1
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_BALLOONBREAK1);
		// ���D���ꂽ���̃p�[�e�B�N������
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOONBREAK, m_apBalloon[nCntBalloon]->GetPos());
		// ���D�̏I������
		m_apBalloon[nCntBalloon]->Uninit();
		// ���D�̊J��
		delete m_apBalloon[nCntBalloon];
		m_apBalloon[nCntBalloon] = NULL;
		// �o�����Ă��镗�D�O���[�v�̌������炷
		m_nPopBalloon_group--;
		// ����镗�D���J�E���g�����炷
		nCntCrack--;
		// �S�Ă̕��D������Ă�����
		if (nCntBalloon == (signed)m_apBalloon.size() - 1)
		{
			// �����蔻��̎g�p��Ԃ�false��
			m_pCollision->SetUse(false);
		}
		// ����镗�D���J�E���g��0�ȉ��Ȃ�
		// ->���[�v�𔲂���
		if (nCntCrack <= 0)
		{
			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D�O���[�v������鏈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::BreakBalloon_group(int const &nCntBalloon_group)
{
	// �����蔻���Ԃ�true�Ȃ�
	// ->�J��
	if (m_apBalloon[nCntBalloon_group]->GetBalloonCollision())
	{
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
		// �o�����Ă��镗�D�O���[�v�̌������炷
		m_nPopBalloon_group--;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���ŕ��D�����点�鏈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Thunder_BreakBalloon_group(void)
{
	// ���D�����点�鏈��
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// �I������
		m_apBalloon[nCntBalloon_group]->Uninit();
		// ���D�̊J��
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
		// �o�����Ă��镗�D�O���[�v�̌��𑝂₷
		m_nPopBalloon_group--;
		// ����D����������֐��𔲂���
		return;
	}
}
