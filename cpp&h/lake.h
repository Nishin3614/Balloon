// ==========================================================
//
// ��[lake.h]
// Author : masayasu wakita
//
// ==========================================================
#ifndef _LAKE_H_
#define _LAKE_H_

#include "main.h"
#include "scene_three.h"

#define	TEXTURE_BULLET	"data/TEXTURE/coin.png"			// �ǂݍ��ރe�N�X�`���t�@�C����

// ==========================================================
//
// �N���X�̒�`
//
// ==========================================================
class CLake : public CScene_THREE
{
public:

	CLake();												// �R���X�g���N�^
	~CLake();												// �f�X�g���N�^

	void Init(void);										// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��

	static CLake *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����
	static HRESULT Load(void);													// ���[�h
	static void Unload(void);													// �A�����[�h

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *m_pVtx;							// ���_���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X

	D3DXVECTOR3	m_vtxMin;						// �ŏ��l
	D3DXVECTOR3	m_vtxMax;						// �ő�l
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ��]
	D3DXVECTOR3 m_move;							// �ړ���
	D3DXCOLOR m_col;							// �F
	float m_fAnim;								// �A�j���[�V�����ړ���
};
#endif