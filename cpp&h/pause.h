// ------------------------------------------
//
// �|�[�Y�w�b�_�[���� [pause.h]
// Author : KOKI NISHIYAMA
//
// ------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CPause_ui;
class CPause_bg;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CPause
{
public:
	/* �֐� */
	CPause();
	~CPause();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SelfInit(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
protected:
private:
	unique_ptr<CPause_ui> m_uni_Pause_ui;	// �|�[�YUI
};
#endif
