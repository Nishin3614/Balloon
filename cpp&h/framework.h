// ----------------------------------------
//
// �t���[�����[�N�����̐���[framework.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_two.h"

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
class CFramework : public CScene_TWO
{
public:
	/* �񋓌^ */

	/* �֐� */
	CFramework();
	~CFramework();
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
	void Scene_MyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	) {};
	// ����ɓ��Ă�ꂽ��̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_OpponentCollision(
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

	// �쐬(�V�[���p������)
	static CFramework * Create(void);
	// �쐬(�V�[���p���Ȃ�)
	static CFramework * Create_Self(void);
	// unique_ptr�쐬(�V�[���p���Ȃ�)
	static std::unique_ptr<CFramework> Creat_Unique(void);
	// �g�p��Ԑݒ�
	void SetUse(bool const &bUse) { m_bUse = bUse; };
	// �g�p��Ԏ擾
	bool const &GetUse(void) { return m_bUse; };
protected:
	// �ݒ� //
private:
	/* �ϐ� */
	bool m_bUse;	// �g�p���
};

#endif