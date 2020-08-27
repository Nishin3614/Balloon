// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���f������ [player.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character_balloon.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PLAYER_FRONTFORCE		(10)
#define PLAYER_G				(0.5f)								// �d��
#define PLAYER_RESISTANCE		(0.5f)								// ��R��
#define PLAYER_MOTIONFILE		"data/LOAD/PLAYER/Tricker.txt"		// ���[�V�����̃t�@�C����
#define PLAYER_FALL				(-20.0f)							// ������ʒu����
#define PLAYER_UI_MP_POS		(D3DXVECTOR3(78.5f, 690.0f, 0.0f))	// UI_MP�̈ʒu
#define PLAYER_MPMAX			(10000)								// MP�̍ő�l
#define FISH_APPONENTPOS		(-40.0f)								// ���o���ʒu
#define FISH_APPONENTTIME		(300)								// ���o���^�C��
#define MPUP_EVERY				(1)									// �}�C�t���[��MPUP
#define MPUP_BREAKBALLOON		(100)								// ���D������������MPUP
#define MPUP_ENEMY_KNOCKDOWN	(1000)								// �G��|�����Ƃ���MPUP
#define MPUP_PLAYER_KNOCKDOWN	(1000)								// �v���C���[��|�����Ƃ���MPUP
#define SPEED_UP_MPDOWN			(100)								// �v���C���[(�X�s�[�h�A�b�v)��MP�����
#define REVIVAL_MPDOWN			(1000)								// �v���C���[(����)��MP�����
#define INVISIBLE_MPDOWN		(10)								// �v���C���[(����)��MP�����
#define SCORE_UP_MPDOWN			(100)								// �v���C���[(�X�R�A�A�b�v)��MP�����

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O���錾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class C2DGauge;		// 2D�Q�[�W�N���X
class CRank;		// �����N�N���X
class CFramework;	// �t���[�����[�N�N���X
class CMeshdome;	// ���b�V���h�[���N���X

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CPlayer : public CCharacter_Balloon
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_JAMP = CCharacter::MOTIONTYPE_MAX,
		MOTIONTYPE_DANCE,
		MOTIONTYPE_MAX
	} MOTIONTYPE;
	// ---------�L�����N�^�[�^�C�v---------- //
	typedef enum
	{
		CHARATYPE_SPEED_UP = 0,
		CHARATYPE_REVIVAL,
		CHARATYPE_INVISIBLE,
		CHARATYPE_SCORE_UP,
		CHARATYPE_MAX
	} CHARATYPE;
	/* �֐� */
	CPlayer(CCharacter::CHARACTER const &character);
	virtual ~CPlayer();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	// �v���C���[�����񂾂Ƃ��̊֐�
	virtual void Die(void);
	void OtherDie(void);
	// ����������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	);
	// ����ɓ��Ă�ꂽ��̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	);
	// �v���C���[�ԍ��̐ݒ�
	void SetPlayerID(int const &nPlayerID) { m_nPlayerID = nPlayerID; };
	// �v���C���[�ԍ��̎擾
	int const &GetPlayerID(void) { return m_nPlayerID; };
	// MP�̃t���O�擾
	void SetMPMax(const bool bValue) { m_bMPMax = bValue; }
	bool const &GetMPMax(void) { return m_bMPMax; }
	// �ړ��ʂ̐ݒ�
	void const SetMoveNow(float fMoveNow) { m_fMoveNow = fMoveNow; }
	static bool GetDie(int nId) { return m_bDie[nId]; }
	void Camera(void);					// �J��������
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	static HRESULT Load(void);			// �ǂݍ���
	static void UnLoad(void);			// UnLoad����
	// MP�グ����
	//	nMpUp	: MP�グ�l
	void MpUp(int const & nMpUp);

protected:
private:
	/* �\���� */
	/* �֐� */
	void MyMove(void);					// ���L�����ړ�����
	void MyAction(const int &nId);		// ���L�����s������
	void OtherMove(void);				// ���L�����ړ�����
	void OtherAction(void);				// ���L�����s������
	void FishApponent(void);			// �����o��
	// ��Ԃɂ���Ẵ��[�V�����ݒ菈��
	void StatusMotion(void);
	/* �ϐ� */
	static int	m_All;					// ����
	static CMeshdome *m_pMeshDome;				// �ړ�����x���p
	CRank		*m_pRank;				// ���ݏ��ʕ\��
	C2DGauge	*m_p2DMPGauge;			// MP�Q�[�W
	D3DXVECTOR3	m_posold;				// �O�̈ʒu
	int m_nPlayerID;					// �ԍ�
	int m_nRank;						// ���̏���
	int m_nCntFishApponent;				// ���o���J�E���g
	int m_nMP;							// MP
	int m_nCloudCount;					// �_���o������܂ł̃J�E���^
	bool m_bMPMax;						// MP���ő傩�ǂ���
	bool m_bResetMP;					// MP�����Z�b�g
	static bool m_bDie[MAX_PLAYER];		// ���S�t���O
	float m_fMoveNow;					// ���݂̈ړ���
	CFramework * m_pFramework;			// �t���[�����[�N���
};
#endif