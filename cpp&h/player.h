// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// モデル処理 [player.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character_balloon.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PLAYER_FRONTFORCE		(10)
#define PLAYER_G				(0.5f)								// 重力
#define PLAYER_RESISTANCE		(0.5f)								// 抵抗力
#define PLAYER_MOTIONFILE		"data/LOAD/PLAYER/Tricker.txt"		// モーションのファイル名
#define PLAYER_FALL				(-20.0f)							// 落ちる位置条件
#define PLAYER_UI_MP_POS		(D3DXVECTOR3(78.5f, 690.0f, 0.0f))	// UI_MPの位置
#define PLAYER_MPMAX			(10000)								// MPの最大値
#define FISH_APPONENTPOS		(-40.0f)								// 魚出現位置
#define FISH_APPONENTTIME		(300)								// 魚出現タイム
#define MPUP_EVERY				(1)									// マイフレームMPUP
#define MPUP_BREAKBALLOON		(100)								// 風船を割った時のMPUP
#define MPUP_ENEMY_KNOCKDOWN	(1000)								// 敵を倒したときのMPUP
#define MPUP_PLAYER_KNOCKDOWN	(1000)								// プレイヤーを倒したときのMPUP
#define SPEED_UP_MPDOWN			(100)								// プレイヤー(スピードアップ)のMP消費量
#define REVIVAL_MPDOWN			(1000)								// プレイヤー(復活)のMP消費量
#define INVISIBLE_MPDOWN		(10)								// プレイヤー(透明)のMP消費量
#define SCORE_UP_MPDOWN			(100)								// プレイヤー(スコアアップ)のMP消費量

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 前方宣言
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class C2DGauge;		// 2Dゲージクラス
class CRank;		// ランククラス
class CFramework;	// フレームワーククラス
class CMeshdome;	// メッシュドームクラス

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// クラス
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CPlayer : public CCharacter_Balloon
{
public:
	// ---------モーションタイプ---------- //
	typedef enum
	{
		MOTIONTYPE_JAMP = CCharacter::MOTIONTYPE_MAX,
		MOTIONTYPE_DANCE,
		MOTIONTYPE_MAX
	} MOTIONTYPE;
	// ---------キャラクタータイプ---------- //
	typedef enum
	{
		CHARATYPE_SPEED_UP = 0,
		CHARATYPE_REVIVAL,
		CHARATYPE_INVISIBLE,
		CHARATYPE_SCORE_UP,
		CHARATYPE_MAX
	} CHARATYPE;
	/* 関数 */
	CPlayer(CCharacter::CHARACTER const &character);
	virtual ~CPlayer();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	// プレイヤーが死んだときの関数
	virtual void Die(void);
	void OtherDie(void);
	// 当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	);
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	);
	// プレイヤー番号の設定
	void SetPlayerID(int const &nPlayerID) { m_nPlayerID = nPlayerID; };
	// プレイヤー番号の取得
	int const &GetPlayerID(void) { return m_nPlayerID; };
	// MPのフラグ取得
	void SetMPMax(const bool bValue) { m_bMPMax = bValue; }
	bool const &GetMPMax(void) { return m_bMPMax; }
	// 移動量の設定
	void const SetMoveNow(float fMoveNow) { m_fMoveNow = fMoveNow; }
	static bool GetDie(int nId) { return m_bDie[nId]; }
	void Camera(void);					// カメラ処理
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	static HRESULT Load(void);			// 読み込み
	static void UnLoad(void);			// UnLoadする
	// MP上げ処理
	//	nMpUp	: MP上げ値
	void MpUp(int const & nMpUp);

protected:
private:
	/* 構造体 */
	/* 関数 */
	void MyMove(void);					// 自キャラ移動処理
	void MyAction(const int &nId);		// 自キャラ行動処理
	void OtherMove(void);				// 他キャラ移動処理
	void OtherAction(void);				// 他キャラ行動処理
	void FishApponent(void);			// 魚が出現
	// 状態によってのモーション設定処理
	void StatusMotion(void);
	/* 変数 */
	static int	m_All;					// 総数
	static CMeshdome *m_pMeshDome;				// 移動上限警告用
	CRank		*m_pRank;				// 現在順位表示
	C2DGauge	*m_p2DMPGauge;			// MPゲージ
	D3DXVECTOR3	m_posold;				// 前の位置
	int m_nPlayerID;					// 番号
	int m_nRank;						// 今の順位
	int m_nCntFishApponent;				// 魚出現カウント
	int m_nMP;							// MP
	int m_nCloudCount;					// 雲が出現するまでのカウンタ
	bool m_bMPMax;						// MPが最大かどうか
	bool m_bResetMP;					// MPをリセット
	static bool m_bDie[MAX_PLAYER];		// 死亡フラグ
	float m_fMoveNow;					// 現在の移動量
	CFramework * m_pFramework;			// フレームワーク情報
};
#endif