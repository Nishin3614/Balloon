//=============================================================================
//
// チュートリアルの処理 [tutorial.cpp]
// Author : Ryouma Inoue
//
//=============================================================================
#include "tutorial.h"			// インクルードファイル
#include "fade.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "manager.h"
#include "network.h"
#include "ui.h"

//=============================================================================
//
// コンストラクタ
//
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
//
// デストラクタ
//
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
//
// 初期化処理
//
//=============================================================================
HRESULT CTutorial::Init()
{
	CUi::LoadCreate(CUi::UITYPE_TUTORIALUI);
	// 初期化
	return S_OK;
}

//=============================================================================
//
// 終了処理
//
//=============================================================================
void CTutorial::Uninit(void)
{
	// 全ての開放
	CScene::ReleaseAll();
}

//=============================================================================
//
// 更新処理
//
//=============================================================================
void CTutorial::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CJoypad *pJoypad = CManager::GetJoy();
	CNetwork *pNetwork = CManager::GetNetwork();

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RETURN))
		{
			if (pNetwork != NULL)
			{
				if (pNetwork->Connect() == S_OK)
				{

					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						// チュートリアルへ
						pFade->SetFade(CManager::MODE_SELECT);
					}
				}
			}
		}

		if (pJoypad != NULL)
		{
			if (pJoypad->GetTrigger(0, CJoypad::KEY_START) || pJoypad->GetTrigger(0, CJoypad::KEY_A))
			{
				if (pNetwork->Connect() == S_OK)
				{
					pFade->SetFade(CManager::MODE_TUTORIAL);
				}
			}
		}
	}
}

//=============================================================================
//
// 描画処理
//
//=============================================================================
void CTutorial::Draw(void)
{

}

//=============================================================================
//
// タイトルの生成
//
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	// 変数
	CTutorial *pTutorial;

	// メモリの確保
	pTutorial = new CTutorial;

	// 初期化
	pTutorial->Init();

	return pTutorial;
}