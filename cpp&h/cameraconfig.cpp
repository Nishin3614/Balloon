// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �J�����ݒ菈���̐���[cameraconfig.cpp]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* �`�� */
#include "cameraconfig.h"
#include "pause.h"
#include "fade.h"
#include "game.h"
#include "ui.h"
#include "pause_ui.h"
#include "camera.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CAMERACONFIG_TEXANIM (0.5f)
#define CCTA CAMERACONFIG_TEXANIM
#define CAMERACONFIG_NUMBER_TEXANIM (0.1f)
#define CCBTA CAMERACONFIG_NUMBER_TEXANIM

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I��
int CCameraconfig::m_nSelect = 0;
bool CCameraconfig::m_bConfig = false;						// �ݒ���
int CCameraconfig::m_nSpeed = 3;							// �J�����X�s�[�h
D3DXVECTOR2 CCameraconfig::m_AddSpeed = { 0.01f,-0.01f };		// �J�����X�s�[�h���Z

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCameraconfig::CCameraconfig()
{
	m_nSelect = 0;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCameraconfig::~CCameraconfig()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Init(void)
{
	// �w�i�̐���
	m_BgUi = std::move(CUi::LoadCreate_Self(CUi::UITYPE_SETTINGUI_BG));
	// �I��UI�̐���
	m_uni_SelectUi = std::move(CScene_TWO::Creat_Unique(
		CScene_TWO::OFFSET_TYPE_CENTER,
		D3DVECTOR3_ZERO,
		{95.0f,60.0f},
		0.0f,
		{ 1.0f,1.0f,1.0f,1.0f }
	));
	// �e�N�X�`���[�ݒ�
	m_uni_SelectUi->BindTexture(CTexture_manager::GetTexture(69));
	// UI�̐���
	m_Ui = std::move(CUi::LoadCreate_Self(
		CUi::UITYPE_SETTINGUI_SELECT
	));
	// �e�N�X�`���[�A�j���[�V�����ݒ�
	SetTexAnim();
	// �I��UI�̈ʒu�X�V
	m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
	m_uni_SelectUi->Set_Vtx_Pos();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Uninit(void)
{
	// �w�i�̏I������
	for (int nCntUi = 0; nCntUi < (signed)m_BgUi.size(); nCntUi++)
	{
		m_BgUi[nCntUi]->Uninit();
	}
	// �I��UI�̏I������
	if (m_uni_SelectUi != NULL)
	{
		m_uni_SelectUi->Uninit();
	}
	// PauseUI�̏I������
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Uninit();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Update(void)
{
	/* �W���C�p�b�h */
	if (CManager::GetJoy() != NULL)
	{
		// �X�e�B�b�N�̉������ɌX�����Ƃ� |
		// ����󂪉����ꂽ�Ƃ� |
		// ->���̍��ڂ�
		if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_DOWN) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_DOWN))
		{
			m_nSelect++;
			// �����������
			if (m_nSelect >= CAMERACONFIG_MAX)
			{
				m_nSelect = CAMERACONFIG_UPDOWN;
			}
			// �I��UI�̈ʒu�X�V
			m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
			m_uni_SelectUi->Set_Vtx_Pos();
			// �J�[�\����
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
		}
		// �X�e�B�b�N�̏�����ɌX�����Ƃ� |
		// ���󂪉����ꂽ�Ƃ� |
		// ->�O�̍��ڂ�
		else if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_UP) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_UP))
		{
			m_nSelect--;
			// ������������
			if (m_nSelect < CAMERACONFIG_UPDOWN)
			{
				m_nSelect = CAMERACONFIG_RESET;
			}
			// �I��UI�̈ʒu�X�V
			m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
			m_uni_SelectUi->Set_Vtx_Pos();
			// �J�[�\����
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
		}
		// B�{�^������������ |
		// ->�I�����Ă��鍀�ڂ̏���
		if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_B))
		{
			Select();
		}
		// �E�X�e�B�b�N��|������ |
		// �E������������
		// ->�J�����̑��x���オ��
		else if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_RIGHT) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_RIGHT))
		{
			// �J�����̑����ݒ�
			if (m_nSelect == CAMERACONFIG_SPEED)
			{
				if (m_nSpeed < 9)
				{
					D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
					RotSpeed.x += m_AddSpeed.x;
					RotSpeed.y += m_AddSpeed.y;
					m_nSpeed++;
					// �G���^�[��
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
				}
			}
			// �e�N�X�`���[�A�j���[�V�����ݒ�
			SetTexAnim();
		}
		// ���X�e�B�b�N��|������ |
		// ��������������
		// ->�J�����̑��x��������
		else if (CManager::GetJoy()->GetBoolStickLeft(0, CJoypad::DIRECTION_LEFT) ||
			CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_LEFT))
		{
			// �J�����̑����ݒ�
			if (m_nSelect == CAMERACONFIG_SPEED)
			{
				if (m_nSpeed > 1)
				{
					D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
					RotSpeed.x -= m_AddSpeed.x;
					RotSpeed.y -= m_AddSpeed.y;
					m_nSpeed--;
					// �G���^�[��
					CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
				}
			}
			// �e�N�X�`���[�A�j���[�V�����ݒ�
			SetTexAnim();
		}
		// A�{�^������������ |
		// ->�߂�
		else if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_A))
		{
			// �|�[�Y�̃J�����ݒ��Ԃ�false��
			m_bConfig = false;
			// �I��ԍ�������������
			m_nSelect = CCameraconfig::CAMERACONFIG_UPDOWN;
		}
	}
	/* �L�[�{�[�h */
	// �������������� |
	// S�{�^������������ |
	// ->���̍��ڂ�
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_DOWN) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_S))
	{
		m_nSelect++;
		// �����������
		if (m_nSelect >= CAMERACONFIG_MAX)
		{
			m_nSelect = CAMERACONFIG_UPDOWN;
		}
		// �I��UI�̈ʒu�X�V
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
		// �J�[�\����
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
	}
	// ������������� |
	// W�{�^������������ |
	// ->�O�̍��ڂ�
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_UP) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_W))
	{
		m_nSelect--;
		// ������������
		if (m_nSelect < CAMERACONFIG_UPDOWN)
		{
			m_nSelect = CAMERACONFIG_RESET;
		}
		// �I��UI�̈ʒu�X�V
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
		// �J�[�\����
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND1);
	}
	// �G���^�[�������� |
	// ->�I�����Ă��鍀�ڂ̏���
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
	{
		Select();
	}
	// �E����������
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RIGHT) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_D))
	{
		// �J�����̑����ݒ�
		if (m_nSelect == CAMERACONFIG_SPEED)
		{
			if (m_nSpeed < 9)
			{
				D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
				RotSpeed.x += m_AddSpeed.x;
				RotSpeed.y += m_AddSpeed.y;
				m_nSpeed++;
				// �G���^�[��
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
			}
		}
		// �e�N�X�`���[�A�j���[�V�����ݒ�
		SetTexAnim();
	}
	// ������������
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_LEFT) ||
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_A))
	{
		// �J�����̑����ݒ�
		if (m_nSelect == CAMERACONFIG_SPEED)
		{
			if (m_nSpeed > 1)
			{
				D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();
				RotSpeed.x -= m_AddSpeed.x;
				RotSpeed.y -= m_AddSpeed.y;
				m_nSpeed--;
				// �G���^�[��
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
			}
		}
		// �e�N�X�`���[�A�j���[�V�����ݒ�
		SetTexAnim();
	}
	// BackSpace���������� |
	// ->�߂�
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_BACKSPACE))
	{
		// �|�[�Y�̃J�����ݒ��Ԃ�false��
		m_bConfig = false;
		// �I��ԍ�������������
		m_nSelect = CCameraconfig::CAMERACONFIG_UPDOWN;
		// �I��UI�̈ʒu�X�V
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
		// �G���^�[��
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	}
	/* �eUI�̍X�V���� */
	// �w�i�̍X�V����
	for (int nCntUi = 0; nCntUi < (signed)m_BgUi.size(); nCntUi++)
	{
		m_BgUi[nCntUi]->Update();
	}
	// �I��UI�̍X�V����
	if (m_uni_SelectUi != NULL)
	{
		m_uni_SelectUi->Update();
	}
	// UI�̍X�V����
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Update();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�揈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Draw(void)
{
	// �w�i�̍X�V����
	for (int nCntUi = 0; nCntUi < (signed)m_BgUi.size(); nCntUi++)
	{
		m_BgUi[nCntUi]->Draw();
	}
	// �I��UI�̕`�揈��
	if (m_uni_SelectUi != NULL)
	{
		m_uni_SelectUi->Draw();
	}
	// UI�̕`�揈��
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Draw();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �S�̂̏�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::SelfInit(void)
{
	// �I��������
	m_nSelect = 0;
}

#ifdef _DEBUG
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O�\��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Debug(void)
{
}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CCameraconfig::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::UnLoad(void)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �쐬����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::unique_ptr<CCameraconfig> CCameraconfig::Create_Self(void)
{
	// �ϐ��錾
	std::unique_ptr<CCameraconfig> pCameraconfig(new CCameraconfig);
	// ����������
	pCameraconfig->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pCameraconfig;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::Select(void)
{
	// �G���^�[��
	CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	D3DXVECTOR2 &RotSpeed = CManager::GetRenderer()->GetCamera()->GetRotSpeed();

	// �J�����㉺�ݒ�
	if (m_nSelect == CAMERACONFIG_UPDOWN)
	{
		RotSpeed.x *= -1;
		m_AddSpeed.x *= -1;
	}
	// �J�������E�ݒ�
	else if (m_nSelect == CAMERACONFIG_LEFTRIGHT)
	{
		RotSpeed.y *= -1;
		m_AddSpeed.y *= -1;
	}
	// �J�����̑����ݒ�
	else if (m_nSelect == CAMERACONFIG_SPEED)
	{
		if (m_nSpeed < 9)
		{
			RotSpeed.x += m_AddSpeed.x;
			RotSpeed.y += m_AddSpeed.y;
			m_nSpeed++;
		}
	}
	// �߂�
	else if (m_nSelect == CAMERACONFIG_BACK)
	{
		// �|�[�Y�̃J�����ݒ��Ԃ�false��
		m_bConfig = false;
		// �I��ԍ�������������
		m_nSelect = CCameraconfig::CAMERACONFIG_UPDOWN;
		// �I��UI�̈ʒu�X�V
		m_uni_SelectUi->SetPosition(m_Ui[m_nSelect]->GetScene_Two()->GetPosition());
		m_uni_SelectUi->Set_Vtx_Pos();
	}
	// ���ׂẴJ��������O�̏�Ԃɖ߂�
	else if (m_nSelect == CAMERACONFIG_RESET)
	{
		// ���ׂẴJ�����������Ƃ̏�Ԃɖ߂�
		CManager::GetRenderer()->GetCamera()->SetCameraInfo();
		m_nSpeed = 3;					// �J�����X�s�[�h
		m_AddSpeed = { 0.01f,-0.01f };	// �J�����X�s�[�h���Z
	}
	// �e�N�X�`���[�A�j���[�V�����ݒ�
	SetTexAnim();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �e�N�X�`���[�A�j���[�V�����ݒ菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCameraconfig::SetTexAnim(void)
{
	// y�̃J�����̉�]�X�s�[�h��-�Ȃ�
	if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().x > 0)
	{
		// UI�̃e�N�X�`���[�A�j���[�V�����ݒ�
		m_Ui[CAMERACONFIG_UPDOWN]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_NORMAL }, { 1.0f,CCTA + CCTA * TEX_NORMAL });
	}
	// y�̃J�����̉�]�X�s�[�h��+�Ȃ�
	else if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().x < 0)
	{
		// UI�̃e�N�X�`���[�A�j���[�V�����ݒ�
		m_Ui[CAMERACONFIG_UPDOWN]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_INVERSION }, { 1.0f,CCTA + CCTA * TEX_INVERSION });
	}
	// x�̃J�����̉�]�X�s�[�h��-�Ȃ�
	if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().y > 0)
	{
		// UI�̃e�N�X�`���[�A�j���[�V�����ݒ�
		m_Ui[CAMERACONFIG_LEFTRIGHT]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_INVERSION }, { 1.0f,CCTA + CCTA * TEX_INVERSION });
	}
	// x�̃J�����̉�]�X�s�[�h��+�Ȃ�
	else if (CManager::GetRenderer()->GetCamera()->GetRotSpeed().y < 0)
	{
		// UI�̃e�N�X�`���[�A�j���[�V�����ݒ�
		m_Ui[CAMERACONFIG_LEFTRIGHT]->GetScene_Two()->SetTex({ 0.0f,CCTA * TEX_NORMAL }, { 1.0f,CCTA + CCTA * TEX_NORMAL });
	}
	// �J�����X�s�[�h�̕ω�
	m_Ui[CAMERACONFIG_SPEED]->GetScene_Two()->SetTex({ CCBTA * m_nSpeed,0.0f }, { CCBTA + CCBTA * m_nSpeed,1.0f });
}
