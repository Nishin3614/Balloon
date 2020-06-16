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
	// �����蔻��̌`
	typedef enum
	{
		COLLISIONTYPE_SQUARE = 0,
		COLLISIONTYPE_CIRCLE,
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;
	// �I�u�W�F�N�g�J�e�S���[
	typedef enum
	{
		OBJTYPE_CHARACTER = 0,
		OBJTYPE_BALLOON,
		OBJTYPE_ACTOR,
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
	virtual void Debug(void) = 0;
#endif // _DEBUG
	// ����̗L��
	// ��`�N���X�̓����蔻���r
	virtual bool Judg(CRectShape * const RectShape) = 0;
	// ��`�N���X�̓����蔻���r(�����o������)
	virtual bool Judg(CRectShape * const RectShape,D3DXVECTOR3 * pPos) = 0;
	// ���N���X�̓����蔻���r
	virtual bool Judg(CSphereShape * const SphereShape) = 0;
	// �~���N���X�̓����蔻���r
	virtual bool Judg(CColumnShape * const ColumnShape) = 0;
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
	bool CollisionDetection(void);
	// �`�ʂ̓����蔻��̋��

	// �����蔻���Ԃ̋���false��
	// ����������̍s�����N���������ɔ����false�ɂ���
	void SetCollision(void);
	// �����蔻���Ԃ̎擾
	bool &GetbCollision(void) { return m_bCollision; };
	// �����̃I�u�W�F�N�g�ԍ��ݒ�
	void SetObjectID(OBJTYPE const &obj) { m_nMyObjectId = obj; };
	// �`���擾
	virtual CShape * const GetShape(void) = 0;

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
		CRectShape * const pRectShapeA,	// ��`A
		CRectShape * const pRectShapeB,	// ��`B
		D3DXVECTOR3 * pPos				// �ʒu�|�C���^�[
	);
	// ��`�Ƌ��̓����蔻��
	static bool RectAndSphere(
		CRectShape * const pRectShapeA,		// ��`A
		CSphereShape * const pSphereShapeB	// ��B
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
	// �~���Ɖ~���̓����蔻��
	static bool ColumnAndColumn(
		CColumnShape * const pColumnShapeA,	// �~��A
		CColumnShape * const pColumnShapeB	// �~��B
	);
protected:

private:
	/* �ϐ� */
	bool m_bCollision;						// �����蔻����
	int m_nMyObjectId;						// �I�u�W�F�N�g�ԍ�
	int m_nOponentId;						// �����������̑���
};

// ----------------------------------------------------------------------------------------------------
//
// �v���g�^�C�v�錾
//
// ----------------------------------------------------------------------------------------------------

#endif