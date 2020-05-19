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
		LABEL_BGM_TITLE = 0,	// タイトル
		LABEL_BGM_GAME,			// ゲーム
		LABEL_BGM_RANKINGMOVE,	// ランキング
		LABEL_SE_ENTER,			// 決定音
		LABEL_SE_SWORDSLASH1,	// 攻撃が当たった時の音
		LABEL_SE_SWORD,			// 剣を振りかざし
		LABEL_SE_TRICKBEFORE,	// 秘奥義発動直前
		LABEL_SE_BOMB,			// 爆発音
		LABEL_SE_CURSOL,		// カーソル音
		LABEL_SE_SWITCH,		// 文字表示時の音
		LABEL_SE_CLEAR,			// クリア時
		LABEL_SE_WORNING,		// 警告音
		LABEL_VOICE_ATTCK,		// 攻撃
		LABEL_VOICE_SKILL_1,	// 技１
		LABEL_VOICE_SKILL_2,	// 技２
		LABEL_VOICE_TRICK1,		// 秘奥義１
		LABEL_VOICE_TRICK2,		// 秘奥義２
		LABEL_VOICE_DAMAGE,		// ダメージ
		LABEL_SE_MENU,			// メニューへ
		LABEL_SE_GAMEOVER,		// ゲームオーバー
		LABEL_SE_GAMESTART,		// ゲームスタート
		LABEL_VOICE_DIED,		// プレイヤーが戦闘不能時の声
		LABEL_VOICE_DIED2,		// プレイヤーが戦闘不能時の声2
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