// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター処理 [character.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "model.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 前方宣言
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CExtrusion;
class CMeshobit;
class CCollision;
class CStencilshadow;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 構造体
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// クラス
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCharacter : public CScene
{
public:
	/* 列挙型 */
	// ステータス
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DIE,
		STATE_MAX
	} STATE;
	// 基本モーションタイプ
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,		// 待機モーション
		MOTIONTYPE_MAX
	} MOTIONTYPE;
	// キャラクター
	typedef enum
	{
		// バルーンプレイヤー用 //
		CHARACTER_BALLOON1 = 0,					// バルーン1
		CHARACTER_BALLOON2,						// バルーン2
		CHARACTER_BALLOON3,						// バルーン3
		CHARACTER_BALLOON4,						// バルーン4
		CHARACTER_PLAYERMAX,					// プレイヤー用のキャラクター最大数
		// バルーン敵用 //
		CHARACTER_NPC = CHARACTER_PLAYERMAX,	// NPC
		// 妨害キャラクター用 //
		CHARACTER_FISH,	// 妨害キャラクター(魚)
		CHARACTER_MAX,							// キャラクター全体数
	} CHARACTER;

	// バルーン敵用キャラクター最大数
#define CHARACTER_ENEMYMAX (1)		// バルーン敵用キャラクター最大数
	// 妨害用キャラクター最大数
#define CHARACTER_DISTURBANCEMAX (1)	// 敵用キャラクター最大数

	/* 構造体 */
	// ステータス情報
	typedef struct STATUS
	{
		/* 関数 */
		// 初期化
		STATUS()
		{
			nMaxBalloon = 0;			// 最大風船数
			nMaxPopBalloon = 0;			// 最大出現風船数
			fMaxInertia = 0;			// 慣性力
			fMaxJump = 0;				// ジャンプ力
			fMaxMove = 0;				// 移動力
			nMaxMp = 0;					// 最大MP数
			nMaxMpUp_Every = 0;			// マイフレームで増えるMP数
			nMaxMpUp_KnockDown = 0;		// 倒したときのMP数
			nMaxMpDown = 0;				// スキル使用時の減る量
			fMaxSkill = 0;				// 能力の倍率
		}
		/* 変数 */
		int			nMaxBalloon;		// 最大風船数
		int			nMaxPopBalloon;		// 最大出現風船数
		float		fMaxInertia;		// 慣性力
		float		fMaxJump;			// ジャンプ力
		float		fMaxMove;			// 移動力
		int			nMaxMp;				// 最大MP数
		int			nMaxMpUp_Every;		// マイフレームで増えるMP数
		int			nMaxMpUp_KnockDown;	// 倒したときのMP数
		int			nMaxMpDown;			// スキル使用時の減る量
		float		fMaxSkill;			// 能力の倍率
		// ポイントゾーン ポイント加算(100)
		// スコアをとった時のゲージの上昇率
		// ポイントの倍率
	} STATUS, *PSTATUS;
	/* 関数 */
	CCharacter(CHARACTER const &character);
	virtual ~CCharacter();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	// キャラクターが死んだとき
	virtual void Die(void);
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
	) = 0;
	// 相手に当てられなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) = 0;
	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return &m_posold; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return &m_move; };
	// 必要に応じた動作 //
	// 重力
	void AddGravity(float const &fGravity)					{ m_move.y -= fGravity; };
	// 設定 //
	// 位置
	void SetPos(D3DXVECTOR3 const &pos)						{ m_pos = pos; };
	// 移動量
	void SetMove(D3DXVECTOR3 const &move)					{ m_move = move; };
	// 回転
	void SetRot(D3DXVECTOR3 const &rot)						{ m_rot = rot; };
	// 着地状態設定
	void SetbLanding(bool const &bLanding)					{ m_bLanding = bLanding; };
	// 移動状態設定
	void SetbMove(bool const &bMove)						{ m_bMove = bMove; };
	// 方向ベクトル設定
	void SetDirectionVec(D3DXVECTOR3 const &direct)			{ m_Directvector = direct; };
	// 取得 //
	// 位置
	D3DXVECTOR3 &GetPos(void)								{ return m_pos; };
	// 移動量
	D3DXVECTOR3 &GetMove(void)								{ return m_move; };
	// 回転
	D3DXVECTOR3 &GetRot(void)								{ return m_rot; };
	// 親と子の回転量
	D3DXVECTOR3 *GetPartsRot(int const nModelID);
	// 親と子の位置
	D3DXVECTOR3 * GetPartsPos(int const nModelID);
	// 親と子の行列
	D3DXMATRIX *GetMatrix(int const nModelID);
	// 状態
	STATE GetState(void) const								{ return m_State; };
	// キャラクター
	CHARACTER	GetCharacter(void) const					{ return m_character; };
	// ステータス(キャラクターのクラスを基底クラスに持っているクラス)
	STATUS &GetStatus(void) { return m_sStatus[m_character]; };
	// ステータス(キャラクター別)
	// 引数:キャラクター番号
	static STATUS &GetStatus(CHARACTER const &character)	{ return m_sStatus[character]; };
	// 着地状態取得
	bool GetbLanding(void)									{ return m_bLanding; };
	// 移動状態取得
	bool GetbMove(void)										{ return m_bMove; };
	// 前方方向ベクトル取得
	D3DXVECTOR3 GetDirectionVec(void)						{ return m_Directvector; };
	// 床の高さ
	bool GetFloorHeight(void);
	// モーションのフレーム情報取得処理
	int GetMaxFrame(
		CHARACTER character,					// キャラクター
		int nMotionID,							// モーションID
		int nNowKeyCnt = -1						// 現在のキーカウント
	);
	// カメラ追尾しているID
	static int GetCameraCharacter(void);
	// キャラクター全ソースの読み込み
	static HRESULT Load(void);
	// キャラクターの情報読み込み
	static HRESULT Load_Character(void);
	// ステータス情報読み込み
	static HRESULT LoadStatus(void);
	// キャラクター全ソースの開放
	static void UnLoad(void);
	// キャラクターの静的変数の初期化
	static void InitStatic(void);
	// 目標回転量設定
	void SetRotDest(D3DXVECTOR3 const &rotDest) { m_rotLast = rotDest; };
	// 目標回転量取得
	D3DXVECTOR3 GetRotDest(void) const { return m_rotLast; };
