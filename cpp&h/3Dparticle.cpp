// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3D�p�[�e�B�N���̏���[particle.h]
// Author : Nishiyama koki
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "3Dparticle.h"
#include "3Deffect.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle::PARTICLE_OFFSET C3DParticle::m_ParticleOffset[C3DParticle::OFFSET_ID_MAX] = {};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle::C3DParticle() : CScene()
{
	m_nFlameCount = 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle::~C3DParticle()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Init(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Uninit(void)
{

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V
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
		// �ϐ��錾
		D3DXVECTOR3	move = D3DVECTOR3_ZERO;		// �ړ���
		D3DXVECTOR3	pos = D3DVECTOR3_ZERO;		// �ʒu
		D3DXVECTOR3 rot = D3DVECTOR3_ZERO;		// ��]
		D3DXVECTOR2	size = D3DVECTOR2_ZERO;		// �T�C�Y
		D3DXCOLOR	col = D3DXCOLOR_INI;		// �F
		D3DXVECTOR3	posRand = D3DVECTOR3_ZERO;	// �ʒu�����_��
		int			nLife = 0;					// ���C�t
		int			nColRand = 0;				// �F�̃����_��
		float		fSpeed = 0;					// ���x
		float		fAngle[3];					// �p�x
		fAngle[0] = 0;
		fAngle[1] = 0;
		fAngle[2] = 0;

		// �ݒ萔���[�v
		for (int nCntEffect = 0; nCntEffect < m_ParticleOffset[m_offsetID].nNumber; nCntEffect++)
		{
			/* �J���[�ݒ� */
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

			/* ���a�ݒ� */
			// �ǂݍ��񂾃T�C�Y����
			size = m_ParticleOffset[m_offsetID].Size;
			// �����_���Őݒ肵�������Z
			if (m_ParticleOffset[m_offsetID].SizeXRand.nMax > 0)
			{
				size.x += (float)(rand() % m_ParticleOffset[m_offsetID].SizeXRand.nMax + m_ParticleOffset[m_offsetID].SizeXRand.nMin);
			}
			if (m_ParticleOffset[m_offsetID].SizeYRand.nMax > 0)
			{
				size.y += (float)(rand() % m_ParticleOffset[m_offsetID].SizeYRand.nMax + m_ParticleOffset[m_offsetID].SizeXRand.nMin);
			}
			/* ���C�t�ݒ� */
			nLife = m_ParticleOffset[m_offsetID].nLife;
			// �����_���̃��C�t��ݒ�
			if (m_ParticleOffset[m_offsetID].nLifeRand.nMax > 0)
			{
			nLife +=
				(rand() % m_ParticleOffset[m_offsetID].nLifeRand.nMax +
					m_ParticleOffset[m_offsetID].nLifeRand.nMin);
			}

			/* ���x�̐ݒ� */
			fSpeed = m_ParticleOffset[m_offsetID].fSpeed;
			// �����_���̃X�s�[�h�ݒ�
			if (m_ParticleOffset[m_offsetID].nSpeedRand.nMax > 0)
			{
				fSpeed +=
					(float)(rand() % m_ParticleOffset[m_offsetID].nSpeedRand.nMax +
						m_ParticleOffset[m_offsetID].nSpeedRand.nMin);
			}

			/* �p�x�̐ݒ� */
			fAngle[0] = m_ParticleOffset[m_offsetID].Rot.x;
			fAngle[1] = m_ParticleOffset[m_offsetID].Rot.y;
			fAngle[2] = m_ParticleOffset[m_offsetID].Rot.z;
			// �����_���̊p�x�ݒ�
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

			/* �ʒu�ݒ� */
			// �����_���̊p�x�ݒ�
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

			// �ʒu
			pos =
			{
				posRand.x + m_ParticleOffset[m_offsetID].Pos.x,
				posRand.y + m_ParticleOffset[m_offsetID].Pos.y,
				posRand.z + m_ParticleOffset[m_offsetID].Pos.z
			};

			/* �ړ��ʐݒ� */
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
// �J���[
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Col(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �T�C�Y
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Size(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���C�t
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Life(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�s�[�h
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Speed(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �p�x
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Angle(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ʒu
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Pos(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ړ���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Update_Move(void)
{
}
*/
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Draw(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
C3DParticle * C3DParticle::Create(PARTICLE_OFFSET_ID OffsetID, CONST D3DXVECTOR3 origin)
{
	// �ϐ��錾
	C3DParticle *p3DParticle = new C3DParticle;
	// �V�[���Ǘ��ݒ�
	p3DParticle->ManageSetting(CScene::LAYER_3DPARTICLE);
	// �ݒ�
	p3DParticle->SetParticle(OffsetID);
	p3DParticle->SetOrigin(origin);
	return p3DParticle;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �p�[�e�B�N���̐ݒ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::SetParticle(PARTICLE_OFFSET_ID OffsetID)
{
	m_offsetID = OffsetID;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT C3DParticle::Load(void)
{
	// �ϐ��錾
	FILE *pFile = NULL;				// �t�@�C���̃|�C���^
	char cRead[128];				// �ǂݍ��ݗp
	char cComp[128];				// ��r�p
	char cEmpty[128];				// �v��Ȃ����̗p
	int nCntError = 0;				// �G���[�p
	int nCntOffset = 0;				// �I�t�Z�b�g�̃J�E���g
	
	// �ꎞ�ۑ��p
	// �t�@�C�����J����Ă��Ȃ�������
	if ((pFile = fopen("data/LOAD/ParticleInfo.txt", "r")) == NULL)
	{
		CCalculation::Messanger("data/LOAD/ParticleInfo.txt�̃e�L�X�g������܂���");
		return E_FAIL;
	}

	while (strcmp(cComp, "SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			CCalculation::Messanger("�X�N���v�g������܂���");
			return E_FAIL;
		}
	}

	while (strcmp(cComp, "END_SCRIPT") != 0)
	{// END_SCRIPT�܂Ń��[�v
	 // 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			fclose(pFile);
			CCalculation::Messanger("�G���h�X�N���v�g������܂���");
			return E_FAIL;
		}
		else if (strcmp(cComp, "OFFSET") == 0)
		{
			while (strcmp(cComp, "END_OFFSET") != 0)
			{
				// 1�s�ǂݍ���
				fgets(cRead, sizeof(cRead), pFile);
				// �ǂݍ���Ǖ�������
				sscanf(cRead, "%s", &cComp);
				if (strcmp(cComp, "IF") == 0)
				{
					// �ǂݍ���Ǖ�������
					sscanf(cRead, "%s %s", &cEmpty, &cComp);
					/* �ʒu�����_�� */
					if (strcmp(cComp, "POSRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty , &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);

								if (strcmp(cComp, "POSX") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty,
										&m_ParticleOffset[nCntOffset].PosXRand.nMax,
										&m_ParticleOffset[nCntOffset].PosXRand.nMin
									);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "POSY") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty,
										&m_ParticleOffset[nCntOffset].PosYRand.nMax,
										&m_ParticleOffset[nCntOffset].PosYRand.nMin
									);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "POSZ") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty,
										&m_ParticleOffset[nCntOffset].PosZRand.nMax,
										&m_ParticleOffset[nCntOffset].PosZRand.nMin
									);
									// ������̏�����
									cComp[0] = '\0';
									cRead[0] = '\0';
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					/* �F�����_�� */
					else if (strcmp(cComp, "COLRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							// ������
							m_ParticleOffset[nCntOffset].Col.r = 1.0f;
							m_ParticleOffset[nCntOffset].Col.g = 1.0f;
							m_ParticleOffset[nCntOffset].Col.b = 1.0f;
							m_ParticleOffset[nCntOffset].Col.a = 1.0f;

							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "RED") == 0)
								{
									// �����_����Ԃ�
									m_ParticleOffset[nCntOffset].bRedRand = true;
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "GREEN") == 0)
								{
									// �����_����Ԃ�
									m_ParticleOffset[nCntOffset].bGreenRand = true;
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "BLUE") == 0)
								{
									// �����_����Ԃ�
									m_ParticleOffset[nCntOffset].bBlueRand = true;
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "ALPHA") == 0)
								{
									// �����_����Ԃ�
									m_ParticleOffset[nCntOffset].bAlphaRand = true;
									// ������̏�����
									cComp[0] = '\0';
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "SIZERAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);

								if (strcmp(cComp, "SIZEX") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].SizeXRand.nMax, &m_ParticleOffset[nCntOffset].SizeXRand.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "SIZEY") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].SizeYRand.nMax, &m_ParticleOffset[nCntOffset].SizeYRand.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "ANGLERAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nAngleRand.nMax);
									// ������̏�����
									cComp[0] = '\0';

								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nAngleRand.nMin);
									// ������̏�����
									cComp[0] = '\0';

								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "SPEEDRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nSpeedRand.nMax);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nSpeedRand.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "LIFERAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nLifeRand.nMax);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_ParticleOffset[nCntOffset].nLifeRand.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
				}
				else if (strcmp(cComp, "POS") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].Pos.x,
							&m_ParticleOffset[nCntOffset].Pos.y,
							&m_ParticleOffset[nCntOffset].Pos.z);
					}

					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "ANGLE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].Rot.x,
							&m_ParticleOffset[nCntOffset].Rot.y,
							&m_ParticleOffset[nCntOffset].Rot.z);
					}

					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "COL") == 0)
				{
					// ������̏�����
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

					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "SIZE") == 0)
				{
					// ������̏�����
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
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "SPEED") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].fSpeed);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "LIFE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nLife);
					}
					// ������̏�����
					cComp[0] = '\0';
				}

				else if (strcmp(cComp, "FRAME") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nFrame);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "NUMBER") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nNumber);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "TEXTYPE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nEffeTexType);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "EFFETYPE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nEffeType);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "PARTICLETYPE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].type);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
			}
			// �I�t�Z�b�g�J�E���g��i�߂�
			nCntOffset++;
		}
	}
	fclose(pFile);
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �J��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Unload(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���_�ʒu�̐ݒ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::SetOrigin(CONST D3DXVECTOR3 & Origin)
{
	m_Origin = Origin;
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O�\��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void C3DParticle::Debug(void)
{
}
#endif // _DEBUG