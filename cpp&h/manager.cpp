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
CGame * CManager::m_game = NULL;						// ゲーム
CManager::MODE CManager::m_mode = CManager::MODE_GAME;	// モード
bool CManager::m_bWire = false;							// ワイヤー

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
	/* 画面 */
	// ゲームの生成
	m_game = new CGame;
	// モードの設定
	m_mode = STARTMODE;

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
	// ゲーム
	if (m_game != NULL)
	{
		m_game->Uninit();
		delete m_game;
		m_game = NULL;
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
		// ゲーム
	case MODE_GAME:
		m_game->Update();
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
		// ゲーム
	case MODE_GAME:
		m_game->Uninit();
		break;
	default:
		break;
	}

	m_mode = mode;	// 現在のモードを代入

	// 現在のモード初期化
	switch (mode)
	{
		// ゲーム
	case MODE_GAME:
		m_game->Init();
		break;
	default:
		break;
	}
}