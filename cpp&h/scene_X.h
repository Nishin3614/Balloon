// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// X�V�[�������̐���[scene_X.h]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SCENE_X_H_
#define _SCENE_X_H_	 // �t�@�C������������߂�

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "model_info.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �O���錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCollision;
class CExtrusion;
class CScene_THREE;

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CScene_X : public CScene
{
public:
	/* �\���� */
	// ���f�����
	typedef struct MODEL_LOAD
	{
		// �R���X�g���N�^
		MODEL_LOAD()
		{
			pMesh = NULL;
			pBuffMat = NULL;
			nNumMat = 0;
			vtxMinMaterials = D3DVECTOR3_ZERO;
			vtxMaxMaterials = D3DVECTOR3_ZERO;
			size = D3DVECTOR3_ZERO;
		}
		LPD3DXMESH			pMesh;					// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER		pBuffMat;				// �}�e���A�����ւ̃|�C���^
		std::vector<LPDIRECT3DTEXTURE9> vec_pTexture;	// �e�N�X�`���[���
		DWORD				nNumMat;				// �}�e���A���̐�
		D3DXVECTOR3			vtxMinMaterials;		// ���f�����̈ʒu�̍ŏ��l
		D3DXVECTOR3			vtxMaxMaterials;		// ���f�����̈ʒu�̍ő�l
		D3DXVECTOR3			size;					// �T�C�Y
	} MODEL_LOAD;

	/* �֐� */
	CScene_X();
	~CScene_X();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// ����������̏���
	// ����1:�I�u�W�F�N�g�^�C�v
	// ����2:����̃V�[�����
	virtual void Scene_Collision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	)
	{};
	// �����蔻��������I�ɍ폜
	void CollisionDelete(void);
	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	// �쐬����(�V�[���Ǘ�)
	static CScene_X * Create(
		D3DXVECTOR3 const &pos,
		D3DXVECTOR3 const &rot = D3DVECTOR3_ZERO,
		int const &nModelId = 0,
		bool const &bShadowMap = false
	);
	// �쐬����(�l�Ǘ�)
	static CScene_X * Create_Self(
		D3DXVECTOR3 const &pos,
		D3DXVECTOR3 const &rot = D3DVECTOR3_ZERO,
		int const &nModelId = 0,
		bool const &bShadowMap = false
	);
	// �쐬����(�l�Ǘ�)
	static std::unique_ptr<CScene_X> Create_Uni(
		D3DXVECTOR3 const &pos,
		D3DXVECTOR3 const &rot = D3DVECTOR3_ZERO,
		int const &nModelId = 0,
		bool const &bShadowMap = false
	);

	// ���f�����̓ǂݍ���
	static HRESULT LoadModel(void);
	// ���f�����̊J��
	static HRESULT UnLoadModel(void);
	// �ݒ�
	void SetPos(D3DXVECTOR3 const &pos) { m_pos = pos; };						// �ʒu
	void SetRot(D3DXVECTOR3 const &rot) { m_rot = rot; };						// ��]
	void SetModelId(int const &nModelId) { m_nModelId = nModelId; };			// ���f���ԍ�
	void SetShadowMap(bool const &bShadow) { m_bShadowMap = bShadow; };			// ���f���ԍ�
	void SetCollision(void);													// �����蔻��
	void SetParentMtx(D3DXMATRIX * ParentMax) { m_pParentMtx = ParentMax; };	// �e�}�g���b�N�X�̐ݒ�
	// �����蔻��ݒ�
	// nShapeType:0:��`�A1:���A2:�~��
	// obj:�I�u�W�F�N�g�^�C�v
	// bPush:�����o������
	// pParent:�e���
	void SetCollision(
		int const &nShapeType,
		int const &obj,
		bool const &bPush = false,
		bool const &bOpponent = false,
		CScene * pParent = NULL
	);									// �����蔻��ݒ�

	// �擾
	CScene_X::MODEL_LOAD * GetModel(int const & nModelId);						// ���f�����擾
	D3DXVECTOR3 &GetPos(void) { return m_pos; };								// �ʒu
	D3DXVECTOR3 &GetRot(void) { return m_rot; };								// ��]
	D3DXMATRIX &GetMatrix(void) { return m_mtxWorld; };							// �}�g���b�N�X���
	// �����蔻���Ԏ擾
	bool const GetbCollision(void);													// �����蔻����
	// �����蔻��̏����擾
	CCollision * GetCollision(void);
	static MODEL_LOAD * GetModelLoad(int const &nModelId);						// ���f�����擾
protected:
private:
	/* �֐� */
	static void ModelSetting(MODEL_LOAD * pModel_load);
	/* �ϐ� */
	static std::vector<std::unique_ptr<MODEL_LOAD>> m_pModelLoad;	// ���f�����̓ǂݍ��ݗp

	D3DXVECTOR3		m_pos;								// �ʒu���
	D3DXVECTOR3		m_rot;								// ��]���
	D3DXMATRIX		*m_pParentMtx;						// �e�}�g���b�N�X
	D3DXMATRIX		m_mtxWorld;							// ���[���h�}�g���b�N�X
	int				m_nModelId;							// ���f���ԍ�
	bool			m_bShadowMap;						// �V���h�E�}�b�s���O�ɂ��邩���Ȃ���
	float			m_fModelAlpha;						// ���f���̃A���t�@�l
	float			m_fShadowAlpha;						// �e�̃��l
	CScene_THREE *	m_pShadow;							// �܂�e
	CExtrusion		*m_pExtrusion;						// �����o��
	CCollision		*m_Collision;						// �����蔻��
};

#endif