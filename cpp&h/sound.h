// ----------------------------------------
//
// サウンド処理の説明[sound.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "main.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define MAX_SE (10)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CSound
{
public:
	/* 列挙型 */
	// 音タイプ
	typedef enum
	{
		SOUND_BGM= 0,	// BGM
		SOUND_SE,		// SE
		SOUND_VOICE,	// VOICE
		SOUND_MAX,
	} SOUND;
	// ラベル
	typedef enum
	{
		LABEL_SE_BALLOONBREAK1 = 0,
		LABEL_SE_BALLOONBREAK2,
		LABEL_SE_BALLOONBREAK3,
		LABEL_SE_KERSPLASH1,
		LABEL_SE_KERSPLASH2,
		LABEL_SE_KERSPLASH3,
		LABEL_SE_KERSPLASH4,
		LABEL_SE_LANDING1,
		LABEL_SE_LANDING2,
		LABEL_SE_POINTGET1,
		LABEL_SE_POINTGET2,
		LABEL_SE_POINTGET3,
		LABEL_SE_SELECTEDSOUND1,
		LABEL_SE_SELECTEDSOUND2,
		LABEL_SE_SELECTEDSOUND3,
		LABEL_SE_THUNDER1,
		LABEL_SE_THUNDER2,
		LABEL_SE_THUNDER3,
		LABEL_SE_THUNDER4,
		LABEL_SE_THUNDER5,
		LABEL_SE_THUNDER6,
		LABEL_SE_WIND1,
		LABEL_SE_WIND2,
		LABEL_MAX,
	} LABEL;
	/* 関数 */
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(
		LABEL const &label		// ラベル
	);
	void StopSound(LABEL label);
	void StopCompusionSound(LABEL label);
	void StopSound(void);
	// スクリプト情報を読み込む
	static HRESULT Load(void);
protected:

private:
	/* 関数 */
	HRESULT AudioCreate(HWND hWnd);
	HRESULT SoundCreate(HWND hWnd);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	/* 変数 */
	static vector<string> m_vec_Filename;					// ファイル名
	static vector<int> m_vec_nLoop;							// ループカウント
	static vector<SOUND> m_vec_SoundType;					// サウンドタイプ
	static IXAudio2 *m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// マスターボイス
	static BYTE *m_apDataAudio[LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[LABEL_MAX];					// オーディオデータサイズ
	static IXAudio2SourceVoice *m_SourceBGM;				// ソースBGM
	static IXAudio2SourceVoice *m_apSourceSE[MAX_SE];		// ソースSE
	static IXAudio2SourceVoice *m_pSoureceVOICE;			// ソースVOICE
};

#endif