#ifdef _DEBUG
	virtual void  Debug(void);
	static void AllDebug(void);
#endif // _DEBUG
	CCollision * GetCollision(void) { return m_pCharacterCollision; };
protected:
	/* 関数 */
	// 設定 //
	// キャラクター
	void SetCharacter(CHARACTER const character)	{ m_character = character; };
	// モーション設定
	void SetMotion(int const nMotiontype);
	// 強制モーション設定
	void ComplusionSetMotion(int const nMotiontype);
	// 重力
	void FagGravity(void);						// 重力
	// 透明度の設定
	static void SetAlpha(float fAlpha) { m_fAlpha = fAlpha; }
	// 設定 //
	// 現在のモーション
	int GetMotion(void) const						{ return m_nMotiontype; };
	// 過去のモーション
	int GetOldMotion(void) const					{ return m_nMotiontypeOld; };
	// キーカウント
	int GetKeyInfoCnt(void) const					{ return m_keyinfoCnt; };
	// モーションカメラの更新
	void MotionCamera(void);
	/* 変数 */
	static int						m_nCameraCharacter;		// キャラクターに追尾するID
	static STATUS					m_sStatus[CHARACTER_MAX];		// キャラクターすべてのスタータス情報
	D3DXVECTOR3						m_pos;					// 位置
	D3DXVECTOR3						m_move;					// 移動量
	D3DXVECTOR3						m_rot;					// 現在回転量

	// 仮
	STATE							m_State;				// 現状のステータス
	int								m_nCntState;			// カウントステータス



	/* プロトタイプ用 */
	void Limit(void);										// 制限区域
private:
	/* 関数 */
	void Collision(void);									// それぞれの当たり判定
	void Update_Normal(void);								// 通常時の更新
	void NextKeyMotion(void);								// 次のモーション
	void Move(void);										// 移動
	void Motion(void);										// モーション
	void ModelUpdate(void);									// モデルの更新
	void TrackCamera(void);									// カメラ追尾
	void Motion_Effect(void);								// モーションエフェクト
	void Motion_Obit(void);									// モーション軌跡
	static void Status_Reset(void);								// ステータスリセット
	/* 変数 */
	/* 構造体のスタティックにする */
	static MODEL_ALL				*m_modelAll[CHARACTER_MAX];				// モデル全体の情報
	static std::vector<int>				m_modelId[CHARACTER_MAX];			// モデル番号
	static CModel_info				*m_model_info[CHARACTER_MAX];			// モデル情報
	static D3DXVECTOR3				m_CharacterSize[CHARACTER_MAX];			// キャラクターのサイズ
	static int						m_NumModel[CHARACTER_MAX];				// 最大モデル数
	static int						m_NumParts[CHARACTER_MAX];				// 動かすモデル数
	static int						m_nAllCharacter;						// 出現しているキャラクター人数
	static float					m_fAlpha;								// アルファ値
	CMeshobit						*m_pMeshobit;							// 軌跡
	CModel 							*m_pModel;								// モデル
	CHARACTER						m_character;							// キャラクター
	D3DXMATRIX						m_mtxWorld;								// 行列
	D3DXVECTOR3						m_posold;								// 前の位置
	D3DXVECTOR3						m_rotLast;								// 向きたい方向
	D3DXVECTOR3						m_rotbetween;							// 回転の差分
	D3DXVECTOR3						m_size;									// キャラクターのサイズ
	int								m_nMotiontype;							// モーションタイプ
	int								m_nMotiontypeOld;						// 前回のモーションタイプ
	int								m_nMaxMotion;							// 最大モーション数
	int								m_keyinfoCnt;							// キー情報のカウント
	int								m_nFrame;								// フレームカウント
	int								m_nMotionFrame;							// 一つのモーションのカウント
	int								m_nIdAttackKey;							// 攻撃用のキーID
	int								m_nCntDamage;							// ダメージカウント
	float							m_fLength;								// 攻撃の当たり範囲
	bool							m_bMotionCamera;						// モーションカメラの切り替えON・OFF
	bool							m_bLanding;								// 着地状態
	bool							m_bMove;								// 移動状態
	D3DXVECTOR3						m_Directvector;							// 方向のベクトル
	CCollision						*m_pCharacterCollision;					// キャラクターの当たり判定
	std::vector<std::unique_ptr<CCollision>>	m_vec_AttackCollision;		// 攻撃当たり判定
	std::vector<std::unique_ptr<CMeshobit>>	m_vec_pMeshObit;				// 奇跡
	CStencilshadow					* m_pStencilshadow;						// ステンシルシャドウ
};

#endif