//=============================================================================
//
// スコア[score.h]
// Author:Ryouma Inoue
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

#define MAX_SCORE (8)

#define SCORE_POS_X (100.0f)			 // Xの位置
#define SCORE_POS_Y (100.0f)			 // Yの位置
#define SCORE_SIZE_X (33.0f)			 // Xのサイズ
#define SCORE_SIZE_Y (50.0f)			 // Yのサイズ
#define SCORE_INTERVAL_X (33)			 // 横の感覚
#define SCORE_INTERVAL (10.0f)			 // 

class CNumber;
//=============================================================================
//
// クラスの定義
//
//=============================================================================
class CScore : public CScene
{
public:

	CScore();					// コンストラクタ
	~CScore();					// デストラクタ

	void Init(void);			// 初期化
	void Uninit(void);			// 終了
	void Update(void);			// 更新
	void Draw(void);			// 描画
	void SetPos(D3DXVECTOR3 pos);
	void AddScore(int nValue);
	void SetScore(int nScore);

	static int GetNowScore(void);
	static CScore *GetScore(void);
	static CScore *Create(void);

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;
	static CScore *m_pScore;
	static int	m_nScore;				// スコア

	CNumber *m_apNumber[MAX_SCORE];
	D3DXVECTOR3 m_pos;
	int	m_nRanking;

};
#endif