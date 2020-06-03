// ----------------------------------------------------------------------------------------------------
//
// マネージャー処理の説明[manager.cpp]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------
/* My */
#include "manager.h"

/* 描画 */
#include "scene.h"
#include "game.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "ranking.h"
#include "network.h"

// ----------------------------------------------------------------------------------------------------
//
// マクロ関数
//
// ----------------------------------------------------------------------------------------------------
#define STARTMODE (MODE_GAME)

// ----------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------
CRenderer *CManager::m_renderer = NULL;					// レンダラー
CKeyboard * CManager::m_keyboard = NULL;				// キーボード
CJoypad * CManager::m_joypad = NULL;					// ジョイパッド
CMouse * CManager::m_mouse = NULL;						// マウス
CKeyConfig * CManager::m_keyconfig = NULL;				// キー詳細
CSound * CManager::m_sound = NULL;						// サウンド
CFade * CManager::m_fade = NULL;						// フェード
CTitle * CManager::m_title = NULL;						// タイトル
CTutorial * CManager::m_tutorial = NULL;				// チュートリアル
CGame * CManager::m_game = NULL;						// ゲーム
CResult * CManager::m_result = NULL;					// リザルト
CRanking * CManager::m_ranking = NULL;					// ランキング
CManager::MODE CManager::m_mode = CManager::MODE_GAME;	// モード
bool CManager::m_bWire = false;							// ワイヤー
CNetwork * CManager::m_pNetwork = NULL;					// ネットワーク

// ----------------------------------------------------------------------------------------------------
// コンストラクタ
// ----------------------------------------------------------------------------------------------------
CManager::CManager()
{
}

// ----------------------------------------------------------------------------------------------------
// デストラクタ
// ----------------------------------------------------------------------------------------------------
CManager::~CManager()
{
}

// ----------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------
HRESULT CManager::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	/* メモリの生成 */
	/* 入力デバイス */
	// キーボードの生成
	m_keyboard = new CKeyboard;
	// ジョイパッドの生成
	m_joypad = new CJoypad;
	// マウスの生成
	m_mouse = new CMouse;
	// キー詳細の生成
	m_keyconfig = new CKeyConfig;
	/* ゲームに欠かせないもの */
	// サウンドの生成
	m_sound = new CSound;
	// レンダリングの生成
	m_renderer = new CRenderer;
	// ネットワークの生成
	m_pNetwork = new CNetwork;
	/* 画面 */
	// タイトルの生成
	m_title = new CTitle;
	// チュートリアルの生成
	m_tutorial = new CTutorial;
	// ゲームの生成
	m_game = new CGame;
	// リザルトの生成
	m_result = new CResult;
	// リザルトの生成
	m_ranking = new CRanking;
	// モードの設定
	m_mode = STARTMODE;

	// ネットワークの設定データ読み込み
	CNetwork::LoadConfiguration();

	/* 初期化 */
	// キーボード
	if (!m_keyboard->Init(hInstance, hWnd) == S_OK)
	{
		m_keyboard->Uninit();
		delete m_keyboard;
		m_keyboard = NULL;
	}
	// ジョイパッド
	if (!m_joypad->Init(hInstance, hWnd) == S_OK)
	{
		m_joypad->Uninit();
		delete m_joypad;
		m_joypad = NULL;
	}
	// マウス
	if (!m_mouse->Init(hInstance, hWnd) == S_OK)
	{
		m_mouse->Uninit();
		delete m_mouse;
		m_mouse = NULL;
	}
	// キー詳細
	m_keyconfig->Init();
	// サウンド
	if (!m_sound->Init(hWnd) == S_OK)
	{
		m_sound->Uninit();
		delete m_sound;
		m_sound = NULL;
		return E_FAIL;
	}
	// レンダリング
	if (!m_renderer->Init(hWnd, bWindow) == S_OK)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = NULL;
		return E_FAIL;
	}
	// ネットワーク
	if (!m_pNetwork->Init(hInstance, hWnd) == S_OK)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = NULL;
		return E_FAIL;
	}

	if (m_pNetwork != NULL)
	{
		m_pNetwork->Connect();
	}
	// 画面遷移
	m_fade = CFade::Create(STARTMODE);

	return S_OK;
}

