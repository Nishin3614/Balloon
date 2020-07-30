// ==========================================================
//
// �v���C���[(�X�R�A�A�b�v)���� [scoreUP.h]
// Author : RYOUMA INOUE
//
// ==========================================================
#ifndef _SCOREUP_H_
#define _SCOREUP_H_

#define _CRT_SECURE_NO_WARNINGS

// ==========================================================
// �C���N���[�h�t�@�C��
// ==========================================================
#include "player.h"

// ==========================================================
// �O���錾
// ==========================================================


// ==========================================================
// �N���X
// ==========================================================
class CScoreUP : public CPlayer
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CPlayer::MOTIONTYPE_MAX
	} MOTIONTYPE;
	/* �֐� */
	CScoreUP();
	~CScoreUP();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// �v���C���[�����񂾂Ƃ��̊֐�
	void Die(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
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
	// ��������(�V�[���Ǘ�)
	static CScoreUP * Create(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);			// �쐬
				// ��������(�l�Ǘ�)
	static CScoreUP * Create_Self(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);
	static HRESULT Load(void);			// �ǂݍ���
	static void UnLoad(void);			// UnLoad����
	static bool GetScoreUP(void) { return m_bScoreUP; }	// ��Ԏ擾
protected:
private:
	/* �\���� */
	/* �֐� */

	/* �ϐ� */
	static bool m_bScoreUP;					// �X�L���A�b�v���邩�ǂ���
};
#endif
