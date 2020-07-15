// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3D�p�[�e�B�N���̏���[particle.h]
// Author : Nishiyama koki
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _3DPARTICLE_H_
#define _3DPARTICLE_H_

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "Scene.h"

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
	// �����ݒ�
	typedef enum
	{
		OFFSET_ID_NONE = -1,
		OFFSET_ID_DIRT,				// �y��
		OFFSET_ID_FIRE,				// ��
		OFFSET_ID_TRICK1,			// �Z�@�̃G�t�F�N�g
		OFFSET_ID_AWAYSMOKE,		// ������т��ނ�
		OFFSET_ID_EXPLOSIONSMOKE,	// �������ނ�
		OFFSET_ID_SHOCKWAVE,		// �Ռ��g
		OFFSET_ID_GET,				//
		OFFSET_ID_SPARKS,			// �Ή�
		OFFSET_ID_STAR,				// ����
		OFFSET_ID_CROSSLINE,		// �N���X���C��
		OFFSET_ID_WEAVELINE,		// �҂ݕ����C��
		OFFSET_ID_RANDAMLINE,		// �����_�����C��
		OFFSET_ID_CENTERRANDAMLINE,	// ���S�����_�����C��
		OFFSET_ID_ONELINE,			// ����C��
		OFFSET_ID_CONCENTLINE,		// �R�l�N�g���C��
		OFFSET_ID_MAX,
	} PARTICLE_OFFSET_ID;
	/* �\���� */
	typedef struct PARTICLE_OFFSET
	{
		PARTICLE_OFFSET()
		{
			nFrame = 0;							// �t���[������
			nNumber = 0;						// �o����
			nEffeTexType = 0;					// �G�t�F�N�g�̃e�N�X�`���̎��
			nEffeType = 0;						// �G�t�F�N�g�̎��
			type = TYPE_NORMAL;					// ���(��Ɉړ���)
			/* �ʒu��� */
			Pos = D3DVECTOR3_ZERO;				// �ʒu�̃|�C���^
			PosXRand = INTEGER2(0,0);			// �ʒuX���W�����_���p�̃|�C���^
			PosYRand = INTEGER2(0, 0);			// �ʒuY���W�����_���p�̃|�C���^
			PosZRand = INTEGER2(0, 0);			// �ʒuY���W�����_���p�̃|�C���^
			/* �J���[��� */
			Col = D3DXCOLOR_INI;				// �F�̃|�C���^
			bRedRand = false;					// �ԃ����_��
			bGreenRand = false;					// �΃����_��
			bBlueRand = false;					// �����_��
			bAlphaRand = false;					// �����x�����_��
			/* �T�C�Y��� */
			Size = D3DVECTOR2_ZERO;				// �T�C�Y
			SizeXRand = INTEGER2(0, 0);			// �T�C�Yx�����_���p�̃|�C���^�[
			SizeYRand = INTEGER2(0, 0);			// �T�C�Yy�����_���p�̃|�C���^�[
			/* �p�x��� */
			Rot = D3DVECTOR3_ZERO;				// ��]�̃|�C���^�[
			nAngleRand = INTEGER2(0, 0);		// �p�x�̃����_���p�̃|�C���^
			/* ���x��� */
			fSpeed = 0.0f;						// ���x�̃|�C���^
			nSpeedRand = INTEGER2(0, 0);		// ���x�̃����_���p�̃|�C���^
			/* ���C�t��� */
			nLife = 0;							// ���C�t�̃|�C���^
			nLifeRand = INTEGER2(0, 0);			// ���C�t�̃����_���p�̃|�C���^
		}
		// �ϐ��錾
		int					nFrame;			// �t���[������
		int					nNumber;		// �o����
		int					nEffeTexType;	// �G�t�F�N�g�̃e�N�X�`���̎��
		int					nEffeType;		// �G�t�F�N�g�̎��
		C3DParticle::TYPE	type;			// ���(��Ɉړ���)
		/* �ʒu��� */
		D3DXVECTOR3			Pos;			// �ʒu�̃|�C���^
		INTEGER2			PosXRand;		// �ʒuX���W�����_���p�̃|�C���^
		INTEGER2			PosYRand;		// �ʒuY���W�����_���p�̃|�C���^
		INTEGER2			PosZRand;		// �ʒuY���W�����_���p�̃|�C���^
		/* �J���[��� */
		D3DXCOLOR			Col;			// �F�̃|�C���^
		bool				bRedRand;		// �ԃ����_��
		bool				bGreenRand;		// �΃����_��
		bool				bBlueRand;		// �����_��
		bool				bAlphaRand;		// �����x�����_��
		/* �T�C�Y��� */
		D3DXVECTOR2			Size;			// �T�C�Y
		INTEGER2			SizeXRand;		// �T�C�Yx�����_���p�̃|�C���^�[
		INTEGER2			SizeYRand;		// �T�C�Yy�����_���p�̃|�C���^�[
		/* �p�x��� */
		D3DXVECTOR3			Rot;			// ��]�̃|�C���^�[
		INTEGER2			nAngleRand;		// �p�x�̃����_���p�̃|�C���^
		/* ���x��� */
		float				fSpeed;			// ���x�̃|�C���^
		INTEGER2			nSpeedRand;		// ���x�̃����_���p�̃|�C���^
		/* ���C�t��� */
		int					nLife;			// ���C�t�̃|�C���^
		INTEGER2			nLifeRand;		// ���C�t�̃����_���p�̃|�C���^
	} PARTICLE_OFFSET;

	/* �֐� */
	C3DParticle();
	~C3DParticle();
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
	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return NULL; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	static C3DParticle * Create(PARTICLE_OFFSET_ID OffsetID, CONST D3DXVECTOR3 origin);
	static HRESULT Load(void);
	static void Unload(void);
	void SetParticle(PARTICLE_OFFSET_ID OffsetID);
	void SetOrigin(CONST D3DXVECTOR3 &Origin);

private:
	/* �֐� */
	/* �ϐ� */
	static PARTICLE_OFFSET	m_ParticleOffset[OFFSET_ID_MAX];	// �p�[�e�B�N���̃I�t�Z�b�g
	PARTICLE_OFFSET_ID		m_offsetID;							// �I�t�Z�b�gID
	int						m_nFlameCount;						// �t���[���̃J�E���g
	D3DXVECTOR3				m_Origin;							// ���_
};

#endif
