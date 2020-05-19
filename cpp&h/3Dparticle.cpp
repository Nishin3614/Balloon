// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3Dパーティクルの処理[particle.h]
// Author : Nishiyama koki
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "3Dparticle.h"
#include "3Deffect.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 静的メンバ変数の初期化
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle::PARTICLE_OFFSET C3DParticle::m_ParticleOffset[C3DParticle::OFFSET_ID_MAX] = {};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle::C3DParticle() : CScene()
{
	m_nFlameCount = 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle::~C3DParticle()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Init(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Uninit(void)
{

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update(void)
{

	m_nFlameCount++;
	if (m_nFlameCount > m_ParticleOffset[m_offsetID].nFrame)
	{
		m_nFlameCount = 0;
		Release();
	}
	else
	{
		// 変数宣言
		D3DXVECTOR3	move = D3DVECTOR3_ZERO;		// 移動量
		D3DXVECTOR3	pos = D3DVECTOR3_ZERO;		// 位置
		D3DXVECTOR3 rot = D3DVECTOR3_ZERO;		// 回転
		D3DXVECTOR2	size = D3DVECTOR2_ZERO;		// サイズ
		D3DXCOLOR	col = D3DXCOLOR_INI;		// 色
		D3DXVECTOR3	posRand = D3DVECTOR3_ZERO;	// 位置ランダム
		int			nLife = 0;					// ライフ
		int			nColRand = 0;				// 色のランダム
		float		fSpeed = 0;					// 速度
		float		fAngle[3];					// 角度
		fAngle[0] = 0;
		fAngle[1] = 0;
		fAngle[2] = 0;

		// 設定数ループ
		for (int nCntEffect = 0; nCntEffect < m_ParticleOffset[m_offsetID].nNumber; nCntEffect++)
		{
			/* カラー設定 */
			col = m_ParticleOffset[m_offsetID].Col;
			if (m_ParticleOffset[m_offsetID].bRedRand)
			{
				nColRand = rand() % (int)(col.r * 10);
				col.r = (float)nColRand / 10;
			}
			if (m_ParticleOffset[m_offsetID].bGreenRand)
			{
				nColRand = rand() % (int)(col.g * 10);
				col.g = (float)nColRand / 10;
			}
			if (m_ParticleOffset[m_offsetID].bBlueRand)
			{
				nColRand = rand() % (int)(col.b * 10);
				col.b = (float)nColRand / 10;
			}
			if (m_ParticleOffset[m_offsetID].bAlphaRand)
			{
				nColRand = rand() % (int)(col.a * 10);
				col.a = (float)nColRand / 10;
			}

			/* 半径設定 */
			// 読み込んだサイズを代入
			size = m_ParticleOffset[m_offsetID].Size;
			// ランダムで設定した分加算
			if (m_ParticleOffset[m_offsetID].SizeXRand.nMax > 0)
			{
				size.x += (float)(rand() % m_ParticleOffset[m_offsetID].SizeXRand.nMax + m_ParticleOffset[m_offsetID].SizeXRand.nMin);
			}
			if (m_ParticleOffset[m_offsetID].SizeYRand.nMax > 0)
			{
				size.y += (float)(rand() % m_ParticleOffset[m_offsetID].SizeYRand.nMax + m_ParticleOffset[m_offsetID].SizeXRand.nMin);
			}
			/* ライフ設定 */
			nLife = m_ParticleOffset[m_offsetID].nLife;
			// ランダムのライフを設定
			if (m_ParticleOffset[m_offsetID].nLifeRand.nMax > 0)
			{
			nLife +=
				(rand() % m_ParticleOffset[m_offsetID].nLifeRand.nMax +
					m_ParticleOffset[m_offsetID].nLifeRand.nMin);
			}

			/* 速度の設定 */
			fSpeed = m_ParticleOffset[m_offsetID].fSpeed;
			// ランダムのスピード設定
			if (m_ParticleOffset[m_offsetID].nSpeedRand.nMax > 0)
			{
				fSpeed +=
					(float)(rand() % m_ParticleOffset[m_offsetID].nSpeedRand.nMax +
						m_ParticleOffset[m_offsetID].nSpeedRand.nMin);
			}

			/* 角度の設定 */
			fAngle[0] = m_ParticleOffset[m_offsetID].Rot.x;
			fAngle[1] = m_ParticleOffset[m_offsetID].Rot.y;
			fAngle[2] = m_ParticleOffset[m_offsetID].Rot.z;
			// ランダムの角度設定
			if (m_ParticleOffset[m_offsetID].nAngleRand.nMax > 0)
			{
				fAngle[0] +=
					(rand() % m_ParticleOffset[m_offsetID].nAngleRand.nMax +
						m_ParticleOffset[m_offsetID].nAngleRand.nMin)*0.01f;
				fAngle[1] +=
					(rand() % m_ParticleOffset[m_offsetID].nAngleRand.nMax +
						m_ParticleOffset[m_offsetID].nAngleRand.nMin)*0.01f;
				fAngle[2] +=
					(rand() % m_ParticleOffset[m_offsetID].nAngleRand.nMax +
						m_ParticleOffset[m_offsetID].nAngleRand.nMin)*0.01f;
			}

			/* 位置設定 */
			// ランダムの角度設定
			if (m_ParticleOffset[m_offsetID].PosXRand.nMax > 0)
			{
				posRand.x = (float)(rand() % m_ParticleOffset[m_offsetID].PosXRand.nMax + m_ParticleOffset[m_offsetID].PosXRand.nMin);
			}
			if (m_ParticleOffset[m_offsetID].PosYRand.nMax > 0)
			{
				posRand.y = (float)(rand() % m_ParticleOffset[m_offsetID].PosYRand.nMax + m_ParticleOffset[m_offsetID].PosYRand.nMin);
			}
			if (m_ParticleOffset[m_offsetID].PosZRand.nMax > 0)
			{
				posRand.z = (float)(rand() % m_ParticleOffset[m_offsetID].PosZRand.nMax + m_ParticleOffset[m_offsetID].PosZRand.nMin);
			}

			// 位置
			pos =
			{
				posRand.x + m_ParticleOffset[m_offsetID].Pos.x,
				posRand.y + m_ParticleOffset[m_offsetID].Pos.y,
				posRand.z + m_ParticleOffset[m_offsetID].Pos.z
			};

			/* 移動量設定 */
			move =
			{
				sinf(fAngle[1])*sinf(fAngle[2])*fSpeed,
				cosf(fAngle[0])*cosf(fAngle[2])*fSpeed,
				cosf(fAngle[0])*sinf(fAngle[1])*fSpeed
			};

			C3DEffect::Set3DEffect(
				(C3DEffect::EFFECT_TYPE)m_ParticleOffset[m_offsetID].nEffeType,
				m_ParticleOffset[m_offsetID].nEffeTexType,
				pos + m_Origin,
				D3DXVECTOR3(
					fAngle[0],
					fAngle[1],
					fAngle[2]
				),
				move,
				col,
				size,
				nLife
			);
		}
	}
}
/*
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// カラー
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Col(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// サイズ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Size(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ライフ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Life(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// スピード
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Speed(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 角度
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Angle(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 位置
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Pos(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動量
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Move(void)
{
}
*/
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Draw(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle * C3DParticle::Create(PARTICLE_OFFSET_ID OffsetID, CONST D3DXVECTOR3 origin)
{
	// 変数宣言
	C3DParticle *p3DParticle = new C3DParticle;
	// シーン管理設定
	p3DParticle->ManageSetting(CScene::LAYER_3DPARTICLE);
	// 設定
	p3DParticle->SetParticle(OffsetID);
	p3DParticle->SetOrigin(origin);
	return p3DParticle;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// パーティクルの設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::SetParticle(PARTICLE_OFFSET_ID OffsetID)
{
	m_offsetID = OffsetID;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT C3DParticle::Load(void)
{
	// 変数宣言
	FILE *pFile = NULL;				// ファイルのポインタ
	char cRead[128];				// 読み込み用
	char cComp[128];				// 比較用
	char cEmpty[128];				// 要らないもの用
	int nCntError = 0;				// エラー用
	int nCntOffset = 0;				// オフセットのカウント
	
	// 一時保存用
	// ファイルが開かれていなかったら
	if ((pFile = fopen("data/LOAD/ParticleInfo.txt", "r")) == NULL)
	{
		CCalculation::Messanger("data/LOAD/ParticleInfo.txtのテキストがありません");
		return E_FAIL;
	}

	while (strcmp(cComp, "SCRIPT") != 0)
	{
		// 1行読み込む
		fgets(cRead, sizeof(cRead), pFile);
		// 読み込んど文字列代入
		sscanf(cRead, "%s", &cComp);

		// エラーカウントをインクリメント
		nCntError++;
		if (nCntError > 1048576)
		{// エラー
			nCntError = 0;
			CCalculation::Messanger("スクリプトがありません");
			return E_FAIL;
		}
	}

	while (strcmp(cComp, "END_SCRIPT") != 0)
	{// END_SCRIPTまでループ
	 // 1行読み込む
		fgets(cRead, sizeof(cRead), pFile);
		// 読み込んど文字列代入
		sscanf(cRead, "%s", &cComp);

		// エラーカウントをインクリメント
		nCntError++;
		if (nCntError > 1048576)
		{// エラー
			nCntError = 0;
			fclose(pFile);
			CCalculation::Messanger("エンドスクリプトがありません");
			return E_FAIL;
		}
		else if (strcmp(cComp, "OFFSET") == 0)
		{
			while (strcmp(cComp, "END_OFFSET") != 0)
			{
				// 1行読み込む
				fgets(cRead, sizeof(cRead), pFile);
				// 読み込んど文字列代入
				sscanf(cRead, "%s", &cComp);
				if (strcmp(cComp, "IF") == 0)
				{
					// 読み込んど文字列代入
					sscanf(cRead, "%s %s", &cEmpty, &cComp);
					/* 位置ランダム */
					if (strcmp(cComp, "POSRAND") == 0)
					{
						// 読み込んど文字列代入
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty , &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1行読み込む
								fgets(cRead, sizeof(cRead), pFile);
								// 読み込んど文字列代入
								sscanf(cRead, "%s", &cComp);

								if (strcmp(cComp, "POSX") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty,
										&m_ParticleOffset[nCntOffset].PosXRand.nMax,
										&m_ParticleOffset[nCntOffset].PosXRand.nMin
									);
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "POSY") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty,
										&m_ParticleOffset[nCntOffset].PosYRand.nMax,
										&m_ParticleOffset[nCntOffset].PosYRand.nMin
									);
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "POSZ") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty,
										&m_ParticleOffset[nCntOffset].PosZRand.nMax,
										&m_ParticleOffset[nCntOffset].PosZRand.nMin
									);
									// 文字列の初期化
									cComp[0] = '\0';
									cRead[0] = '\0';
								}
							}
							// 文字列の初期化
							cComp[0] = '\0';
						}
						// 文字列の初期化
						cComp[0] = '\0';
					}
					/* 色ランダム */
					else if (strcmp(cComp, "COLRAND") == 0)
					{
						// 読み込んど文字列代入
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							// 初期化
							m_ParticleOffset[nCntOffset].Col.r = 1.0f;
							m_ParticleOffset[nCntOffset].Col.g = 1.0f;
							m_ParticleOffset[nCntOffset].Col.b = 1.0f;
							m_ParticleOffset[nCntOffset].Col.a = 1.0f;

							while (strcmp(cComp, "}") != 0)
							{
								// 1行読み込む
								fgets(cRead, sizeof(cRead), pFile);
								// 読み込んど文字列代入
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "RED") == 0)
								{
									// ランダム状態に
									m_ParticleOffset[nCntOffset].bRedRand = true;
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "GREEN") == 0)
								{
									// ランダム状態に
									m_ParticleOffset[nCntOffset].bGreenRand = true;
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "BLUE") == 0)
								{
									// ランダム状態に
									m_ParticleOffset[nCntOffset].bBlueRand = true;
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "ALPHA") == 0)
								{
									// ランダム状態に
									m_ParticleOffset[nCntOffset].bAlphaRand = true;
									// 文字列の初期化
									cComp[0] = '\0';
								}
							}
							// 文字列の初期化
							cComp[0] = '\0';
						}
						// 文字列の初期化
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "SIZERAND") == 0)
					{
						// 読み込んど文字列代入
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1行読み込む
								fgets(cRead, sizeof(cRead), pFile);
								// 読み込んど文字列代入
								sscanf(cRead, "%s", &cComp);

								if (strcmp(cComp, "SIZEX") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].SizeXRand.nMax, &m_ParticleOffset[nCntOffset].SizeXRand.nMin);
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "SIZEY") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].SizeYRand.nMax, &m_ParticleOffset[nCntOffset].SizeYRand.nMin);
									// 文字列の初期化
									cComp[0] = '\0';
								}
							}
							// 文字列の初期化
							cComp[0] = '\0';
						}
						// 文字列の初期化
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "ANGLERAND") == 0)
					{
						// 読み込んど文字列代入
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1行読み込む
								fgets(cRead, sizeof(cRead), pFile);
								// 読み込んど文字列代入
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nAngleRand.nMax);
									// 文字列の初期化
									cComp[0] = '\0';

								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nAngleRand.nMin);
									// 文字列の初期化
									cComp[0] = '\0';

								}
							}
							// 文字列の初期化
							cComp[0] = '\0';
						}
						// 文字列の初期化
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "SPEEDRAND") == 0)
					{
						// 読み込んど文字列代入
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1行読み込む
								fgets(cRead, sizeof(cRead), pFile);
								// 読み込んど文字列代入
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nSpeedRand.nMax);
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nSpeedRand.nMin);
									// 文字列の初期化
									cComp[0] = '\0';
								}
							}
							// 文字列の初期化
							cComp[0] = '\0';
						}
						// 文字列の初期化
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "LIFERAND") == 0)
					{
						// 読み込んど文字列代入
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1行読み込む
								fgets(cRead, sizeof(cRead), pFile);
								// 読み込んど文字列代入
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nLifeRand.nMax);
									// 文字列の初期化
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nLifeRand.nMin);
									// 文字列の初期化
									cComp[0] = '\0';
								}
							}
							// 文字列の初期化
							cComp[0] = '\0';
						}
						// 文字列の初期化
						cComp[0] = '\0';
					}
				}
				else if (strcmp(cComp, "POS") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].Pos.x,
							&m_ParticleOffset[nCntOffset].Pos.y,
							&m_ParticleOffset[nCntOffset].Pos.z);
					}

					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "ANGLE") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].Rot.x,
							&m_ParticleOffset[nCntOffset].Rot.y,
							&m_ParticleOffset[nCntOffset].Rot.z);
					}

					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "COL") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].Col.r,
							&m_ParticleOffset[nCntOffset].Col.g,
							&m_ParticleOffset[nCntOffset].Col.b,
							&m_ParticleOffset[nCntOffset].Col.a);
					}

					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "SIZE") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f %f",
							&cEmpty, 
							&cEmpty,
							&m_ParticleOffset[nCntOffset].Size.x,
							&m_ParticleOffset[nCntOffset].Size.y
							);

					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "SPEED") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].fSpeed);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "LIFE") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nLife);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}

				else if (strcmp(cComp, "FRAME") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nFrame);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "NUMBER") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nNumber);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "TEXTYPE") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nEffeTexType);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "EFFETYPE") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nEffeType);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "PARTICLETYPE") == 0)
				{
					// 文字列の初期化
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].type);
					}
					// 文字列の初期化
					cComp[0] = '\0';
				}
			}
			// オフセットカウントを進める
			nCntOffset++;
		}
	}
	fclose(pFile);
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 開放
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Unload(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 原点位置の設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::SetOrigin(CONST D3DXVECTOR3 & Origin)
{
	m_Origin = Origin;
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Debug(void)
{
}
#endif // _DEBUG