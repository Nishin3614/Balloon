// ----------------------------------------
//
// �T�E���h�����̐���[sound.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "main.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_SE (10)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CSound
{
public:
	/* �񋓌^ */
	// ���^�C�v
	typedef enum
	{
		SOUND_BGM= 0,	// BGM
		SOUND_SE,		// SE
		SOUND_VOICE,	// VOICE
		SOUND_MAX,
	} SOUND;
	// ���x��
	typedef enum
	{
		LABEL_BGM_TITLE = 0,	// �^�C�g��
		LABEL_BGM_GAME,			// �Q�[��
		LABEL_BGM_RANKINGMOVE,	// �����L���O
		LABEL_SE_ENTER,			// ���艹
		LABEL_SE_SWORDSLASH1,	// �U���������������̉�
		LABEL_SE_SWORD,			// ����U�肩����
		LABEL_SE_TRICKBEFORE,	// �鉜�`�������O
		LABEL_SE_BOMB,			// ������
		LABEL_SE_CURSOL,		// �J�[�\����
		LABEL_SE_SWITCH,		// �����\�����̉�
		LABEL_SE_CLEAR,			// �N���A��
		LABEL_SE_WORNING,		// �x����
		LABEL_VOICE_ATTCK,		// �U��
		LABEL_VOICE_SKILL_1,	// �Z�P
		LABEL_VOICE_SKILL_2,	// �Z�Q
		LABEL_VOICE_TRICK1,		// �鉜�`�P
		LABEL_VOICE_TRICK2,		// �鉜�`�Q
		LABEL_VOICE_DAMAGE,		// �_���[�W
		LABEL_SE_MENU,			// ���j���[��
		LABEL_SE_GAMEOVER,		// �Q�[���I�[�o�[
		LABEL_SE_GAMESTART,		// �Q�[���X�^�[�g
		LABEL_VOICE_DIED,		// �v���C���[���퓬�s�\���̐�
		LABEL_VOICE_DIED2,		// �v���C���[���퓬�s�\���̐�2
		LABEL_MAX,
	} LABEL;
	/* �֐� */
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(
		LABEL const &label		// ���x��
	);
	void StopSound(LABEL label);
	void StopCompusionSound(LABEL label);
	void StopSound(void);
	// �X�N���v�g����ǂݍ���
	static HRESULT Load(void);
protected:

private:
	/* �֐� */
	HRESULT AudioCreate(HWND hWnd);
	HRESULT SoundCreate(HWND hWnd);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	/* �ϐ� */
	static vector<string> m_vec_Filename;					// �t�@�C����
	static vector<int> m_vec_nLoop;							// ���[�v�J�E���g
	static vector<SOUND> m_vec_SoundType;					// �T�E���h�^�C�v
	static IXAudio2 *m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// �}�X�^�[�{�C�X
	static BYTE *m_apDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static IXAudio2SourceVoice *m_SourceBGM;				// �\�[�XBGM
	static IXAudio2SourceVoice *m_apSourceSE[MAX_SE];		// �\�[�XSE
	static IXAudio2SourceVoice *m_pSoureceVOICE;			// �\�[�XVOICE
};

#endif