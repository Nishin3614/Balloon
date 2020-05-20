// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �J�������� [camera.h]
// Author : KOKI_NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "main.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O���錾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCamera_info_bg;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCamera
{
public:
	/* �񋓌^ */
	typedef enum
	{
		TYPE_FOLLOW = 0,
		TYPE_TITLEBEFORE,
		TYPE_TITLEAFTER,
		TYPE_EVENTPERFOM,
		TYPE_STATICTIS,
		TYPE_GAMECLEAR,
		TYPE_GAMEDIED,
		TYPE_RANKING,
		TYPE_MAX
	} TYPE;
	/* �\���� */
	// �ǂݍ��ݗp
	typedef struct
	{
		D3DXVECTOR3 rot;	// ��]��
		D3DXVECTOR3 offset;	// �����_�̃I�t�Z�b�g
		float fLengh;		// �����_�Ǝ��_�̒���
		float fHeight;		// �����_�Ǝ��_�̍���
		int nType;			// �^�C�v
	} LOAD;
	/* �֐� */
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG

	static CCamera * Create(void);	// �쐬
	// �ǂݍ���
	static HRESULT Load(void);
	// �j��
	static void Unload(void);
	// �J�����̏�񏉊���
	void InfoInit(
		D3DXVECTOR3 const &pos,	// �ʒu���
		D3DXVECTOR3 const &rot	// ��]���
		);
	// �J�������̐ݒ�擾
	bool GetCamera_infoSet(void)  const { return m_bSet; };
	// �J�����ݒ�
	void Set(void);
	// �ړI�����_�̐ݒ�
	void SetPosDestR(
		D3DXVECTOR3 const & pos,	// �ʒu��� 
		D3DXVECTOR3 const & rot		// ��]��� 
	);
	void SetPosDestRPlayer(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot);
	// �����_�̐ݒ�
	void SetPosR(
		D3DXVECTOR3 const & pos,	// �ʒu��� 
		D3DXVECTOR3 const & rot		// ��]��� 
	);
	// �J�������ݒ�̎g�p��Ԑݒ�
	void SetCamera_InfoSet(bool const &bSet) { m_bSet = bSet; };
	// �J�������[�V�����̐ݒ�
	void SetCamera_Motion(
		D3DXVECTOR3 const &posR,	// �����_�̈ʒu
		D3DXVECTOR3 const &rot,		// ��]
		float const & fLength,		// ����
		float const & fHeight,		// ����
		float const & fIntertia		// �����̔䗦
	);
	// �J�������o�̐ݒ�
	void SetCamera_Perfom(
		D3DXVECTOR3 const &posR,	// �����_�̈ʒu
		D3DXVECTOR3 const &rot,		// ��]
		float const & fLength,		// ����
		float const & fHeight		// ����
	);
	// �J�����^�C�v�̐ݒ�
	void SetType(
		TYPE type
	);

	// �J�������̕ύX
	static void ChangeInfo(void);
	// ��]���擾
	D3DXVECTOR3 GetRot(void);
	// ��]�X�s�[�h�擾
	D3DXVECTOR2 &GetRotSpeed(void);
	// �J�����ݒ肷�ׂĂ̏�����
	void SetCameraInfo(void);
	// �J�����̎��_�擾
	D3DXVECTOR3 &GetPosV(void) { return m_posV; };
protected:

private:
	/* �֐� */
	void Update_Play(void);						// �v���C���̃J����
	void Perfom_Normal(void);					// �ʏ��Ԃ̃J�������o
	void Rot(void);								// ��]����
	/* �ϐ� */
	static	LOAD	m_load[TYPE_MAX];			// ���ۑ�
	D3DXVECTOR3		m_posV;						// ���_
	D3DXVECTOR3		m_posVDest;					// �ړI���_
	D3DXVECTOR3		m_posVDiff;					// �ړI���_���王�_
	D3DXVECTOR3		m_posR;						// �����_
	D3DXVECTOR3		m_posRDest;					// �ڕW�����_
	D3DXVECTOR3		m_posRDiff;					// �ړI�����_���璍���_
	D3DXVECTOR3		m_posU;						// ������x�N�g��
	D3DXVECTOR3		m_between;					// �v���C���[�Ƃ̋��� 
	D3DXVECTOR3		m_last;						// 
	D3DXVECTOR3		m_move;						// �ړ���
	D3DXVECTOR3		m_rot;						// ���_�̉�]��
	D3DXVECTOR3		m_rotDest;					// ���_�̖ړI��]�n�_
	D3DXVECTOR3		m_rotDiff;					// �ړI��]�n�_���猻�݉�]�n�_
	D3DXVECTOR3		m_rotBetween;				// �ړI��]�n�_�ƌ��݉�]�n�_�̍���
	D3DXVECTOR3		m_rotOrigin;				// ���̉�]��
	D3DXMATRIX		m_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X(�e���r���_)
	D3DXMATRIX		m_mtxView;					// �r���[�}�g���b�N�X(�J�����}�����_)
	D3DXVECTOR2		m_RotSpeed;					// ��]�X�s�[�h
	TYPE			m_type;						// �^�C�v[
	float			m_fHeight;					// �����_����̎��_�̍���
	float			m_fLength;					// ���_�ƒ����_�̋���
	float			m_fIntertia;				// �����̔䗦
	bool			m_bSet;						// �J�����ݒ�
};

#endif