// ==========================================================
//
// �v���C���[(����)���� [revival.h]
// Author : RYOUMA INOUE
//
// ==========================================================
#ifndef _REVIVAL_H_
#define _REVIVAL_H_

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
class CRevival : public CPlayer
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CPlayer::MOTIONTYPE_MAX
	} MOTIONTYPE;
	/* �֐� */
	CRevival();
	~CRevival();
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
	static CRevival * Create(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);			// �쐬
				// ��������(�l�Ǘ�)
	static CRevival * Create_Self(
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
	bool m_bRevival;					// �������邩�ǂ���
};
#endif
