// ==========================================================
//
// �����̗�[thunderMulti.h]
// Author:Ryouma Inoue
//
// ==========================================================
#ifndef _THUNDERMULTI_H_
#define _THUNDERMULTI_H_

#include "main.h"
#include "scene_three.h"

// ==========================================================
// �}�N����`
// ==========================================================
#define	ANIM_TEX		(1.0f / 8.0f)					// �A�j���[�V�����e�N�X�`��

// ==========================================================
//
// �N���X�̒�`
//
// ==========================================================
class CThunderMulti : public CScene_THREE
{
public:

	CThunderMulti();										// �R���X�g���N�^
	~CThunderMulti();										// �f�X�g���N�^

	void Init(void);										// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��
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
	static CThunderMulti *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *m_pVtx;									// ���_���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X

	static CThunderMulti *m_pThunderMulti;
	static int m_ThunderCnt;							// ���̃J�E���g

	D3DXVECTOR3	m_vtxMin;								// �ŏ��l
	D3DXVECTOR3	m_vtxMax;								// �ő�l
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_posOld;								// �O��̈ʒu
	D3DXVECTOR3 m_rot;									// ��]
	D3DXVECTOR3 m_move;									// �ړ���
	D3DXCOLOR m_col;									// �F

	int	m_nCounterAnim;									// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;									// �A�j���[�V�����p�^�[��
	float m_fDistance;									// ����
	bool m_bThunder;									// ���̏��
};
#endif