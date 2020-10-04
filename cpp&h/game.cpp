// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �Q�[������ [game.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "game.h"
/* �`�� */
#include "number.h"
#include "fade.h"
#include "floor.h"
#include "meshobit.h"
#include "meshdome.h"
#include "meshsphere.h"
#include "meshwall.h"
#include "3Deffect.h"
#include "bgdome.h"
#include "time.h"
#include "collision.h"
#include "camera.h"
#include "3Dparticle.h"
#include "keyboard.h"
#include "ui_group.h"
#include "Extrusion.h"
#include "3Dmap.h"
#include "score.h"
#include "network.h"
#include "item.h"
#include "thunder.h"
#include "selectcharacter.h"
#include "character_fish.h"
#include "invisible.h"
#include "revival.h"
#include "speedUP.h"
#include "scoreUP.h"
#include "rank.h"
#include "lake.h"
#include "loadscreen.h"

/* �|�[�Y */
#include "pause.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define ITEM_SPACE	(100)			// �A�C�e�����m�̊Ԋu
#define CIRCLE_SIZE (300)			// �~�̑傫��

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::STATE CGame::m_state = CGame::STATE_NORMAL;		// ���
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::CGame()
{
	m_pause = NULL;
	m_state = CGame::STATE_NORMAL;
	m_nWatchingId = 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Init(void)
{
	// ���[�h�X�N���[���̕ϐ�����������
	CManager::GetLoadScreen()->VariableInit();
	CNetwork *pNetwork = CManager::GetNetwork();

	// �J�����̃^�C�v�ݒ�
	CManager::GetRenderer()->GetCamera()->SetType(CCamera::TYPE_FOLLOW);
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();
	/* ������ */
	// ���
	m_state = STATE_NORMAL;
	// �L�����N�^�[�̑��l��
	CCharacter::InitStatic();
	/* �쐬 */
	// 3D�G�t�F�N�g�̐���
	C3DEffect::Create();
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();
	// ���̐ݒ�
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		100000.0f);
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();
	// 3D�}�b�v����
	CLake::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(25000.0f, 25000.0f, 0.0f));
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();

	C3DMap::LoadScript("data/LOAD/MAPPING/rand.txt");
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();
	C3DMap::LoadCreate(C3DMap::MAP_STAGE_1);
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();
	// �v���C���[����
	PlayerCreate();
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();

	// �X�R�A����
	m_pScore = CScore::Create();
	// �|�[�Y�̐���
	m_pause = new CPause();
	// �|�[�Y�̏�����
	m_pause->Init();
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();
	if (pNetwork != NULL)
	{
		pNetwork->ResetCoin();				// �R�C���̃f�[�^�x�[�X�����Z�b�g
	}
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();

	CScene_X::LoadScrept("data/LOAD/MAPPING/object.csv");
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();

	// �X�^�[�g�R�[��
	CUi_group::Create(CUi::UITYPE_GAMESTART);
	// �ǂݍ��݉�ʕ`��
	CManager::GetRenderer()->LoadDraw();

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Uninit(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork != NULL)
	{// �l�b�g���[�N�����݂��Ă����Ƃ�
		pNetwork->StopUpdate();				// �X�V��~�\��
		pNetwork->CloseTCP();				// �T�[�o�[�Ƃ̑�����߂�
	}

	// �|�[�Y
	if (m_pause != NULL)
	{
		m_pause->Uninit();
		delete m_pause;
		m_pause = NULL;
	}
	// �X�R�A
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}
	// �Q�[����Ԃ̏�����
	m_state = STATE_NORMAL;
	// �V�[���̊J��
	CScene::ReleaseAll();
	// �V�[���X�g�b�v����
	CScene::UpdateStop(false);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Update(void)
{
	// �����蔻�菈��
	CCollision::CollisionDetection();
	// �|�[�Y��ԂȂ��
	if (m_state == STATE_PAUSE)
	{
		if (m_pause != NULL)
		{
			m_pause->Update();
		}
	}
	// �|�[�Y��Ԃł͂Ȃ��Ƃ�
	else
	{
		// �|�[�Y��
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_POUSE))
		{
			//PauseState();
		}
	}

	if (CPlayer::GetDie(CManager::GetNetwork()->GetId()))
	{
		CKeyboard *pKeyboard = CManager::GetKeyboard();

		if (pKeyboard != NULL)
		{
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				FocusPlayer();
			}
		}

		if (!CPlayer::GetDie(m_nWatchingId))
		{
			m_pPlayer[m_nWatchingId]->Camera();
		}
	}

