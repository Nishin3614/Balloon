// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ゲーム処理 [game.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "game.h"
/* 描画 */
#include "number.h"
#include "fade.h"
#include "floor.h"
#include "meshobit.h"
#include "meshdome.h"
#include "meshsphere.h"
#include "meshwall.h"
#include "3Deffect.h"
#include "bgdome.h"
#include "time.h"
#include "collision.h"
#include "camera.h"
#include "3Dparticle.h"
#include "keyboard.h"
#include "ui_group.h"
#include "Extrusion.h"
#include "3Dmap.h"
#include "score.h"
#include "network.h"
#include "item.h"
#include "thunder.h"
#include "selectcharacter.h"
#include "character_fish.h"
#include "invisible.h"
#include "revival.h"
#include "speedUP.h"
#include "scoreUP.h"
#include "rank.h"
#include "lake.h"
#include "loadscreen.h"

/* ポーズ */
#include "pause.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define ITEM_SPACE	(100)			// アイテム同士の間隔
#define CIRCLE_SIZE (300)			// 円の大きさ

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::STATE CGame::m_state = CGame::STATE_NORMAL;		// 状態
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::CGame()
{
	m_pause = NULL;
	m_state = CGame::STATE_NORMAL;
	m_nWatchingId = 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Init(void)
{
	// ロードスクリーンの変数初期化処理
	CManager::GetLoadScreen()->VariableInit();
	CNetwork *pNetwork = CManager::GetNetwork();

	// カメラのタイプ設定
	CManager::GetRenderer()->GetCamera()->SetType(CCamera::TYPE_FOLLOW);
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	/* 初期化 */
	// 状態
	m_state = STATE_NORMAL;
	// キャラクターの総人数
	CCharacter::InitStatic();
	/* 作成 */
	// 3Dエフェクトの生成
	C3DEffect::Create();
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	// 球の設定
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		100000.0f);
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	// 3Dマップ生成
	CLake::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(25000.0f, 25000.0f, 0.0f));
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();

	C3DMap::LoadScript("data/LOAD/MAPPING/rand.txt");
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	C3DMap::LoadCreate(C3DMap::MAP_STAGE_1);
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	// プレイヤー生成
	PlayerCreate();
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();

	// スコア生成
	m_pScore = CScore::Create();
	// ポーズの生成
	m_pause = new CPause();
	// ポーズの初期化
	m_pause->Init();
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();
	if (pNetwork != NULL)
	{
		pNetwork->ResetCoin();				// コインのデータベースをリセット
	}
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();

	CScene_X::LoadScrept("data/LOAD/MAPPING/object.csv");
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();

	// スタートコール
	CUi_group::Create(CUi::UITYPE_GAMESTART);
	// 読み込み画面描画
	CManager::GetRenderer()->LoadDraw();

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Uninit(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork != NULL)
	{// ネットワークが存在していたとき
		pNetwork->StopUpdate();				// 更新停止予約
		pNetwork->CloseTCP();				// サーバーとの窓口を閉める
	}

	// ポーズ
	if (m_pause != NULL)
	{
		m_pause->Uninit();
		delete m_pause;
		m_pause = NULL;
	}
	// スコア
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}
	// ゲーム状態の初期化
	m_state = STATE_NORMAL;
	// シーンの開放
	CScene::ReleaseAll();
	// シーンストップ解除
	CScene::UpdateStop(false);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Update(void)
{
	// 当たり判定処理
	CCollision::CollisionDetection();
	// ポーズ状態ならば
	if (m_state == STATE_PAUSE)
	{
		if (m_pause != NULL)
		{
			m_pause->Update();
		}
	}
	// ポーズ状態ではないとき
	else
	{
		// ポーズへ
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_POUSE))
		{
			//PauseState();
		}
	}

	if (CPlayer::GetDie(CManager::GetNetwork()->GetId()))
	{
		CKeyboard *pKeyboard = CManager::GetKeyboard();

		if (pKeyboard != NULL)
		{
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				FocusPlayer();
			}
		}

		if (!CPlayer::GetDie(m_nWatchingId))
		{
			m_pPlayer[m_nWatchingId]->Camera();
		}
	}

