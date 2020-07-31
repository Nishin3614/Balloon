// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���D�O���[�v�����̐���[balloon_group.h]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _BALLOON_GROUP_H_
#define _BALLOON_GROUP_H_	 // �t�@�C������������߂�

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "balloon.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �O���錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCollision;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CBalloon_group : public CScene
{
public:
	/* �֐� */
	CBalloon_group();
	~CBalloon_group();
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
	);
	// ����ɓ��Ă�ꂽ��̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	);
	// �|�C���^�[�ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPos(void) { return m_pPos; };
	// �|�C���^�[�ߋ��̈ʒu�����擾
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// �|�C���^�[�ړ��ʏ��̎擾
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	// �ʒu���ݒ�
	// pPos:�ʒu���
	void SetPPos(D3DXVECTOR3 * pPos);
	// ���D�O���[�v�̏���������
	void SetBiginBalloon_group(int const &nBringBalloon_group) { m_nBringBalloon_group = nBringBalloon_group; };
	// ���D�O���[�v�����Ă����ω�������(�㏸�E����)
	void SetBringBalloon_group(int const &nBringBalloon_group) { m_nBringBalloon_group += nBringBalloon_group; };
	// �o�����Ă��镗�D�O���[�v�̌���ω�������(�㏸�E����)
	void SetPopBalloon_group(int const &nPopBalloon_group = 1) { m_nPopBalloon_group += nPopBalloon_group; };
	// �O�ɏo���Ēu���镗�D�O���[�v�̍ő����ݒ�
	void SetPopMaxBalloom(
		int const &nPopMaxBaloon = 2,
		int const &nObjType = 0,
		CScene * pParent = NULL
	);
	// ���D�O���[�v�𐶐�
	void CreateBalloon_group(
		int const & nObjType,
		CScene * pParent
	);
	// �����蔻��̊J��
	void CollisionDelete(void);
	// ���D���擾
	CBalloon * GetBalloon(int const &nBalloon_group);	// ���D�̏��擾
	// ���D�O���[�v�������Ă�������擾
	int const &GetBringBalloon_group(void) { return m_nBringBalloon_group; };
	// ���D�O���[�v���o�����Ă�������擾
	int const &GetPopBalloon_group(void) { return m_nPopBalloon_group; };
	// ���݂̕��D�O���[�v�̍ő�o�����̎擾
	int const &GetPopMaxBalloon_group(void) { return m_nMaxPopBalloon_group; };
	// ���D�O���[�v������鏈��
	// nCntBalloon_group:���D�J�E���g
	void BreakBalloon_group(int const &nCntBalloon_group);	// ���D�O���[�v������鏈��
	// ���ŕ��D�����点�鏈��
	void Thunder_BreakBalloon_group(void);

	// ����
	static CBalloon_group * Create(
		D3DXVECTOR3 *pPos,					// �ʒu���
		D3DXMATRIX	*pMtx,					// �s����
		int const &nPopMaxBalloon_group,	// ���D�O���[�v�̍ő�o����
		int const &nObjType,				// �I�u�W�F�N�g�^�C�v
		CScene * pParent					// �e���
	);
	// ���\�[�X���ǂݍ��ސݒ�
	static HRESULT Load(void);					// ���\�[�X���ǂݍ��ސݒ�
	// �ǂݍ��񂾃��\�[�X�����J������
	static void UnLoad(void);					// �ǂݍ��񂾃��\�[�X�����J������
protected:
private:
	/* �֐� */
	// �����蔻����ݒ菈��
	//	nObjType	: �I�u�W�F�^�C�v
	//	pParent		: �e���
	void SetCollision(
		int const &nObjType,				// �I�u�W�F�N�g�^�C�v
		CScene * pParent					// �e���
	);
	// ���D������鏈��
	//	nCrackBalloon	: ����镗�D��
	void CrackBalloon(
		int const &nCrackBalloon = 1		// ����镗�D��
	);
	/* �ϐ� */
	std::vector<CBalloon *> m_apBalloon;			// ���D���f�����
	D3DXVECTOR3 *m_pPos;							// �ʒu���
	D3DXVECTOR3 m_offsetPos;						// �I�t�Z�b�g�ʒu
	D3DXMATRIX	*m_pMtx;							// �s����
	CCollision	*m_pCollision;						// �����蔻����
	int m_nPopBalloon_group;						// ���ݏo�����Ă��镗�D�O���[�v�̌�
	int m_nBringBalloon_group;						// ���ݎ����Ă��镗�D�O���[�v�̌�
	int m_nMaxPopBalloon_group;						// �ő�o�����̌�
	float m_fAngleBalloon_group;					// ���D�O���[�v�̏o������p�x(�~���� * 2 / �ő�o����)
};

#endif