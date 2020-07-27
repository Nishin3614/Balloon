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
// �}�N����`
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O���錾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class C2DGauge;		// 2D�Q�[�W�N���X

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CPlayer : public CCharacter_Balloon
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CCharacter::MOTIONTYPE_MAX
	} MOTIONTYPE;
	// ---------�L�����N�^�[�^�C�v---------- //
	typedef enum
	{
		CHARATYPE_SPEED_UP = 0,
		CHARATYPE_REVIVAL,
		CHARATYPE_INVISIBLE,
		CHARATYPE_ATTACK_UP,
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
	bool const &GetMPMax(void) { return m_bMPMax; }
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
	void Camera(void);					// �J��������
	void OtherMove(void);				// ���L�����ړ�����
	void OtherAction(void);				// ���L�����s������
	void FishApponent(void);			// �����o��

	/* �ϐ� */
	static int	m_All;					// ����
	C2DGauge	*m_p2DMPGauge;			// MP�Q�[�W
	D3DXVECTOR3	m_posold;				// �O�̈ʒu
	int m_nPlayerID;					// �ԍ�
	int m_nCntFishApponent;				// ���o���J�E���g
	int m_nMP;							// MP
	bool m_bMPMax;						// MP���ő傩�ǂ���
	bool m_bResetMP;					// MP�����Z�b�g
};
#endif
