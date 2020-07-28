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

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int	CPlayer::m_All = 0;					// ����

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::CPlayer(CHARACTER const &character) : CCharacter_Balloon::CCharacter_Balloon(character)
{
	m_p2DMPGauge = NULL;			// MP�Q�[�W
	m_pRank = NULL;					// ���ݏ���
	m_posold = D3DVECTOR3_ZERO;		// �O�̈ʒu
	m_nCntState = 0;				// �X�e�[�g�J�E���g
	m_All++;						// ����
	m_nCntFishApponent = 0;			// ���o���J�E���g
	m_nMP = 0;						// MP
	m_bMPMax = false;				// MP���ő傩�ǂ���
	m_bResetMP = false;				// MP�����Z�b�g
	m_nRank = -1;					// �����L���O�̏�����
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
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
	m_fMoveNow = CCharacter::GetStatus().fMaxMove;

	// �J�����̏�����
	// �J�����̒����_�ݒ�
	CManager::GetRenderer()->GetCamera()->SetPosR(
		CCharacter::GetPos() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		CCharacter::GetRot() + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f)
	);
	// ���[�h���Q�[���Ȃ�
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �L�����N�^�[���̂̃v���C���[�ԍ��ƃR���g���[�����Ă���v���C���[�ԍ��������Ȃ�
		// ->�Q�[�W����
		if (m_nPlayerID == nId)
		{
			// MP�Q�[�W�̐���
			m_p2DMPGauge = C2DGauge::Create(
				PLAYER_UI_MP_POS,
				D3DXVECTOR2(500.0f, 25.0f),
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
			);
			// MP�Q�[�W�̕ω��萔��ݒ�
			m_p2DMPGauge->SetConstance((float)PLAYER_MPMAX);
			// MP�Q�[�W�̕ω��萔��ݒ�
			m_p2DMPGauge->BeginGauge((float)m_nMP);
			// MP�Q�[�W�̃��C���J���[�ݒ�
			m_p2DMPGauge->SetMainCol(
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
		}

		m_pRank = CRank::Create();

		if (m_pRank != NULL)
		{
			m_pRank->SetPos(m_pos);
		}
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
		m_p2DMPGauge = NULL;
	}
	if (m_pRank != NULL)
	{
		m_pRank = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	const int nId = pNetwork->GetId();

	// ���[�V�����ݒ�
	CCharacter::SetMotion(MOTIONTYPE_NEUTRAL);
	// �I����ʈȊO�Ȃ�
	if (CManager::GetMode() != CManager::MODE_SELECT)
	{
		// �L�����N�^�[���̂̃v���C���[�ԍ��ƃR���g���[�����Ă���v���C���[�ԍ��������Ȃ�
		// ->�s������
		if (m_nPlayerID == nId)
		{
			// ���L�����̍s������
			MyAction(m_nPlayerID);
		}
		// ����ȊO�̃L�����N�^�[�̏���
		else
		{
			// ���L�����̍s������
			OtherAction();
		}
	}

	// �L�����N�^�[�X�V
	CCharacter_Balloon::Update();

	/* �v���g�^�C�v�p */
	// �L�����N�^�[�̋��錾
	if (CManager::GetPlayerID() != m_nPlayerID)
	{
		CCharacter::Limit();
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
	}
#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_8))
	{
		CCharacter_Balloon::Thunder_BreakBalloon();
	}
#endif // _DEBUG

	// ���o������
	FishApponent();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���L�����s������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyAction(const int &nId)
{
	// ���L�����̈ړ�����
	MyMove();
	// ���D��c��܂���
	if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_BALLOONCREATE))
	{
		// ���D�𐶐����鏈��
		CCharacter_Balloon::BalloonCreate();
	}
	// �J�����̏���
	Camera();
	// MP�グ����(�}�C�t���[��)
	MpUp(MPUP_EVERY);
	// MP�Q�[�W�̕ω��萔��ݒ�
	m_p2DMPGauge->ChangeGauge((float)m_nMP);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ړ�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::MyMove(void)
{
	// �ϐ��錾
	D3DXVECTOR3 move, rot;			// �ړ��ʁA��]
	bool bMove = false;				// �ړ����
	float fRot;						// ��]

	// ���擾
	rot = CCharacter::GetRotDest();								// �ړI��]��
	move = CCharacter::GetMove();								// �ړ���
	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// �J������]
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CJoypad *pJoypad = CManager::GetJoy();

	// �ړ� //
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
			// ���x�̌v�Z
			if (abs(nValueH) > abs(nValueV))
			{
				fMove = (abs(nValueH) * m_fMoveNow) / 1024.0f;
			}
			else
			{
				fMove = (abs(nValueV) * m_fMoveNow) / 1024.0f;
			}
			rot.y = fAngle + fRot;

			// �X�e�B�b�N�̊p�x�ɂ���ăv���C���[�ړ�
			move.x -= sinf(fAngle + fRot) * (fMove);
			move.z -= cosf(fAngle + fRot) * (fMove);
			// �ړ����on
			bMove = true;
		}
	}

	/* �L�[�{�[�h */
	// ��
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		// �ړ����on
		bMove = true;
		// ��
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = -D3DX_PI * 0.25f + fRot;

			move.x += sinf(D3DX_PI * 0.75f + fRot) * m_fMoveNow;
			move.z += cosf(D3DX_PI * 0.75f + fRot) * m_fMoveNow;
		}
		// ��O
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = -D3DX_PI * 0.75f + fRot;

			move.x += sinf(D3DX_PI * 0.25f + fRot) * m_fMoveNow;
			move.z += cosf(D3DX_PI * 0.25f + fRot) * m_fMoveNow;
		}
		// ��
		else
		{
			rot.y = -D3DX_PI * 0.5f + fRot;
			move.x += sinf(D3DX_PI * 0.5f + fRot) * m_fMoveNow;
			move.z += cosf(D3DX_PI * 0.5f + fRot) * m_fMoveNow;
		}
	}
	// �E
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		// �ړ����on
		bMove = true;

		// ��
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			rot.y = D3DX_PI * 0.25f + fRot;

			move.x += sinf(-D3DX_PI * 0.75f + fRot) * m_fMoveNow;
			move.z += cosf(-D3DX_PI * 0.75f + fRot) * m_fMoveNow;
		}
		// ��O
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			rot.y = D3DX_PI * 0.75f + fRot;

			move.x += sinf(-D3DX_PI * 0.25f + fRot) * m_fMoveNow;
			move.z += cosf(-D3DX_PI * 0.25f + fRot) * m_fMoveNow;
		}
		// �E
		else
		{
			rot.y = D3DX_PI * 0.5f + fRot;

			move.x += sinf(-D3DX_PI * 0.5f + fRot) * m_fMoveNow;
			move.z += cosf(-D3DX_PI * 0.5f + fRot) * m_fMoveNow;
		}
	}
	// ���ɍs��
	else if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		// �ړ����on
		bMove = true;
		rot.y = D3DX_PI * 0.0f + fRot;
		move.x += sinf(-D3DX_PI * 1.0f + fRot) * m_fMoveNow;
		move.z += cosf(-D3DX_PI * 1.0f + fRot) * m_fMoveNow;
	}
	// ��O�ɍs��
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		// �ړ����on
		bMove = true;
		rot.y = D3DX_PI * 1.0f + fRot;
		move.x += sinf(D3DX_PI * 0.0f + fRot) * m_fMoveNow;
		move.z += cosf(D3DX_PI * 0.0f + fRot) * m_fMoveNow;
	}
	// ���D��NULL�ł͂Ȃ��Ȃ�
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		// ���D������Ȃ�
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
		{
			// ���ɕ���
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// �ړ���y��0�����Ȃ�
				if (move.y < 0.0f)
				{
					move.y = 0.0f;
				}
				move.y += CCharacter::GetStatus().fMaxJump;
			}
			else
			{
				if (pJoypad != NULL)
				{
					// ���ɕ���
					if (pJoypad->GetTrigger(0, CJoypad::KEY_A) || pJoypad->GetTrigger(0, CJoypad::KEY_X))
					{
						// �ړ���y��0�����Ȃ�
						if (move.y < 0.0f)
						{
							move.y = 0.0f;
						}
						move.y += CCharacter::GetStatus().fMaxJump;
					}
				}
			}
		}
	}
	// �ړ���ԂȂ�
	if (bMove == true)
	{
		CCharacter::SetMotion(MOTIONTYPE_MOVE);
	}
	// y�̏���ݒ�
	if (move.y > 10.0f)
	{
		move.y = 10.0f;
	}
	if (move.y < -5.0f)
	{
		move.y = -5.0f;
	}
	CCharacter::SetMove(move);
	CCharacter::SetRotDest(rot);
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
	if (m_bResetMP == false)
	{
		// MP���グ��
		m_nMP += nMpUp;
		// ����𒴂�����ő�MP�����
		if (m_nMP > PLAYER_MPMAX)
		{
			m_nMP = PLAYER_MPMAX;
		}
		// MP���}�b�N�X��������
		if (m_nMP == PLAYER_MPMAX)
		{
			// ���Z�b�g�J�n
			m_bResetMP = true;
			// ��ԕω�
			m_bMPMax = true;
		}
	}
	else
	{
		// MP���グ��
		m_nMP -= 100;
		// MP���}�b�N�X��������
		if (m_nMP == 0)
		{
			// MP��Ԃ̏�����
			m_bMPMax = false;
			// ���Z�b�g�I��
			m_bResetMP = false;
		}
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
// ���o������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::FishApponent(void)
{
	// �v���C���[�̈ʒu���w�肵���ʒu�ȉ��Ȃ�
	if (CCharacter::GetPos().y >= FISH_APPONENTPOS)
	{
		// �o���J�E���g
		if (m_nCntFishApponent == FISH_APPONENTTIME)
		{
			// ������
			CCharacter_Fish::Create(CCharacter::GetPos());
			// ���o���J�E���g����������
			m_nCntFishApponent = 0;
		}
		// ���o���J�E���g�A�b�v
		m_nCntFishApponent++;
	}
	// ����ȊO
	else
	{
		// ���o���J�E���g����������
		m_nCntFishApponent = 0;
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
	bool bMove = false;				// �ړ����
	float fRot;						// ��]
	// ���擾
	rot = CCharacter::GetRotDest();								// �ړI��]��
	move = CCharacter::GetMove();								// �ړ���
	// �T�[�o�[������J�����̉�]�����擾����
	fRot = pNetwork->GetRot(m_nPlayerID);	// �J������]
	// �ړ� //
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

		/* �v���C���[�ړ� */
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
			// ���x�̌v�Z
			if (abs(nValueH) > abs(nValueV))
			{
				fMove = (abs(nValueH) * CCharacter::GetStatus().fMaxMove) / 1024.0f;
			}
			else
			{
				fMove = (abs(nValueV) * CCharacter::GetStatus().fMaxMove) / 1024.0f;
			}
			rot.y = fAngle + fRot;

			// �X�e�B�b�N�̊p�x�ɂ���ăv���C���[�ړ�
			move.x -= sinf(fAngle + fRot) * (fMove);
			move.z -= cosf(fAngle + fRot) * (fMove);
			// �ړ����on
			bMove = true;
		}
	}
	/* �L�[�{�[�h */
	// ��
	if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_A))
	{
		// �ړ����on
		bMove = true;
		// ��
		if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
		{
			rot.y = -D3DX_PI * 0.25f + fRot;

			move.x += sinf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// ��O
		else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
		{
			rot.y = -D3DX_PI * 0.75f + fRot;

			move.x += sinf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// ��
		else
		{
			rot.y = -D3DX_PI * 0.5f + fRot;
			move.x += sinf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
	}
	// �E
	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_D))
	{
		// �ړ����on
		bMove = true;

		// ��
		if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
		{
			rot.y = D3DX_PI * 0.25f + fRot;

			move.x += sinf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(-D3DX_PI * 0.75f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// ��O
		else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
		{
			rot.y = D3DX_PI * 0.75f + fRot;

			move.x += sinf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(-D3DX_PI * 0.25f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
		// �E
		else
		{
			rot.y = D3DX_PI * 0.5f + fRot;

			move.x += sinf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
			move.z += cosf(-D3DX_PI * 0.5f + fRot) * CCharacter::GetStatus().fMaxMove;
		}
	}
	// ���ɍs��
	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_W))
	{
		// �ړ����on
		bMove = true;
		rot.y = D3DX_PI * 0.0f + fRot;
		move.x += sinf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
		move.z += cosf(-D3DX_PI * 1.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	}
	// ��O�ɍs��
	else if (pNetwork->GetPressKeyboard(m_nPlayerID, NUM_KEY_S))
	{
		// �ړ����on
		bMove = true;
		rot.y = D3DX_PI * 1.0f + fRot;
		move.x += sinf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
		move.z += cosf(D3DX_PI * 0.0f + fRot) * CCharacter::GetStatus().fMaxMove;
	}
	// ���D��NULL�ł͂Ȃ��Ȃ�
	if (CCharacter_Balloon::GetBalloon() != NULL)
	{
		if (CCharacter_Balloon::GetBalloon()->GetPopBalloon_group() != 0)
		{
			// ���ɕ���
			if (pNetwork->GetTriggerKeyboard(m_nPlayerID, NUM_KEY_SPACE))
			{
				move.y += CCharacter::GetStatus().fMaxJump;
			}
		}
	}
	// �ړ���ԂȂ�
	if (bMove == true)
	{
		CCharacter::SetMotion(MOTIONTYPE_MOVE);
	}
	//CCharacter::SetMove(move);
	CCharacter::SetRotDest(rot);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�揈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	// �L�����N�^�[�`��
	CCharacter_Balloon::Draw();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���S����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Die(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	char aDie[64];
	sprintf(aDie, "DIE %d", pNetwork->GetId());
	pNetwork->SendTCP(aDie, sizeof(aDie));

	if (m_pRank != NULL)
	{
		m_pRank->Release();
		m_pRank = NULL;
	}

	// ���S����
	CCharacter_Balloon::Die();
	// �R���g���[�����鎩�L�����̏ꍇ
	if (m_nPlayerID == CManager::GetPlayerID())
	{
		OutputDebugString("�����Ɓ[�I");
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
	// �o���[���L�����N�^�[�̓���������̏���
	CCharacter_Balloon::Scene_MyCollision(nObjType, pScene);
	// �V�[�����NULL�Ȃ�
	// ->�֐��𔲂���
	if (pScene == NULL) return;
	// �I�u�W�F�N�g�^�C�v���A�C�e���Ȃ�
	else if (nObjType == CCollision::OBJTYPE_ITEM)
	{
		// �ϐ��錾
		// �l�b�g���[�N���擾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_COIN);
		}
	}
	// �I�u�W�F�N�g�^�C�v���v���C���[���D�Ȃ� ||
	// �I�u�W�F�N�g�^�C�v���G���D�Ȃ� ||
	else if (nObjType == CCollision::OBJTYPE_PLAYER_BALLOON ||
		nObjType == CCollision::OBJTYPE_ENEMY_BALLOON)
	{
		// �ϐ��錾
		// �l�b�g���[�N���擾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			// �X�R�A���Z����
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_BALLOON);
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


		// �ϐ��錾
		// �l�b�g���[�N���擾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
		// ���S����
		BalloonNone();
		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_PLAYER);
			// MP�グ����(�v���C���[)
			MpUp(MPUP_PLAYER_KNOCKDOWN);
		}
	}
	// �I�u�W�F�N�g�^�C�v���G�Ȃ�
	else if (nObjType == CCollision::OBJTYPE_ENEMY)
	{
		// �ϐ��錾
		// �l�b�g���[�N���擾
		CNetwork *pNetwork = CManager::GetNetwork();	// �l�b�g���[�N���
		// ���S����
		BalloonNone();
		// �v���C���[�̃X�R�A���Z�ǉ�
		if (m_nPlayerID == pNetwork->GetId())
		{
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_ENEMY);
			// MP�グ����(�G)
			MpUp(MPUP_ENEMY_KNOCKDOWN);
		}
	}
	// �I�u�W�F�N�g�^�C�v���A�C�e���Ȃ�
	else if (nObjType == CCollision::OBJTYPE_FISH)
	{
		// ���S
		Die();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����ɓ��Ă�ꂽ��̏���
//	nObjType	: �I�u�W�F�N�g�^�C�v
//	pScene		: ����̃V�[�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CPlayer::Scene_OpponentCollision(int const & nObjType, CScene * pScene)
{
	// �o���[���L�����N�^�[�̑���ɓ��Ă�ꂽ��̏���
	CCharacter_Balloon::Scene_OpponentCollision(nObjType, pScene);
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
			CManager::GetGame()->GetScore()->AddScore(SCORETYPE_COIN);
		}
		// ���S����
		BalloonNone();
	}
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
		m_nMP = PLAYER_MPMAX;
		// MP�Q�[�W��NULL�`�F�b�N
		if (m_p2DMPGauge != NULL)
		{
			// �Q�[�W��ς���
			m_p2DMPGauge->ChangeGauge((float)m_nMP);
		}
	}
	CDebugproc::Print("-----�v���C���[�ԍ�[%d]-----\n", m_nPlayerID);
	// �L�����N�^�[�f�o�b�O
	CCharacter_Balloon::Debug();


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
