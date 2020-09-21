// ------------------------------------------
//
// �}�l�[�W���[�����̐���[manager.h]
// Author : Koki Nishiyama
//
// ------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_	 // �t�@�C��������T�����߂�

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
/* ��{ */
#include "main.h"
#include "Calculation.h"

/* �`�� */
#include "renderer.h"

/* ���̓f�o�C�X */
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "keyconfig.h"

/* �T�E���h */
#include "sound.h"

/* �f�o�b�O�\�� */
#include "debugproc.h"

// ------------------------------------------
//
// �}�N���֐�
//
// ------------------------------------------
#define ONEPLAYER_STAGE		(5)
#define DOUBLEPLAYER_STAGE	(5)
#define DERAY_TIME(X)		(X * 60)
#define MAX_PLAYER			(4)

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CFade;		// ��ʑJ��
class CGame;		// �Q�[��
class CTitle;		// �^�C�g��
class CTutorial;	// �`���[�g���A��
class CResult;		// ���U���g
class CRanking;		// �����L���O
class CNetwork;		// �l�b�g���[�N
class CSelect;		// �I�����
class CLoadScreen;	// �ǂݍ��݉��

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CManager
{
public:
	/* �񋓌^ */
	// ���[�h
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_SELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	} MODE;
	/* �֐� */
	CManager();
	~CManager();
	HRESULT  Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE const mode);							// ���[�h�ݒ�
	static CRenderer * GetRenderer(void) { return m_renderer; };	// �����_�����O�̎��؀
	static CKeyboard * GetKeyboard(void) { return m_keyboard; };	// �L�[�{�[�h�̎��؀
	static CJoypad * GetJoy(void) { return m_joypad; };				// �W���C�p�b�h�̎��؀
	static CMouse * GetMouse(void) { return m_mouse; };				// �}�E�X�̎��؀
	static CKeyConfig * GetKeyConfig(void) { return m_keyconfig; };	// �L�[�ڍׂ̎��؀
	static CSound * GetSound(void) { return m_sound; };				// �T�E���h�̎��؀
	static CFade * GetFade(void) { return m_fade; };				// ��ʑJ�ڂ̎��؀
	static CGame * GetGame(void) { return m_game; };				// �Q�[���̎��؀
	static CLoadScreen * GetLoadScreen(void) { return m_pLoadScreen; };	// �ǂݍ��݉�ʎ擾
	static MODE GetMode(void) { return m_mode; };					// ���[�h�̎��؀
	static CNetwork * GetNetwork(void) { return m_pNetwork; }		// �l�b�g���[�N�̎��؀
	static CSelect * GetSelect(void) { return m_select; };			// �I����ʂ̎��؀

	// �v���C���[�ԍ��̎擾
	static int const &GetPlayerID(void) { return m_nPlayerID; };	// �v���C���[�ԍ�
protected:

private:
	// �Q�[���Ɍ������Ȃ�����
	static CRenderer * m_renderer;			// �����_�����O
	static CSound * m_sound;				// �T�E���h

											// ���̓f�o�C�X
	static CKeyboard * m_keyboard;			// �L�[�{�[�h
	static CJoypad * m_joypad;				// �W���C�p�b�h
	static CMouse * m_mouse;				// �}�E�X
	static CKeyConfig * m_keyconfig;		// �L�[�ڍ�

	// ���
	static CFade * m_fade;					// ��ʑJ��
	static CTitle * m_title;				// �^�C�g��
	static CTutorial * m_tutorial;			// �`���[�g���A��
	static CGame * m_game;					// �Q�[��
	static CSelect * m_select;				// �I�����
	static CLoadScreen * m_pLoadScreen;		// �ǂݍ��݉��
	static CResult * m_result;				// ���U���g
	static CRanking * m_ranking;			// �����L���O
	static CNetwork * m_pNetwork;			// �l�b�g���[�N

	static MODE m_mode;						// ���[�h
	static bool	m_bWire;					// ���C���[���[�h
	static int m_nPlayerID;					// �v���C���[�ԍ�
};

#endif // !_MANAGER_H_