// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Collision�����̐���[collision.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Collision.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define COLLISION_FILE "data/LOAD/collision.txt"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �O���[�o���ϐ�
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ�
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
int CCollision::nCollisionTime = 0;
#endif

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCollision::CCollision() : CScene::CScene()
{
	// ������
	m_pOwner = NULL;
	m_pParent = NULL;
	m_bCollision = false;
	m_bUse = true;
	m_nMyObjectId = 0;
	m_nOponentId = -1;
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCollision::Debug(void)
{
	// �ϐ��錾
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posold;

	// ����� //
	// �ʒu���擾
	if (GetShape()->Get_PPos() != NULL)
	{
		pos = *GetShape()->Get_PPos();
	}
	else
	{
		pos = GetShape()->Get_Pos();
	}
	// �ߋ��̈ʒu���擾
	if (GetShape()->Get_PPosold() != NULL)
	{
		posold = *GetShape()->Get_PPosold();
	}
	else
	{
		posold = GetShape()->Get_Posold();
	}
	/*
	ImGui::Text("Pos(%.1f,%.1f,%.1f)",
		pos.x,
		pos.y,
		pos.z
	);
	ImGui::Text("PosOld(%.1f,%.1f,%.1f)",
		posold.x,
		posold.y,
		posold.z
	);
	ImGui::Text("nCollisionTime:%d", nCollisionTime);
	*/
}

#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�N���X�̑I��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SelectShape(CShape * const shape)
{
	// �N���X�^��r //
	// ��`�N���X
	if (shape->GetType() == CShape::SHAPETYPE_RECT)
	{
		return Judg((CRectShape*)shape);
	}
	// ���N���X
	else if (shape->GetType() == CShape::SHAPETYPE_SPHERE)
	{
		return Judg((CSphereShape*)shape);
	}
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻��(�w��)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(CCollision * pCollision)
{
	// �����̓����蔻����NULL�̏ꍇ ||
	// �����̓����蔻�肪�����̂����蔻��Ȃ�
	// ->�֐��𔲂���
	if (pCollision == NULL ||
		this == pCollision)
	{
		return false;
	}
	// �����̓����蔻��̎g�p��Ԃ�false ||
	// ����̓����蔻��̎g�p��Ԃ�false ||
	// ->�֐��𔲂���
	if (!this->m_bUse ||
		!pCollision->m_bUse)
	{
		return false;
	}
	// �����̃I�u�W�F�N�g����NULL�`�F�b�N ||
	// ����̃I�u�W�F�N�g�̐e����NULL�`�F�b�N ||
	// �����̃I�u�W�F�N�g���Ƒ���̃I�u�W�F�N�g�̐e��񂪓����Ȃ�
	// ->�֐��𔲂���
	if (this->m_pOwner == NULL ||
		this->m_pOwner == pCollision->m_pParent)
	{
		return false;
	}

	// �ϐ��錾
	bool bJudg = false;	// �����蔻����
	// �N���X�^��r //
	// ��`�N���X
	if (pCollision->GetShape()->GetType() == CShape::SHAPETYPE_RECT)
	{
		bJudg = Judg((CRectShape*)pCollision->GetShape());
	}
	// ���N���X
	else if (pCollision->GetShape()->GetType() == CShape::SHAPETYPE_SPHERE)
	{
		bJudg = Judg((CSphereShape*)pCollision->GetShape());
	}
	// �~���N���X
	else if (pCollision->GetShape()->GetType() == CShape::SHAPETYPE_COLUMN)
	{
		bJudg = Judg((CColumnShape*)pCollision->GetShape());
	}
	// ���肪true�Ȃ�
	// ->����ۑ�
	if (bJudg ==  true)
	{

#ifdef _DEBUG
		// �e�X�g�ϐ�
		nCollisionTime++;
#endif // _DEBUG

		// ����̓����蔻���Ԃ�true��
		pCollision->m_bCollision = true;
		// ����̔ԍ�����
		pCollision->m_nOponentId = m_nMyObjectId;
		// �V�[�����NULL�ł͂Ȃ��Ȃ�
		// ->����������̏������s��
		if (m_pOwner != NULL)
		{
			m_pOwner->Scene_MyCollision(pCollision->m_nMyObjectId, pCollision->m_pOwner);
		}
		// ����̃V�[�����NULL�ł͂Ȃ��Ȃ�
		// ->����������̏������s��
		if (pCollision->m_pOwner != NULL)
		{
			pCollision->m_pOwner->Scene_OpponentCollision(m_nMyObjectId, m_pOwner);
		}
	}
	// �����蔻���Ԃ�Ԃ�
	return bJudg;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻��(�����o������)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(
	CCollision * collision,
	D3DXVECTOR3 * pPos
)
{
	// �����̓����蔻����NULL�̏ꍇ
	// ->�֐��𔲂���
	if (collision == NULL)
	{
		return false;
	}
	// �ϐ��錾
	bool bJudg = false;	// �����蔻����
	// �N���X�^��r //
	// ��`�N���X
	if (collision->GetShape()->GetType() == CShape::SHAPETYPE_RECT)
	{
		bJudg = Judg((CRectShape*)collision->GetShape(),pPos);
	}
	// ���N���X
	else if (collision->GetShape()->GetType() == CShape::SHAPETYPE_SPHERE)
	{

	}
	// �~���N���X
	else if (collision->GetShape()->GetType() == CShape::SHAPETYPE_COLUMN)
	{

	}
	// ���肪true�Ȃ�
	// ->����ۑ�
	if (bJudg == true)
	{
		// ����̓����蔻���Ԃ�true��
		collision->m_bCollision = true;
		// ����̔ԍ�����
		collision->m_nOponentId = m_nMyObjectId;
	}
	// �����蔻���Ԃ�Ԃ�
	return bJudg;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻��(�w��I�u�W�F�N�g)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::CollisionDetection(OBJTYPE const & obj)
{
	// �ϐ��錾
	CCollision * pCollision;	// �����蔻����
	bool bCollision = false;	// �����蔻����
	// ����
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(LAYER_COLLISION); nCntLayer++)
	{
		// �����蔻��擾
		pCollision = (CCollision *)CScene::GetScene(LAYER_COLLISION, nCntLayer);
		// �����蔻���NULL�`�F�b�N ||
		// �����蔻�肪�����̓����蔻��ƃA�h���X�������Ȃ�
		// ->���[�v�X�L�b�v
		if (pCollision == NULL ||
			pCollision == this) continue;
		// �w�肵���I�u�W�F�N�g�ł͂Ȃ��Ȃ�
		// ->���[�v�X�L�b�v
		else if (pCollision->m_nMyObjectId != obj) continue;
		// �����蔻���true�ɂ���
		bCollision |= this->CollisionDetection(pCollision);
	}
	// �����蔻���Ԃ�Ԃ�
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻��(�Ǘ����Ă���S��)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCollision::CollisionDetection(void)
{
	// �ϐ��錾
	CCollision * pCollision1 = NULL;	// �����蔻����
	CCollision * pCollision2 = NULL;	// �����蔻����

	// ����
	for (int nCntLayer1 = 0; nCntLayer1 < CScene::GetMaxLayer(LAYER_COLLISION); nCntLayer1++)
	{
		// �����蔻��擾
		pCollision1 = (CCollision *)CScene::GetScene(LAYER_COLLISION, nCntLayer1);
		// �����蔻����NULL�Ȃ�
		if (pCollision1 == NULL)
		{
			continue;
		}
		// !�I�u�W�F�N�g�^�C�v���v���C���[�Ȃ� ||
		// !�I�v�W�F�N�g�^�C�v���G�l�~�[�Ȃ� ||
		// !�I�u�W�F�N�g�^�C�v�����Ȃ�
		else if (!(pCollision1->m_nMyObjectId == OBJTYPE_PLAYER ||
			pCollision1->m_nMyObjectId == OBJTYPE_ENEMY ||
			pCollision1->m_nMyObjectId == OBJTYPE_FISH)
			)
		{
			continue;
		}
		// ����
		for (int nCntLayer2 = 0; nCntLayer2 < CScene::GetMaxLayer(LAYER_COLLISION); nCntLayer2++)
		{
			// �����蔻��擾
			pCollision2 = (CCollision *)CScene::GetScene(LAYER_COLLISION, nCntLayer2);
			// �����̓����蔻����NULL�̏ꍇ ||
			// �����̓����蔻�肪�����̂����蔻��Ȃ�
			// ->�֐��𔲂���
			if (pCollision2 == NULL ||
				pCollision1 == pCollision2)
			{
				continue;
			}
			// �����̓����蔻��̎g�p��Ԃ�false ||
			// ����̓����蔻��̎g�p��Ԃ�false ||
			// ->�֐��𔲂���
			else if (!pCollision1->m_bUse ||
				!pCollision2->m_bUse)
			{
				continue;
			}
			// �����̃I�u�W�F�N�g����NULL�`�F�b�N ||
			// ����̃I�u�W�F�N�g�̐e����NULL�`�F�b�N ||
			// �����̃I�u�W�F�N�g���Ƒ���̃I�u�W�F�N�g�̐e��񂪓����Ȃ�
			// ->�֐��𔲂���
			else if (pCollision1->m_pOwner == NULL ||
				pCollision1->m_pOwner == pCollision2->m_pParent)
			{
				continue;
			}
			// �ϐ��錾
			bool bJudg = false;	// �����蔻����
								// �N���X�^��r //
								// ��`�N���X
			if (pCollision2->GetShape()->GetType() == CShape::SHAPETYPE_RECT)
			{
				bJudg = pCollision1->Judg((CRectShape*)pCollision2->GetShape());
			}
			// ���N���X
			else if (pCollision2->GetShape()->GetType() == CShape::SHAPETYPE_SPHERE)
			{
				bJudg = pCollision1->Judg((CSphereShape*)pCollision2->GetShape());
			}
			// �~���N���X
			else if (pCollision2->GetShape()->GetType() == CShape::SHAPETYPE_COLUMN)
			{
				bJudg = pCollision1->Judg((CColumnShape*)pCollision2->GetShape());
			}
			// ���肪true�Ȃ�
			// ->����ۑ�
			if (bJudg == true)
			{

#ifdef _DEBUG
				// �e�X�g�ϐ�
				nCollisionTime++;
#endif // _DEBUG

				// ����̓����蔻���Ԃ�true��
				pCollision2->m_bCollision = true;
				// ����̔ԍ�����
				pCollision2->m_nOponentId = pCollision1->m_nMyObjectId;
				// �V�[�����NULL�ł͂Ȃ��Ȃ�
				// ->����������̏������s��
				if (pCollision1->m_pOwner != NULL)
				{
 					pCollision1->m_pOwner->Scene_MyCollision(pCollision2->m_nMyObjectId, pCollision2->m_pOwner);
				}
				// ����̃V�[�����NULL�ł͂Ȃ��Ȃ�
				// ->����������̏������s��
				if (pCollision2->m_pOwner != NULL)
				{
					pCollision2->m_pOwner->Scene_OpponentCollision(pCollision1->m_nMyObjectId, pCollision1->m_pOwner);
				}
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻���Ԃ̋���false��
// ����������̍s�����N���������ɔ����false�ɂ���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCollision::SetCollision(void)
{
	m_bCollision = false;
	m_nOponentId = -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �����蔻������L���Ă���V�[����������NULL���
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCollision::CompulsionScene(void)
{
	m_pOwner = NULL;
	m_pParent = NULL;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��`�Ƌ�`�̔���
// pRectShapeA:��`A
// pRectShapeB:��`B
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndRect(
	CRectShape * const pRectShapeA,	// ��`A
	CRectShape * const pRectShapeB	// ��`B
)
{
	// �ϐ��錾
	D3DXVECTOR3 const &min_A = pRectShapeA->GetMin();
	D3DXVECTOR3 const &min_B = pRectShapeB->GetMin();
	D3DXVECTOR3 const &max_A = pRectShapeA->GetMax();
	D3DXVECTOR3 const &max_B = pRectShapeB->GetMax();
	D3DXVECTOR3 const &minOld_A = pRectShapeA->GetMinOld();
	D3DXVECTOR3 const &minOld_B = pRectShapeB->GetMinOld();
	D3DXVECTOR3 const &maxOld_A = pRectShapeA->GetMaxOld();
	D3DXVECTOR3 const &maxOld_B = pRectShapeB->GetMaxOld();
	D3DXVECTOR3 *pos_A = NULL;
	bool bCollision = false;
	// �|�C���^�[�ʒu���NULL�ł͂Ȃ��Ȃ�
	// ->�ʒu���ɑ��
	if (pRectShapeA->Get_PPos() != NULL)
	{
		pos_A = pRectShapeA->Get_PPos();
	}
	// �ڐG���Ă��Ȃ��Ƃ���false��Ԃ�
	if (max_A.y > min_B.y &&
		min_A.y < max_B.y)
	{
		// �f�ނ�Z�͈�
		if (max_A.z > min_B.z&&
			min_A.z < max_B.z)
		{
			// �����蔻��(��)
			if (max_A.x > min_B.x &&
				maxOld_A.x <= min_B.x)
			{
				// �ߋ��̈ʒu���A��NULL�ł͂Ȃ��Ȃ� ||
				// �����o������������Ȃ�
				// ->�����o������
				if (pos_A != NULL ||
					pRectShapeA->m_bPush &&
					pRectShapeB->m_bOpponentPush
					)
				{
					// �f�ޏ�̍���
					pos_A->x = min_B.x - pRectShapeA->GetSize().x * 0.6f;
				}
				// �ڐG���Ă���Ƃ���true��Ԃ�
				bCollision = true;
			}

			// �����蔻��(�E)
			else if (min_A.x < max_B.x &&
				minOld_A.x >= max_B.x)
			{
				// �ߋ��̈ʒu���A��NULL�ł͂Ȃ��Ȃ� ||
				// �����o������������Ȃ�
				// ->�����o������
				if (pos_A != NULL ||
					pRectShapeA->m_bPush &&
					pRectShapeB->m_bOpponentPush
					)
				{
					// �f�ޏ�̍���
					pos_A->x = max_B.x + pRectShapeA->GetSize().x * 0.6f;
				}
				// �ڐG���Ă���Ƃ���true��Ԃ�
				bCollision = true;
			}
		}
		// �f�ނ�X�͈�
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// �����蔻��(��O)
			if (max_A.z > min_B.z&&
				maxOld_A.z <= min_B.z)
			{
				// �ߋ��̈ʒu���A��NULL�ł͂Ȃ��Ȃ� ||
				// �����o������������Ȃ�
				// ->�����o������
				if (pos_A != NULL ||
					pRectShapeA->m_bPush &&
					pRectShapeB->m_bOpponentPush
					)
				{
					// �f�ޏ�̍���
					pos_A->z = min_B.z - pRectShapeA->GetSize().z * 0.6f;
				}
				// �ڐG���Ă���Ƃ���true��Ԃ�
				bCollision = true;
			}

			// �����蔻��(��)
			else if (min_A.z < max_B.z &&
				minOld_A.z >= max_B.z)
			{
				// �ߋ��̈ʒu���A��NULL�ł͂Ȃ��Ȃ� ||
				// �����o������������Ȃ�
				// ->�����o������
				if (pos_A != NULL ||
					pRectShapeA->m_bPush &&
					pRectShapeB->m_bOpponentPush
					)
				{
					// �f�ޏ�̍���
					pos_A->z = max_B.z +
						pRectShapeA->GetSize().z * 0.6f;
				}
				// �ڐG���Ă���Ƃ���true��Ԃ�
				bCollision = true;
			}

		}
	}
	// �f�ނ�Z�͈�
	if (max_A.z > min_B.z&&
		min_A.z < max_B.z)
	{
		// �f�ނ�X�͈�
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// �����蔻��(��)
			if (max_A.y > min_B.y &&
				maxOld_A.y <= min_B.y)
			{
				// �ߋ��̈ʒu���A��NULL�ł͂Ȃ��Ȃ� ||
				// �����o������������Ȃ�
				// ->�����o������
				if (pos_A != NULL ||
					pRectShapeA->m_bPush &&
					pRectShapeB->m_bOpponentPush
					)
				{
					// �f�ޏ�̍���
					pos_A->y = min_B.y - pRectShapeA->GetSize().y;
				}
				// �ڐG���Ă���Ƃ���true��Ԃ�
 				bCollision = true;
			}

			// �����蔻��(��)
			else if (min_A.y < max_B.y&&
				minOld_A.y >= max_B.y)
			{
				// �ߋ��̈ʒu���A��NULL�ł͂Ȃ��Ȃ� ||
				// �����o������������Ȃ�
				// ->�����o������
				if (pos_A != NULL ||
					pRectShapeA->m_bPush)
				{
					// �f�ޏ�̍���
					pos_A->y = max_B.y + 0.1f;
				}
				// �ڐG���Ă���Ƃ���true��Ԃ�
				bCollision = true;
			}

		}
	}
	// �������Ă�����X�V
	if (bCollision)
	{
		// �ʒu���X�V
		pRectShapeA->PassPos(D3DVECTOR3_ZERO);
	}
	// �ڐG���Ă���Ƃ���true��Ԃ�
	return bCollision;






	// ��邱��
	// ����������𐮗�����
	// ����Ȃ���������

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��`�Ƌ�`�̓����蔻��
// pRectShapeA:��`A
// pRectShapeB:��`B
// pPos:�ʒu�|�C���^�[(�e���̈ʒu)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndRect(
	CRectShape * pRectShapeA,		// ��`A
	CRectShape * const pRectShapeB,	// ��`B
	D3DXVECTOR3 * pPos				// �ʒu�|�C���^�[
)
{
	// �ϐ��錾
	bool bCollision = false;
	/*
	D3DXVECTOR3 const &min_A = pRectShapeA->GetMin();
	D3DXVECTOR3 const &min_B = pRectShapeB->GetMin();
	D3DXVECTOR3 const &max_A = pRectShapeA->GetMax();
	D3DXVECTOR3 const &max_B = pRectShapeB->GetMax();
	// �ڐG���Ă��Ȃ��Ƃ���false��Ԃ�
	if (max_A.y > min_B.y &&
		min_A.y < max_B.y)
	{
		// �f�ނ�Z�͈�
		if (max_A.z > min_B.z&&
			min_A.z < max_B.z)
		{
			// �f�ނ�Z�͈�
			if (max_A.x > min_B.x&&
				min_A.x < max_B.x)
			{
				// �����蔻��(��)
				if (max_A.x > min_B.x)
				{
					// �f�ޏ�̍���
					pPos->x = min_B.x - pRectShapeA->GetSize().x * 0.6f;
					// �ڐG���Ă���Ƃ���true��Ԃ�
					bCollision = true;
				}

				// �����蔻��(�E)
				else if (min_A.x < max_B.x)
				{
					// �f�ޏ�̍���
					pPos->x = max_B.x + pRectShapeA->GetSize().x * 0.6f;
					// �ڐG���Ă���Ƃ���true��Ԃ�
					bCollision = true;
				}
			}
		}
		// �f�ނ�X�͈�
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// �f�ނ�X�͈�
			if (max_A.z > min_B.z&&
				min_A.z < max_B.z)
			{

				// �����蔻��(��O)
				if (max_A.z > min_B.z)
				{
					// �f�ޏ�̍���
					pPos->z = min_B.z - pRectShapeA->GetSize().z * 0.6f;
					// �ڐG���Ă���Ƃ���true��Ԃ�
					bCollision = true;
				}

				// �����蔻��(��)
				else if (min_A.z < max_B.z)
				{
					// �f�ޏ�̍���
					pPos->z = max_B.z +
						pRectShapeA->GetSize().z * 0.6f + 0.1f;
					// �ڐG���Ă���Ƃ���true��Ԃ�
					bCollision = true;
				}
			}
		}
	}
	// �f�ނ�Z�͈�
	if (max_A.z > min_B.z&&
		min_A.z < max_B.z)
	{
		// �f�ނ�X�͈�
		if (max_A.x > min_B.x&&
			min_A.x < max_B.x)
		{
			// �f�ނ�X�͈�
			if (max_A.y > min_B.y&&
				min_A.y < max_B.y)
			{
				// �����蔻��(��)
				if (max_A.y > min_B.y)
				{
					// �f�ޏ�̍���
					pPos->y = min_B.y - pRectShapeA->GetSize().y * 0.6f;
					// �ڐG���Ă���Ƃ���true��Ԃ�
					bCollision = true;
				}

				// �����蔻��(��)
				else if (min_A.y < max_B.y)
				{
					// �f�ޏ�̍���
					pPos->y = max_B.y + pRectShapeA->GetSize().y * 0.6f;
					// �ڐG���Ă���Ƃ���true��Ԃ�
					bCollision = true;
				}
			}
		}
	}
	// �����蔻��̍X�V
	pRectShapeA->PassPos(*pPos);
	*/


	// �ڐG���Ă��Ȃ��Ƃ���false��Ԃ�
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��`�Ƌ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndSphere(CRectShape * const pRectShapeA, CSphereShape * const pSphereShapeB)
{
	// �ϐ��錾
	D3DXVECTOR3 ClosestPoint;	// ������W�̍ł��߂��A�{�b�N�X��̍��W
	D3DXVECTOR3 Pos_B;			// �ʒu
	// �|�C���^�[�ʒu��񂪂���ꍇ
	if (pSphereShapeB->Get_PPos() != NULL)
	{
		// �ʒu�����
		Pos_B = *pSphereShapeB->Get_PPos();
		// ������W�̍ł��߂��A�{�b�N�X��̍��W
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	// �Ȃ��ꍇ
	else
	{
		// �ʒu�����
		Pos_B = pSphereShapeB->Get_Pos();
		// ������W�̍ł��߂��A�{�b�N�X��̍��W
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	if (CCalculation::DiffPointSquare(Pos_B, ClosestPoint) <
		pSphereShapeB->GetRadius() * pSphereShapeB->GetRadius())
	{
		bool b = true;
	}
	// ���������a���Z���ꍇtrue,����ȊOfalse��Ԃ�
	return
		CCalculation::DiffPointSquare(Pos_B,ClosestPoint) <
		pSphereShapeB->GetRadius() * pSphereShapeB->GetRadius();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��`�Ƌ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndSphere(CRectShape * const pRectShapeA, CSphereShape * const pSphereShapeB, D3DXVECTOR3 * pPos)
{
	// �ϐ��錾
	D3DXVECTOR3 ClosestPoint;	// ������W�̍ł��߂��A�{�b�N�X��̍��W
	D3DXVECTOR3 Pos_B;			// �ʒu
								// �|�C���^�[�ʒu��񂪂���ꍇ
	if (pSphereShapeB->Get_PPos() != NULL)
	{
		// �ʒu�����
		Pos_B = *pSphereShapeB->Get_PPos();
		// ������W�̍ł��߂��A�{�b�N�X��̍��W
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	// �Ȃ��ꍇ
	else
	{
		// �ʒu�����
		Pos_B = pSphereShapeB->Get_Pos();
		// ������W�̍ł��߂��A�{�b�N�X��̍��W
		ClosestPoint = pRectShapeA->GetClosestpoint(Pos_B);
	}
	// ���������a���Z���ꍇtrue,����ȊOfalse��Ԃ�
	return
		CCalculation::DiffPointSquare(Pos_B, ClosestPoint) <
		pSphereShapeB->GetRadius() * pSphereShapeB->GetRadius();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��`�Ɖ~��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::RectAndColumn(CRectShape * const pRectShapeA, CColumnShape * const pColumnShapeB)
{
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���Ɖ~��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SphereAndColumn(CSphereShape * const pSphereShapeA, CColumnShape * const pColumnShapeB)
{
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���Ƌ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SphereAndSphere(CSphereShape * const pSphereShapeA, CSphereShape * const pSphereShapeB)
{
	// �ϐ��錾
	D3DXVECTOR3 *pos_A;
	D3DXVECTOR3 *pos_B;
	bool bCollision = false;
	// �X�t�B�AA�̃|�C���g�ʒu���NULL�ł͂Ȃ��ꍇ
	// �ʒu�����
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_A = pSphereShapeA->Get_PPos();
	}
	else
	{
		pos_A = &pSphereShapeA->Get_Pos();
	}
	// �X�t�B�AB�̃|�C���g�ʒu���NULL�ł͂Ȃ��ꍇ
	// �ʒu�����
	if (pSphereShapeB->Get_PPos() != NULL)
	{
		pos_B = pSphereShapeB->Get_PPos();
	}
	else
	{
		pos_B = &pSphereShapeB->Get_Pos();
	}

	// �ϐ��錾
	//D3DXVECTOR3 posA = pSphereShapeA->m_DestPos;	// �ʒuA
	//D3DXVECTOR3 posB = pSphereShapeB->m_DestPos;	// �ʒuB
	// �������Ă��邩�ǂ���
	bCollision = CCalculation::Collision_Sphere(
		*pos_A + pSphereShapeA->GetOffset(),
		pSphereShapeA->GetRadius(),
		*pos_B + pSphereShapeB->GetOffset(),
		pSphereShapeB->GetRadius()
	);
	// �������Ă����� &&
	// ��A�̉����o��������true�Ȃ� &&
	// ��B�̑���ɑ΂��鉟���o��������true�Ȃ�
	// ->��A�������o�����
	if (bCollision &&
		pSphereShapeA->m_bPush &&
		pSphereShapeB->m_bOpponentPush
		)
	{
		D3DXVECTOR3 diff = *pos_A - *pos_B;						// B����A�̍�
		D3DXVECTOR3 vec;									// B->A�̃x�N�g��
															// �x�N�g���̐��K��
		D3DXVec3Normalize(&vec, &diff);
		// �����o��
		*pos_A = *pos_B + vec * (pSphereShapeA->GetRadius() + pSphereShapeB->GetRadius());

		pSphereShapeA->PassPos(D3DVECTOR3_ZERO);
	}
	return bCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���Ƌ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::SphereAndSphere(CSphereShape * const pSphereShapeA, CSphereShape * const pSphereShapeB, D3DXVECTOR3 * pPos)
{
	// �ϐ��錾
	D3DXVECTOR3 pos_A;
	D3DXVECTOR3 pos_B;
	// �X�t�B�AA�̃|�C���g�ʒu���NULL�ł͂Ȃ��ꍇ
	// �ʒu�����
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_A = *pSphereShapeA->Get_PPos();
	}
	else
	{
		pos_A = pSphereShapeA->Get_Pos();
	}
	// �X�t�B�AB�̃|�C���g�ʒu���NULL�ł͂Ȃ��ꍇ
	// �ʒu�����
	if (pSphereShapeA->Get_PPos() != NULL)
	{
		pos_B = *pSphereShapeB->Get_PPos();
	}
	else
	{
		pos_B = pSphereShapeB->Get_Pos();
	}

	return CCalculation::Collision_Sphere(
		pos_A + pSphereShapeA->GetOffset(),
		pSphereShapeA->GetRadius(),
		pos_B + pSphereShapeB->GetOffset(),
		pSphereShapeB->GetRadius()
	);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �~���Ɖ~��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCollision::ColumnAndColumn(CColumnShape * const pColumnShapeA, CColumnShape * const pColumnShapeB)
{
	return false;
}
