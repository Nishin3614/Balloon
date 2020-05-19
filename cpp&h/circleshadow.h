// ----------------------------------------
//
// �~�`�L�����N�^�[�����̐���[circleshadow.h]
// Author : Koki Nishiyama
//
// ----------------------------------------
#ifndef _CIRCLESHADOW_H_
#define _CIRCLESHADOW_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_three.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define CIRCLESHADOW_HP (20)
#define CIRCLESHADOW_MP (50)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CCircleshadow : public CScene_THREE
{
public:
	/* �񋓌^ */

	/* �֐� */
	CCircleshadow();
	~CCircleshadow();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// �쐬(�V�[���p������)
	static CCircleshadow * Create(
		D3DXVECTOR3 const &pos,							// �ʒu
		D3DXVECTOR3 const &size							// �T�C�Y
	);					// �쐬
	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
	// �ݒ� //

	// �擾 // 
protected:
private:
	/* �֐� */
	/* �ϐ� */
};
#endif