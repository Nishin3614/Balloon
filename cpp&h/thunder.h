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

	static CThunder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����
	static void Unload(void);													// �A�����[�h

private:
	CMeshdome *m_pMeshDome;								// ���b�V���h�[���ւ̃|�C���^

	D3DXVECTOR3 m_move;									// �ړ���

	int	m_nCounterAnim;									// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;									// �A�j���[�V�����p�^�[��
	int m_nCntThunder;									// ���̃J�E���g
	int m_nCntDraw;										// ���̕`��J�E���g
	float m_fDistance;									// ����
	bool m_bThunder;									// ���̏��
};
#endif