// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �L�����N�^�[�I������ [selectcharacter.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "selectcharacter.h"
/* �`�� */
#include "p_thunder.h"
#include "p_zombie.h"
#include "invisible.h"
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
	m_pThunder = NULL;
	m_pZombie = NULL;
	m_pInvisible = NULL;
	m_CharacterType = 0;
	m_PlayerID = 0;
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
	// �v���C���[(��)
	m_pThunder = CP_thunder::Create_Self(m_PlayerID, m_pos);
	// �v���C���[(�]���r)
	m_pZombie = CP_zombie::Create_Self(m_PlayerID, m_pos);
	// �v���C���[(����)
	m_pInvisible = CInvisible::Create_Self(m_PlayerID, m_pos);
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
	// �v���C���[(��)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pThunder != NULL)
	{
		m_pThunder->Uninit();
		delete m_pThunder;
		m_pThunder = NULL;
	}
	// �v���C���[(�]���r)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pZombie != NULL)
	{
		m_pZombie->Uninit();
		delete m_pZombie;
		m_pZombie = NULL;
	}
	// �v���C���[(����)��NULL�ł͂Ȃ��Ȃ�
	// ->�I������
	if (m_pInvisible != NULL)
	{
		m_pInvisible->Uninit();
		delete m_pInvisible;
		m_pInvisible = NULL;
	}
	// �I��UI��NULL�`�F�b�N
	// ->�I������
	if (m_pSelectUi != NULL)
	{
		// �I������
		//m_pSelectUi->Release();
		m_pSelectUi = NULL;
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
#ifdef _DEBUG
	CDebugproc::Print("�L�����N�^�[�I��:%d\n", m_CharacterType);
#endif // _DEBUG

	// ���݂̃L�����N�^�[�ԍ��̕ۑ�
	m_SaveCharaType[m_PlayerID] = m_CharacterType;

	// �v���C���[�̍X�V
	switch (m_CharacterType)
	{
		// �v���C���[(��)
	case 0:
		// �v���C���[(��)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pThunder != NULL)
		{
			m_pThunder->Update();
		}
		break;
		// �v���C���[(�]���r)
	case 1:
		// �v���C���[(�]���r)��NULL�ł͂Ȃ��Ȃ�
		// ->�X�V����
		if (m_pZombie != NULL)
		{
			m_pZombie->Update();
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
		// �v���C���[(��)
	case 0:
		// �v���C���[(��)��NULL�ł͂Ȃ��Ȃ�
		// ->�`�揈��
		if (m_pThunder != NULL)
		{
			m_pThunder->Draw();
		}
		break;
		// �v���C���[(�]���r)
	case 1:
		// �v���C���[(�]���r)��NULL�ł͂Ȃ��Ȃ�
		// ->�`�揈��
		if (m_pZombie != NULL)
		{
			m_pZombie->Draw();
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
