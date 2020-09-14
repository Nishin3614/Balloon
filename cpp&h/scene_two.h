// ----------------------------------------
//
// 2D�V�[�������̐���[scene_two.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _SCENE_TWO_H_
#define _SCENE_TWO_H_	 // �t�@�C������������߂�

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

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CScene_TWO : public CScene
{
public:
	/* �񋓌^ */
	// �I�t�Z�b�g
	typedef enum
	{
		OFFSET_TYPE_CENTER = 0,
		OFFSET_TYPE_LEFT,
		OFFSET_TYPE_MAX
	} OFFSET_TYPE;
	/* �֐� */
	CScene_TWO();
	~CScene_TWO();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// ����������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// ����ɓ��Ă�ꂽ��̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// �������瓖����Ȃ�������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_NoMyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// ����ɓ��Ă��Ȃ�������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_NoOpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};

	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	// ���_���W�ݒ�
	void Set_Vtx_Pos(
		OFFSET_TYPE const &offsettype = OFFSET_TYPE_CENTER,			// �I�t�Z�b�g�^�C�v
		VERTEX_2D * pVtx = NULL										// ���_���
	);
	// ���_�J���[�ݒ�
	void Set_Vtx_Col(VERTEX_2D * pVtx = NULL);
	// ���_�J���[�ݒ�(�E�̐F�ƍ��̐F)
	void Set_Vtx_Col2(
		D3DXCOLOR const &col_r,		// �E�̐F
		D3DXCOLOR const &col_l,		// ���̐F
		VERTEX_2D * pVtx = NULL);	// 2D���_���
									// ���_�J���[�ݒ�(��̐F�Ɖ��̐F)
	void Set_Vtx_Col3(
		D3DXCOLOR const &col_o,		// ��̐F
		D3DXCOLOR const &col_u,		// ���̐F
		VERTEX_2D * pVtx = NULL);	// 2D���_���
	// �I�t�Z�b�g�ݒ�
	void SetOffset(OFFSET_TYPE const &type) { m_offsetType = type; };
	// �T�C�Y�ݒ�
	void SetSize(D3DXVECTOR2 const &size) { m_size = size; };
	// �ʒu�ݒ�
	void SetPosition(D3DXVECTOR3 const &pos) { m_pos = pos; };
	// �p�x�ݒ�
	void SetRot(float const &frot) { m_rot = frot; };
	// �F�ݒ�
	void SetCol(
		D3DXCOLOR const &col) { m_col = col; };
	// �e�N�X�`���[�ݒ�
	void SetTex(
		D3DXVECTOR2 const &first = D3DXVECTOR2(0.0f,0.0f),			// �����̔z�u
		D3DXVECTOR2 const &last = D3DXVECTOR2(1.0f, 1.0f)			// �Ō�̔z�u
	);
	void SetAnimation(float fTexX, float fTexY, float fTexY2, int nPatternAnim);					// �A�j���[�V�����̐ݒ�
																									// �e�N�X�`���[�ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 const &p_Tex) { m_pTexture = p_Tex; };
	// �T�C�Y�擾
	D3DXVECTOR2 const GetSize(void) { return m_size; };
	// �ʒu�擾
	D3DXVECTOR3 const GetPosition(void) { return m_pos; };
	// �F�擾
	D3DXCOLOR const GetCol(void) { return m_col; };
	// �p�x�擾
	float const GetRot(void) { return m_rot; };
	// �����擾
	float const GetLengh(void) { return m_fLengh; };

	// �쐬(�V�[���p������)
	static CScene_TWO * Create(
		OFFSET_TYPE	const & type,									// �^�C�v
		D3DXVECTOR3 const & pos,									// �ʒu
		D3DXVECTOR2 const & size,									// �T�C�Y
		float		const & frot = 0.0f,							// �p�x
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),	// �F
		CScene::LAYER	const & layer = CScene::LAYER_UI			// ���C���[
	);
	// �쐬(�V�[���p���Ȃ�)
	static CScene_TWO * Create_Self(
		OFFSET_TYPE	const & type,									// �^�C�v
		D3DXVECTOR3 const & pos,									// �ʒu
		D3DXVECTOR2 const & size,									// �T�C�Y
		float		const & frot = 0.0f,							// �p�x
		D3DXCOLOR	const & col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// �F
	);
	// unique_ptr�쐬(�V�[���p���Ȃ�)
	static std::unique_ptr<CScene_TWO> Creat_Unique(
		OFFSET_TYPE const & type,
		D3DXVECTOR3 const & pos,
		D3DXVECTOR2 const & size,
		float const & frot,
		D3DXCOLOR const & col
	);

protected:
	// �ݒ� //
private:
	/* �񋓌^ */

	/* �\���� */
	/* �֐� */
	void Offset_Center(VERTEX_2D *pVtx);	// �I�t�Z�b�g���Z���^�[
	void Offset_Left(VERTEX_2D *pVtx);		// �I�t�Z�b�g����

	/* �ϐ� */
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// ���S���W
	D3DXVECTOR2 m_size;						// �T�C�Y
	D3DXCOLOR	m_col;						// �J���[
	OFFSET_TYPE	m_offsetType;				// �I�t�Z�b�g�^�C�v
	float m_rot;							// �p�x
	float m_fLengh;							// ����
	float m_fAngle;							// �p�x
};

#endif