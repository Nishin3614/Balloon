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
		LABEL_SE_BALLOONBREAK1 = 0,	// �o���[������������1
		LABEL_SE_BALLOONBREAK2,		// �o���[������������2
		LABEL_SE_BALLOONBREAK3,		// �o���[������������3
		LABEL_SE_KERSPLASH1,		// kersplash1
		LABEL_SE_KERSPLASH2,		// kersplash2
		LABEL_SE_KERSPLASH3,		// kersplash3
		LABEL_SE_KERSPLASH4,		// kersplash4
		LABEL_SE_LANDING1,			// ���n1
		LABEL_SE_LANDING2,			// ���n2
		LABEL_SE_POINTGET1,			// �|�C���g�Q�b�g1
		LABEL_SE_POINTGET2,			// �|�C���g�Q�b�g2
		LABEL_SE_POINTGET3,			// �|�C���g�Q�b�g3
		LABEL_SE_SELECTEDSOUND1,	// �I��1
		LABEL_SE_SELECTEDSOUND2,	// �I��2
		LABEL_SE_SELECTEDSOUND3,	// �I��3
		LABEL_SE_THUNDER1,			// ��1
		LABEL_SE_THUNDER2,			// ��2
		LABEL_SE_THUNDER3,			// ��3
		LABEL_SE_THUNDER4,			// ��4
		LABEL_SE_THUNDER5,			// ��5
		LABEL_SE_THUNDER6,			// ��6
		LABEL_SE_WIND1,				// ��1
		LABEL_SE_WIND2,				// ��2
		LABEL_BGM_TITLE,			// �^�C�g��
		LABEL_BGM_SELECTCHARACTER,	// �I���L�����N�^
		LABEL_BGM_GAME,				// �Q�[��
		LABEL_BGM_RESULT,			// ���U���g
		LABEL_MAX,					//
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
	static std::vector<std::string> m_vec_Filename;					// �t�@�C����
	static std::vector<int> m_vec_nLoop;							// ���[�v�J�E���g
	static std::vector<SOUND> m_vec_SoundType;					// �T�E���h�^�C�v
	static IXAudio2 *m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// �}�X�^�[�{�C�X
	static BYTE *m_apDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static IXAudio2SourceVoice *m_SourceBGM;				// �\�[�XBGM
	static IXAudio2SourceVoice *m_apSourceSE[MAX_SE];		// �\�[�XSE
	static IXAudio2SourceVoice *m_pSoureceVOICE;			// �\�[�XVOICE
};

#endif