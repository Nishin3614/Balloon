//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : Ryouma Inoue
//
//=============================================================================
#include "title.h"			// インクルードファイル
#include "fade.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "manager.h"
#include "ui.h"
#include "network.h"

//=============================================================================
//
// コンストラクタ
//
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//
// デストラクタ
//
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//
// 初期化処理
//
//=============================================================================
HRESULT CTitle::Init()
{
	// UI生成
	CUi::LoadCreate(CUi::UITYPE_TITLEUI_NAME);
	// 初期化
	return S_OK;
}

//=============================================================================
//
// 終了処理
//
//=============================================================================
void CTitle::Uninit(void)
{
	// 全ての開放
	CScene::ReleaseAll();
}

//=============================================================================
//
// 更新処理
//
//=============================================================================
void CTitle::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CNetwork *pNetwork = CManager::GetNetwork();
	CJoypad *pJoypad = CManager::GetJoy();

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			if (pNetwork != NULL)
			{
				if (pNetwork->Connect() == S_OK)
				{
					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						// チュートリアルへ
						pFade->SetFade(CManager::MODE_TUTORIAL);
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
void CTitle::Draw(void)
{

}

//=============================================================================
//
// タイトルの生成
//
//=============================================================================
CTitle * CTitle::Create(void)
{
	// 変数
	CTitle *pTitle;

	// メモリの確保
	pTitle = new CTitle;

	// 初期化
	pTitle->Init();

	return pTitle;
}