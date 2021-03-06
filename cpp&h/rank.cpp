// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 順位表示処理 [rank.cpp]
// Author : masayasu wakita
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "rank.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CRank::CRank()
{

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CRank::~CRank()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRank::Init(void)
{
	SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CScene_THREE::Init();

	CScene_THREE::SetBillboard(true);
	CScene_THREE::SetLighting(true);
	CScene_THREE::SetAlphaBlend(true);
	CScene_THREE::SetTexType(26);
	CScene_THREE::SetAnimation(1.0f / 4, 1.0f, 0.0f, 0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRank::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRank::Update(void)
{
	CScene_THREE::Update();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRank::Draw(void)
{
	CScene_THREE::Draw();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 順位表示の生成
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CRank *CRank::Create(void)
{
	CRank *pRank = new CRank();

	if (pRank != NULL)
	{
		pRank->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		pRank->SetPos(D3DXVECTOR3(0.0f, 500.0f, 0.0f));
		pRank->Init();
		pRank->ManageSetting(LAYER_CHARARANK);
	}

	return pRank;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// リソース情報読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CRank::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだリソース情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CRank::UnLoad(void)
{
}
