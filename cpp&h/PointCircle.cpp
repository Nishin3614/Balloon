// ==========================================================
//
// �|�C���g�T�[�N��[PointCircle.cpp]
// Author : masayasu wakita
//
// ==========================================================
#include "PointCircle.h"
#include "meshdome.h"
#include "character.h"
#include "player.h"
#include "game.h"
#include "3Dparticle.h"
#include "item.h"
#include "score.h"

// ==========================================================
//
// �}�N����`
//
// ==========================================================
#define COUNT_DRAW (600)
#define RELEASE_DRAW (1200)

// ==========================================================
//
// �ÓI�ϐ�������
//
// ==========================================================
int CPointCircle::m_nAllPointCircle = 0;
bool CPointCircle::m_bPoint = false;

// ==========================================================
//
// �R���X�g���N�^
//
// ==========================================================
CPointCircle::CPointCircle() : CScene_THREE()
{
	m_nAllPointCircle++;
}

// ==========================================================
//
// �f�X�g���N�^
//
// ==========================================================
CPointCircle::~CPointCircle()
{
	m_nAllPointCircle--;
}

// ==========================================================
// ������
// ==========================================================
void CPointCircle::Init(void)
{
	// �I�t�Z�b�g�^�C�v�ݒ�
	CScene_THREE::SetOffsetType(OFFSET_TYPE_VERTICAL_CENTER);
	// �F�̐ݒ�
	CScene_THREE::SetCol(D3DXCOLOR_CA(1.0f, 1.0f));
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	// �r���{�[�h
	CScene_THREE::SetBillboard(true);
	CScene_THREE::SetLighting(true);		// ���C�e�B���O
											// �e�N�X�`���[�^�C�v�ݒ�
	CScene_THREE::SetTexType(23);			// �e�N�X�`���[�n��
											// �e�N�X�`������
	CScene_THREE::SetTex(D3DXVECTOR2(ANIM_TEX * 5, 0.0f), D3DXVECTOR2(ANIM_TEX + ANIM_TEX * 5, 1.0f));
	// �͈�
	m_fDistance = MAX_DISTANCE;
	// �A�j���[�V�����J�E���^�[������
	m_nCounterAnim = 0;
	// �A�j���[�V�����p�^�[��������
	m_nPatternAnim = 0;
	// ���̃J�E���g������
	m_nCntPoint = 0;
	// ���̕`��J�E���g������
	m_nCntDraw = 0;
	// ���̏�Ԃ�������
	m_bThunder = true;
	// �|�W�V�����擾
	m_pos = GetPos();
	// ���b�V���h�[���̐���
	m_pMeshDome = CMeshdome::Create(
		D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
		D3DXVECTOR3(MAX_DISTANCE, MAX_DISTANCE_Y, MAX_DISTANCE),
		10,
		10,
		CMeshdome::TYPE_POINTCIRCLE,
		D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		false,
		LAYER_DOME);

	// ���b�V���h�[���̎g�p���
	m_pMeshDome->SetUse(true);
}

// ==========================================================
// �I��
// ==========================================================
void CPointCircle::Uninit(void)
{
	if (m_pMeshDome != NULL)
	{
		m_pMeshDome->Release();
		m_pMeshDome = NULL;
	}
	CScene_THREE::Uninit();
}

// ==========================================================
// �X�V
// ==========================================================
void CPointCircle::Update(void)
{
	CScene_THREE::Update();


	// �����v�Z�p
	float fX_Difference;
	float fZ_Difference;
	float fDifference;
	// �e�N�X�`������
	//CScene_THREE::SetTex(D3DXVECTOR2(1.0f / 6.0f * 5, 0.0f), D3DXVECTOR2(1.0f / 6.0f + 1.0f / 6.0f * 5, 1.0f));

	// �J�E���^�[���Z
	m_nCounterAnim++;
	m_nCntDraw++;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �L�����N�^�[�ւ̃|�C���^
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			// �L�����N�^�[�̃|�W�V�����擾
			D3DXVECTOR3 charaPos = pPlayer->GetPos();

			// �O��̃|�W�V�����ݒ�
			m_posOld = m_pos;

			// �G�ƃv���C���[�̇]���W����
			fX_Difference = m_pos.x - charaPos.x;

			// �G�ƃv���C���[��Z���W����
			fZ_Difference = m_pos.z - charaPos.z;

			// �G�ƃv���C���[�̈�苗��
			fDifference = sqrtf(fX_Difference * fX_Difference + fZ_Difference * fZ_Difference);

			// �v���C���[����苗���ɋ߂Â�����
			if (fDifference < m_fDistance)
			{
				// �p�[�e�B�N������
				C3DParticle::Create(
					C3DParticle::PARTICLE_ID_CROSSLINE,
					charaPos
				);

				if (nCount == CManager::GetNetwork()->GetId())
				{
					if (m_nCntPoint > 60)
					{
						m_bPoint = true;
						//CManager::GetGame()->GetScore()->AddScore(CItem::GetStatus().nScorePoint);
						m_nCntPoint = 0;
					}
					else
					{
						m_bPoint = false;
						m_nCntPoint++;
					}
				}
			}
		}
	}

	if (m_nCntDraw >= RELEASE_DRAW)
	{
		if (m_pMeshDome != NULL)
		{
			// ���b�V���h�[���̎g�p���
			m_pMeshDome->SetUse(false);
			m_pMeshDome->Release();
			m_pMeshDome = NULL;
		}
		Release();
	}
}

// ==========================================================
// �`��
// ==========================================================
void CPointCircle::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	if (m_bThunder == false)
	{
		// �`��
		CScene_THREE::Draw();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	}
}

// ==========================================================
// ����
// ==========================================================
CPointCircle *CPointCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[�����I�Ɋm��
	CPointCircle *pPointCircle = new CPointCircle();

	if (pPointCircle != NULL)
	{
		// �ʒu�ݒ�
		pPointCircle->SetPos(pos);

		// �T�C�Y�ݒ�
		pPointCircle->SetSize(size);

		// �V�[��������
		pPointCircle->Init();

		pPointCircle->ManageSetting(LAYER_3DOBJECT2);

		return pPointCircle;
	}
	return NULL;
}

// ==========================================================
// �j��
// ==========================================================
void CPointCircle::Unload(void)
{
}