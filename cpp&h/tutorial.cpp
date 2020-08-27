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
#include "character_fish.h"
#include "speedUP.h"
#include "collision.h"
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
	CCharacter::InitStatic();
	/* 作成 */
	// 3Dエフェクトの生成
	C3DEffect::Create();
	// 球の設定
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		10000.0f);
	// 3Dマップ生成
	CLake::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(2500.0f, 2500.0f, 0.0f));
	C3DMap::LoadScript("data/LOAD/MAPPING/rand.csv");
	C3DMap::LoadCreate(C3DMap::MAP_STAGE_1);
	CScene_X::LoadScrept("data/LOAD/MAPPING/object.csv");
	CSpeedUP::Create(0, D3DVECTOR3_ZERO);
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
	// 当たり判定処理
	CCollision::CollisionDetection();

	CFade *pFade = CManager::GetFade();
	CJoypad *pJoypad = CManager::GetJoy();

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RETURN))
		{
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// チュートリアルへ
				pFade->SetFade(CManager::MODE_SELECT);
			}
		}

		if (pJoypad != NULL)
		{
			if (pJoypad->GetTrigger(0, CJoypad::KEY_START) || pJoypad->GetTrigger(0, CJoypad::KEY_A))
			{
				pFade->SetFade(CManager::MODE_SELECT);
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