// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// パーティクルの処理[particle.h]
// Author : Nishiyama koki
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "3Deffect.h"
#include "manager.h"

#define EFFECT_FILENAME "data/LOAD/EffectInfo.txt"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// マクロ定義
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BASEANGLE (D3DX_PI * 0.25f)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 静的メンバ変数の初期化
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9	C3DEffect::m_pVtxBuff = NULL;
C3DEffect::EFFECT		C3DEffect::m_aEffect[EFFECT_MAX] = {};
int						C3DEffect::m_nNumTextureMax = 0;
int						C3DEffect::m_nTexId[EFFECT_TYPE_MAX] = 
{
	1,
	2,
	4,
	3
};	// テクスチャーID

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 引数ありのコンストラクタ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DEffect::C3DEffect() :CScene()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DEffect::~C3DEffect()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Init(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice;					// デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// 値の初期化
	this->InitValues();
	// 頂点情報作成
	this->MakeVertex(pDevice);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Update(void)
{
	// 変数定義
	VERTEX_3D *pVtx;				// 頂点情報のポインタ
	C3DEffect::EFFECT *pEffect;		// エフェクトのポインタ
	// ポインタの初期化
	pEffect = &C3DEffect::m_aEffect[0];

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 最大数分ループ
	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++, pVtx+=4)
	{
		// 使用フラグがオフの時
		if (pEffect->bUse == false)
		{
			continue;
		}
		// 使用中のやつの更新
		if (this->UpdateLife(pVtx, pEffect) == false)
		{
			continue;
		}
		// 移動の更新
		this->UpdateMove(pVtx, pEffect);
		// 頂点情報の更新
		this->UpdateVetex(pVtx, pEffect);
	}
	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ライフの更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool C3DEffect::UpdateLife(VERTEX_3D *pVtx, EFFECT * pEffect)
{
	if (pEffect->nLife < 0)
	{
		// ライフが0になったとき
		pEffect->bUse = false;
		return false;
	}
	else
	{
		// ライフを減らすw
		pEffect->nLife--;
		return true;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 頂点の更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool C3DEffect::UpdateVetex(VERTEX_3D * pVtx, EFFECT * pEffect)
{
	// 半径を変化させる
	pEffect->size -= pEffect->sizeValue;
	// 角度を変化させる
	//pEffect->rot.y += (rand() % 10) * 0.01f;
	//CCalculation::Rot_One_Limit(pEffect->rot.y);
	pEffect->fAngle += (rand() % 10) * 0.01f;
	CCalculation::Rot_One_Limit(pEffect->fAngle);
	SetVartexSize(pVtx, pEffect);
	// アルファ値を変化させる
	pEffect->col.a -= pEffect->fAlphaValue;
	SetVetexColor(pVtx, pEffect);
	return true;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動の更新
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::UpdateMove(VERTEX_3D * pVtx, EFFECT * pEffect)
{
	switch (pEffect->EffectType)
	{
	case C3DEffect::EFFECT_TYPE_EXPLOSION:
		// 慣性
		pEffect->move.x += (0 - pEffect->move.x)*0.2f;
		pEffect->move.y += (0 - pEffect->move.y)*0.2f;
		pEffect->move.z += (0 - pEffect->move.z)*0.2f;
		break;
	case C3DEffect::EFFECT_TYPE_SPARK:
		break;
	case C3DEffect::EFFECT_TYPE_LINE:

		break;
	default:
		break;
	}
	// 位置情報の更新
	pEffect->pos += pEffect->move;

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice;					// デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			// 計算用マトリックス
	C3DEffect::EFFECT *pEffect;						// エフェクトのポインタ

	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	pEffect = &m_aEffect[0];						// ポインタの初期化

	// 3Dエフェクト用描画変化
	CManager::GetRenderer()->SetType(CRenderer::TYPE_3DEFFECT_ON);

	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			// マトリックスビューの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			
			// ビルボード
			CCalculation::SetBillboard(
				&pEffect->mtxWorld,
				&mtxView
			);
			
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(
				&mtxRot,
				pEffect->rot.y,
				pEffect->rot.x,
				pEffect->rot.z);
			D3DXMatrixMultiply(
				&pEffect->mtxWorld,
				&pEffect->mtxWorld,
				&mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(
				&mtxTrans,
				pEffect->pos.x,
				pEffect->pos.y,
				pEffect->pos.z);
			D3DXMatrixMultiply(
				&pEffect->mtxWorld,
				&pEffect->mtxWorld,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			// 頂点バッファをデータストリームにバインド
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, CTexture_manager::GetTexture(m_nTexId[pEffect->EffectType]));
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
	// 3Dエフェクト用描画変化
	CManager::GetRenderer()->SetType(CRenderer::TYPE_3DEFFECT_OFF);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 値の初期化
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::InitValues(void)
{
	// 変数宣言
	C3DEffect::EFFECT *pEffect;		// エフェクトのポインタ
	// ポインタの初期化
	pEffect = &C3DEffect::m_aEffect[0];

	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++)
	{	// 最大数分ループ
		pEffect->pos			= D3DVECTOR3_ZERO;				// 位置
		pEffect->rot			= D3DVECTOR3_ZERO;				// 回転量
		pEffect->move			= D3DVECTOR3_ZERO;				// 移動量
		pEffect->col			= D3DXCOLOR_INI;				// 色
		pEffect->size			= D3DVECTOR2_ZERO;				// サイズ
		pEffect->sizeValue		= D3DVECTOR2_ZERO;				// 半径の変化値
		pEffect->fAngle			= 0.0f;							// 角度
		pEffect->fAlphaValue	= 0.0f;							// アルファ値の変化値
		pEffect->nLife			= 0;							// 持ち時間
		pEffect->nTexType		= 0;							// テクスチャの種類
		pEffect->bUse			= false;						// 使用しているかどうか
		pEffect->EffectType		= C3DEffect::EFFECT_TYPE_NONE;	// エフェクトの種類
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 頂点の作成
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT C3DEffect::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// 変数宣言
	VERTEX_3D *pVtx;							// 頂点情報のポインタ

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * EFFECT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEffect = 0; nCntEffect < EFFECT_MAX; nCntEffect++, pVtx += 4)
	{
		SetVartexSize(pVtx, NULL, &nCntEffect);

		// 法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// texture座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 頂点サイズの設定
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::SetVartexSize(VERTEX_3D * pVtx, EFFECT * pEffect, const int * nIndex)
{
	if (nIndex != NULL)
	{
		// 変数宣言
		C3DEffect::EFFECT *pLocalEffect;					// エフェクトのポインタ
		pLocalEffect = &C3DEffect::m_aEffect[*nIndex];		// ポインタの初期化

		// 頂点の設定
		pVtx[0].pos.x = -sinf(BASEANGLE + pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[0].pos.y = -cosf(BASEANGLE + pLocalEffect->fAngle) * pLocalEffect->size.y;
		pVtx[0].pos.z = -cosf(BASEANGLE + pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[1].pos.x = -sinf(BASEANGLE - pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[1].pos.y = cosf(BASEANGLE - pLocalEffect->fAngle) * pLocalEffect->size.y;
		pVtx[1].pos.z = -cosf(BASEANGLE - pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[2].pos.x = sinf(BASEANGLE - pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[2].pos.y = -cosf(BASEANGLE - pLocalEffect->fAngle) * pLocalEffect->size.y;
		pVtx[2].pos.z = cosf(BASEANGLE - pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[3].pos.x = sinf(BASEANGLE + pLocalEffect->fAngle) * pLocalEffect->size.x;
		pVtx[3].pos.y = cosf(BASEANGLE + pLocalEffect->fAngle) * pLocalEffect->size.y;
		pVtx[3].pos.z = cosf(BASEANGLE + pLocalEffect->fAngle) * pLocalEffect->size.x;
		return;
	}
	if (pEffect != NULL)
	{
		// 頂点の設定
		pVtx[0].pos.x = -sinf(BASEANGLE + pEffect->fAngle) * pEffect->size.x;
		pVtx[0].pos.y = -cosf(BASEANGLE + pEffect->fAngle) * pEffect->size.y;
		pVtx[0].pos.z = -cosf(BASEANGLE + pEffect->fAngle) * pEffect->size.x;
		pVtx[1].pos.x = -sinf(BASEANGLE - pEffect->fAngle) * pEffect->size.x;
		pVtx[1].pos.y = cosf(BASEANGLE - pEffect->fAngle) * pEffect->size.y;
		pVtx[1].pos.z = -cosf(BASEANGLE - pEffect->fAngle) * pEffect->size.x;
		pVtx[2].pos.x = sinf(BASEANGLE - pEffect->fAngle) * pEffect->size.x;
		pVtx[2].pos.y = -cosf(BASEANGLE - pEffect->fAngle) * pEffect->size.y;
		pVtx[2].pos.z = cosf(BASEANGLE - pEffect->fAngle) * pEffect->size.x;
		pVtx[3].pos.x = sinf(BASEANGLE + pEffect->fAngle) * pEffect->size.x;
		pVtx[3].pos.y = cosf(BASEANGLE + pEffect->fAngle) * pEffect->size.y;
		pVtx[3].pos.z = cosf(BASEANGLE + pEffect->fAngle) * pEffect->size.x;
		return;
	}
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 頂点カラーの設定
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::SetVetexColor(VERTEX_3D * pVtx, EFFECT * pEffect, const int * nIndex)
{
	if (nIndex != NULL)
	{
		// 変数宣言
		C3DEffect::EFFECT *pLocalEffect;					// エフェクトのポインタ
		pLocalEffect = &C3DEffect::m_aEffect[*nIndex];		// ポインタの初期化

		pVtx[0].col =
			pVtx[1].col =
			pVtx[2].col =
			pVtx[3].col = pLocalEffect->col;
	}
	if (pEffect != NULL)
	{
		pVtx[0].col =
			pVtx[1].col =
			pVtx[2].col =
			pVtx[3].col = pEffect->col;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DEffect * C3DEffect::Create(void)
{
	// 変数宣言
	C3DEffect *p3DEffect = new C3DEffect;
	// シーン管理設定
	p3DEffect->ManageSetting(CScene::LAYER_3DPARTICLE);
	// 初期化
	p3DEffect->Init();
	return p3DEffect;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 削除
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Delete(int nCntIndex)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// エフェクトの設定
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Set3DEffect(
	EFFECT_TYPE EffectType, 
	int nTexType,
	D3DXVECTOR3 pos, 
	D3DXVECTOR3 rot,
	D3DXVECTOR3 move, 
	D3DXCOLOR col,
	D3DXVECTOR2 size,
	int nLife,
	D3DXVECTOR2 sizeValue
)
{
	// 変数宣言
	C3DEffect::EFFECT *pEffect;			// エフェクトのポインタ
	pEffect = &C3DEffect::m_aEffect[0];	// ポインタの初期化

	// 最大数ループ
	for (int nCntEffect = 0; nCntEffect < EFFECT_MAX; nCntEffect++, pEffect++)
	{
		// 使用フラグオフの個体の時
		if (pEffect->bUse == false)
		{
			// 変数定義
			VERTEX_3D *pVtx;		// 頂点ポインタ
			//頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			// 頂点ポインタの更新
			pVtx += nCntEffect * 4;
			// ライフの設定
			pEffect->nLife = nLife;
			// テクスチャ種類の設定
			pEffect->nTexType = nTexType;
			// エフェクト種類の設定
			pEffect->EffectType = EffectType;
			// 移動量の設定
			pEffect->move = move;
			// 半径の設定
			pEffect->size = size;
			// 位置の設定
			pEffect->pos = pos;
			// 回転の設定
			pEffect->rot = rot;
			// 頂点位置の設定
			SetVartexSize(pVtx, pEffect);
			// 色の設定
			pEffect->col = col;
			// 頂点カラーの設定
			SetVetexColor(pVtx, pEffect);
			// アルファ変化値の設定
			pEffect->fAlphaValue = pEffect->col.a / pEffect->nLife;
			if (pEffect->nTexType == 1)
			{
				// 半径変化値の設定
				pEffect->sizeValue.x = -50.0f;
				pEffect->sizeValue.y = -50.0f;
			}
			else
			{
				// サイズx変化値の設定
				pEffect->sizeValue.x = pEffect->size.x / pEffect->nLife;
				// サイズy変化値の設定
				pEffect->sizeValue.y = pEffect->size.y / pEffect->nLife;
			}
			// 使用フラグをオン
			pEffect->bUse = true;
			//頂点データをアンロック
			m_pVtxBuff->Unlock();
			break;
		}
	}

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT C3DEffect::Load(void)
{
	// テクスチャファイル名の取得
	return C3DEffect::LoadTextureFile();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// テクスチャファイル名の読み込み
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT C3DEffect::LoadTextureFile(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 開放
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Unload(void)
{
}

#ifdef _DEBUG
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DEffect::Debug(void)
{
}
#endif // _DEBUG
