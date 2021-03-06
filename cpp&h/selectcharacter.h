// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター選択処理 [selectcharacter.h]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SELECTCHARACTER_H_
#define _SELECTCHARACTER_H_

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CScene_TWO;			// シーン2D

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CSelectCharacter : public CScene
{
public:
	/* 列挙型 */
	// 状態
	/* 関数 */
	CSelectCharacter();
	~CSelectCharacter();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void) {};
#endif // _DEBUG
	// 当たった後の処理
	// 引数1:オブジェクトタイプ
	// 引数2:相手のシーン情報
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
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	// 生成
	static CSelectCharacter * Create(
		int const &nPlayerId,	// プレイヤーID
		D3DXVECTOR3 const &pos	// 位置
	);
	// 静的変数の初期化
	// (選択画面の初期化時に関数を呼ぶ)
	static void InitStatic(void);
	// プレイヤーが選んだキャラクタータイプを取得
	int GetCharacterType(void) { return m_CharacterType; }
	static int GetSaveCharaType(int const &nPlayerID) { return m_SaveCharaType[nPlayerID]; };
	void SetReady(bool bValue) { m_bReady = bValue; }
protected:
private:
	/* 関数 */
	/* 変数 */
	static int m_SaveCharaType[MAX_PLAYER];							// プレイヤーが選んだキャラクタータイプを保存
	CScene_TWO * m_pSelectCharatUi;									// 選択キャラクターUI
	CScene_TWO * m_pSelectUi;										// 選択UI
	CScene_TWO * m_pCheckUi;										// 確定UI
	CScene_TWO * m_pSelectIcon[CCharacter::CHARACTER_PLAYERMAX];	// キャラクター選択アイコン
	int m_CharacterType;											// キャラクタータイプ
	int m_PlayerID;													// プレイヤー番号
	D3DXVECTOR3 m_pos;												// 位置
	bool m_bReady;													// 準備完了フラグ
};
#endif
