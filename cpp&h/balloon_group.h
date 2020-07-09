// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 風船グループ処理の説明[balloon_group.h]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _BALLOON_GROUP_H_
#define _BALLOON_GROUP_H_	 // ファイル名を基準を決める

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "balloon.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CBalloon_group : public CScene
{
public:
	/* 関数 */
	CBalloon_group();
	~CBalloon_group();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 当たった後の処理
	// 引数1:オブジェクトタイプ
	// 引数2:相手のシーン情報
	virtual void Scene_Collision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	){};
	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return NULL; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	// 行列情報設定
	void SetMatrix(D3DXMATRIX * mtx);			// 行列情報設定
	// 風船グループの初期個数を代入
	void SetBiginBalloon_group(int const &nBringBalloon_group) { m_nBringBalloon_group = nBringBalloon_group; };
	// 風船グループを持てる個数を変化させる(上昇・現状)
	void SetBringBalloon_group(int const &nBringBalloon_group) { m_nBringBalloon_group += nBringBalloon_group; };
	// 出現している風船グループの個数を変化させる(上昇・減少)
	void SetPopBalloon_group(int const &nPopBalloon_group = 1) { m_nPopBalloon_group += nPopBalloon_group; };
	// 外に出して置ける風船グループの最大個数を設定
	void SetPopMaxBalloom(
		int const &nPopMaxBaloon = 2,
		CScene * pParent = NULL
	);
	// 風船グループを生成
	void CreateBalloon_group(CScene * pParent);
	// 風船情報取得
	CBalloon * GetBalloon(int const &nBalloon_group);	// 風船の情報取得
	// 風船グループを持っている個数を取得
	int const &GetBringBalloon_group(void) { return m_nBringBalloon_group; };
	// 風船グループを出現している個数を取得
	int const &GetPopBalloon_group(void) { return m_nPopBalloon_group; };
	// 現在の風船グループの最大出現数の取得
	int const &GetPopMaxBalloon_group(void) { return m_nMaxPopBalloon_group; };
	// 生成
	static CBalloon_group * Create(
		D3DXMATRIX *mtx,							// 行列
		int const &nPopMaxBalloon_group,					// 風船グループの最大出現数
		CScene * pParent							// 親情報
	);
	// リソース情報読み込む設定
	static HRESULT Load(void);					// リソース情報読み込む設定
	// 読み込んだリソース情報を開放する
	static void UnLoad(void);					// 読み込んだリソース情報を開放する
protected:
private:
	/* 関数 */
	void BreakBalloon_group(int const &nCntBalloon_group);	// 風船グループが割れる処理
	/* 変数 */
	std::vector<CBalloon *> m_apBalloon;				// 風船モデル情報
	D3DXMATRIX *m_mtx;							// 行列情報
	int m_nPopBalloon_group;							// 現在出現している風船グループの個数
	int m_nBringBalloon_group;						// 現在持っている風船グループの個数
	int m_nMaxPopBalloon_group;						// 最大出現数の個数
	float m_fAngleBalloon_group;						// 風船グループの出現する角度(円周率 * 2 / 最大出現数)
};

#endif