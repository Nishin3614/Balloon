// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �e�N�X�`���[�Ǘ����� [texture_manager.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "texture_manager.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N���錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TEXTURE_FILE "data/LOAD/TEXTURE/texture_manager.csv"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
vector<LPDIRECT3DTEXTURE9> CTexture_manager::m_st_vpTexture;

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CTexture_manager::CTexture_manager()
{

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CTexture_manager::~CTexture_manager()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �e�N�X�`���[���̊J��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CTexture_manager::UnLoad(void)
{
	// �s���Ƃɉ�
	for (int nCntLine = 0; nCntLine < (signed)m_st_vpTexture.size(); nCntLine++)
	{
		if (m_st_vpTexture[nCntLine] != NULL)
		{
			m_st_vpTexture[nCntLine]->Release();
			m_st_vpTexture[nCntLine] = NULL;
		}
	}
	// �e�N�X�`���[���̊J��
	vector<LPDIRECT3DTEXTURE9>().swap(m_st_vpTexture);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �e�N�X�`���[�ǂݍ���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CTexture_manager::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	LPDIRECT3DTEXTURE9 pTex = NULL;
	// �t�@�C���̒��g�i�[�p
	vector<vector<string>> vsvec_Contens;	
	// �t�@�C���̒��g���擾����
	vsvec_Contens = CCalculation::FileContens(TEXTURE_FILE, ',');
	// �s���Ƃɉ�
	for (int nCntLine = 0; nCntLine < (signed)vsvec_Contens.size(); nCntLine++)
	{
		// ���ڂ��Ƃɉ�
		for (int nCntItem = 0; nCntItem < (signed)vsvec_Contens.at(nCntLine).size(); nCntItem++)
		{
			switch (nCntItem)
			{
				// �p�X���
			case 0:
				// �e�N�X�`���[����
				D3DXCreateTextureFromFile(
					pDevice, 
					vsvec_Contens.at(nCntLine).at(nCntItem).c_str(),
					&pTex);
				// �e�N�X�`���[�ǉ�
				m_st_vpTexture.push_back(pTex);
				// �k���ɂ���
				pTex = NULL;
				break;
			default:
				break;
			}
		}
	}
	// vector�̑��d�z��J��
	vector<vector<string>>().swap(vsvec_Contens);
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �e�N�X�`���[�擾
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture_manager::GetTexture(int const & nTextureId)
{
	// �e�N�X�`���[�����
	if (nTextureId < (signed)m_st_vpTexture.size())
	{
		return m_st_vpTexture[nTextureId];
	}
	// �e�N�X�`���[����O�Ȃ�Ԃ�
	return NULL;
}