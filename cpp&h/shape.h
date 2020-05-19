// ----------------------------------------------------------------------------------------------------
//
// Shape�w�b�_�[�����̐���[shape.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------

#ifndef _SHAPE_H_
#define _SHAPE_H_	 // �t�@�C������������߂�

// ----------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------
#include "main.h"
#include "Calculation.h"

// ----------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// Shape���
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// �\���̒�`
//
// ----------------------------------------------------------------------------------------------------

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
// ���̌`�N���X
class CShape
{
public:
	/* �񋓌^ */
	// �`�̎��
	typedef enum
	{
		SHAPETYPE_RECT = 0,
		SHAPETYPE_SPHERE,
		SHAPETYPE_COLUMN,
		SHAPETYPE_MAX
	} SHAPETYPE;

	/* �֐� */
	CShape() {};
	virtual ~CShape() {};
	// �`�̎��
	virtual SHAPETYPE GetType(void) const = 0;
	// �s����󂯓n��
	// 1:�s����
	virtual void PassMatrix(D3DXMATRIX const &mtx) = 0;
	// �ʒu�Ɖ�]���󂯓n��
	// 1:�ʒu���,2:�J�X���
	virtual void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	) = 0;
	// �ʒu���󂯓n��
	// 1:�ʒu���
	// �p�x0�̎�
	virtual void PassPos(D3DXVECTOR3 const & pos) = 0;
	// �ʒu�ݒ�
	void SetOffset(D3DXVECTOR3 const &offset) { m_offset = offset; };
	// �ʒu�擾
	D3DXVECTOR3 const &GetOffset(void) { return m_offset; };

protected:

private:
	D3DXVECTOR3 m_offset;	// �I�t�Z�b�g���W
};

// ���̃N���X
class CSphereShape : public CShape
{
public:
	/* �񋓌^ */

	/* �֐� */
	CSphereShape() {};
	virtual ~CSphereShape() {};
	// �쐬
	static unique_ptr<CSphereShape> Create(
		D3DXVECTOR3 const &offset,
		D3DXVECTOR3 const &pos,
		float const &radius
	);
	// �s����󂯓n��
	// 1:�s����
	void PassMatrix(D3DXMATRIX const &mtx);
	// �ʒu�Ɖ�]���󂯓n��
	// 1:�ʒu���,2:�J�X���
	void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	) {};
	// �ʒu���󂯓n��
	// 1:�ʒu���
	// �p�x0�̎�
	void PassPos(D3DXVECTOR3 const & pos) { m_pos = pos; };
	// �ݒ� //
	// ���a�ݒ�
	void SetRadius(float const radius) { m_radius = radius; };
	// �ʒu�ݒ�
	void SetPos(D3DXVECTOR3 const &pos) { m_pos = pos; };

	// �擾 //
	// �`�̎�ގ擾
	SHAPETYPE GetType(void) const { return SHAPETYPE_SPHERE; };
	// ���a�擾
	float GetRadius(void) const { return m_radius; };
	// �ʒu�擾
	D3DXVECTOR3 const &GetPos(void) { return m_pos; };
protected:

private:
	D3DXVECTOR3 m_pos;
	float m_radius;
};

// ��`�̃N���X
class CRectShape : public CShape
{
public:
	/* �񋓌^ */

	/* �^�錾 */
	
	/* �֐� */
	CRectShape() 
	{
		m_size = D3DVECTOR3_ZERO;
		m_Min.x = m_Min.y = m_Min.z = FLT_MAX;
		m_Max.x = m_Max.y = m_Max.z = -FLT_MAX;
	};
	virtual ~CRectShape() {};
	// �ő���W�l�ƍŏ����W�l�̌v�Z
	// 1:�s����
	void PassMatrix(D3DXMATRIX const &mtx);
	// �ő���W�l�ƍŏ����W�l�̌v�Z
	// 1:�ʒu���
	void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	);
	// �ő���W�l�ƍŏ����W�l�̌v�Z
	// 1:�ʒu���
	// �p�x0�̎�
	void PassPos(D3DXVECTOR3 const & pos);
	// ������W����ł��߂��A�{�b�N�X��̍��W��Ԃ�
	D3DXVECTOR3 GetClosestpoint(D3DXVECTOR3 const &pos);
	// �쐬
	static unique_ptr<CRectShape> Create(
		D3DXVECTOR3 const &offset,
		D3DXVECTOR3 const &size
	);
	// �ݒ� //
	// ���a�ݒ�
	void SetSize(D3DXVECTOR3 const size) { m_size = size; };
	// �擾 //
	// �`�̎�ގ擾
	SHAPETYPE GetType(void) const { return SHAPETYPE_RECT; };
	// ���a�擾
	D3DXVECTOR3 GetSize(void) const { return m_size; };
	// �ő���W�l�擾
	D3DXVECTOR3 GetMax(void) const & { return m_Max; };
	// �ŏ����W�l�擾
	D3DXVECTOR3 GetMin(void) const & { return m_Min; };
protected:

private:
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_Min;
	D3DXVECTOR3 m_Max;
};

// �~���̃N���X
class CColumnShape : public CShape
{
public:
	/* �񋓌^ */
	/* �֐� */
	CColumnShape() {};
	virtual ~CColumnShape() {};
	// �쐬
	static unique_ptr<CColumnShape> Create(
		D3DXVECTOR3 const &offset,
		D3DXVECTOR3 const &pos,
		float const & fRadius,
		float const & fVertical
	);
	// �s����󂯓n��
	// 1:�s����
	// ������
	void PassMatrix(D3DXMATRIX const &mtx) {};
	// �ʒu�Ɖ�]���󂯓n��
	// 1:�ʒu���,2:�J�X���
	// ������
	void PassPos(
		D3DXVECTOR3 const & pos,
		D3DXVECTOR3 const & rot
	) {};
	// �ʒu���󂯓n��
	// 1:�ʒu���
	// �p�x0�̎�
	void PassPos(D3DXVECTOR3 const & pos) { m_pos = pos; };
	// �ݒ� //
	// �ʒu�ݒ�
	void SetPos(D3DXVECTOR3 const &pos) { m_pos = pos; };
	// ���a�ݒ�
	void SetRadius(float const & fRadius) { m_fRadius = fRadius; };
	// �c���ݒ�
	void SetVertical(float const & fVertical) { m_fVertical = fVertical; };
	// �擾 //
	// �`�̎�ގ擾
	SHAPETYPE GetType(void) const { return SHAPETYPE_COLUMN; };
	// ���a�擾
	float GetRadius(void) const { return m_fRadius; };
	// �c���擾
	float GetVertical(void) const { return m_fVertical; };
	// �ʒu�擾
	D3DXVECTOR3 const &GetPos(void) { return m_pos; };
protected:

private:
	D3DXVECTOR3 m_pos;
	float m_fRadius;
	float m_fVertical;
};

#endif