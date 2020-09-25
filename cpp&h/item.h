// ==========================================================
//
// �A�C�e��[item.h]
// Author:Ryouma Inoue
//
// ==========================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene_three.h"

#define MAX_BULLET_TEX (4)
#define MAX_BULLET (200)								// �A�C�e���̍ő吔
#define BULLET_SIZE (100.0f)								// �A�C�e���̃T�C�Y
#define	TEXTURE_COIN	"data/TEXTURE/coin_anim.png"			// �ǂݍ��ރe�N�X�`���t�@�C����

// ==========================================================
//
// �O���錾
//
// ==========================================================
class CCollision;

// ==========================================================
//
// �N���X�̒�`
//
// ==========================================================
class CItem : public CScene_THREE
{
public:
	/* �\���� */
	// �X�e�[�^�X���
	typedef struct STATUS
	{
		/* �֐� */
		// ������
		STATUS()
		{
			nScorePoint = 200;	// �X�R�A�|�C���g
			nMpUp = 0;			// MP�A�b�v
		}
		/* �ϐ� */
		int	nScorePoint;		// �X�R�A�|�C���g
		int nMpUp;				// MP�A�b�v
	} STATUS, *PSTATUS;

	CItem();												// �R���X�g���N�^
	~CItem();												// �f�X�g���N�^

	void Init(void);										// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��
	// ����������̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_MyCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	);
	// ����ɓ��Ă�ꂽ��̏���
	//	nObjType	: �I�u�W�F�N�g�^�C�v
	//	pScene		: ����̃V�[�����
	void Scene_OpponentCollision(
		int const &nObjType = 0,	// �I�u�W�F�N�g�^�C�v
		CScene * pScene = NULL		// ����̃V�[�����
	);
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
	bool ItemCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin);				// �e�̓����蔻��
	CCollision *GetCollision(void) { return m_pCollision; }
	// �X�e�[�^�X(�L�����N�^�[��)
	static STATUS &GetStatus(void) { return m_sStatus; };

	static CItem *Create(const int nId, D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����
	static HRESULT Load(void);													// ���[�h
	static void Unload(void);													// �A�����[�h
	static void LoadStatus(void);
	static int &GetAllItem(void) { return m_nAllItem; };
protected:

private:
	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`��
	static STATUS	m_sStatus;					// �A�C�e���̃X�^�[�^�X���
	static int m_nAllItem;						// �A�C�e���̌�
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *m_pVtx;							// ���_���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X

	static CItem *m_pItem;

	D3DXVECTOR3	m_vtxMin;								// �ŏ��l
	D3DXVECTOR3	m_vtxMax;								// �ő�l
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_rot;									// ��]
	D3DXVECTOR3 m_move;									// �ړ���
	D3DXCOLOR m_col;									// �F
	CCollision * m_pCollision;							// �����蔻����
	int m_nCntEffect;
	int m_nId;											// �R�C����ID

};
#endif