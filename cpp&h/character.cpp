// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �L�����N�^�[���� [character.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character.h"
#include "floor.h"
#include "input.h"
#include "collision.h"
#include "3Dparticle.h"
#include "camera.h"
#include "game.h"
#include "meshobit.h"
#include "ui.h"
#include "Extrusion.h"

#include "rectcollision.h"
#include "spherecollision.h"
#include "columncollision.h"
#include "circleshadow.h"
#include "stencilshadow.h"
#include "balloon.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CHARACTER_KEYMOVE (1)													// �L�[�ړ�
#define CHARACTER_G (0.5f)														// �d��
#define CHARACTER_RESISTANCE (0.5f)												// ��R��
#define CHARACTER_STATUS_FILE ("data/LOAD/STATUS/status_manager_Character.csv")	// �t�@�C����
#define CIRCLESHADOW (true)														// �~�`�̃V���h�E�ɂ��邩���Ȃ���

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MODEL_ALL	*CCharacter::m_modelAll[CHARACTER_MAX] = {};		// ���f���S�̂̏��
CModel_info	*CCharacter::m_model_info[CHARACTER_MAX] = {};		// ���f�����
vector<int>	CCharacter::m_modelId[CHARACTER_MAX];				// ���f���ԍ�
D3DXVECTOR3	CCharacter::m_CharacterSize[CHARACTER_MAX] = {};	// �L�����N�^�[�̃T�C�Y
CCharacter::STATUS CCharacter::m_sStatus[CHARACTER_MAX] = {};	// �L�����N�^�[���ׂẴX�^�[�^�X���
int			CCharacter::m_NumParts[CHARACTER_MAX] = {};			// ���������f����
int			CCharacter::m_NumModel[CHARACTER_MAX] = {};			// �ő僂�f����
int			CCharacter::m_nCameraCharacter = 0;					// �L�����N�^�[�ɒǔ�����ID

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I�[�o�[���[�o�[�R���X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter::CCharacter() : CScene::CScene()
{
	m_pMeshobit = NULL;								// �O��
	m_pModel = NULL;								// ���f��
	m_character = CHARACTER_PLAYER;					// �L�����N�^�[
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			// �ʒu
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O�̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݉�]��
	m_rotLast = m_rot;								// ������������
	m_rotbetween = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�̍���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �L�����N�^�[�̃T�C�Y
	m_nMotiontypeOld = 0;							// �O��̃��[�V�����^�C�v
	m_nMotiontype = 0;								// ���[�V�����^�C�v
	m_keyinfoCnt = 0;								// �L�[���̃J�E���g
	m_nFrame = 0;									// �t���[���J�E���g
	m_nMotionFrame = 0;								// ���[�V������̂̃t���[���J�E���g
	m_nMaxMotion = 0;								// �ő僂�[�V������
	m_nIDWho = 0;									// �G��������
	m_State = STATE_NORMAL;							// ����̃X�e�[�^�X
	m_nCntState = 0;								// �J�E���g�X�e�[�^�X
	m_fLength = 0;									// �U���̓�����͈�
	m_fAlpha = 1.0f;								// �A���t�@�l
	m_bMotionCamera = false;						// ���[�V�����J�����̐؂�ւ�
	m_pStencilshadow = NULL;						// �X�e���V���V���h�E
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCharacter::~CCharacter()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Init()
{
	// ���f���̃������m��
	m_pModel = new CModel[m_NumParts[m_character]];

	// �L�����N�^�[�̐ݒ�
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// �L�����N�^�[���n��
		m_pModel[nCntModel].Init();
		// ���f���̏���n��
		m_pModel[nCntModel].BindModel(
			m_modelAll[m_character]->pModel_offset[nCntModel]
		);
		// ���f���̔ԍ��ݒ�
		m_pModel[nCntModel].SetModelId(m_modelId[m_character][nCntModel]);
		// �V���h�Eon
		if (CIRCLESHADOW == false)
		{
			m_pModel[nCntModel].SetShadowMap(true);
		}
		// ���[�V�����ݒ�
		m_pModel[nCntModel].BeginMotion(
			m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel],
			m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
		// ���ׂĂ̐e�ȊO
		if (nCntModel != 0)
		{
			// �e���ݒ�
			m_pModel[nCntModel].SetParentMtx(
				&m_pModel[m_modelAll[m_character]->pModel_offset[nCntModel].nParent].GetMatrix()
			);
		}
		// ���ׂĂ̐e
		else
		{
			// �e���ݒ�
			m_pModel[nCntModel].SetParentMtx(
				&m_mtxWorld
			);
		}
	}
	// �G��������
	if (m_character == CHARACTER_PLAYER)
	{
		m_nIDWho = 0;
	}
	else
	{
		m_nIDWho = 1;
	}

	// �O�Ղ̐ݒ�
	for (int nCntObit_Basic = 0; nCntObit_Basic < (signed)m_modelAll[m_character]->v_MeshObitLoad.size(); nCntObit_Basic++)
	{
		m_vec_pMeshObit.push_back(std::move(CMeshobit::Create_Self(
			m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).nLine,
			m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).BeginOffset,
			m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).EndOffset,
			(CMeshobit::TEX)m_modelAll[m_character]->v_MeshObitLoad.at(nCntObit_Basic).nTexType
		)));
	}

	// �U�������蔻��ݒ�
	for (int nCntAttackCollision = 0; nCntAttackCollision < (signed)m_modelAll[m_character]->v_AttackCollision.size(); nCntAttackCollision++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos;
		// �����蔻��̈ʒu�̐ݒ� 
		D3DXVec3TransformCoord(
			&pos,
			&m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
			&m_pModel[m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).nParts].GetMatrix()
		);
		// ��`�̓����蔻��
		if (m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_RectInfo)
		{
			// ��`�̓����蔻��
			m_vec_AttackCollision.push_back(std::move(CRectCollision::Create_Self(
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_RectInfo->size
			)));
		}
		// ���̓����蔻��
		else if (m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_SphereInfo)
		{
			// ���̓����蔻��
			m_vec_AttackCollision.push_back(std::move(CSphereCollision::Create_Self(
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
				pos,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_SphereInfo->fRadius
			)));
		}
		// �~���̓����蔻��
		else if (m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_ColumnInfo)
		{
			// �~���̓����蔻��
			m_vec_AttackCollision.push_back(std::move(CColumnCollision::Create_Self(
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).Offset,
				pos,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_ColumnInfo->fRadius,
				m_modelAll[m_character]->v_AttackCollision.at(nCntAttackCollision).p_uni_ColumnInfo->fVertical
			)));
		}
	}

	// �L�����N�^�[�����蔻��ݒ�
	if (m_modelAll[m_character]->pCharacterCollision != NULL)
	{
		m_pCharacterCollision = std::move(CRectCollision::Create_Self(
			m_modelAll[m_character]->pCharacterCollision->Offset,
			m_pos + m_modelAll[m_character]->pCharacterCollision->RectInfo->size
		));
	}
	// �V���h�Eon
	if (CIRCLESHADOW == true)
	{
		D3DXVECTOR3 pos = m_pos;
		pos.y = 0;
		// �X�e���V���V���h�E�̐���
		m_pStencilshadow = CStencilshadow::Create(m_pos, D3DXVECTOR3(10.0f, 10000.0f, 10.0f));
	}

	// ���D����
	m_pBalloon = CBalloon::Create(&m_mtxWorld);
	// �X�e�[�^�X�̔��f //
	// �������D�������Ă����
	m_pBalloon->SetBiginBalloon(m_sStatus[m_character].nMaxBalloon);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Uninit(void)
{
	// �k���`�F�b�N
	if (m_pModel != NULL)
	{
		delete[] m_pModel;
		m_pModel = NULL;
	}
	if (m_pCharacterCollision != NULL)
	{
		m_pCharacterCollision->Uninit();
		m_pCharacterCollision = NULL;
	}
	for (int nCntMotionObit = 0; nCntMotionObit < (signed)m_vec_pMeshObit.size(); nCntMotionObit++)
	{
		// �O�Ղ̏I������
		m_vec_pMeshObit.at(nCntMotionObit)->Uninit();
	}
	// �X�e���V���V���h�E�̏�����
	if (m_pStencilshadow != NULL)
	{
		m_pStencilshadow = NULL;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Update(void)
{
	// �J�����ǔ�����
	TrackCamera();
	// �ʏ펞�̍X�V����
	Update_Normal();
	// ��搧��
	Limit();
	// �����蔻�菈��
	Collision();
	// �X�e���V���V���h�E�̈ʒu�ݒ�
	if (m_pStencilshadow != NULL)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = m_pos;
		pos.y = -1000.0f;
		// �X�e���V���V���h�E�̈ʒu�ݒ�
		m_pStencilshadow->SetPos(pos);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���ꂼ��̓����蔻�菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Collision(void)
{
	// ����
	CCharacter * pCharacter;
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(LAYER_CHARACTER); nCntLayer++)
	{
		// �L�����N�^�[���擾
		pCharacter = (CCharacter *)CScene::GetScene(LAYER_CHARACTER, nCntLayer);
		// �L�����N�^�[��񂪓����Ă��Ȃ��ꍇ
		// ->���[�v�X�L�b�v
		if (pCharacter == NULL) continue;
		// ���݂̃L�����N�^�[���Ǝ擾�����L�����N�^�[��񂪓����ꍇ
		// ->���[�v�X�L�b�v
		else if (pCharacter == this) continue;
		// �L�����N�^�[���m�̓����蔻�菈��
		else if (m_pCharacterCollision->CollisionDetection(pCharacter->GetCollision()))
		{
			// �L�����N�^�[���m�������Ă���
			// ->�o�E���h����
			D3DXVECTOR3 rot = D3DVECTOR3_ZERO;
			D3DXVECTOR3 diffpos = D3DVECTOR3_ZERO;
			diffpos = pCharacter->m_pos - m_pos;
			// ���肩�猩�ăv���C���[������p�x
			rot.y = (atan2f(diffpos.x, diffpos.z));
			m_move.x = sinf(rot.y + D3DX_PI) * 2.5f;
			m_move.z = cosf(rot.y + D3DX_PI) * 2.5f;
		}
		// �L�����N�^�[�ƕ��D�̓����蔻�菈��
		BalloonCollision(pCharacter->m_pBalloon);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D�Ƃ̓����蔻�菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::BalloonCollision(
	CBalloon * pBalloon	// ���D�̏��
)
{
	// �L�����N�^�[�ƕ��D�̓����蔻�菈��
	for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX; nCntBalloon++)
	{
		// ����L�����N�^�[�̕��D��NULL�Ȃ�
		// ->�֐��𔲂���
		if (pBalloon->GetSceneX(nCntBalloon) == NULL) continue;
		// ����L�����N�^�[�̕��D�̃��f����NULL�Ȃ�
		// ->�֐��𔲂���
		else if (pBalloon->GetSceneX(nCntBalloon)->GetCollision() == NULL) continue;
		// ���L�����N�^�[�Ƒ���̃L�����N�^�[�̕��D�̔���
		else if (m_pCharacterCollision->CollisionDetection(
			pBalloon->GetSceneX(nCntBalloon)->GetCollision()))
		{

		}
	}
	// ��������
	// �܂�����������̔�����Ƃ�������

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ʏ펞�̍X�V����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Update_Normal(void)
{
	// �ړ�
	Move();
	// ����
	GetFloorHeight();
	// ���[�V����
	Motion();
	// �G�t�F�N�g���X�V
	Motion_Effect();
	// ���f���X�V
	ModelUpdate();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���̃��[�V�����ݒ菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::NextKeyMotion(void)
{
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// �k���`�F�b�N
		if (&m_pModel[nCntModel] != NULL)
		{
			// ���[�V�����ݒ�
			m_pModel[nCntModel].SetMotion(
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel],
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ړ�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Move(void)
{
	// ���݉�]����
	m_rotbetween = m_rotLast - m_rot;

	// ���x����
	m_rotbetween.x = CCalculation::Rot_One_Limit(m_rotbetween.x);
	m_rotbetween.y = CCalculation::Rot_One_Limit(m_rotbetween.y);
	m_rotbetween.z = CCalculation::Rot_One_Limit(m_rotbetween.z);

	// ��]�ړ�
	m_rot += m_rotbetween * 0.1f;

	// ���x����
	m_rot.x = CCalculation::Rot_One_Limit(m_rot.x);
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
	m_rot.z = CCalculation::Rot_One_Limit(m_rot.z);
	
	// �ړ�
	m_move.y -= 0.1f;
	if (m_nMotiontype != MOTIONTYPE_STANDUP)
	{
		m_pos.x += m_move.x;
		m_pos.z += m_move.z;
		m_pos.y += m_move.y;
	}
	// �����蔻��̍X�V
	m_pCharacterCollision->GetShape()->PassPos(m_pos);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���[�V��������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Motion(void)
{
	// �t���[���J�E���g�A�b�v
	m_nFrame++;
	m_nMotionFrame++;
	// ���[�V�����^�C�v���ω�
	// ������
	if (m_nMotiontype != m_nMotiontypeOld)
	{
		m_nFrame = 0;		// �t���[���L�[���̃J�E���g
		m_nMotionFrame = 0;	// ���[�V������̃t���[���J�E���g
		m_keyinfoCnt = 0;	// �L�[���̃J�E���g
		// ���̃��[�V�����ݒ�
		NextKeyMotion();
	}
	// ���[�V�����̕ۑ�
	m_nMotiontypeOld = m_nMotiontype;
	// �t���[�����������ɂȂ�����
	if (m_nFrame >= m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame)
	{
		// ������
		m_nFrame = 0;	// �t���[��
		// �J�E���g�A�b�v
		m_keyinfoCnt++;
		// ���[�V�����J�����̐؂�ւ��̏�����
		m_bMotionCamera = false;
		// �L�[��񂪒�������
		if (m_keyinfoCnt >= m_modelAll[m_character]->pMotion[m_nMotiontype].nNumKey)
		{
			// ���[�v���Ȃ��Ƃ�
			if (m_modelAll[m_character]->pMotion[m_nMotiontype].nLoop == 0)
			{
				m_nMotiontype = 0;	// ���[�V�����^�C�v
			}
			// ������
			m_keyinfoCnt = 0;				// �L�[���
			m_nMotionFrame = 0;				// ���[�V������̃t���[���J�E���g
		}
		// ���̃��[�V�����ݒ�
		NextKeyMotion();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���f���̍X�V����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::ModelUpdate(void)
{
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// �k���`�F�b�N
		if (&m_pModel[nCntModel] != NULL)
		{
			// �X�V
			m_pModel[nCntModel].Update();
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �J�����ǔ�
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::TrackCamera(void)
{
	if (m_character != CHARACTER_PLAYER)
	{
		return;
	}
	// ���[�h���Q�[���ƃ`���[�g���A���̏ꍇ
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �J�����̒����_�ݒ�
		CManager::GetRenderer()->GetCamera()->SetPosDestRPlayer(
			CCharacter::GetPos(),
			CCharacter::GetRot()
		);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Limit(void)
{
	// x�̐���
	if (m_pos.x < -950)
	{
		m_pos.x = -950;
	}
	if (m_pos.x > 950)
	{
		m_pos.x = 950;
	}
	// z�̐���
	if (m_pos.z < -950)
	{
		m_pos.z = -950;
	}
	if (m_pos.z > 950)
	{
		m_pos.z = 950;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���[�V�����G�t�F�N�g�X�V
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Motion_Effect(void)
{
	// �ϐ��錾
	D3DXVECTOR3 pos;
	for (int nCntMotionEffect = 0; nCntMotionEffect < (signed)m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.size(); nCntMotionEffect++)
	{
		// �J�n���ԊO�Ȃ�X�L�b�v
		if (m_nFrame < m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nStart)
		{
			continue;
		}
		// �I�����ԊO�Ȃ�X�L�b�v
		else if (m_nFrame > m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nEnd)
		{
			continue;
		}
		// ���ԓ��Ȃ�
		// �ʒu�ݒ�
		D3DXVec3TransformCoord(
			&pos,
			&m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).offset,
			CCharacter::GetMatrix(m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nKeyID)
		);
		// �p�[�e�B�N���̐���
		C3DParticle::Create(
			(C3DParticle::PARTICLE_OFFSET_ID)m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].v_MotionEffect.at(nCntMotionEffect).nParticleType,
			pos);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���[�V�����O�ՍX�V
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Motion_Obit()
{
	for (int nCntMotionObit = 0; nCntMotionObit < (signed)m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.size(); nCntMotionObit++)
	{
		// �J�n���ԊO�Ȃ�X�L�b�v
		if (m_nMotionFrame < m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nBeginFram)
		{
			continue;
		}
		// �I�����ԊO�Ȃ�X�L�b�v
		else if (m_nMotionFrame > m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nEndFram)
		{
			continue;
		}
		// �J�n���Ɉʒu��������
		else if (m_nMotionFrame == m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nBeginFram)
		{
			m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->InitPos(*CCharacter::GetMatrix(m_modelAll[m_character]->v_MeshObitLoad.at(
				m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID).nPart));
		}
		// �O�Ղ̐F�̐ݒ�
		m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->SetCol(
			m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).BeginCol,
			m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).EndCol
		);
		// �O�Ղ̕`��ݒ�
		m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->DrawSet(*CCharacter::GetMatrix(m_modelAll[m_character]->v_MeshObitLoad.at(
			m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID).nPart));
		// �O�Ղ̕`��
		m_vec_pMeshObit.at(m_modelAll[m_character]->pMotion[m_nMotiontype].v_MeshObit_detail.at(nCntMotionObit).nObitID)->Draw();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���[�V�����J�����̍X�V
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::MotionCamera(void)
{
	// �ϐ��錾
	// ���擾
	static CCamera * pCamera = CManager::GetRenderer()->GetCamera();	// �J����
	// ���[�V�����J�����̐؂�ւ���OFF�̏ꍇ
	if (!m_bMotionCamera)
	{
		// �v�f���������珈�����s��
		if (m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera != NULL)
		{
			// �J�������[�V�����ݒ�
			pCamera->SetCamera_Motion(
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->offsetR + m_pos,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->rot + m_rot,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->fLength,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->fHeight,
				m_modelAll[m_character]->pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].pMotionCamera->fIntertia
			);
			// ���[�V�����J�����̐؂�ւ�
			m_bMotionCamera = true;
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�揈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Draw(void)
{
	// �ϐ��錾
	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	// �X�P�[���𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxRot);


	// �ʒu�𔽉f //
	// ���s�ړ��s��쐬(�I�t�Z�b�g)
	D3DXMatrixTranslation(&mtxTrans,	// �����̓��ꕨ
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:�ړ��s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxTrans);					// 3


	// ���f��
	for (int nCntModel = 0; nCntModel < m_NumParts[m_character]; nCntModel++)
	{
		// �k���`�F�b�N
		if (&m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel].Draw();
		}
	}
	// ���[�V�����O�ՍX�V
	Motion_Obit();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���񂾂Ƃ��̏���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Die(void)
{
	D3DXVECTOR3 ParticlePos;		// �p�[�e�B�N�����o��ʒu
	// �p�[�e�B�N���̈ʒu(�̂̈ʒu)
	ParticlePos = D3DXVECTOR3(
		CCharacter::GetMatrix(1)->_41,
		CCharacter::GetMatrix(1)->_42,
		CCharacter::GetMatrix(1)->_43
	);
	// �p�[�e�B�N������
	C3DParticle::Create(
		C3DParticle::OFFSET_ID_CROSSLINE,
		ParticlePos
	);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D�𐶐����鏈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::BalloonCreate(void)
{
	// ���D�𐶐����鏈��
	m_pBalloon->CreateBalloon();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �t�B�[���h�̍������Z�o
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CCharacter::GetFloorHeight(void)
{
	// �ϐ��錾
	CFloor * pFloor = NULL;	// ��
							// ���擾
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		pFloor = (CFloor*)CScene::GetScene( CScene::LAYER_3DOBJECT, nCntLayer,CFloor());	// ��
		if (pFloor != NULL)
		{
			// ���̍�������
			if (m_pos.y < pFloor->GetHeight(m_pos))
			{
				m_pos.y = pFloor->GetHeight(m_pos);
				m_move.y = 0;
				return true;
			}
		}
	}
	return false;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���[�V�����̃t���[�����擾����
// 1)�L�����N�^�[ID�A2)���[�V����ID�A3)���݂̃L�[�J�E���g
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CCharacter::GetMaxFrame(
	CHARACTER character,	// �L�����N�^�[
	int nMotionID,			// ���[�V����ID
	int nNowKeyCnt			// ���݂̃L�[�J�E���g
)
{
	// ���[�V�����S�̂̃t���[����
	if (nNowKeyCnt == -1)
	{
		return m_modelAll[character]->pMotion[nMotionID].nAllFrame;
	}
	// ��̃L�[�Ԃ̃t���[����
	return m_modelAll[character]->pMotion[nMotionID].KeyInfo[nNowKeyCnt].nFrame;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �J�����ǔ�����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CCharacter::GetCameraCharacter(void)
{
	return m_nCameraCharacter;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �d�͏���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::FagGravity(void)
{
	// �d�͏���
	m_move.y -= 1.0f;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���[�V�����ݒ菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::SetMotion(int const nMotiontype)
{
	// ���[�v��Ԃ̎�
	if (m_modelAll[m_character]->pMotion[m_nMotiontype].nLoop == 1)
	{
		m_nMotiontype = nMotiontype;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �������[�V�����ݒ菈��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::ComplusionSetMotion(int const nMotiontype)
{
	m_nMotiontype = nMotiontype;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ��]�擾����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 *CCharacter::GetPartsRot(int const nModelID)
{
	// ���f���̍s����擾
	if (nModelID >= 0 ||
		nModelID < m_NumParts[m_character])
	{
		return &m_pModel[nModelID].GetRot();
	}
	// �L�����N�^�[�̍s����擾
	else if (nModelID == -1)
	{
		return &m_rot;
	}
#ifdef _DEBUG
	CCalculation::Messanger("�L�����N�^�[�̃��f���̉�]��񂪂���܂���");
#endif // _DEBUG
	// �w�肳�ꂽID���Ȃ��ꍇ
	return &m_rot;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ʒu�擾����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 *CCharacter::GetPartsPos(int const nModelID)
{
	// ���f���̍s����擾
	if (nModelID >= 0 ||
		nModelID < m_NumParts[m_character])
	{
		return &m_pModel[nModelID].GetPos();
	}
	// �L�����N�^�[�̍s����擾
	else if (nModelID == -1)
	{
		return &m_rot;
	}
#ifdef _DEBUG
	CCalculation::Messanger("�L�����N�^�[�̃��f���̉�]��񂪂���܂���");
#endif // _DEBUG
	// �w�肳�ꂽID���Ȃ��ꍇ
	return &m_rot;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �s��擾����
// -1�̓L�����N�^�[�̍s����A0�`�̓��f���̍s����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
D3DXMATRIX * CCharacter::GetMatrix(int const nModelID)
{
	// ���f���̍s����擾
	if(nModelID >= 0 ||
		nModelID < m_NumParts[m_character])
	{
		return &m_pModel[nModelID].GetMatrix();
	}
	// �L�����N�^�[�̍s����擾
	else if (nModelID == -1)
	{
		return &m_mtxWorld;
	}
#ifdef _DEBUG
	CCalculation::Messanger("�L�����N�^�[�̃��f���̍s���񂪂���܂���");
#endif // _DEBUG
	// �w�肳�ꂽID���Ȃ��ꍇ
	return &m_mtxWorld;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::Load(
	CHARACTER const character,
	int const nMaxMotion,
	const char * file_name
)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	// ���f���ƃ��[�V�������̐���
	m_modelAll[character] = new MODEL_ALL;
	// �L�����N�^�[�̃e�L�X�g�f�[�^�̎擾
	CModel_info::TextLoad(
		m_modelAll[character],					// ���f�����
		m_modelId[character],					// ���f���t�@�C��
		nMaxMotion,								// ���[�V������
		m_NumModel[character],					// �ő僂�f����
		m_NumParts[character],					// ���������f����
		file_name								// �t�@�C����
	);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�e�[�^�X���ǂݍ��ݏ���
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CCharacter::LoadStatus(void)
{
	// �ϐ��錾
	vector<vector<string>> vsvec_Contens;	// �t�@�C���̒��g�i�[�p
	// �t�@�C���̒��g���擾����
	vsvec_Contens = CCalculation::FileContens(CHARACTER_STATUS_FILE, ',');
	// �s���Ƃɉ�
	for (int nCntLine = 0; nCntLine < (signed)vsvec_Contens.size(); nCntLine++)
	{
		// �L�����N�^�[������𒴂��Ă����甲����
		if (nCntLine >= CHARACTER_MAX)
		{
			break;
		}
		// ���ڂ��Ƃɉ�
		for (int nCntItem = 0; nCntItem < (signed)vsvec_Contens.at(nCntLine).size(); nCntItem++)
		{
			switch (nCntItem)
			{
				// ���D�̌�
			case 0:
				m_sStatus[nCntLine].nMaxBalloon = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
				// ������
			case 1:
				m_sStatus[nCntLine].nMaxInertia = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
				// �W�����v��
			case 2:
				m_sStatus[nCntLine].nMaxJump = stoi(vsvec_Contens.at(nCntLine).at(nCntItem));
				break;
			default:
				break;
			}
		}
	}
	// vector�̑��d�z��J��
	vector<vector<string>>().swap(vsvec_Contens);
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��񂾏���j������
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCharacter::UnLoad(
	CHARACTER const character,
	int const nMaxMotion)
{
	// �ϐ��錾
	int	nCntMotion = 0;		// ���[�V�����J�E���g
	int	nCntKeySet = 0;		// �t���[����6

	// ���f���E���[�V�����̔j��
	CModel_info::TextUnload(m_modelAll[character], nMaxMotion);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O�\��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
void CCharacter::Debug(void)
{
}
#endif // _DEBUG

