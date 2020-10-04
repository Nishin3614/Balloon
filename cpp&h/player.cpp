// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���f������ [player.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "player.h"
#include "input.h"
#include "camera.h"
#include "balloon_group.h"
#include "ui.h"
#include "network.h"
#include "manager.h"
#include "fade.h"
#include "collision.h"
#include "game.h"
#include "score.h"
#include "joypad.h"
#include "character_fish.h"
#include "2Dgauge.h"
#include "rank.h"
#include "scoreUP.h"
#include "invisible.h"
#include "framework.h"
#include "ui_group.h"
#include "meshdome.h"
#include "item.h"
#include "thundercloud.h"
#include "PointCircle.h"
#include "3Dparticle.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PLAYER_GRAVITY (0.1f)
#define PLAYER_UPMOVELIMIT		(10.0f)	// �v���C���[�̏㏸�ړ��ʐ���
#define PLAYER_UNDERMOVELIMIT	(5.0f)	// �v���C���[�̉��~�ړ��ʐ���

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int	CPlayer::m_All = 0;					// ����
bool CPlayer::m_bDie[MAX_PLAYER] = {};
CMeshdome *CPlayer::m_pMeshDome = NULL;	// �ړ�����x���\���p

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::CPlayer(CHARACTER const &character) : CCharacter_Balloon::CCharacter_Balloon(character)
{
	m_p2DMPGauge = NULL;			// MP�Q�[�W
	m_pRank = NULL;					// ���ݏ���
	m_nCloudCount = 0;				// �_���o������܂ł̃J�E���^
	m_posold = D3DVECTOR3_ZERO;		// �O�̈ʒu
	m_nCntState = 0;				// �X�e�[�g�J�E���g
	m_All++;						// ����
	m_nMP = 0;						// MP
	m_bMPMax = false;				// MP���ő傩�ǂ���
	m_bResetMP = false;				// MP�����Z�b�g
	m_nRank = -1;					// �����L���O�̏�����
	m_pFramework = NULL;			// �t���[�����[�N���
	for (int nCntFishApponent = 0; nCntFishApponent < MAX_FISHAPPONENT; nCntFishApponent++)
	{
		m_nCntFishApponent[nCntFishApponent] = 0;			// ���o���J�E���g
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	m_All--;						// ����
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Init(void)
{
	// �ϐ��錾
	CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N
	const int nId = pNetwork->GetId();				// ������ID���擾
	// �o���[���L�����N�^�[������
	CCharacter_Balloon::Init();
	// �ϐ��錾
	D3DXVECTOR3 pos;	// �Q�[�W�̔z�u�p

	// �ړ��ʑ��
	m_fMoveAdd = CCharacter::GetStatus().fMaxMove * 0.1f;
	m_fMoveNow = CCharacter::GetStatus().fMaxMove;

	// �J�����̏�����
	// �J�����̒����_�ݒ�
	CManager::GetRenderer()->GetCamera()->SetPosR(
		CCharacter::GetPos() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		CCharacter::GetRot() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f)
	);
	// �h�[����NULL�`�F�b�N
	if (m_pMeshDome == NULL)
	{
		// ���b�V���h�[���̐���
		m_pMeshDome = CMeshdome::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1300, 2000, 1300),
			10,
			10,
			CMeshdome::TYPE_WARNING,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			false,
			LAYER_BGDOME);

		if (m_pMeshDome != NULL)
		{
			// ���b�V���h�[���̎g�p���
			m_pMeshDome->SetUse(false);
			m_pMeshDome->SetDrawBack(true);
		}
	}
	// ���[�h���Q�[���Ȃ�
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �L�����N�^�[���̂̃v���C���[�ԍ��ƃR���g���[�����Ă���v���C���[�ԍ��������Ȃ�
		// ->�Q�[�W����
		if (m_nPlayerID == nId)
		{
			// �L�����N�^�[2
			if (GetCharacter() == CHARACTER_BALLOON2)
			{
				// MP�Q�[�W�̐���
				m_p2DMPGauge = C2DGauge::Create(
					PLAYER_UI_MP_POS,
					D3DXVECTOR2(480.0f, 25.0f),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
					GetCharacter()
				);

			}
			// �L�����N�^�[4
			else if (GetCharacter() == CHARACTER_BALLOON4)
			{
				// MP�Q�[�W�̐���
				m_p2DMPGauge = C2DGauge::Create(
					PLAYER_UI_MP_POS,
					D3DXVECTOR2(470.0f, 25.0f),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
					GetCharacter()
				);
			}
			else
			{
				// MP�Q�[�W�̐���
				m_p2DMPGauge = C2DGauge::Create(
					PLAYER_UI_MP_POS,
					D3DXVECTOR2(500.0f, 25.0f),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
					GetCharacter()
				);
			}
			// MP�Q�[�W�̕ω��萔��ݒ�
			m_p2DMPGauge->SetConstance((float)CCharacter::GetStatus().nMaxMp);
			// MP�Q�[�W�̕ω��萔��ݒ�
			m_p2DMPGauge->BeginGauge((float)m_nMP);
			// MP�Q�[�W�̃��C���J���[�ݒ�
			m_p2DMPGauge->SetMainCol(
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
			// �t���[�����[�N�̐���
			m_pFramework = CFramework::Create();
		}

		m_pRank = CRank::Create();

		if (m_pRank != NULL)
		{
			m_pRank->SetPos(m_pos);
		}

		m_bDie[m_nPlayerID] = false;
		CCharacter_Balloon::GetBalloon()->SetID(m_nPlayerID);

	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// MP�Q�[�W�̐���
		m_p2DMPGauge = C2DGauge::Create(
			PLAYER_UI_MP_POS,
			D3DXVECTOR2(500.0f, 25.0f),
			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
			GetCharacter()
		);
		// MP�Q�[�W�̕ω��萔��ݒ�
		m_p2DMPGauge->SetConstance((float)CCharacter::GetStatus().nMaxMp);
		// MP�Q�[�W�̕ω��萔��ݒ�
		m_p2DMPGauge->BeginGauge((float)m_nMP);
		// MP�Q�[�W�̃��C���J���[�ݒ�
		m_p2DMPGauge->SetMainCol(
			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
			D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
		// �t���[�����[�N�̐���
		m_pFramework = CFramework::Create();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	// �L�����N�^�[�̏I������
	CCharacter_Balloon::Uninit();
	// MP�Q�[�W�̊J��
	if (m_p2DMPGauge != NULL)
	{
		m_p2DMPGauge->Release();
		m_p2DMPGauge = NULL;
	}
	// �����N���̊J��
	if (m_pRank != NULL)
	{
		m_pRank->Release();
		m_pRank = NULL;
	}
	// �t���[�����[�N���̊J��
	if (m_pFramework != NULL)
	{
		m_pFramework->Release();
		m_pFramework = NULL;
	}
	// ���b�V���h�[���̊J��
	if (m_pMeshDome != NULL)
	{
		m_pMeshDome->Release();
		m_pMeshDome = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	const int nId = pNetwork->GetId();

	//CDebugproc::Print("[%d]��]�� : %f\n", m_nPlayerID, GetRot().y);
	CDebugproc::Print("[%d]�ʒu : %f\n", m_nPlayerID, m_pos.y);

	// �I����ʈȊO�Ȃ�
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �L�����N�^�[���̂̃v���C���[�ԍ��ƃR���g���[�����Ă���v���C���[�ԍ��������Ȃ�
		// ->�s������
		if (m_nPlayerID == nId)
		{
			// ���L�����̍s������
			MyAction(m_nPlayerID);
			Skill_Particle();
		}
		// ����ȊO�̃L�����N�^�[�̏���
		else
		{
			// ���L�����̍s������
			OtherAction();
		}
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// ���L�����̍s������
		MyAction(m_nPlayerID);
		Skill_Particle();
	}
	// ���[�V�����ݒ菈��
	StatusMotion();

	// �L�����N�^�[�X�V
	CCharacter_Balloon::Update();

	/* �v���g�^�C�v�p */
	// �L�����N�^�[�̋��錾
	if (CManager::GetPlayerID() != m_nPlayerID)
	{
		CCharacter::Limit();
	}

	if (m_pos.y > 900.0f)
	{
		if (m_nCloudCount > 10)
		{
			for (int nCount = 0; nCount < 5; nCount++)
			{
				D3DXVECTOR3 pos = CCharacter_Balloon::GetBalloon()->GetCorePos();
				CThunderCloud::Create(pos);
				m_nCloudCount = 0;
			}
		}
		else
		{
			m_nCloudCount++;
		}
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_pRank != NULL)
		{
			if (m_nRank != pNetwork->GetRank(m_nPlayerID))
			{
				m_nRank = pNetwork->GetRank(m_nPlayerID);
				m_pRank->SetAnimation(1.0f / 4, 1.0f, 0.0f, m_nRank - 1);
			}
		}

		if (pNetwork != NULL)
		{
			if (pNetwork->GetDie(m_nPlayerID))
			{
				OtherDie();
			}
		}

		if (m_pRank != NULL)
		{
			m_pRank->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 120.0f, m_pos.z));
		}

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// �L�����N�^�[���擾
			CCharacter::CHARACTER character = CCharacter::GetCharacter();

			// �v���C���[�̃X�R�A���Z�ǉ�
			if (m_nPlayerID == pNetwork->GetId())
			{
				if (CPointCircle::GetPoint() == true)
				{
					// �L�����N�^�[����v������
					if (character != CCharacter::CHARACTER_BALLOON2)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
					// �L�����N�^�[����v������
					if (character == CCharacter::CHARACTER_BALLOON2)
					{
						// ���
						if (CScoreUP::GetScoreUP() == true)
						{
							CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
						}
						else
						{
							CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
						}
					}
				}
			}
		}

	}

	if (m_pos.y <= -60.0f)
	{
		// ���D���ꂽ���̃p�[�e�B�N������
		C3DParticle::Create(C3DParticle::PARTICLE_ID_WATER, m_pos);
	}
#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_8))
	{
		CCharacter_Balloon::Thunder_BreakBalloon();
	}
#endif // _DEBUG
	//// ���o������
	//FishApponent();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���L�����s������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyAction(const int &nId)
{
	// ���L�����̈ړ�����
	MyMove();

	//// ���D��c��܂���
	//if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_BALLOONCREATE))
	//{
	//	// ���D�𐶐����鏈��
	//	CCharacter_Balloon::BalloonCreate();
	//}
	// MP�グ����(�}�C�t���[��)
	MpUp(CCharacter::GetStatus().nMaxMpUp_Every);
	// �J�����̍X�V
	Camera();
	// MP�Q�[�W�̕ω��萔��ݒ�
	if (m_p2DMPGauge != NULL)
	{
		m_p2DMPGauge->ChangeGauge((float)m_nMP);
	}
	D3DXVECTOR3 pos = GetPos();
	float fDifference = sqrtf(pos.x * pos.x + pos.z * pos.z);

	if (fDifference > 1000.0f)
	{
		if (m_pMeshDome != NULL)
		{
			if (!m_pMeshDome->GetUse())
			{
				m_pMeshDome->SetUse(true);
			}
		}
	}
	else
	{
		if (m_pMeshDome != NULL)
		{
			if (m_pMeshDome->GetUse())
			{
				m_pMeshDome->SetUse(false);
			}
		}
	}

	if (fDifference > 1200.0f)
	{// ��������������Ă����Ƃ�
		D3DXVECTOR3 save = pos - D3DXVECTOR3(0.0f, pos.y, 0.0f);
		D3DXVECTOR3 vec;
		D3DXVec3Normalize(&vec, &save);			//���K������

		float y = pos.y;

		// �H�����񂾕������߂�
		pos = vec * 1200.0f;

		pos.y = y;

		// �H�����񂾕������߂�
		SetPos(pos);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�L���ɂ��p�[�e�B�N������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Skill_Particle(void)
{
	// MP���}�b�N�X��Ԃł͂Ȃ��Ƃ�
	// ->�֐��𔲂���
	if (!m_bMPMax) return;
	// �L�����N�^�[�ɂ��p�[�e�B�N������
	switch (CCharacter::GetCharacter())
	{
		// �L�����N�^�[�o���[��1
	case CCharacter::CHARACTER_BALLOON1:
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON1SKILL, CCharacter::GetPos());
		break;
		// �L�����N�^�[�o���[��2
	case CCharacter::CHARACTER_BALLOON2:
		C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON2SKILL, CCharacter::GetPos());
		break;
	default:
		break;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ړ�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyMove(void)
{
	// �ϐ��錾
	D3DXVECTOR3 move, rot;			// �ړ��ʁA��]
	D3DXVECTOR3 vec;				// �x�N�g��
	float fRot;						// ��]

	// ���擾
	rot = CCharacter::GetRotDest();								// �ړI��]��
	move = CCharacter::GetMove();								// �ړ���
	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// �J������]
	vec = CCharacter::GetDirectionVec();						// �x�N�g��
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CJoypad *pJoypad = CManager::GetJoy();

	// �ړ� //
	/* �L�[�{�[�h */
	// ��
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		// �ړ����on
		CCharacter::SetbMove(true);
		// ��
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = -D3DX_PI * 0.25f + fRot;
			vec = D3DXVECTOR3(sinf(D3DX_PI * 0.75f + fRot), 0.0f, cosf(D3DX_PI * 0.75f + fRot));
			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// ���n��ԂȂ�
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// ��O
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = -D3DX_PI * 0.75f + fRot;
			vec = D3DXVECTOR3(sinf(D3DX_PI * 0.25f + fRot), 0.0f, cosf(D3DX_PI * 0.25f + fRot));
			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// ���n��ԂȂ�
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// ��
		else
		{
			rot.y = -D3DX_PI * 0.5f + fRot;
			vec = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + fRot), 0.0f, cosf(D3DX_PI * 0.5f + fRot));
			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// ���n��ԂȂ�
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
	}
	// �E
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		// �ړ����on
		CCharacter::SetbMove(true);

		// ��
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = D3DX_PI * 0.25f + fRot;
			vec = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f + fRot), 0.0f, cosf(-D3DX_PI * 0.75f + fRot));

			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// ���n��ԂȂ�
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// ��O
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = D3DX_PI * 0.75f + fRot;
			vec = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f + fRot), 0.0f, cosf(-D3DX_PI * 0.25f + fRot));

			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// ���n��ԂȂ�
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
		// �E
		else
		{
			rot.y = D3DX_PI * 0.5f + fRot;
			vec = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f + fRot), 0.0f, cosf(-D3DX_PI * 0.5f + fRot));

			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				move.x += vec.x * m_fMoveAdd;
				move.z += vec.z * m_fMoveAdd;
			}
			// ���n��ԂȂ�
			else
			{
				move.x += vec.x * m_fMoveNow;
				move.z += vec.z * m_fMoveNow;
			}
		}
	}
	// ���ɍs��
	else if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		// �ړ����on
		CCharacter::SetbMove(true);
		rot.y = D3DX_PI * 0.0f + fRot;
		vec = D3DXVECTOR3(sinf(-D3DX_PI * 1.0f + fRot), 0.0f, cosf(-D3DX_PI * 1.0f + fRot));
		// ���n��Ԃł͂Ȃ��Ȃ�
		if (!CCharacter::GetbLanding())
		{
			move.x += vec.x * m_fMoveAdd;
			move.z += vec.z * m_fMoveAdd;
		}
		// ���n��ԂȂ�
		else
		{
			move.x += vec.x * m_fMoveNow;
			move.z += vec.z * m_fMoveNow;
		}
	}
	// ��O�ɍs��
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		// �ړ����on
		CCharacter::SetbMove(true);
		rot.y = D3DX_PI * 1.0f + fRot;
		vec = D3DXVECTOR3(sinf(D3DX_PI * 0.0f + fRot), 0.0f, cosf(D3DX_PI * 0.0f + fRot));
		// ���n��Ԃł͂Ȃ��Ȃ�
		if (!CCharacter::GetbLanding())
		{
			move.x += vec.x * m_fMoveAdd;
			move.z += vec.z * m_fMoveAdd;
		}
		// ���n��ԂȂ�
		else
		{
			move.x += vec.x * m_fMoveNow;
			move.z += vec.z * m_fMoveNow;
		}
	}
	// ����ȊO
	else
	{
		// �ړ����off
		CCharacter::SetbMove(false);
	}

	/* �W���C�p�b�h */
	// �p�b�h�p //
	int nValueH, nValueV;	// �Q�[���p�b�h�̃X�e�B�b�N���̎擾�p
	float fMove;			// �ړ����x
	float fAngle;			// �X�e�B�b�N�p�x�̌v�Z�p�ϐ�
	fAngle = 0.0f;			// �p�x

	if (CManager::GetJoy() != NULL)
	{
		// �Q�[���p�b�h�̃X�e�B�b�N�����擾
		CManager::GetJoy()->GetStickLeft(0, nValueH, nValueV);

		// �v���C���[�ړ�
		// �Q�[���p�b�h�ړ�
		if (nValueH != 0 || nValueV != 0)
		{
			// �p�x�̌v�Z
			fAngle = atan2f((float)nValueH, (float)nValueV);

			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}
			// ���n��Ԃł͂Ȃ��Ȃ�
			if (!CCharacter::GetbLanding())
			{
				// ���x�̌v�Z
				if (abs(nValueH) > abs(nValueV))
				{
					fMove = (abs(nValueH) * m_fMoveAdd) / 1024.0f;
				}
				else
				{
					fMove = (abs(nValueV) * m_fMoveAdd) / 1024.0f;
				}
			}
			// ���n��ԂȂ�
			else
			{
				// ���x�̌v�Z
				if (abs(nValueH) > abs(nValueV))
				{
					fMove = (abs(nValueH) * m_fMoveNow) / 1024.0f;
				}
				else
				{
					fMove = (abs(nValueV) * m_fMoveNow) / 1024.0f;
				}
			}
			rot.y = fAngle + fRot;
			vec = D3DXVECTOR3(sinf(fAngle + fRot), 0.0f, cosf(fAngle + fRot));
			// �X�e�B�b�N�̊p�x�ɂ���ăv���C���[�ړ�
			move.x -= sinf(fAngle + fRot) * (fMove);
			move.z -= cosf(fAngle + fRot) * (fMove);
			// �ړ����on
			CCharacter::SetbMove(true);
		}
	}
	if (vec.x < 0)
	{
		vec.x *= -1;
	}
	if (vec.z < 0)
	{
		vec.z *= -1;
	}
	CCharacter::SetDirectionVec(vec);
	// ���D��NULL�ł͂Ȃ��Ȃ�
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		// ���D������Ȃ�
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
		{
			// ���ɕ���
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				move.y += CCharacter::GetStatus().fMaxJump;
			}
			else
			{
				if (pJoypad != NULL)
				{
					// ���ɕ���
					if (pJoypad->GetTrigger(0, CJoypad::KEY_RIGHT_1))
					{
						move.y += CCharacter::GetStatus().fMaxJump;
					}
				}
			}
		}
	}
	// y�̏���ݒ�
	if (move.y > PLAYER_UPMOVELIMIT)
	{
		move.y = PLAYER_UPMOVELIMIT;
	}
	if (move.y < -PLAYER_UNDERMOVELIMIT)
	{
		move.y = -PLAYER_UNDERMOVELIMIT;
	}
	CCharacter::SetMove(move);

	// �L�����N�^�[�̏d�͉��Z����
	CCharacter::AddGravity(PLAYER_GRAVITY);
	CCharacter::SetRotDest(rot);

	//if (pKeyboard->GetKeyboardTrigger(DIK_C))
	//{
	//	CGame::GetPlayer(1)->SetRotDest(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	//}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �J��������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Camera(void)
{
	// �J������̃v���C���[�ʒu�E��]���̐ݒ�
	CCamera * pCamera = CManager::GetRenderer()->GetCamera();
	pCamera->SetPosDestRPlayer(
		CCharacter::GetPos(),
		CCharacter::GetRot()
	);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// MP�A�b�v���
//	nMpUp	: MP�グ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MpUp(
	int const &nMpUp	// MP�グ
)
{
	// �L�����N�^�[���擾
	CCharacter::CHARACTER character = CCharacter::GetCharacter();

	if (m_bResetMP == false)
	{
		// MP���グ��
		m_nMP += nMpUp;
		// ����𒴂�����ő�MP�����
		if (m_nMP > CCharacter::GetStatus().nMaxMp)
		{
			m_nMP = CCharacter::GetStatus().nMaxMp;
		}
		// MP���}�b�N�X��������
		if (m_nMP == CCharacter::GetStatus().nMaxMp)
		{
			// ���Z�b�g�J�n
			m_bResetMP = true;
			// �T�[�o�[�ɕ�
			CNetwork *pNetwork = CManager::GetNetwork();
			pNetwork->SendTCP("START_SP", sizeof("START_SP"));

			// ��ԕω�
			m_bMPMax = true;
			// �t���[�����[�N����NULL�`�F�b�N
			if (m_pFramework != NULL)
			{
				// �t���[�����[�N���̎g�p��Ԑݒ�
				m_pFramework->SetUse(true);
			}
			// �L�����N�^�[�ɂ��p�[�e�B�N������
			switch (CCharacter::GetCharacter())
			{
				// �L�����N�^�[�o���[��3
			case CCharacter::CHARACTER_BALLOON3:
				C3DParticle::Create(C3DParticle::PARTICLE_ID_BALLOON3SKILL, CCharacter::GetPos());
				break;
			}
		}
	}
	else
	{
		// MP��������
		m_nMP -= CCharacter::GetStatus().nMaxMpDown;

		// MP���}�b�N�X��������
		if (m_nMP == 0)
		{
			// MP��Ԃ̏�����
			m_bMPMax = false;

			// �T�[�o�[�ɕ�
			CNetwork *pNetwork = CManager::GetNetwork();
			pNetwork->SendTCP("STOP_SP", sizeof("STOP_SP"));

			// ���Z�b�g�I��
			m_bResetMP = false;
			// �t���[�����[�N����NULL�`�F�b�N
			if (m_pFramework != NULL)
			{
				// �t���[�����[�N���̎g�p��Ԑݒ�
				m_pFramework->SetUse(false);
			}
		}
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �Q�[�W����������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::GaugeStatusInit(void)
{
	m_nMP = 0;						// MP
	// �ʂ邿��
	if (m_p2DMPGauge != NULL)
	{
		// MP�Q�[�W�̕ω��萔��ݒ�
		m_p2DMPGauge->SetConstance((float)CCharacter::GetStatus().nMaxMp);
		// MP�Q�[�W�̕ω��萔��ݒ�
		m_p2DMPGauge->BeginGauge((float)m_nMP);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���L�����s������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::OtherAction(void)
{
	// ���L�����̈ړ�����
	OtherMove();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����o��
//	nFishApponent	: ���̏o���ԍ�
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::FishApponent(
	int const &nFishApponent	// ���̏o���ԍ�
)
{
	// ���[�h���`���[�g���A���Ȃ�
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// �o���J�E���g
		if (m_nCntFishApponent[nFishApponent] == FISH_APPONENTTIME)
		{
			// ������
			CCharacter_Fish::Create(CCharacter::GetPos());
			// ���o���J�E���g����������
			m_nCntFishApponent[nFishApponent] = 0;
		}
		// ���o���J�E���g�A�b�v
		m_nCntFishApponent[nFishApponent]++;
	}
	// ����ȊO�Ȃ�
	else
	{
		// �ϐ��錾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���擾
		const int nId = pNetwork->GetId();				// �����̃N���C�A���g�ԍ�
		// ���L�����ȊO�Ȃ�
		// �֐��𔲂���
		if (m_nPlayerID != nId)
		{
			return;
		}
		// �o���J�E���g
		if (m_nCntFishApponent[nFishApponent] == FISH_APPONENTTIME)
		{
			// ������
			CCharacter_Fish::Create(CCharacter::GetPos());
			// ���o���J�E���g����������
			m_nCntFishApponent[nFishApponent] = 0;
		}
		// ���o���J�E���g�A�b�v
		m_nCntFishApponent[nFishApponent]++;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��Ԃɂ���Ẵ��[�V�����ݒ菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::StatusMotion(void)
{
	// �������[�V����

	// �W�����v��
	if (!CCharacter::GetbLanding())
	{
		SetMotion(MOTIONTYPE_JAMP);
	}
	// �ړ���
	else if (CCharacter::GetbMove())
	{
		// ���[�V�����ݒ�(�ړ�)
		SetMotion(MOTIONTYPE_MOVE);
	}
	// �ҋ@
	else
	{
		SetMotion(MOTIONTYPE_NEUTRAL);
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���L�����ړ�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::OtherMove(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	// �ϐ��錾
	D3DXVECTOR3 move, rot;			// �ړ��ʁA��]
	float fRot = 0.0f;						// ��]
	// ���擾
	rot = CCharacter::GetRotDest();								// �ړI��]��
	move = CCharacter::GetMove();								// �ړ���
	// �ړ� //
	/* �W���C�p�b�h */
	// �p�b�h�p //

	/* �L�[�{�[�h */
	//// ��
	//if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_A))
	//{
	//	// �ړ����on
	//	CCharacter::SetbMove(true);
	//	// ��
	//	if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	//	{
	//		rot.y = -D3DX_PI * 0.25f + fRot;

	//		move.x += sinf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// ��O
	//	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	//	{
	//		rot.y = -D3DX_PI * 0.75f + fRot;

	//		move.x += sinf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// ��
	//	else
	//	{
	//		rot.y = -D3DX_PI * 0.5f + fRot;
	//		move.x += sinf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//}
	//// �E
	//else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_D))
	//{
	//	// �ړ����on
	//	CCharacter::SetbMove(true);

	//	// ��
	//	if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	//	{
	//		rot.y = D3DX_PI * 0.25f + fRot;

	//		move.x += sinf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// ��O
	//	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	//	{
	//		rot.y = D3DX_PI * 0.75f + fRot;

	//		move.x += sinf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//	// �E
	//	else
	//	{
	//		rot.y = D3DX_PI * 0.5f + fRot;

	//		move.x += sinf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//		move.z += cosf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	}
	//}
	//// ���ɍs��
	//else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	//{
	//	// �ړ����on
	//	CCharacter::SetbMove(true);
	//	rot.y = D3DX_PI * 0.0f + fRot;
	//	move.x += sinf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	move.z += cosf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//}
	//// ��O�ɍs��
	//else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	//{
	//	// �ړ����on
	//	CCharacter::SetbMove(true);
	//	rot.y = D3DX_PI * 1.0f + fRot;
	//	move.x += sinf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//	move.z += cosf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	//}
	//// ����ȊO
	//else
	//{
	//	// �ړ����off
	//	CCharacter::SetbMove(false);
	//}
	//// ���D��NULL�ł͂Ȃ��Ȃ�
	//if (CCharacter_Balloon::GetBalloon() != NULL)
	//{
	//	if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
	//	{
	//		// ���ɕ���
	//		if (pNetwork->GetTriggerKeyboard(m_nPlayerID, NUM_KEY_SPACE))
	//		{
	//			move.y += CCharacter::GetStatus().fMaxJump;
	//		}
	//	}
	//}

	// �T�[�o�[������J�����̉�]�����擾����
	rot.y = pNetwork->GetRot(m_nPlayerID);	// �J������]

	//	// ��]���Z�b�g
	//CCharacter::SetRotDest(rot);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�揈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	// �ϐ��錾
	CNetwork *pNetwork = CManager::GetNetwork();			// �l�b�g���[�N���
	// �v���C���[�ԍ����N���C�A���g���ŊǗ����Ă���v���C���[�ԍ��Ȃ�
	if (m_nPlayerID == pNetwork->GetId())
	{
		// �L�����N�^�[�`��
		CCharacter_Balloon::Draw();
		// �֐��𔲂���
		return;
	}
	// ����ȊO�Ȃ�
	// �ϐ��錾
	CInvisible * pInvisible = NULL;								// �������L�����N�^�[���
	static char const * cClassName = typeid(CInvisible).name();	// �N���X��
	bool		bInvisible = false;								// �������ǂ���
	// �N���X���������Ȃ�(CInvisible)
	if (typeid(*this).name() == cClassName)
	{
		// �w��̃N���X�Ƀ_�E���L���X�g����
		pInvisible = (CInvisible *)this;
		// �������ǂ�����false�Ȃ�
		if (!pInvisible->GetInvisible())
		{
			// �L�����N�^�[�o���[���`�揈��
			CCharacter_Balloon::Draw();
		}
		return;
	}
	// ���̃N���X���Ȃ�
	else
	{
		// �L�����N�^�[�o���[���`�揈��
		CCharacter_Balloon::Draw();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���S����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Die(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_nPlayerID == CManager::GetNetwork()->GetId())
		{
			CNetwork *pNetwork = CManager::GetNetwork();
			pNetwork->SendTCP("DIE", sizeof("DIE"));
			OutputDebugString("���S�鍐");
		}

		// MP�Q�[�W�̊J��
		if (m_p2DMPGauge != NULL)
		{
			m_p2DMPGauge->Release();
			m_p2DMPGauge = NULL;
		}
		// �����N���̊J��
		if (m_pRank != NULL)
		{
			m_pRank->Release();
			m_pRank = NULL;
		}
		// �t���[�����[�N���̊J��
		if (m_pFramework != NULL)
		{
			m_pFramework->SetUse(false);
			m_pFramework->Release();
			m_pFramework = NULL;
		}
		// ���b�V���h�[���̊J��
		if (m_pMeshDome != NULL)
		{
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}

		// ���S����
		CCharacter_Balloon::Die();
		// �R���g���[�����鎩�L�����̏ꍇ
		if (m_nPlayerID == CManager::GetNetwork()->GetId())
		{
			m_bDie[m_nPlayerID] = true;			// ���S�t���O�𗧂Ă�
			CUi_group::Create(CUi::UITYPE_DIE);
		}
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		// ���S����
		CCharacter_Balloon::Die();
		// MP�Q�[�W�̊J��
		if (m_p2DMPGauge != NULL)
		{
			m_p2DMPGauge->Release();
			m_p2DMPGauge = NULL;
		}
		// �����N���̊J��
		if (m_pRank != NULL)
		{
			m_pRank->Release();
			m_pRank = NULL;
		}
		// �t���[�����[�N���̊J��
		if (m_pFramework != NULL)
		{
			m_pFramework->SetUse(false);
			m_pFramework->Release();
			m_pFramework = NULL;
		}
		// ���b�V���h�[���̊J��
		if (m_pMeshDome != NULL)
		{
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �l�`�̎��S����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::OtherDie(void)
{
	// ���S����
	CCharacter_Balloon::Die();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_MyCollision(int const & nObjType, CScene * pScene)
{

	printf("��������");

	// �L�����N�^�[���擾
	CCharacter::CHARACTER character = CCharacter::GetCharacter();
	// �ϐ��錾
	// �l�b�g���[�N���擾
	CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
	// �o���[���L�����N�^�[�̓���������̏���
	CCharacter_Balloon::Scene_MyCollision(nObjType, pScene);
	// �I�u�W�F�N�g�^�C�v���A�C�e���Ȃ�
	if (nObjType == CCollision::OBJTYPE_ITEM)
	{
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// �v���C���[�̃X�R�A���Z�ǉ�
			if (m_nPlayerID == pNetwork->GetId())
			{
				// �L�����N�^�[����v������
				if (character != CCharacter::CHARACTER_BALLOON2)
				{
					CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
				}
				// �L�����N�^�[����v������
				if (character == CCharacter::CHARACTER_BALLOON2)
				{
					// ���
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
				}
				// MP�グ����(���D)
				MpUp(CItem::GetStatus().nMpUp);
			}
		}
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			// MP�グ����(���D)
			MpUp(CItem::GetStatus().nMpUp);
		}
	}
	// �I�u�W�F�N�g�^�C�v���v���C���[���D�Ȃ� ||
	// �I�u�W�F�N�g�^�C�v���G���D�Ȃ� ||
	else if (nObjType == CCollision::OBJTYPE_PLAYER_BALLOON ||
		nObjType == CCollision::OBJTYPE_ENEMY_BALLOON)
	{
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// �v���C���[�̃X�R�A���Z�ǉ�
			if (m_nPlayerID == pNetwork->GetId())
			{
				// �L�����N�^�[����v������
				if (character != CCharacter::CHARACTER_BALLOON2)
				{
					// �X�R�A���Z����
					CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON);
				}
				// �L�����N�^�[����v������
				if (character == CCharacter::CHARACTER_BALLOON2)
				{
					// ���
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON);
					}
				}
				// MP�グ����(���D)
				MpUp(MPUP_BREAKBALLOON);
			}
		}
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			// MP�グ����(���D)
			MpUp(MPUP_BREAKBALLOON);
		}
	}
	// �I�u�W�F�N�g�^�C�v���v���C���[�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_PLAYER)
	{
		// ��邱��
		// �X�R�A���Z��MP���Z�̏ꏊ
		// �����ł͂Ȃ�
		// ���������񂾎��ł͂Ȃ��A���肪���񂾂Ƃ��ɉ��Z


		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			// ���S����
			BalloonNone();



			// ���̏������ǂ��ōs�����s��
			//CManager::GetGame()->GetScore()->AddScore(SCORETYPE_PLAYER);
			// MP�グ����(�v���C���[)
			//MpUp(MPUP_PLAYER_KNOCKDOWN);
		}
	}
	// �I�u�W�F�N�g�^�C�v���G�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_ENEMY)
	{
		// �ϐ��錾
		// �l�b�g���[�N���擾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			// ���S����
			BalloonNone();


			// ���̏������ǂ��ōs�����s��
			//CManager::GetGame()->GetScore()->AddScore(SCORETYPE_ENEMY);
			// MP�グ����(�G)
			//MpUp(MPUP_ENEMY_KNOCKDOWN);
		}
	}
	// �I�u�W�F�N�g�^�C�v�����Ȃ�
	else if (nObjType == CCollision::OBJTYPE_FISH)
	{
		Die();
	}
	// �I�u�W�F�N�g�^�C�v���o����1�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_APPEFISH1)
	{
		FishApponent(0);
	}
	// �I�u�W�F�N�g�^�C�v���o����2�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_APPEFISH2)
	{
		FishApponent(1);
	}
	// �I�u�W�F�N�g�^�C�v���o����3�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_APPEFISH3)
	{
		FishApponent(2);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	// �L�����N�^�[���擾
	CCharacter::CHARACTER character = CCharacter::GetCharacter();

	// �o���[���L�����N�^�[�̑���ɓ��Ă�ꂽ��̏���
	CCharacter_Balloon::Scene_OpponentCollision(nObjType, pScene);

	printf("��������");

	// �V�[�����NULL�Ȃ�
	// ->�֐��𔲂���
	if (pScene == NULL) return;
	// �I�u�W�F�N�g�^�C�v���A�C�e���Ȃ�
	else if (nObjType == CCollision::OBJTYPE_FISH)
	{
		// ���S
		Die();
	}
	// �I�u�W�F�N�g�^�C�v���G�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_ENEMY)
	{
		// �ϐ��錾
		// �l�b�g���[�N���擾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				// �L�����N�^�[����v������
				if (character != CCharacter::CHARACTER_BALLOON2)
				{
					CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
				}
				// �L�����N�^�[����v������
				if (character == CCharacter::CHARACTER_BALLOON2)
				{
					// ���
					if (CScoreUP::GetScoreUP() == true)
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint * 2);
					}
					else
					{
						CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
					}
				}
			}
		}
		// ���S����
		BalloonNone();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �������瓖����Ȃ�������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_NoMyCollision(int const & nObjType, CScene * pScene)
{
	// �I�u�W�F�N�g�^�C�v���o����1�Ȃ�
	if (nObjType == CCollision::OBJTYPE_APPEFISH1)
	{
		m_nCntFishApponent[0] = 0;
	}
	// �I�u�W�F�N�g�^�C�v���o����2�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_APPEFISH2)
	{
		m_nCntFishApponent[1] = 0;
	}
	// �I�u�W�F�N�g�^�C�v���o����3�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_APPEFISH3)
	{
		m_nCntFishApponent[2] = 0;
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����ɓ��Ă��Ȃ�������̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_NoOpponentCollision(int const & nObjType, CScene * pScene)
{

}

#ifdef _DEBUG
//-------------------------------------------------------------------------------------------------------------
// �f�o�b�O�\��
//-------------------------------------------------------------------------------------------------------------
void CPlayer::Debug(void)
{
	if (m_nPlayerID == 0)
	{
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_R))
		{
			CCharacter::SetPos(D3DVECTOR3_ZERO);
		}
	}
	// MP�S��
	if (CManager::GetKeyboard()->GetKeyboardTrigger(TESTPLAY_NUMBER3))
	{
		// MP�S��
		m_nMP = CCharacter::GetStatus().nMaxMp;
		// MP�Q�[�W��NULL�`�F�b�N
		if (m_p2DMPGauge != NULL)
		{
			// �Q�[�W��ς���
			m_p2DMPGauge->ChangeGauge((float)m_nMP);
		}
	}
	//CDebugproc::Print("-----�v���C���[�ԍ�[%d]-----\n", m_nPlayerID);
	// �L�����N�^�[�f�o�b�O
	CCharacter_Balloon::Debug();
	// ���݂̃X�s�[�h��\��
	CDebugproc::Print("���݂̃X�s�[�h(%.3f)\n", m_fMoveNow);

}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���\�[�X���ǂݍ��ݏ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CPlayer::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��񂾃��\�[�X����j������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::UnLoad(void)
{
}
