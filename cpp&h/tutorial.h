//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.h]
// Author : Ryouma Inoue
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "lake.h"
#include "floor.h"
#include "meshobit.h"
#include "meshdome.h"
#include "meshsphere.h"
#include "meshwall.h"
#include "3Deffect.h"
#include "bgdome.h"
#include "camera.h"
#include "3Dparticle.h"
#include "keyboard.h"
#include "3Dmap.h"
#include "item.h"
#include "thunder.h"

//=============================================================================
// �O���錾	( �|�C���^�����Ȃ�g���� )
//=============================================================================

//=============================================================================
// �Ǘ��N���X
//=============================================================================
class CTutorial
{
public:

	CTutorial();													// �R���X�g���N�^
	~CTutorial();													// �f�X�g���N�^

	HRESULT Init();												// ������
	void	Uninit(void);										// �I��
	void	Update(void);										// �X�V
	void	Draw(void);											// �`��

	static  CTutorial		*Create(void);						// �`���[�g���A���̐���

private:
	void PopEvent(void);
	// �`���[�g���A���������̐�������
	void Create_Tutorial_Explan(void);
	int nCntPop;
};
#endif
