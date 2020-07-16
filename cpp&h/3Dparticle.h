// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3Dパーティクルの処理[particle.h]
// Author : Nishiyama koki
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _3DPARTICLE_H_
#define _3DPARTICLE_H_

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "Scene.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// マクロ定義
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// クラス定義
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class C3DParticle :public CScene
{
public:
	/* 列挙型 */
	// エフェクトタイプ
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_CHARGE,
		TYPE_MAX,
	} TYPE;
	// 初期設定
	typedef enum
	{
		OFFSET_ID_NONE = -1,
		OFFSET_ID_DIRT,				// 土煙
		OFFSET_ID_FIRE,				// 炎
		OFFSET_ID_TRICK1,			// 技①のエフェクト
		OFFSET_ID_AWAYSMOKE,		// 吹っ飛びけむり
		OFFSET_ID_EXPLOSIONSMOKE,	// 爆発けむり
		OFFSET_ID_SHOCKWAVE,		// 衝撃波
		OFFSET_ID_GET,				//
		OFFSET_ID_SPARKS,			// 火花
		OFFSET_ID_STAR,				// 星空
		OFFSET_ID_CROSSLINE,		// クロスライン
		OFFSET_ID_WEAVELINE,		// 編み物ライン
		OFFSET_ID_RANDAMLINE,		// ランダムライン
		OFFSET_ID_CENTERRANDAMLINE,	// 中心ランダムライン
		OFFSET_ID_ONELINE,			// 一つライン
		OFFSET_ID_CONCENTLINE,		// コネクトライン
		OFFSET_ID_MAX,
	} PARTICLE_OFFSET_ID;
	/* 構造体 */
	typedef struct PARTICLE_OFFSET
	{
		PARTICLE_OFFSET()
		{
			nFrame = 0;							// フレーム時間
			nNumber = 0;						// 出現個数
			nEffeTexType = 0;					// エフェクトのテクスチャの種類
			nEffeType = 0;						// エフェクトの種類
			type = TYPE_NORMAL;					// 種類(主に移動の)
			/* 位置情報 */
			Pos = D3DVECTOR3_ZERO;				// 位置のポインタ
			PosXRand = INTEGER2(0,0);			// 位置X座標ランダム用のポインタ
			PosYRand = INTEGER2(0, 0);			// 位置Y座標ランダム用のポインタ
			PosZRand = INTEGER2(0, 0);			// 位置Y座標ランダム用のポインタ
			/* カラー情報 */
			Col = D3DXCOLOR_INI;				// 色のポインタ
			bRedRand = false;					// 赤ランダム
			bGreenRand = false;					// 緑ランダム
			bBlueRand = false;					// 青ランダム
			bAlphaRand = false;					// 透明度ランダム
			/* サイズ情報 */
			Size = D3DVECTOR2_ZERO;				// サイズ
			SizeXRand = INTEGER2(0, 0);			// サイズxランダム用のポインター
			SizeYRand = INTEGER2(0, 0);			// サイズyランダム用のポインター
			/* 角度情報 */
			Rot = D3DVECTOR3_ZERO;				// 回転のポインター
			nAngleRand = INTEGER2(0, 0);		// 角度のランダム用のポインタ
			/* 速度情報 */
			fSpeed = 0.0f;						// 速度のポインタ
			nSpeedRand = INTEGER2(0, 0);		// 速度のランダム用のポインタ
			/* ライフ情報 */
			nLife = 0;							// ライフのポインタ
			nLifeRand = INTEGER2(0, 0);			// ライフのランダム用のポインタ
		}
		// 変数宣言
		int					nFrame;			// フレーム時間
		int					nNumber;		// 出現個数
		int					nEffeTexType;	// エフェクトのテクスチャの種類
		int					nEffeType;		// エフェクトの種類
		C3DParticle::TYPE	type;			// 種類(主に移動の)
		/* 位置情報 */
		D3DXVECTOR3			Pos;			// 位置のポインタ
		INTEGER2			PosXRand;		// 位置X座標ランダム用のポインタ
		INTEGER2			PosYRand;		// 位置Y座標ランダム用のポインタ
		INTEGER2			PosZRand;		// 位置Y座標ランダム用のポインタ
		/* カラー情報 */
		D3DXCOLOR			Col;			// 色のポインタ
		bool				bRedRand;		// 赤ランダム
		bool				bGreenRand;		// 緑ランダム
		bool				bBlueRand;		// 青ランダム
		bool				bAlphaRand;		// 透明度ランダム
		/* サイズ情報 */
		D3DXVECTOR2			Size;			// サイズ
		INTEGER2			SizeXRand;		// サイズxランダム用のポインター
		INTEGER2			SizeYRand;		// サイズyランダム用のポインター
		/* 角度情報 */
		D3DXVECTOR3			Rot;			// 回転のポインター
		INTEGER2			nAngleRand;		// 角度のランダム用のポインタ
		/* 速度情報 */
		float				fSpeed;			// 速度のポインタ
		INTEGER2			nSpeedRand;		// 速度のランダム用のポインタ
		/* ライフ情報 */
		int					nLife;			// ライフのポインタ
		INTEGER2			nLifeRand;		// ライフのランダム用のポインタ
	} PARTICLE_OFFSET;

	/* 関数 */
	C3DParticle();
	~C3DParticle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return NULL; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	static C3DParticle * Create(PARTICLE_OFFSET_ID OffsetID, CONST D3DXVECTOR3 origin);
	static HRESULT Load(void);
	static void Unload(void);
	void SetParticle(PARTICLE_OFFSET_ID OffsetID);
	void SetOrigin(CONST D3DXVECTOR3 &Origin);

private:
	/* 関数 */
	/* 変数 */
	static PARTICLE_OFFSET	m_ParticleOffset[OFFSET_ID_MAX];	// パーティクルのオフセット
	PARTICLE_OFFSET_ID		m_offsetID;							// オフセットID
	int						m_nFlameCount;						// フレームのカウント
	D3DXVECTOR3				m_Origin;							// 原点
};

#endif
