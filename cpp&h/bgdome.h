// ----------------------------------------
//
// �o�b�O�O���E���h�h�[�������̐���[bgdome.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _BGDOME_H_
#define _BGDOME_H_	 // �t�@�C������������߂�

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
class CMeshdome;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CBgdome : public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		TYPE_BG = 0,
		TYPE_STAR,
		TYPE_MAX
	} TYPE;
	/* �֐� */
	CBgdome();
	~CBgdome();
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
	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBgdome * Create(D3DXVECTOR3 const &pos);	// �쐬
	void SetUse(bool bUse);						// �g�p���
	void SetPos(D3DXVECTOR3 const &pos);			// �ʒu
	void SetRot(D3DXVECTOR3 const &rot);			// ��]
	void Set(
		D3DXVECTOR3 const &pos,
		D3DXVECTOR3 const &rot,
		int const &nFrame
	);
protected:

private:
	/* �ϐ� */
	CMeshdome	*m_aMeshdome[TYPE_MAX];	// ���b�V���h�[��
	bool		m_bUse;					// �g�p���
	int			m_CntFrame;				// �J�E���g�t���[��
	int			m_nMaxFrame;			// �ő�t���[��
	D3DXVECTOR3			m_pos;					// �ʒu
};

#endif