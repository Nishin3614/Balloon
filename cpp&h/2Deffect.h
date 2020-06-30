// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 2D�G�t�F�N�g�̏���[effect.h]
// Author : Nishiyama koki
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _2DEFFECT_H_
#define _2DEFFECT_H_

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �}�N����`
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define EFFECT_MAX			(5000)						// �ő吔
#define EFFECT_NUM_VERTEX	(4)							// ���_��

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X��`
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CRenderer;
class C2DEffect :public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		EFFECT_TYPE_NONE = -1,	// �Ȃ�
		EFFECT_TYPE_EXPLOSION,	// ����
		EFFECT_TYPE_SPARK,		// �Ή�
		EFFECT_TYPE_SMOKE,		// ��
		EFFECT_TYPE_LINE,		// ��
		EFFECT_TYPE_MAX			// �ő吔
	} EFFECT_TYPE;

	/* �\���� */
	// �G�t�F�N�g�v���~�e�B�u
	typedef struct
	{
		D3DXVECTOR3		pos;			// �ʒu
		D3DXVECTOR3		rot;			// ��]��
		D3DXVECTOR3		move;			// �ړ���
		D3DXCOLOR		col;			// �F
		D3DXVECTOR2		size;			// �T�C�Y
		D3DXVECTOR2		sizeValue;		// �T�C�Y�̕ω��l
		float			fAngle;			// �p�x
		float			fAlphaValue;	// �A���t�@�l�̕ω��l
		int				nLife;			// ��������
		int				nTexType;		// �e�N�X�`���̎��
		bool			bUse;			// �g�p���Ă��邩�ǂ���
		EFFECT_TYPE		EffectType;		// �G�t�F�N�g�̎��
	} EFFECT;

	/* �֐� */
	C2DEffect();
	~C2DEffect();
	static HRESULT Load(void);
	static void Unload(void);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static C2DEffect *Create(void);
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
	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return NULL; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	// ������
	void InitValues(void);
	// ���_�쐬
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	// ���_�T�C�Y�ݒ�
	static void SetVartexSize(
		VERTEX_2D *pVtx,
		EFFECT *pEffect = NULL,
		const int *nIndex = NULL
	);
	// ���_�J���[�ݒ�
	static void SetVetexColor(
		VERTEX_2D *pVtx,
		EFFECT *pEffect = NULL, 
		const int *nIndex = NULL
	);
	// ����
	void Delete(int nCntIndex);
	// �S�̂̐ݒ�
	static void Set2DEffect(
		EFFECT_TYPE EffectType,
		int nTexType,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		D3DXVECTOR3 move,
		D3DXCOLOR col,
		D3DXVECTOR2 size,
		int nLife,
		D3DXVECTOR2 sizeValue = D3DVECTOR2_ZERO
	);
private:
	/* �֐� */
	// �e�N�X�`���[�̓ǂݍ���
	static HRESULT LoadTextureFile(void);
	bool UpdateLife(VERTEX_2D *pVtx, EFFECT *pEffect);
	bool UpdateVetex(VERTEX_2D *pVtx, EFFECT *pEffect);
	void UpdateMove(VERTEX_2D *pVtx, EFFECT *pEffect);

	/* �����o�ϐ� */
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;					// �o�b�t�@���
	static int						m_nTexId[EFFECT_TYPE_MAX];	// �e�N�X�`���[ID
	static EFFECT					m_aEffect[EFFECT_MAX];		// �G�t�F�N�g���
	static int						m_nNumTextureMax;			// �e�N�X�`���̍ő吔
};

#endif