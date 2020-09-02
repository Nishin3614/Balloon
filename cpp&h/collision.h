// ----------------------------------------------------------------------------------------------------
//
// Collision�w�b�_�[�����̐���[calculation.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------

#ifndef _COLLISION_H_
#define _COLLISION_H_	 // �t�@�C������������߂�

// ----------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------
#include "scene.h"
#include "shape.h"

// ----------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------
#define COLLISION_MAX (128)

// ----------------------------------------------------------------------------------------------------
//
// Collision���
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// �\���̒�`
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���O��`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �O���錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCollision : public CScene
{
public:
	/* �񋓌^ */
	// �I�u�W�F�N�g�J�e�S���[
	typedef enum
	{
		OBJTYPE_ACTOR = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_FISH,
		OBJTYPE_PLAYER_BALLOON,
		OBJTYPE_ENEMY_BALLOON,
		OBJTYPE_ATTACK,
		OBJTYPE_ITEM,
		OBJTYPE_APPEFISH,
		OBJTYPE_MAX
	} OBJTYPE;
	/* �֐� */
	CCollision();
	virtual ~CCollision() {};
	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
#ifdef _DEBUG
	// �f�o�b�O����
	virtual void Debug(void);
	// �����蔻����J�̐ݒ�
	virtual void Collision_Visible_Set(void) = 0;
#endif // _DEBUG
	// ����������̏���
	// ����1:�I�u�W�F�N�g�^�C�v
	// ����2:����̃V�[�����
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	)
	{};
	// ����������̏���
	// ����1:�I�u�W�F�N�g�^�C�v
	// ����2:����̃V�[�����
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	)
	{};
	// �|�C���^�[�ʒu�����擾
	virtual D3DXVECTOR3 * Scene_GetPPos(void) = 0;
	// �|�C���^�[�ߋ��̈ʒu�����擾
	virtual D3DXVECTOR3 * Scene_GetPPosold(void) = 0;
	// �|�C���^�[�ړ��ʏ��̎擾
	virtual D3DXVECTOR3 * Scene_GetPMove(void) = 0;
	// ����̗L��
	// ��`�N���X�̓����蔻���r
	virtual bool Judg(CRectShape * const RectShape) = 0;
	// ��`�N���X�̓����蔻���r(�����o������)
	virtual bool Judg(CRectShape * const RectShape,D3DXVECTOR3 * pPos) = 0;
	// ���N���X�̓����蔻���r
	virtual bool Judg(CSphereShape * const SphereShape) = 0;
	// �~���N���X�̓����蔻���r
	virtual bool Judg(CColumnShape * const ColumnShape) = 0;
	// �`���擾
	virtual CShape * const GetShape(void) = 0;

	// �`�N���X�̓����蔻��
	bool SelectShape(CShape * const shape);
	// �����蔻�蓯�m�̔���(�w��)
	bool CollisionDetection(CCollision * collision);
	// �����蔻�蓯�m�̔���(�����o������)
	bool CollisionDetection(
		CCollision * collision,
		D3DXVECTOR3 * pPos);
	// �����蔻�蓯�m�̔���(�w��I�u�W�F�N�g)
	bool CollisionDetection(OBJTYPE const &obj);
	// �����蔻�蓯�m�̔���(�S��)
	static void CollisionDetection(void);
	// �`�ʂ̓����蔻��̋��

	// �����蔻���Ԃ̋���false��
	// ����������̍s�����N���������ɔ����false�ɂ���
	void SetCollision(void);
	// �����蔻���Ԃ̎擾
	bool &GetbCollision(void) { return m_bCollision; };
	// �����蔻��̎g�p��Ԑݒ菈��
	void SetUse(bool const &bUse) { m_bUse = bUse; };
	// �����蔻��̎g�p��Ԏ擾
	bool const &GetUse(void) { return m_bUse; };
	// �����̃I�u�W�F�N�g�ԍ��ݒ�
	void SetObjectID(OBJTYPE const &obj) { m_nMyObjectId = obj; };
	// �����蔻������L���Ă���V�[�����擾
	CScene * GetOwnScene(void) { return m_pOwner; };
	// �����蔻������L���Ă���V�[�����ݒ�
	void SetOwnScene(CScene * pScene) { m_pOwner = pScene; };
	// // �����蔻������L���Ă���I�u�W�F�N�g�̐e���擾
	CScene * GetParent(void) { return m_pParent; };
	// // �����蔻������L���Ă���I�u�W�F�N�g�̐e���ݒ�
	void SetParent(CScene * pParent) { m_pParent = pParent; };
	// �����蔻������L���Ă���V�[����������NULL���
	void CompulsionScene(void);
	// ��`�Ƌ�`�̓����蔻��
	// pRectShapeA:��`A
	// pRectShapeB:��`B
	static bool RectAndRect(
		CRectShape * const pRectShapeA,	// ��`A
		CRectShape * const pRectShapeB	// ��`B
	);
	// ��`�Ƌ�`�̓����蔻��
	// pRectShapeA:��`A
	// pRectShapeB:��`B
	// pPos:�ʒu�|�C���^�[(�e���̈ʒu)
	static bool RectAndRect(
		CRectShape * pRectShapeA,		// ��`A
		CRectShape * const pRectShapeB,	// ��`B
		D3DXVECTOR3 * pPos				// �ʒu�|�C���^�[
	);
	// ��`�Ƌ��̓����蔻��
	static bool RectAndSphere(
		CRectShape * const pRectShapeA,		// ��`A
		CSphereShape * const pSphereShapeB	// ��B
	);
	// ��`�Ƌ��̓����蔻��
	static bool RectAndSphere(
		CRectShape * const pRectShapeA,		// ��`A
		CSphereShape * const pSphereShapeB,	// ��B
		D3DXVECTOR3 * pPos					// �ʒu
	);
	// ��`�Ɖ~���̓����蔻��
	static bool RectAndColumn(
		CRectShape * const pRectShapeA,		// ��`A
		CColumnShape * const pColumnShapeB	// �~��B
	);
	// ���Ɖ~���̓����蔻��
	static bool SphereAndColumn(
		CSphereShape * const pSphereShapeA,	// ��A
		CColumnShape * const pColumnShapeB	// �~��B
	);
	// ���Ƌ��̓����蔻��
	static bool SphereAndSphere(
		CSphereShape * const pSphereShapeA,	// ��A
		CSphereShape * const pSphereShapeB	// ��B
	);
	// ���Ƌ��̓����蔻��
	static bool SphereAndSphere(
		CSphereShape * const pSphereShapeA,	// ��A
		CSphereShape * const pSphereShapeB,	// ��B
		D3DXVECTOR3 * pPos					// �ʒu
	);
	// �~���Ɖ~���̓����蔻��
	static bool ColumnAndColumn(
		CColumnShape * const pColumnShapeA,	// �~��A
		CColumnShape * const pColumnShapeB	// �~��B
	);
protected:

private:
	/* �ϐ� */
	bool m_bCollision;						// �����蔻��̔�����
	bool m_bUse;							// �����蔻��̎g�p���
	int m_nMyObjectId;						// �I�u�W�F�N�g�ԍ�
	int m_nOponentId;						// �����������̑���
	CScene * m_pOwner;						// �����蔻������L���Ă���V�[�����
	CScene * m_pParent;						// �����蔻������L���Ă���I�u�W�F�N�g�̐e���


#ifdef _DEBUG
	static int nCollisionTime;
#endif
};

// ----------------------------------------------------------------------------------------------------
//
// �v���g�^�C�v�錾
//
// ----------------------------------------------------------------------------------------------------

#endif