// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 選択画面処理 [select.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "select.h"
/* 描画 */
#include "fade.h"
#include "p_thunder.h"
#include "p_zombie.h"
#include "meshsphere.h"
#include "3Deffect.h"
#include "3Dmap.h"
#include "camera.h"
#include "selectcharacter.h"
#include "network.h"
#include "BalloonNum.h"

/* ポーズ */
#include "pause.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelect::CSelect()
{
	m_nRand = 0;
	m_bReady = false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSelect::~CSelect()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelect::Init(void)
{
	// 初期化
	CSelectCharacter::InitStatic();
	// カメラのタイプ設定
	CManager::GetRenderer()->GetCamera()->SetType(CCamera::TYPE_FOLLOW);
	/* 初期化 */
	/* 作成 */
	// 3Dエフェクトの生成
	C3DEffect::Create();
	// 球の設定
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		10000.0f);
	// 3Dマップ生成
	C3DMap::LoadCreate(C3DMap::MAP_STAGE_2);
	// 選択キャラクターの生成
	// もし、キャラ選択決定した後に全プレイヤーの
	m_pSelectCharacter = CSelectCharacter::Create(
		CManager::GetPlayerID(),			// プレイヤー番号
		D3DXVECTOR3(200.0f, 0.0f, 200.0f)	// 位置
	);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelect::Uninit(void)
{
	// シーンの開放
	CScene::ReleaseAll();
	// シーンストップ解除
	CScene::UpdateStop(false);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelect::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CNetwork *pNetwork = CManager::GetNetwork();
	CJoypad *pJoypad = CManager::GetJoy();

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (!m_bReady)
		{// 準備中だったとき

			if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_1))
			{
				CBalloonNum::Create(0);
			}
			else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_2))
			{
				CBalloonNum::Create(1);
			}
			else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_3))
			{
				CBalloonNum::Create(2);
			}
			else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_4))
			{
				CBalloonNum::Create(3);
			}
			// 選択画面へ遷移
			if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
			{
				if (pNetwork != NULL)
				{
					if (CManager::GetNetwork()->CheckCharacterReady(m_pSelectCharacter->GetCharacterType()))
					{
						char aData[64];
						memset(aData, 0, sizeof(aData));
						sprintf(aData, "READY %d %d", 1, m_pSelectCharacter->GetCharacterType());
						pNetwork->SendTCP(aData, sizeof(aData));
					}
				}
			}

			if (pJoypad != NULL)
			{
				if (pJoypad->GetTrigger(0, CJoypad::KEY_A))
				{
					if (pNetwork != NULL)
					{
						if (CManager::GetNetwork()->CheckCharacterReady(m_pSelectCharacter->GetCharacterType()))
						{
							char aData[64];
							memset(aData, 0, sizeof(aData));
							sprintf(aData, "READY %d %d", 1, m_pSelectCharacter->GetCharacterType());
							pNetwork->SendTCP(aData, sizeof(aData));
						}
					}
				}
			}
		}
		else
		{// 準備完了していたとき
			if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
			{
				char aData[64];
				sprintf(aData, "READY %d", 0);
				pNetwork->SendTCP(aData, sizeof(aData));
			}

			if (pJoypad != NULL)
			{
				if (pJoypad->GetTrigger(0, CJoypad::KEY_A))
				{
					char aData[64];
					sprintf(aData, "READY %d", 0);
					pNetwork->SendTCP(aData, sizeof(aData));
				}
			}
		}
	}

	CDebugproc::Print("Rand = %d\n", m_nRand);
	int nAnswer = rand() % (100);
	if (nAnswer > 95)
	{
		m_nRand = nAnswer;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelect::Draw(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 準備完了
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSelect::SetReady(bool bValue)
{
	m_bReady = bValue;
	m_pSelectCharacter->SetReady(bValue);
}