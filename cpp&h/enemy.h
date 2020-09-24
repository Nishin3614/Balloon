// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 敵処理 [enemy.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character_balloon.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 前方宣言
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// クラス
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CEnemy : public CCharacter_Balloon
{
public:
	/* 列挙型 */
	// AI行動
	typedef enum
	{
		AIACTION_STAND = 0,		// 立っている状態(他に何もしていない)
		AIACTION_JUMP,			// ジャンプしている状態
		AIACTION_BALLOON_NONE	// 出現している風船がすべて割られている状態
	} AIACTION;
	// 種類
	typedef enum
	{
		TYPE_MOVE = 0,	// 動いているタイプ
		TYPE_STOP,		// 止まっているタイプ
		TYPE_MAX		// タイプの最大数
	} TYPE;

	/* 構造体 */
	// ジャンプ変数
	typedef struct JUMP_VARIABLE
	{
		// コンストラクタ
		JUMP_VARIABLE()
		{
			nCoolTime = 0;	// クーリングタイム
		}
		int nCoolTime;	// クーリングタイム
	} JUMP_VARIABLE;
	/* 関数 */
	// コンストラクタ
	CEnemy(CHARACTER const &character);
	// デストラクタ
	virtual ~CEnemy();
	// 初期化処理
	virtual void Init(void);
	// 終了処理
	virtual void Uninit(void);
	// 更新処理
	virtual void Update(void);
	// 描画処理
	virtual void Draw(void);
#ifdef _DEBUG
	// デバッグ処理
	void Debug(void);
#endif // _DEBUG
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
	// 自分から当たらなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_NoMyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 敵が死んだときの関数
	virtual void Die(void);
	static HRESULT Load(void);								// 読み込み
	static void UnLoad(void);								// UnLoadする
	// 敵の総数取得
	static int &GetAllEnemy(int const &nType) { return m_nAllEnemy[nType]; };	// 敵の総数取得
protected:
	/* 列挙型 */
	/* 関数 */
	// タイプ設定
	void SetType(TYPE const &type) { m_Type = type; };
	/* 変数 */
	// 行動
private:
	/* 関数 */
	// AIアクション処理
	void Ai_Action(void);
	// AI行動_ジャンプ状態
	void AiAction_Jump(void);
	// 移動距離制限処理
	void MoveRestriction(void);
	/* 変数 */
	static int		m_nAllEnemy[TYPE_MAX];	// 敵の総数
	TYPE			m_Type;					// タイプ
	JUMP_VARIABLE	m_Jump;					// ジャンプ用変数
	AIACTION		m_AI;					// AI状態
};
#endif