#ifdef _DEBUG
	// 情報取得
	CFade *pFade = CManager::GetFade();	// フェード情報

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(TESTPLAY_NUMBER1))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// リザルトへ
				pFade->SetFade(CManager::MODE_TUTORIAL);
			}
		}
	}
	// テスト用
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(TESTPLAY_NUMBER2))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// リザルトへ
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
	}
	DebugStatus();

	// 終了表示
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_T))
	{
		CUi_group::Create(CUi::UITYPE_FINISH);
	}
	// ステータスリセット
	if (CManager::GetKeyboard()->GetKeyboardPress(DIK_LCONTROL) &&
		CManager::GetKeyboard()->GetKeyboardTrigger(DIK_4))
	{
		CCharacter::LoadStatus();
		CItem::LoadStatus();
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				continue;
			}
			m_pPlayer[nCntPlayer]->GaugeStatusInit();
		}
	}
#endif // _DEBUG
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Draw(void)
{
	if (m_state == STATE_PAUSE)
	{
		if (m_pause != NULL)
		{
			m_pause->Draw();
		}
	}
	if (m_pScore != NULL)
	{
		m_pScore->Draw();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 注目させる処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::FocusPlayer(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork == NULL) return;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_nWatchingId++;

		if (m_nWatchingId == MAX_PLAYER)
		{
			m_nWatchingId = 0;
		}

		if (!pNetwork->GetDie(m_nWatchingId))
		{
			OutputDebugString("ふぁっきゅー");
			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグステータス処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::DebugStatus(void)
{
	// ステータスの更新 //
	CDebugproc::Print("LCTRL + 4:ステータスの更新\n");
	//CCharacter::AllDebug();
	//CItem::AllDebug();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ポーズ状態
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::PauseState(void)
{
	// ゲーム状態をポーズに
	if (m_state != STATE_PAUSE)
	{
		m_state = STATE_PAUSE;
		// 更新を止める
		CScene::UpdateStop(true);
		// メニュー音
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// プレイヤー生成
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::PlayerCreate(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	char aAns[256];
	int aData[MAX_PLAYER];
	char cDie[64];
	D3DXVECTOR3 pos;

	memset(&cDie, 0, sizeof(cDie));

	pNetwork->SendTCP("CHARACTER_LOAD", sizeof("CHARACTER_LOAD"));
	pNetwork->DataRecv(SOCKETTYPE_CLIENT, (char*)&aAns, sizeof(aAns));
	sscanf(aAns, "%s %d %d %d %d", &cDie, &aData[0], &aData[1], &aData[2], &aData[3]);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		switch (nCntPlayer)
		{
		case 0:
			pos = D3DXVECTOR3(-850.0f, 0.0f, 850.0f);
			break;
		case 1:
			pos = D3DXVECTOR3(850.0f, 0.0f, 850.0f);
			break;
		case 2:
			pos = D3DXVECTOR3(-850.0f, 0.0f, -850.0f);
			break;
		case 3:
			pos = D3DXVECTOR3(850.0f, 0.0f, -850.0f);
			break;
		default:
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}

		switch (aData[nCntPlayer])
		{
		case CHARATYPE_SPEED_UP:
			m_pPlayer[nCntPlayer] = CSpeedUP::Create(nCntPlayer, pos);
			break;
		case CHARATYPE_SCORE_UP:
			m_pPlayer[nCntPlayer] = CScoreUP::Create(nCntPlayer, pos);
			break;
		case CHARATYPE_INVISIBLE:
			m_pPlayer[nCntPlayer] = CInvisible::Create(nCntPlayer, pos);
			break;
		case CHARATYPE_REVIVAL:
			m_pPlayer[nCntPlayer] = CRevival::Create(nCntPlayer, pos);
			break;
		}
	}
}
