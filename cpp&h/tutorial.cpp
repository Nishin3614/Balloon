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
#include "item.h"
#include "PointCircle.h"
#include "solider.h"
#include "network.h"
#include "ui.h"
#include "thunder.h"
#include "tutorial_explan.h"

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
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	CCharacter::InitStatic();

	CLake::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(25000.0f, 25000.0f, 0.0f));
	/* 作成 */
	C3DMap::LoadScript("data/LOAD/MAPPING/rand.txt");
	C3DMap::LoadCreate(C3DMap::MAP_STAGE_TUTORIAL);

	// 3Dエフェクトの生成
	C3DEffect::Create();
	// 球の設定
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		100000.0f);
	// 3Dマップ生成
	//CScene_X::LoadScrept("data/LOAD/MAPPING/object.csv");
	CSpeedUP::Create(0, D3DVECTOR3_ZERO,D3DXVECTOR3(0.0f,D3DX_PI,0.0f));
	CItem::Create(0, D3DXVECTOR3(600.0f, 50.0f, 200.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	CPointCircle::Create(D3DXVECTOR3(-200.0f, 0.0f, 200.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f));
	CThunder::Create(D3DXVECTOR3(-800.0f, 0.0f, 200.0f), D3DXVECTOR3(100.0f, 500.0f, 0.0f));
	CSolider::Create(D3DXVECTOR3(200.0f, 50.0f, 400.0f), D3DVECTOR3_ZERO, CEnemy::TYPE_MOVE);
	CSolider::Create(D3DXVECTOR3(200.0f, 50.0f, 200.0f), D3DVECTOR3_ZERO, CEnemy::TYPE_STOP);
	CUi::LoadCreate(CUi::UITYPE_TUTORIALUI);
	// チュートリアル説明文の生成処理
	Create_Tutorial_Explan();
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
	// 出現イベント処理
	PopEvent();
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
						// 選択画面へ
						pFade->SetFade(CManager::MODE_SELECT);
					}
				}
			}
		}

		if (pJoypad != NULL)
		{
			if (pJoypad->GetTrigger(0, CJoypad::KEY_START))
			{
				if (pNetwork->Connect() == S_OK)
				{
					// 選択画面へ
					pFade->SetFade(CManager::MODE_SELECT);
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

//=============================================================================
//
// 出現イベント処理
//
//=============================================================================
void CTutorial::PopEvent(void)
{
	if (CItem::GetAllItem() == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CItem::Create(0, D3DXVECTOR3(600.0f, 50.0f, 200.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
		}
		nCntPop++;
	}
	if (CPointCircle::GetAllPointCircle() == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CPointCircle::Create(D3DXVECTOR3(-200.0f, 50.0f, 200.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		}
		nCntPop++;
	}
	if (CThunder::GetAllThunder() == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CThunder::Create(D3DXVECTOR3(-800.0f, 0.0f, 200.0f), D3DXVECTOR3(100.0f, 500.0f, 0.0f));
		}
		nCntPop++;
	}
	if (CEnemy::GetAllEnemy(CEnemy::TYPE_MOVE) == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CSolider::Create(D3DXVECTOR3(200.0f, 50.0f, 400.0f), D3DVECTOR3_ZERO, CEnemy::TYPE_MOVE);
		}
		nCntPop++;
	}
	if (CEnemy::GetAllEnemy(CEnemy::TYPE_STOP) == 0)
	{
		if (nCntPop % 120 == 0)
		{
			CSolider::Create(D3DXVECTOR3(200.0f, 50.0f, 200.0f),D3DVECTOR3_ZERO, CEnemy::TYPE_STOP);
		}
		nCntPop++;
	}
	if (CSpeedUP::GetAll() == 0)
	{
		CSpeedUP::Create(0, D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	}
}

//=============================================================================
//
// チュートリアル説明文の生成処理
//
//=============================================================================
void CTutorial::Create_Tutorial_Explan(void)
{
	for (int nCntExplan = 0; nCntExplan < CTutorial_Explan::EXPLAN_MAX; nCntExplan++)
	{
		CTutorial_Explan::Create(nCntExplan);
	}
}
