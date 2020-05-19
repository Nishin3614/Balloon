// ----------------------------------------
//
// �������̐���[floor.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _FLOOR_H_
#define _FLOOR_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------


// ----------------------------------------
//
// �O���錾
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CFloor : public CScene
{
public:
	/* �֐� */
	CFloor();
	~CFloor();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG

	static HRESULT Load(void);
	static void UnLoad(void);
	static CFloor * Create(		// �쐬
		D3DXVECTOR3 const &pos,
		D3DXVECTOR3 const & size,
		D3DXVECTOR3 const & rot,
		int const & nWidth,
		int const & nDepth,
		int const & nTexType
	);
	float GetHeight(D3DXVECTOR3 &pos);								// �����擾

protected:

private:
	/* �֐� */
	/* �ϐ� */
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIndex;					// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_OriginBlock;							// �����z�u
	D3DXMATRIX  m_mtxWorld;								// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXVECTOR3 m_rot;									// �p�x
	int	m_nNumberVertex;								// �����_��
	int m_nNumIndex;									// ���C���f�b�N�X
	int m_nNumPolygon;									// ���|���S��
	int m_nBlock_Depth;									// �c�u���b�N��
	int m_nBlock_Width;									// ���u���b�N��
	int m_nTexType;										// �e�N�X�`���[�^�C�v
};

#endif