#ifdef _DEBUG
	// ���擾
	CFade *pFade = CManager::GetFade();	// �t�F�[�h���

	// �t�F�[�h���Ă��Ȃ��Ƃ�
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// �Q�[���֑J��
		if (CManager::GetKeyboard()->GetKeyboardPress(TESTPLAY_NUMBER1))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// ���U���g��
				pFade->SetFade(CManager::MODE_TUTORIAL);
			}
		}
	}
	// �e�X�g�p
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// �Q�[���֑J��
		if (CManager::GetKeyboard()->GetKeyboardPress(TESTPLAY_NUMBER2))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// ���U���g��
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
	}
	DebugStatus();

	// �I���\��
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_T))
	{
		CUi_group::Create(CUi::UITYPE_FINISH);
	}
	// �X�e�[�^�X���Z�b�g
	if (CManager::GetKeyboard()->GetKeyboardPress(DIK_LCONTROL) &&
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_4))
	{
		CCharacter::LoadStatus();
		CItem::LoadStatus();
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				continue;
			}
			m_pPlayer[nCntPlayer]->GaugeStatusInit();
		}
	}
#endif // _DEBUG
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Draw(void)
{
	if (m_state == STATE_PAUSE)
	{
		if (m_pause != NULL)
		{
			m_pause->Draw();
		}
	}
	if (m_pScore != NULL)
	{
		m_pScore->Draw();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���ڂ����鏈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::FocusPlayer(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork == NULL) return;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_nWatchingId++;

		if (m_nWatchingId == MAX_PLAYER)
		{
			m_nWatchingId = 0;
		}

		if (!pNetwork->GetDie(m_nWatchingId))
		{
			OutputDebugString("�ӂ�������[");
			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O�X�e�[�^�X����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::DebugStatus(void)
{
	// �X�e�[�^�X�̍X�V //
	CDebugproc::Print("LCTRL + 4:�X�e�[�^�X�̍X�V\n");
	//CCharacter::AllDebug();
	//CItem::AllDebug();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �|�[�Y���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::PauseState(void)
{
	// �Q�[����Ԃ��|�[�Y��
	if (m_state != STATE_PAUSE)
	{
		m_state = STATE_PAUSE;
		// �X�V���~�߂�
		CScene::UpdateStop(true);
		// ���j���[��
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �v���C���[����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::PlayerCreate(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	char aAns[256];
	int aData[MAX_PLAYER];
	char cDie[64];
	D3DXVECTOR3 pos;

	memset(&cDie, 0, sizeof(cDie));

	pNetwork->SendTCP("CHARACTER_LOAD", sizeof("CHARACTER_LOAD"));
	pNetwork->DataRecv(SOCKETTYPE_CLIENT, (char*)&aAns, sizeof(aAns));
	sscanf(aAns, "%s %d %d %d %d", &cDie, &aData[0], &aData[1], &aData[2], &aData[3]);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		switch (nCntPlayer)
		{
		case 0:
			pos = D3DXVECTOR3(-850.0f, 0.0f, 850.0f);
			break;
		case 1:
			pos = D3DXVECTOR3(850.0f, 0.0f, 850.0f);
			break;
		case 2:
			pos = D3DXVECTOR3(-850.0f, 0.0f, -850.0f);
			break;
		case 3:
			pos = D3DXVECTOR3(850.0f, 0.0f, -850.0f);
			break;
		default:
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}

		switch (aData[nCntPlayer])
		{
		case CHARATYPE_SPEED_UP:
			m_pPlayer[nCntPlayer] = CSpeedUP::Create(nCntPlayer, pos);
			break;
		case CHARATYPE_SCORE_UP:
			m_pPlayer[nCntPlayer] = CScoreUP::Create(nCntPlayer, pos);
			break;
		case CHARATYPE_INVISIBLE:
			m_pPlayer[nCntPlayer] = CInvisible::Create(nCntPlayer, pos);
			break;
		case CHARATYPE_REVIVAL:
			m_pPlayer[nCntPlayer] = CRevival::Create(nCntPlayer, pos);
			break;
		}
	}
}
