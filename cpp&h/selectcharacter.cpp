// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �L�����N�^�[�I������ [selectcharacter.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "selectcharacter.h"
/* �`�� */
#include "speedUP.h"
#include "revival.h"
#include "invisible.h"
#include "attackUP.h"
#include "scene_two.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_ICON_ORIGINPOS (D3DXVECTOR3(250.0f,658.0f,0.0f))	// �L�����N�^�[�A�C�R����1�Ԗڂ̈ʒu
#define CHARACTER_ICON_ORIGINPOS_X (250.0f)							// �L�����N�^�[�A�C�R����1�Ԗڂ�X�ʒu
#define CHARACTER_ICON_ORIGINPOS_Y (658.0f)							// �L�����N�^�[�A�C�R����1�Ԗڂ�Y�ʒu
#define CHARACTER_ICON_SPACE (250.0f)								// �L�����N�^�[�A�C�R�����m�̈ʒu�Ԋu
#define CHARACTER_ICON_SIZE (85.0f)									// �L�����N�^�[�A�C�R���̃T�C�Y

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CSelectCharacter::m_SaveCharaType[MAX_PLAYER] = {};	// �v���C���[���I�񂾃L�����N�^�[�^�C�v��ۑ�


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelectCharacter::CSelectCharacter() : CScene::CScene()
{
	// ������
	m_pSpeedUP = NULL;
	m_pRevival = NULL;
	m_pInvisible = NULL;
	m_pAttackUP = NULL;
	m_pCheckUi = NULL;
	m_CharacterType = 0;
	m_PlayerID = 0;
	m_bReady = false;
	for (int nCntCharacter = 0; nCntCharacter < CCharacter::CHARACTER_PLAYERMAX; nCntCharacter++)
	{
		m_pSelectIcon[nCntCharacter] = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelectCharacter::~CSelectCharacter()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Init(void)
{
	// �v���C���[(�X�s�[�h�A�b�v)
	m_pSpeedUP = CSpeedUP::Create_Self(m_PlayerID, m_pos);
	// �v���C���[(����)
	m_pRevival = CRevival::Create_Self(m_PlayerID, m_pos);
	// �v���C���[(����)
	m_pInvisible = CInvisible::Create_Self(m_PlayerID, m_pos);
	// �v���C���[(�A�^�b�N�A�b�v)
	m_pAttackUP = CAttackUP::Create_Self(m_PlayerID, m_pos);
	// �I��UI����
	m_pSelectUi = CScene_TWO::Create(
		CScene_TWO::OFFSET_TYPE_CENTER,
		CHARACTER_ICON_ORIGINPOS,
		D3DXVECTOR2(CHARACTER_ICON_SIZE, CHARACTER_ICON_SIZE));
	// �I��UI��NULL�`�F�b�N
	// ->�e�N�X�`���[�ݒ�
	if (m_pSelectUi != NULL)
	{
		// �e�N�X�`���[�ݒ�
		m_pSelectUi->BindTexture(CTexture_manager::GetTexture(13));
	}

	// ���ꂼ��̑I���A�C�R��
	for (int nCntCharacter = 0; nCntCharacter < CCharacter::CHARACTER_PLAYERMAX; nCntCharacter++)
	{
		// �I���A�C�R������
		m_pSelectIcon[nCntCharacter] = CScene_TWO::Create(
			CScene_TWO::OFFSET_TYPE_CENTER,
			D3DXVECTOR3(CHARACTER_ICON_ORIGINPOS_X * (nCntCharacter + 1), CHARACTER_ICON_ORIGINPOS_Y, 0.0f),
			D3DXVECTOR2(CHARACTER_ICON_SIZE, CHARACTER_ICON_SIZE));
		// �e�N�X�`���[���ݒ�
		//
		m_pSelectIcon[nCntCharacter]->BindTexture(CTexture_manager::GetTexture(18));
		//
		// �e�N�X�`���[���ݒ�
	}
	// �I��UI��NULL�`�F�b�N
	// ->�ʒu�ݒ�
	if (m_pSelectUi != NULL)
	{
		// �I��UI�̈ʒu�ݒ�
		m_pSelectUi->SetPosition(m_pSelectIcon[m_CharacterType]->GetPosition());
		m_pSelectUi->Set_Vtx_Pos();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Uninit(void)
{
	// �v���C���[(�X�s�[�h�A�b�v)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pSpeedUP != NULL)
	{
		m_pSpeedUP->Uninit();
		delete m_pSpeedUP;
		m_pSpeedUP = NULL;
	}
	// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pRevival != NULL)
	{
		m_pRevival->Uninit();
		delete m_pRevival;
		m_pRevival = NULL;
	}
	// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pInvisible != NULL)
	{
		m_pInvisible->Uninit();
		delete m_pInvisible;
		m_pInvisible = NULL;
	}
	// �v���C���[(�A�^�b�N�A�b�v)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pAttackUP != NULL)
	{
		m_pAttackUP->Uninit();
		delete m_pAttackUP;
		m_pAttackUP = NULL;
	}
	// �I��UI��NULL�`�F�b�N
	// ->�I������
	if (m_pSelectUi != NULL)
	{
		// �I������
		//m_pSelectUi->Release();
		m_pSelectUi = NULL;
	}
	// �L�����N�^�[�m��UI��NULL�`�F�b�N
	// ->�I������
	if (m_pCheckUi != NULL)
	{
		// �I������
		//m_pSelectUi->Release();
		m_pCheckUi = NULL;
	}
	// ���ꂼ��̑I���A�C�R��
	// ->�I������
	for (int nCntCharacter = 0; nCntCharacter < CCharacter::CHARACTER_PLAYERMAX; nCntCharacter++)
	{
		// �I���A�C�R����NULL�ł͂Ȃ��Ȃ�
		// ->�I������
		if (m_pSelectIcon[nCntCharacter] != NULL)
		{
			// �I������
			//m_pSelectIcon[nCntCharacter]->Release();
			m_pSelectIcon[nCntCharacter] = NULL;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Update(void)
{
	if (!m_bReady)
	{
		if (m_pCheckUi != NULL)
		{
			m_pCheckUi->Release();
			m_pCheckUi = NULL;
		}
		// �E�����͂��ꂽ��
		// ->�L�����N�^�[�ԍ������Z
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_RIGHT))
		{
			m_CharacterType++;
		}
		// �������͂��ꂽ��
		// ->�L�����N�^�[�ԍ������Z
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_LEFT))
		{
			m_CharacterType--;
		}
		// �͈͐ݒ�
		if (m_CharacterType >= CPlayer::CHARACTER_PLAYERMAX)
		{
			m_CharacterType = 0;
		}
		else if (m_CharacterType < 0)
		{
			m_CharacterType = CPlayer::CHARACTER_PLAYERMAX - 1;
		}
	}
	else
	{
		if (m_pCheckUi == NULL)
		{
			m_pCheckUi = CScene_TWO::Create(
				CScene_TWO::OFFSET_TYPE_CENTER,
				CHARACTER_ICON_ORIGINPOS,
				D3DXVECTOR2(CHARACTER_ICON_SIZE, CHARACTER_ICON_SIZE));
			// �I��UI��NULL�`�F�b�N
			// ->�e�N�X�`���[�ݒ�
			if (m_pCheckUi != NULL)
			{
				// �e�N�X�`���[�ݒ�
				m_pCheckUi->BindTexture(CTexture_manager::GetTexture(27));
				// �I��UI�̈ʒu�ݒ�
				m_pCheckUi->SetPosition(m_pSelectIcon[m_CharacterType]->GetPosition());
				m_pCheckUi->Set_Vtx_Pos();
			}
		}
	}
#ifdef _DEBUG
	CDebugproc::Print("�L�����N�^�[�I��:%d\n", m_CharacterType);
#endif // _DEBUG

	// ���݂̃L�����N�^�[�ԍ��̕ۑ�
	m_SaveCharaType[m_PlayerID] = m_CharacterType;

	// �v���C���[�̍X�V
	switch (m_CharacterType)
	{
		// �v���C���[(�X�s�[�h�A�b�v)
	case 0:
		// �v���C���[(�X�s�[�h�A�b�v)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pSpeedUP != NULL)
		{
			m_pSpeedUP->Update();
		}
		break;
		// �v���C���[(����)
	case 1:
		// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pRevival != NULL)
		{
			m_pRevival->Update();
		}
		break;
		// �v���C���[(����)
	case 2:
		// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pInvisible != NULL)
		{
			m_pInvisible->Update();
		}
		break;
	case 3:
		// �v���C���[(�A�^�b�N�A�b�v)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pAttackUP != NULL)
		{
			m_pAttackUP->Update();
		}
		break;
	default:
		break;
	}

	// �I��UI��NULL�`�F�b�N
	// ->�I��UI�̈ʒu�ݒ�
	if (m_pSelectUi != NULL)
	{
		// �I��UI�̈ʒu�ݒ�
		m_pSelectUi->SetPosition(m_pSelectIcon[m_CharacterType]->GetPosition());
		m_pSelectUi->Set_Vtx_Pos();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::Draw(void)
{
	switch (m_CharacterType)
	{
		// �v���C���[(�X�s�[�h�A�b�v)
	case 0:
		// �v���C���[(�X�s�[�h�A�b�v)��NULL�ł͂Ȃ��Ȃ�
		// ->�`�揈��
		if (m_pSpeedUP != NULL)
		{
			m_pSpeedUP->Draw();
		}
		break;
		// �v���C���[(����)
	case 1:
		// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
		// ->�`�揈��
		if (m_pRevival != NULL)
		{
			m_pRevival->Draw();
		}
		break;
		// �v���C���[(����)
	case 2:
		// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
		// ->�`�揈��
		if (m_pInvisible != NULL)
		{
			m_pInvisible->Draw();
		}
		break;
	case 3:
		// �v���C���[(�A�^�b�N�A�b�v)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pAttackUP != NULL)
		{
			m_pAttackUP->Draw();
		}
		break;
	default:
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelectCharacter * CSelectCharacter::Create(
	int const &nPlayerId,	// �v���C���[ID
	D3DXVECTOR3 const &pos	// �ʒu
)
{
	// �ϐ��錾
	CSelectCharacter * pSelect_chara;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pSelect_chara = new CSelectCharacter;
	// �v���C���[�ԍ��ݒ�
	pSelect_chara->m_PlayerID = nPlayerId;
	// �ʒu�ݒ�
	pSelect_chara->m_pos = pos;
	// ����������
	pSelect_chara->Init();
	// �V�[���Ǘ�
	pSelect_chara->ManageSetting(CScene::LAYER_SELECTCHARACTER);
	// ���������I�u�W�F�N�g��Ԃ�
	return pSelect_chara;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ÓI�ϐ��̏�����
// (�I����ʂ̏��������Ɋ֐����Ă�)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelectCharacter::InitStatic(void)
{
	for (int nCntSelectChara = 0; nCntSelectChara < MAX_PLAYER; nCntSelectChara++)
	{
		m_SaveCharaType[nCntSelectChara] = 0;
	}
}
