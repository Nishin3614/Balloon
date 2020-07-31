// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3D�p�[�e�B�N���̏���[3Dparticle.h]
// Author : Nishiyama Koki
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _3DPARTICLE_H_
#define _3DPARTICLE_H_

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �}�N����`
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X��`
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class C3DParticle :public CScene
{
public:
	/* �񋓌^ */
	// �G�t�F�N�g�^�C�v
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_CHARGE,
		TYPE_MAX,
	} TYPE;
	// �p�[�e�B�N���ԍ�
	typedef enum
	{
		PARTICLE_ID_NONE = -1,
		PARTICLE_ID_FIRE,				// ��
		PARTICLE_ID_TRICK_BEFORE_SHOCK,	// �鉜�`�O�̔g��
		PARTICLE_ID_TRICK1_FIRE,		// �Z�@�̃G�t�F�N�g
		PARTICLE_ID_SHOCK_SMOKE,		// ������т��ނ�
		PARTICLE_ID_ARROW_SMOKE,		// �|���ނ�
		PARTICLE_ID_SHOCKWAVE,			// �Ռ��g
		PARTICLE_ID_GET,				// �A�C�e���Q�b�g
		PARTICLE_ID_CROSSLINE,			// �N���X���C��
		PARTICLE_ID_WEAVELINE,			// �҂ݕ����C��
		PARTICLE_ID_RANDAMLINE,			// �����_�����C��
		PARTICLE_ID_CENTERRANDAMLINE,	// ���S�����_�����C��
		PARTICLE_ID_ONELINE,			// ����C��
		PARTICLE_ID_CONCENTLINE,		// �R�l�N�g���C��
		PARTICLE_ID_BALLOON,			// ���D
		PARTICLE_ID_MAX,
	} PARTICLE_ID;
	/* �\���� */
	// �p�[�e�B�N�����
	typedef struct PARTICLE_INFO
	{
		PARTICLE_INFO()
		{
			nFrame			= 0;				// �t���[������
			nNumber			= 0;				// �o����
			nEffectTexType	= 0;				// �G�t�F�N�g�̃e�N�X�`���̎��
			nEffectType		= 0;				// �G�t�F�N�g�̎��
			type = TYPE_NORMAL;					// ���(��Ɉړ���)
			/* �ʒu��� */
			Pos				= D3DVECTOR3_ZERO;	// �ʒu
			PosXRand		= INTEGER2(0,0);	// �ʒuX���W�����_���p
			PosYRand		= INTEGER2(0, 0);	// �ʒuY���W�����_���p
			PosZRand		= INTEGER2(0, 0);	// �ʒuY���W�����_���p
			/* �J���[��� */
			Col = D3DXCOLOR_INI;				// �F
			bRedRand		= false;			// �ԃ����_��
			bGreenRand		= false;			// �΃����_��
			bBlueRand		= false;			// �����_��
			bAlphaRand		= false;			// �����x�����_��
			/* �T�C�Y��� */
			Size = D3DVECTOR2_ZERO;				// �T�C�Y
			SizeXRand		= INTEGER2(0, 0);	// �T�C�Yx�����_���p
			SizeYRand		= INTEGER2(0, 0);	// �T�C�Yy�����_���p
			/* �p�x��� */
			Rot				= D3DVECTOR3_ZERO;	// ��]�[
			nAngleRand		= INTEGER2(0, 0);	// �p�x�̃����_���p
			/* ���x��� */
			fSpeed			= 0.0f;				// ���x
			nSpeedRand		= INTEGER2(0, 0);	// ���x�̃����_���p
			/* ���C�t��� */
			nLife			= 0;				// ���C�t
			nLifeRand		= INTEGER2(0, 0);	// ���C�t�̃����_���p
			/* �u�����h�^�C�v */
			Blend = CRenderer::BLEND_TRANSLUCENT;	// �u�����h�^�C�v
		}
		// �ϐ��錾
		int					nFrame;			// �t���[������
		int					nNumber;		// �o����
		int					nEffectTexType;	// �G�t�F�N�g�̃e�N�X�`���̎��
		int					nEffectType;	// �G�t�F�N�g�̎��
		C3DParticle::TYPE	type;			// ���(��Ɉړ���)
		/* �ʒu��� */
		D3DXVECTOR3			Pos;			// �ʒu
		INTEGER2			PosXRand;		// �ʒuX���W�����_���p
		INTEGER2			PosYRand;		// �ʒuY���W�����_���p
		INTEGER2			PosZRand;		// �ʒuY���W�����_���p
		/* �J���[��� */
		D3DXCOLOR			Col;			// �F
		bool				bRedRand;		// �ԃ����_��
		bool				bGreenRand;		// �΃����_��
		bool				bBlueRand;		// �����_��
		bool				bAlphaRand;		// �����x�����_��
		/* �T�C�Y��� */
		D3DXVECTOR2			Size;			// �T�C�Y
		INTEGER2			SizeXRand;		// �T�C�Yx�����_���p
		INTEGER2			SizeYRand;		// �T�C�Yy�����_���p
		/* �p�x��� */
		D3DXVECTOR3			Rot;			// ��]�[
		INTEGER2			nAngleRand;		// �p�x�̃����_���p
		/* ���x��� */
		float				fSpeed;			// ���x
		INTEGER2			nSpeedRand;		// ���x�̃����_���p
		/* ���C�t��� */
		int					nLife;			// ���C�t
		INTEGER2			nLifeRand;		// ���C�t�̃����_���p
		/* �u�����h�^�C�v */
		CRenderer::BLEND	Blend;			// �u�����h�^�C�v
	} PARTICLE_INFO;

	/* �֐� */
	// �R���X�g���N�^
	C3DParticle();
	// �f�X�g���N�^
	~C3DParticle();
	// ����������
	void Init(void);
	// �I������
	void Uninit(void);
	// �X�V����
	void Update(void);
	// �`�揈��
	void Draw(void);
#ifdef _DEBUG
	// �f�o�b�O����
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
	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_Origin; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	// ����
	//	ParticleId	: �p�[�e�B�N���ԍ�
	//	origin		: �����ʒu
	static C3DParticle * Create(
		PARTICLE_ID const	&ParticleId,	// �p�[�e�B�N���ԍ�
		D3DXVECTOR3 const	&origin,		// �����ʒu
		bool		const	&b2D = false	// 2D�`����
	);
	// �S���\�[�X���̓ǂݍ���
	static HRESULT Load(void);
	// �S���\�[�X���̊J��
	static void Unload(void);
	// �p�[�e�B�N���ԍ��ݒ�
	//	ParticleId	: �p�[�e�B�N���ԍ�
	void SetParticle(
		PARTICLE_ID const	&ParticleId	// �p�[�e�B�N���ԍ�
	);
	// �����ʒu�ݒ�
	//	origin	: �����ʒu
	void SetOrigin(
		D3DXVECTOR3 const	&origin		// �����ʒu
	);

private:
	/* �֐� */

	/* �ϐ� */
	static PARTICLE_INFO	*m_ParticleOffset[PARTICLE_ID_MAX];	// �p�[�e�B�N���̃I�t�Z�b�g
	PARTICLE_ID				m_offsetID;							// �I�t�Z�b�gID
	bool					m_b2D;								// 2D�`����
	int						m_nFrameCount;						// �t���[���̃J�E���g
	D3DXVECTOR3				m_Origin;							// ���_
};

#endif
