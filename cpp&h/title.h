//=============================================================================
//
// �^�C�g���̏��� [title.h]
// Author : Ryouma Inoue
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

#define TITLE_BG_X (600.0f)				// �^�C�g���ʒu
#define TITLE_BG_Y (300.0f)				// �^�C�g���ʒu
#define TITLE_SIZE_X (450.0f)			// �^�C�g���T�C�Y
#define TITLE_SIZE_Y (250.0f)			// �^�C�g���T�C�Y
#define TITLEUI_POS_X (600.0f)			// �^�C�g��UI�ʒu
#define TITLEUI_POS_Y (600.0f)			// �^�C�g��UI�ʒu
#define TITLEUI_SIZE_X (300.0f)			// �^�C�g��UI�T�C�Y
#define TITLEUI_SIZE_Y (100.0f)			// �^�C�g��UI�T�C�Y

#define RESULT_TITLEUI_POS_X (1000.0f)			// ���U���g�p�^�C�g��UI�ʒu
#define RESULT_TITLEUI_POS_Y (600.0f)			// ���U���g�p�^�C�g��UI�ʒu
#define RESULT_TITLEUI_SIZE_X (200.0f)			// ���U���g�p�^�C�g��UI�T�C�Y
#define RESULT_TITLEUI_SIZE_Y (100.0f)			// ���U���g�p�^�C�g��UI�T�C�Y

#define PLAYER_POS_X (20.0f)			// �v���C���[�̈ʒu
#define PLAYER_POS_Y (20.0f)			// �v���C���[�̈ʒu
#define TITLE_WALL_POS_X (330.0f)		// �ǂ̈ʒu
#define TITLE_WALL_POS_Y (100.0f)		// �ǂ̈ʒu
#define TITLE_WALLF_POS_Y (50.0f)		// �ǂ̈ʒu
#define TITLE_WALL_POS_Z (500.0f)		// �ǂ̈ʒu

//=============================================================================
// �O���錾	( �|�C���^�����Ȃ�g���� )
//=============================================================================
class	CTitleUI;

//=============================================================================
// �Ǘ��N���X
//=============================================================================
class CTitle
{
public:

	CTitle();													// �R���X�g���N�^
	~CTitle();													// �f�X�g���N�^

	HRESULT Init();												// ������
	void	Uninit(void);										// �I��
	void	Update(void);										// �X�V
	void	Draw(void);											// �`��

	static  CTitle		*Create(void);							// �^�C�g���̐���

private:
	CTitleUI *m_pTitleUI;										// �^�C�g��UI�ւ̃|�C���^
};
#endif
