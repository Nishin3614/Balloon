// ==========================================================
//
// ��[thunder.h]
// Author:Ryouma Inoue
//
// ==========================================================
#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"
#include "scene_three.h"

// ==========================================================
// �}�N����`
// ==========================================================
#define	TEXTURE_THUNDER	"data/TEXTURE/coin.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_DISTANCE	(150)							// ����
#define	MAX_DISTANCE_Y	(2000)							// ����

// ==========================================================
//
// �O���錾
//
// ==========================================================
class CMeshdome;

// ==========================================================
//
// �N���X�̒�`
//
// ==========================================================
class CThunder : public CScene_THREE
{
public:

	CThunder();												// �R���X�g���N�^
	~CThunder();											// �f�X�g���N�^

	void Init(void);										// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��
#ifdef _DEBUG
	void Debug(void) {};
#endif // _DEBUG
	// ����������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_MyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// ����ɓ��Ă�ꂽ��̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_OpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// �������瓖����Ȃ�������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_NoMyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// ����ɓ��Ă��Ȃ�������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	static int &GetAllThunder(void) { return m_nAllThunder; };			// �|�C���g�T�[�N���̑����擾
	static CThunder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����
	static void Unload(void);													// �A�����[�h

private:
	/* �֐� */
	// �`���[�g���A���̍X�V����
	void Update_Tutorial(void);
	// �Q�[���̍X�V����
	void Update_Game(void);
	/* �ϐ� */
	static int m_nAllThunder;						// �|�C���g�T�[�N���̑���
	CMeshdome *m_pMeshDome;								// ���b�V���h�[���ւ̃|�C���^


	int	m_nCounterAnim;									// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;									// �A�j���[�V�����p�^�[��
	int m_nCntThunder;									// ���̃J�E���g
	int m_nCntDraw;										// ���̕`��J�E���g
	float m_fDistance;									// ����
};
#endif