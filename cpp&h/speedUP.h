// ==========================================================
//
// �v���C���[(�X�s�[�h�A�b�v)���� [speedUP.h]
// Author : RYOUMA INOUE
//
// ==========================================================
#ifndef _SPEEDUP_H_
#define _SPEEDUP_H_

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
class CSpeedUP : public CPlayer
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CPlayer::MOTIONTYPE_MAX
	} MOTIONTYPE;
	/* �֐� */
	CSpeedUP();
	~CSpeedUP();
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
	static CSpeedUP * Create(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);			// �쐬
				// ��������(�l�Ǘ�)
	static CSpeedUP * Create_Self(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);
	static HRESULT Load(void);			// �ǂݍ���
	static void UnLoad(void);			// UnLoad����
protected:
private:
	/* �\���� */
	/* �֐� */

	/* �ϐ� */
	bool m_bSpeedUP;					// �X�s�[�h�A�b�v���邩�ǂ���
};
#endif
