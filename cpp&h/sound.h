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
		LABEL_SE_BALLOONBREAK1 = 0,	// バルーンを割った音1
		LABEL_SE_BALLOONBREAK2,		// バルーンを割った音2
		LABEL_SE_BALLOONBREAK3,		// バルーンを割った音3
		LABEL_SE_KERSPLASH1,		// kersplash1
		LABEL_SE_KERSPLASH2,		// kersplash2
		LABEL_SE_KERSPLASH3,		// kersplash3
		LABEL_SE_KERSPLASH4,		// kersplash4
		LABEL_SE_LANDING1,			// 着地1
		LABEL_SE_LANDING2,			// 着地2
		LABEL_SE_POINTGET1,			// ポイントゲット1
		LABEL_SE_POINTGET2,			// ポイントゲット2
		LABEL_SE_POINTGET3,			// ポイントゲット3
		LABEL_SE_SELECTEDSOUND1,	// 選択1
		LABEL_SE_SELECTEDSOUND2,	// 選択2
		LABEL_SE_SELECTEDSOUND3,	// 選択3
		LABEL_SE_THUNDER1,			// 雷1
		LABEL_SE_THUNDER2,			// 雷2
		LABEL_SE_THUNDER3,			// 雷3
		LABEL_SE_THUNDER4,			// 雷4
		LABEL_SE_THUNDER5,			// 雷5
		LABEL_SE_THUNDER6,			// 雷6
		LABEL_SE_WIND1,				// 風1
		LABEL_SE_WIND2,				// 風2
		LABEL_BGM_TITLE,			// タイトル
		LABEL_BGM_SELECTCHARACTER,	// 選択キャラクタ
		LABEL_BGM_GAME,				// ゲーム
		LABEL_BGM_RESULT,			// リザルト
		LABEL_MAX,					//
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
	static std::vector<std::string> m_vec_Filename;					// ファイル名
	static std::vector<int> m_vec_nLoop;							// ループカウント
	static std::vector<SOUND> m_vec_SoundType;					// サウンドタイプ
	static IXAudio2 *m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// マスターボイス
	static BYTE *m_apDataAudio[LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[LABEL_MAX];					// オーディオデータサイズ
	static IXAudio2SourceVoice *m_SourceBGM;				// ソースBGM
	static IXAudio2SourceVoice *m_apSourceSE[MAX_SE];		// ソースSE
	static IXAudio2SourceVoice *m_pSoureceVOICE;			// ソースVOICE
};

#endif