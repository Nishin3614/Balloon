// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �L�����N�^�[���� [character.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "model.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O���錾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CExtrusion;
class CMeshobit;
class CCollision;
class CStencilshadow;
class CBalloon;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �\����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCharacter : public CScene
{
public:
	/* �񋓌^ */
	// �X�e�[�^�X
	typedef enum
	{
		STATE_NORMAL = 0,
	} STATE;
	// ��{���[�V�����^�C�v
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@���[�V����
		MOTIONTYPE_MOVE,			// �ړ����[�V����
		MOTIONTYPE_DAMAGEACTION,	// �_���[�W���[�V����
		MOTIONTYPE_DOWNACTION,		// �_�E�����[�V����
		MOTIONTYPE_STANDUP,			// �N���オ�郂�[�V����
		MOTIONTYPE_MAX
	} MOTIONTYPE;
	// �L�����N�^�[
	typedef enum
	{
		CHARACTER_PLAYER = 0,
		CHARACTER_SOLIDER,
		CHARACTER_MAX
	} CHARACTER;
	/* �\���� */
	/* �֐� */
	CCharacter();
	~CCharacter();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// �L�����N�^�[�����񂾂Ƃ�
	virtual void Die(void) = 0;


	// �K�v�ɉ��������� //
	// �ݒ� //
	// �ʒu
	void SetPos(D3DXVECTOR3 const &pos)				{ m_pos = pos; };			
	// �ړ���
	void SetMove(D3DXVECTOR3 const &move)			{ m_move = move; };
	// ��]
	void SetRot(D3DXVECTOR3 const &rot)				{ m_rot = rot; };
	// �擾 //
	// �ʒu
	D3DXVECTOR3 &GetPos(void)						{ return m_pos; };
	// �ړ���
	D3DXVECTOR3 &GetMove(void)						{ return m_move; };
	// ��]
	D3DXVECTOR3 &GetRot(void)						{ return m_rot; };
	// �e�Ǝq�̉�]��
	D3DXVECTOR3 *GetPartsRot(int const nModelID);
	// �e�Ǝq�̈ʒu
	D3DXVECTOR3 * GetPartsPos(int const nModelID);
	// �e�Ǝq�̍s��
	D3DXMATRIX *GetMatrix(int const nModelID);	
	// ���
	STATE GetState(void) const						{ return m_State; };
	// �L�����N�^�[
	CHARACTER	GetCharacter(void) const			{ return m_character; };
	// ���̍���
	bool GetFloorHeight(void);
	// ���[�V�����̃t���[�����擾����
	int GetMaxFrame(
		CHARACTER character,					// �L�����N�^�[
		int nMotionID,							// ���[�V����ID
		int nNowKeyCnt = -1						// ���݂̃L�[�J�E���g
	);												
	// �J�����ǔ����Ă���ID
	static int GetCameraCharacter(void);
	// ���[�h�E�A�����[�h
	static void Load(
		CHARACTER const character,		// �L�����N�^�[
		int const nMaxMotion,			// �ő僂�[�V����
		const char * file_name			// �t�@�C����
		);
	// �X�e�[�^�X���
	static HRESULT LoadStatus(void);
	static void UnLoad(
		CHARACTER const character,		// �L�����N�^�[
		int const nMaxkey				// �ő�L�[
		);	
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	CCollision * GetCollision(void) { return m_pCharacterCollision.get(); };
protected:
	/* �֐� */
	// �ݒ� //
	// �L�����N�^�[
	void SetCharacter(CHARACTER const character)	{ m_character = character; };
	// ���[�V�����ݒ�
	void SetMotion(int const nMotiontype);
	// �������[�V�����ݒ�
	void ComplusionSetMotion(int const nMotiontype);
		
