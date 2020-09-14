// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// エフェクトの処理[effect.h]
// Author : Nishiyama koki
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// マクロ定義
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define EFFECT_MAX			(5000)				// 最大数
#define EFFECT_NUM_VERTEX	(4)					// 頂点数
#define BASEANGLE			(D3DX_PI * 0.25f)	// ベース角度

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 前方宣言
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CRenderer;	// レンダラークラス

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// クラス定義
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CEffect :public CScene
{
public:
	/* 列挙型 */
	// エフェクトタイプ
	typedef enum
	{
		EFFECT_TYPE_NONE = -1,		// なし
		EFFECT_TYPE_EXPLOSION,		// 爆発
		EFFECT_TYPE_SPARK,			// 火花
		EFFECT_TYPE_SMOKE,			// 煙
		EFFECT_TYPE_LINE,			// 線
		EFFECT_TYPE_BALLOON,		// 風船
		EFFECT_TYPE_SHOCK,			// 衝撃
		EFFECT_TYPE_BONFIRE_SPARK,	// 焚火
		EFFECT_TYPE_MAX				// 最大数
	} EFFECT_TYPE;

	/* 構造体 */
	// エフェクトプリミティブ
	typedef struct
	{
		D3DXVECTOR3			pos;				// 位置
		D3DXVECTOR3			rot;				// 回転量
		D3DXVECTOR3			move;				// 移動量
		D3DXCOLOR			col;				// 色
		D3DXVECTOR2			size;				// サイズ
		D3DXVECTOR2			sizeValue;			// サイズの変化値
		float				fAngle;				// 角度
		float				fAlphaValue;		// アルファ値の変化値
		int					nLife;				// 持ち時間
		int					nTexType;			// テクスチャの種類
		int					nCntAnim;			// アニメカウント
		int					nMaxCntAnim;			// 最大アニメカウント
		int					nHorizonAnim;		// 水平のアニメーションパターン
		int					nVirticalAnim;		// 垂直のアニメーションパターン
		int					nMaxHorizonAnim;	// 最大水平アニメーションパターン数
		int					nMaxVirticalAnim;	// 最大垂直のアニメーションパターン数
		bool				bUse;				// 使用しているかどうか
		EFFECT_TYPE			EffectType;			// エフェクトの種類
		CRenderer::BLEND	BlendType;			// ブレンドタイプ
	} EFFECT;

	/* 関数 */
	// コンストラクタ
	CEffect();
	// デストラクタ
	virtual ~CEffect();
	// 全リソース情報の読み込み処理
	static HRESULT Load(void);
	// 全リソース情報の開放
	static void Unload(void);
	// 初期化処理
	virtual void Init(void);
	// 終了処理
	virtual void Uninit(void) = 0;
	// 更新処理
	virtual void Update(void) = 0;
	// 描画処理
	virtual void Draw(void) = 0;
#ifdef _DEBUG
	// デバッグ処理
	virtual void Debug(void);
#endif // _DEBUG
	// 自分から当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 自分から当たらなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_NoMyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられなかった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};


	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return NULL; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	// 値の初期化処理
	//	pEffect		: エフェクト情報
	void InitValues(
		EFFECT *pEffect	// エフェクト情報
	);
	// 値の初期化処理
	//	pEffect		: エフェクト情報
	//	nCntEffect	: エフェクトカウント
	static void Init_OneValues(
		EFFECT * pEffect		// エフェクト情報
	);

protected:
	/* 関数 */
	// ライフ更新処理
	//	pEffect	: エフェクト情報
	bool UpdateLife(
		EFFECT *pEffect		// エフェクト情報
	);
	// ライフ更新処理
	//	pVtx	: 2D頂点情報
	//	pEffect	: エフェクト情報
	bool UpdateVetex(
		EFFECT *pEffect		// エフェクト情報
	);
	// ライフ更新処理
	//	pVtx	: 2D頂点情報
	//	pEffect	: エフェクト情報
	void UpdateMove(
		EFFECT *pEffect		// エフェクト情報
	);
private:
};

#endif