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
	m_pCloudBack = NULL;
	m_fScroll = 0.0f;
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
	// タイトル背景
	m_pCloudBack = CScene_TWO::Create(CScene_TWO::OFFSET_TYPE_CENTER, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
		0.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CScene::LAYER_WORLD
	);

	LPDIRECT3DTEXTURE9 pTex = NULL;

	// テクスチャー生成
	D3DXCreateTextureFromFile(
		CManager::GetRenderer()->GetDevice(),
		"data/TEXTURE/UI/TITLE/cloud.jpg",
		&pTex);

	if (m_pCloudBack != NULL)
	{
		m_pCloudBack->BindTexture(pTex);
	}

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
	CJoypad *pJoypad = CManager::GetJoy();

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		m_fScroll -= 0.0025f;

		if (m_pCloudBack != NULL)
		{
			m_pCloudBack->SetTex(D3DXVECTOR2(0.0f, 0.0f + m_fScroll), D3DXVECTOR2(1.0f, 1.0f + m_fScroll));
		}

		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			// チュートリアルへ
			pFade->SetFade(CManager::MODE_TUTORIAL);
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
				pFade->SetFade(CManager::MODE_TUTORIAL);
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