	void FagGravity(void);						// �d��
	// �ڕW��]�ʐݒ�
	void SetRotDest(D3DXVECTOR3 const &rotDest)		{ m_rotLast = rotDest; };	
	// �ݒ� //
	// ���݂̃��[�V����
	int GetMotion(void) const						{ return m_nMotiontype; };
	// �ߋ��̃��[�V����
	int GetOldMotion(void) const					{ return m_nMotiontypeOld; };
	// �L�[�J�E���g
	int GetKeyInfoCnt(void) const					{ return m_keyinfoCnt; };
	// �ڕW��]�ʎ擾
	D3DXVECTOR3 GetRotDest(void) const				{ return m_rotLast; };	

	// ���[�V�����J�����̍X�V
	void MotionCamera(void);							
	/* �ϐ� */
	static int	m_nCameraCharacter;						// �L�����N�^�[�ɒǔ�����ID
	// ��
	STATE m_State;										// ����̃X�e�[�^�X
	int	m_nCntState;									// �J�E���g�X�e�[�^�X
private:
	/* �֐� */
	void Update_Normal(void);							// �ʏ펞�̍X�V
	void NextKeyMotion(void);							// ���̃��[�V����
	void Move(void);									// �ړ�
	void Motion(void);									// ���[�V����
	void ModelUpdate(void);								// ���f���̍X�V
	void TrackCamera(void);								// �J�����ǔ�
	void Limit(void);									// �������
	void Motion_Effect(void);							// ���[�V�����G�t�F�N�g		
	void Motion_Obit(void);								// ���[�V�����O��
	/* �ϐ� */
	/* �\���̂̃X�^�e�B�b�N�ɂ��� */
	static MODEL_ALL				*m_modelAll[CHARACTER_MAX];		// ���f���S�̂̏��
	static vector<int>				m_modelId[CHARACTER_MAX];		// ���f���ԍ�
	static CModel_info				*m_model_info[CHARACTER_MAX];	// ���f�����
	static D3DXVECTOR3				m_CharacterSize[CHARACTER_MAX];	// �L�����N�^�[�̃T�C�Y
	static int						m_NumModel[CHARACTER_MAX];		// �ő僂�f����
	static int						m_NumParts[CHARACTER_MAX];		// ���������f����
	CMeshobit						*m_pMeshobit;					// �O��
	CModel 							*m_pModel;						// ���f��
	CHARACTER						m_character;					// �L�����N�^�[
	D3DXMATRIX						m_mtxWorld;						// �s��
	D3DXVECTOR3						m_pos;							// �ʒu
	D3DXVECTOR3						m_posold;						// �O�̈ʒu
	D3DXVECTOR3						m_move;							// �ړ���
	D3DXVECTOR3						m_rot;							// ���݉�]��
	D3DXVECTOR3						m_rotLast;						// ������������
	D3DXVECTOR3						m_rotbetween;					// ��]�̍���
	D3DXVECTOR3						m_size;							// �L�����N�^�[�̃T�C�Y
	int								m_nMotiontype;					// ���[�V�����^�C�v
	int								m_nMotiontypeOld;				// �O��̃��[�V�����^�C�v
	int								m_nMaxMotion;					// �ő僂�[�V������
	int								m_keyinfoCnt;					// �L�[���̃J�E���g
	int								m_nFrame;						// �t���[���J�E���g
	int								m_nMotionFrame;					// ��̃��[�V�����̃J�E���g
	int								m_nIdAttackKey;					// �U���p�̃L�[ID
	int								m_nIDWho;						// �G��������
	float							m_fLength;						// �U���̓�����͈�
	float							m_fAlpha;						// �A���t�@�l
	bool							m_bMotionCamera;				// ���[�V�����J�����̐؂�ւ�ON�EOFF
	unique_ptr<CCollision>			m_pCharacterCollision;			// �L�����N�^�[�̓����蔻��
	vector<unique_ptr<CCollision>>	m_vec_AttackCollision;			// �U�������蔻��
	vector<unique_ptr<CMeshobit>>	m_vec_pMeshObit;				// ���
	CStencilshadow					* m_pStencilshadow;				// �X�e���V���V���h�E
	CBalloon						* m_pBalloon;					// ���D
};

#endif