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
#define	MAX_DISTANCE	(100)							// ����
#define	ANIM_TEX		(1.0f / 6.0f)					// �A�j���[�V�����e�N�X�`��

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

	static CThunder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����
	static void Unload(void);													// �A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_pTex;					// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *m_pVtx;									// ���_���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X

	static CThunder *m_pThunder;

	CMeshdome *m_pMeshDome;								// ���b�V���h�[���ւ̃|�C���^

	D3DXVECTOR3	m_vtxMin;								// �ŏ��l
	D3DXVECTOR3	m_vtxMax;								// �ő�l
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_posOld;								// �O��̈ʒu
	D3DXVECTOR3 m_rot;									// ��]
	D3DXVECTOR3 m_move;									// �ړ���
	D3DXCOLOR m_col;									// �F

	int	m_nCounterAnim;									// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;									// �A�j���[�V�����p�^�[��
	int m_nCntThunder;									// ���̃J�E���g
	int m_nCntDraw;										// ���̕`��J�E���g
	float m_fDistance;									// ����
	bool m_bThunder;									// ���̏��
};
#endif