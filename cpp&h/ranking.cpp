//=============================================================================
//
// ランキングの処理 [ranking.cpp]
// Author : Ryouma Inoue
//
//=============================================================================
#include "ranking.h"			// インクルードファイル
#include "fade.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "manager.h"

//=============================================================================
//
// コンストラクタ
//
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
//
// デストラクタ
//
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
//
// 初期化処理
//
//=============================================================================
HRESULT CRanking::Init()
{

	// 初期化
	return S_OK;
}

//=============================================================================
//
// 終了処理
//
//=============================================================================
void CRanking::Uninit(void)
{
	// 全ての開放
	CScene::ReleaseAll();
}

//=============================================================================
//
// 更新処理
//
//=============================================================================
void CRanking::Update(void)
{
	CFade *pFade = CManager::GetFade();

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RETURN))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// タイトルへ
				pFade->SetFade(CManager::MODE_TITLE);
			}
		}
	}
}

//=============================================================================
//
// 描画処理
//
//=============================================================================
void CRanking::Draw(void)
{

}

//=============================================================================
//
// タイトルの生成
//
//=============================================================================
CRanking * CRanking::Create(void)
{
	// 変数
	CRanking *pRanking;

	// メモリの確保
	pRanking = new CRanking;

	// 初期化
	pRanking->Init();

	return pRanking;
}