// ----------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------
void CManager::Uninit(void)
{
	/* メモリの破棄 */
	// 入力デバイス
	CInput::ReleaseAll();
	// キーボード
	if (m_keyboard != NULL)
	{
		m_keyboard->Uninit();
		delete m_keyboard;
		m_keyboard = NULL;
	}
	// ジョイパッド
	if (m_joypad != NULL)
	{
		m_joypad->Uninit();
		delete m_joypad;
		m_joypad = NULL;
	}
	// マウス
	if (m_mouse != NULL)
	{
		m_mouse->Uninit();
		delete m_mouse;
		m_mouse = NULL;
	}
	// キー詳細
	if (m_keyconfig != NULL)
	{
		m_keyconfig->Uninit();
		delete m_keyconfig;
		m_keyconfig = NULL;
	}
	// サウンド
	if (m_sound != NULL)
	{
		m_sound->Uninit();
		delete m_sound;
		m_sound = NULL;
	}
	// レンダリング
	if (m_renderer != NULL)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = NULL;
	}
	// 画面遷移
	if (m_fade != NULL)
	{
		m_fade->Uninit();
		delete m_fade;
		m_fade = NULL;
	}
	// タイトル
	if (m_title != NULL)
	{
		m_title->Uninit();
		delete m_title;
		m_title = NULL;
	}
	// チュートリアル
	if (m_tutorial != NULL)
	{
		m_tutorial->Uninit();
		delete m_tutorial;
		m_tutorial = NULL;
	}
	// ゲーム
	if (m_game != NULL)
	{
		m_game->Uninit();
		delete m_game;
		m_game = NULL;
	}
	// リザルト
	if (m_result != NULL)
	{
		m_result->Uninit();
		delete m_result;
		m_result = NULL;
	}
	// リザルト
	if (m_ranking != NULL)
	{
		m_ranking->Uninit();
		delete m_ranking;
		m_ranking = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------
void CManager::Update(void)
{
	// 入力デバイスのボタンが押されているか同課の初期化
	CInput::InitState();
	// キーボード
	if (m_keyboard != NULL)
	{
		m_keyboard->Update();
	}
	// ジョイパッド
	if (m_joypad != NULL)
	{
		m_joypad->Update();
	}
	// マウス
	if (m_mouse != NULL)
	{
		m_mouse->Update();
	}
	// レンダリング
	m_renderer->Update();

	// 前のモード終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		m_title->Update();
		break;
		// チュートリアル
	case MODE_TUTORIAL:
		m_tutorial->Update();
		break;
		// ゲーム
	case MODE_GAME:
		m_game->Update();
		break;
		// リザルト
	case MODE_RESULT:
		m_result->Update();
		break;
		// ランキング
	case MODE_RANKING:
		m_ranking->Update();
		break;
	default:
		break;
	}

	// 画面遷移
	m_fade->Update();
}

// ----------------------------------------------------------------------------------------------------
//
// 描画関数
//
// ----------------------------------------------------------------------------------------------------
void CManager::Draw(void)
{
	// レンダリング
	m_renderer->Draw();
}

// ----------------------------------------------------------------------------------------------------
// モード設定関数
// ----------------------------------------------------------------------------------------------------
void CManager::SetMode(MODE const mode)
{
	// 前のモード終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		m_title->Uninit();
		break;
		// チュートリアル
	case MODE_TUTORIAL:
		m_tutorial->Uninit();
		break;
		// ゲーム
	case MODE_GAME:
		m_game->Uninit();
		break;
		// リザルト
	case MODE_RESULT:
		m_result->Uninit();
		break;
		// ランキング
	case MODE_RANKING:
		m_ranking->Uninit();
		break;
	default:
		break;
	}

	m_mode = mode;	// 現在のモードを代入

					// 現在のモード初期化
	switch (mode)
	{
		// タイトル
	case MODE_TITLE:
		m_title->Init();
		break;
		// チュートリアル
	case MODE_TUTORIAL:
		m_tutorial->Init();
		break;
		// ゲーム
	case MODE_GAME:
		m_game->Init();
		break;
		// リザルト
	case MODE_RESULT:
		m_result->Init();
		break;
		// ランキング
	case MODE_RANKING:
		m_ranking->Init();
		break;
	default:
		break;
	}
}