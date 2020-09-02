// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 3D�}�b�v�����̐���[3Dmap.h]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _3DMAP_H_
#define _3DMAP_H_	 // �t�@�C������������߂�

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene_X.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class C3DMap
{
public:
	/* �񋓌^ */
	typedef enum
	{
		MAP_STAGE_1 = 0,
		MAP_STAGE_2,
		MAP_MAX
	} MAP;
	/* �񋓌^ */
	// 3D�I�u�W�F�N�g
	typedef struct OBJECT
	{
		OBJECT()
		{
			nModelType = 0;
			pos = D3DVECTOR3_ZERO;
			rot = D3DVECTOR3_ZERO;
		}
		int nModelType;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	} OBJECT;
	// �L�����N�^�[
	typedef struct CHARACTER
	{
		CHARACTER()
		{
			nCharacter = 0;
			pos = D3DVECTOR3_ZERO;
			rot = D3DVECTOR3_ZERO;
		}
		int nCharacter;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	} CHARACTER;
	// �|���S��
	typedef struct POLYGON
	{
		POLYGON()
		{
			nTexType = 0;
			pos = D3DVECTOR3_ZERO;
			rot = D3DVECTOR3_ZERO;
			size = D3DVECTOR2_ZERO;
			bBillboard = false;
			bZEneble = false;
			bLighting = false;
			bAlpha = false;
		}
		int nTexType;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR2 size;
		bool bBillboard;
		bool bZEneble;
		bool bLighting;
		bool bAlpha;
	} POLYGON;
	// ��
	typedef struct FLOOR
	{
		FLOOR()
		{
			nTexType = 0;
			pos = D3DVECTOR3_ZERO;
			rot = D3DVECTOR3_ZERO;
			nBlockDepth = 0;
			nBlockWidth = 0;
			size = D3DVECTOR2_ZERO;
		}
		int nTexType;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nBlockDepth;
		int nBlockWidth;
		D3DXVECTOR2 size;
	} FLOOR;
	// ��
	typedef struct WALL
	{
		WALL()
		{
			nTexType = 0;
			pos = D3DVECTOR3_ZERO;
			rot = D3DVECTOR3_ZERO;
			nBlockDepth = 0;
			nBlockWidth = 0;
			size = D3DVECTOR2_ZERO;
		}
		int nTexType;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nBlockDepth;
		int nBlockWidth;
		D3DXVECTOR2 size;
	} WALL;

	/* �֐� */
	C3DMap();
	~C3DMap();
#ifdef _DEBUG
	static void Debug(void);
#endif // _DEBUG
	static HRESULT LoadCreate(MAP const &map);					// �ǂݍ��񂾏��𐶐�
	static void LoadScript(char* Add);
	static HRESULT Load(void);						// ���\�[�X���ǂݍ��ސݒ�
	// �}�l�[�W���[�̓ǂݍ���
	static HRESULT ManagerLoad(void);
	// �X�N���v�g�̓ǂݍ���
	static HRESULT ScriptLoad(void);
	static void UnLoad(void);						// �ǂݍ��񂾃��\�[�X�����J������
protected:
private:
	/* �֐� */
	// �L�����N�^�[����
	void CharaCreate(void);
	/* �ϐ� */
	static std::vector<std::vector<OBJECT>> m_vec_obj;
	static std::vector<std::vector<CHARACTER>> m_vec_char;
	static std::vector<std::vector<POLYGON>> m_vec_polygon;
	static std::vector<std::vector<FLOOR>> m_vec_floor;
	static std::vector<std::vector<WALL>> m_vec_wall;
	static std::vector<std::string> m_vec_String;					// �t�@�C�����ǂݏ����p
	static D3DXVECTOR3 m_CollisionPos[3];
	int m_nType;									// �^�C�v
};

#endif