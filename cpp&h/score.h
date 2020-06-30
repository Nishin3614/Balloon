//=============================================================================
//
// �X�R�A[score.h]
// Author:Ryouma Inoue
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

#define MAX_SCORE (8)

#define SCORE_POS_X (100.0f)			 // X�̈ʒu
#define SCORE_POS_Y (100.0f)			 // Y�̈ʒu
#define SCORE_SIZE_X (33.0f)			 // X�̃T�C�Y
#define SCORE_SIZE_Y (50.0f)			 // Y�̃T�C�Y
#define SCORE_INTERVAL_X (33)			 // ���̊��o
#define SCORE_INTERVAL (10.0f)			 // 

class CNumber;
//=============================================================================
//
// �N���X�̒�`
//
//=============================================================================
class CScore : public CScene
{
public:

	CScore();					// �R���X�g���N�^
	~CScore();					// �f�X�g���N�^

	void Init(void);			// ������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
	void Draw(void);			// �`��
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
	void SetPos(D3DXVECTOR3 pos);
	void AddScore(int nValue);
	void SetScore(int nScore);

	static int GetNowScore(void);
	static CScore *GetScore(void);
	static CScore *Create(void);

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;
	static CScore *m_pScore;
	static int	m_nScore;				// �X�R�A

	CNumber *m_apNumber[MAX_SCORE];
	D3DXVECTOR3 m_pos;
	int	m_nRanking;

};
#endif