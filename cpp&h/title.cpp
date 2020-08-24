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
#include "2Deffect.h"
#include "3Dparticle.h"
#include "framework.h"

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
	// 2Dエフェクトの生成
	C2DEffect::Create();
	// 3Dパーティクル生成
	C3DParticle::Create(
		C3DParticle::PARTICLE_ID_BALLOON,
		//D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DVECTOR3_ZERO,
		true);

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
					// チュートリアルへ
					pFade->SetFade(CManager::MODE_TUTORIAL);
				}
			}
		}
#ifdef _DEBUG
		// リザルト画面遷移
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_9))
		{
			pFade->SetFade(CManager::MODE_RESULT);
		}
#endif // _DEBUG
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