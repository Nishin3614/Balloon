// ----------------------------------------------------------------------------------------------------
//
// Calculation�w�b�_�[�����̐���[calculation.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------

#ifndef _CALCULATION_H_
#define _CALCULATION_H_	 // �t�@�C������������߂�

// ----------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

/*
#include <random>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <limits>
#include <type_traits>

std::mt19937 create_rand_engine()
{
	std::random_device rnd;
	std::vector<std::uint_least32_t> v(10);// �������p�x�N�^
	std::generate(v.begin(), v.end(), std::ref(rnd));// �x�N�^�̏�����
	std::seed_seq seed(v.begin(), v.end());
	return std::mt19937(seed);// �����G���W��
}

namespace detail
{
	template<typename T> auto diff(T n1, T n2) -> typename std::make_unsigned<T>::type
	{
		static_assert(std::is_integral<T>::value, "T is not integral.");
		if (n1 < n2) std::swap(n1, n2);
		return static_cast<typename std::make_unsigned<T>::type>(n1 - n2);
	}
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_unique(const size_t size, type rand_min, type rand_max)
{
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	std::vector<type> tmp;
	auto engine = create_rand_engine();
	std::uniform_int_distribution<type> distribution(rand_min, rand_max);

	const size_t make_size = size < std::numeric_limits<type>::max() - size / 5 ? size + size / 5 : std::numeric_limits<type>::max();

	tmp.reserve(make_size);
	while (tmp.size() < size) {
		while (tmp.size() < make_size) tmp.push_back(distribution(engine));
		std::sort(tmp.begin(), tmp.end());
		auto unique_end = std::unique(tmp.begin(), tmp.end());

		if (size < static_cast<size_t>(std::distance(tmp.begin(), unique_end))) {
			unique_end = std::next(tmp.begin(), size);
		}
		tmp.erase(unique_end, tmp.end());
	}

	std::shuffle(tmp.begin(), tmp.end(), engine);
	return tmp;
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_hash(const size_t size, type rand_min, type rand_max)
{
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	std::unordered_set<type> tmp;
	auto engine = create_rand_engine();
	std::uniform_int_distribution<type> distribution(rand_min, rand_max);
	while (tmp.size() < size) tmp.insert(distribution(engine));
	return std::vector<type>(tmp.begin(), tmp.end());
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_unique(const size_t size, type rand_min, type rand_max)
{
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	std::vector<type> tmp;
	auto engine = create_rand_engine();
	std::uniform_int_distribution<type> distribution(rand_min, rand_max);

	const size_t make_size = size < std::numeric_limits<type>::max() - size / 5 ? size + size / 5 : std::numeric_limits<type>::max();

	tmp.reserve(make_size);
	while (tmp.size() < size) {
		while (tmp.size() < make_size) tmp.push_back(distribution(engine));
		std::sort(tmp.begin(), tmp.end());
		auto unique_end = std::unique(tmp.begin(), tmp.end());

		if (size < static_cast<size_t>(std::distance(tmp.begin(), unique_end))) {
			unique_end = std::next(tmp.begin(), size);
		}
		tmp.erase(unique_end, tmp.end());
	}

	std::shuffle(tmp.begin(), tmp.end(), engine);
	return tmp;
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_shuffle(const size_t size, type rand_min, type rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	std::vector<type> tmp;
	tmp.reserve(max_min_diff);

	for (auto i = rand_min; i <= rand_max; ++i)tmp.push_back(i);

	auto engine = create_rand_engine();
	std::shuffle(tmp.begin(), tmp.end(), engine);

	tmp.erase(std::next(tmp.begin(), size), tmp.end());

	return tmp;
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_select(const size_t size, type rand_min, type rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	std::vector<type> tmp;
	tmp.reserve(max_min_diff);

	for (auto i = rand_min; i <= rand_max; ++i)tmp.push_back(i);

	auto engine = create_rand_engine();

	for (size_t cnt = 0; cnt < size; ++cnt) {
		size_t pos = std::uniform_int_distribution<size_t>(cnt, tmp.size() - 1)(engine);

		if (cnt != pos) std::swap(tmp[cnt], tmp[pos]);
	}
	tmp.erase(std::next(tmp.begin(), size), tmp.end());

	return tmp;
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_select_with_hash(const size_t size, type rand_min, type rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	//	if(max_min_diff < size) throw std::runtime_error("Invalid argument");
	using hash_map = std::unordered_map<type, type>;

	std::vector<type> tmp;
	tmp.reserve(size);

	hash_map Map;

	auto engine = create_rand_engine();
	for (size_t cnt = 0; cnt < size; ++cnt) {
		type val = std::uniform_int_distribution<type>(rand_min, rand_max)(engine);
		auto itr = Map.find(val);

		type replaced_val;
		auto replaced_itr = Map.find(rand_max);
		if (replaced_itr != Map.end()) replaced_val = replaced_itr->second;
		else replaced_val = rand_max;

		if (itr == Map.end()) {
			tmp.push_back(val);
			if (val != rand_max)Map.insert(std::make_pair(val, replaced_val));
		}
		else {
			tmp.push_back(itr->second);
			itr->second = replaced_val;
		}

		//Map.erase(replaced_val);

		--rand_max;
	}

	return tmp;
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_select_with_hash_no_itr(const size_t size, type rand_min, type rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("�������ُ�ł�");
	std::vector<type> re(size);
	std::unordered_map<type, type> conversion;

	auto engine = create_rand_engine();
	for (auto& r : re) {
		type key = std::uniform_int_distribution<type>(0, max_min_diff)(engine);
		if (!conversion.count(key)) conversion[key] = key;
		auto& conv_at_key = conversion[key];
		r = conv_at_key + rand_min;
		type conv_key = static_cast<type>(max_min_diff - 1);
		conv_at_key = (conversion.count(conv_key)) ? conversion[conv_key] : conv_key;
		--max_min_diff;
	}

	return re;
}

int* fn3_2_make_rand_array_select(const size_t size, int rand_min, int rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const size_t max_min_diff = static_cast<size_t>(rand_max - rand_min + 1);
	if (max_min_diff < size) throw std::runtime_error("�������ُ�ł�");

	int* tmp = (int*)malloc(sizeof(int) * max_min_diff);
	int* srcPtr = tmp;
	for (int i = rand_min; i <= rand_max; i++, srcPtr++)
	{
		*srcPtr = i;
	}

	auto engine = create_rand_engine();
	int distMax = max_min_diff - 1;
	//std::uniform_int_distribution<int> distribution(0, distMax); // ������̕����K��(����A�S���h�a)

	// �擪����߂�l���i�[���郋�[�v
	int* dstPtr = tmp;
	for (size_t cnt = 0; cnt < size; cnt++, dstPtr++) {
		// size��0�̏ꍇ�́A0 > (max_min_diff - 1)�̉\�������� (���s�������runtime_error�ɂȂ�͂�)
		std::uniform_int_distribution<int> distribution(cnt, distMax); // ���̃��W�b�N(���h�a�����̂ݑ���)
		size_t pos = distribution(engine);
		if (cnt != pos) {
			// �㏑������O�ɑޔ�
			int old = *dstPtr; // tmp[cnt]
			*dstPtr = tmp[pos]; // �߂�l������
			tmp[pos] = old; // �g�����l�Ǝg���Ă��Ȃ��l����ւ�
		}
		// cnt��pos�������ꍇ�́A���̒l�̂܂܎c��
	}

	// �擪���璷��size�̃f�[�^��߂�l�Ƃ��Ďg��
	// �g�p��́A�Ăяo������free(tmp)���ĂԂ���
	return tmp;
}

template<typename type>
std::vector<type> make_nonrepeat_rand_array_select2(const size_t size, type rand_min, type rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	std::vector<type> tmp(max_min_diff);
	int i = 0;
	for (auto itr = std::begin(tmp); itr != std::end(tmp); ++itr) *itr = i++;

	auto engine = create_rand_engine();

	for (size_t cnt = 0; cnt < size; ++cnt) {
		size_t pos = std::uniform_int_distribution<size_t>(cnt, tmp.size() - 1)(engine);

		if (cnt != pos) std::swap(tmp[cnt], tmp[pos]);
	}
	tmp.erase(std::next(tmp.begin(), size), tmp.end());

	return tmp;

}

template<typename type>
std::vector<type> make_nonrepeat_rand_array(const size_t size, type rand_min, type rand_max) {
	if (rand_min > rand_max) std::swap(rand_min, rand_max);
	const auto max_min_diff = detail::diff(rand_max, rand_min) + 1;
	//	if (max_min_diff < size) throw std::runtime_error("Invalid argument");

	if (size < max_min_diff / 32) {
		return make_nonrepeat_rand_array_unique(size, rand_min, rand_max);
	}
	else {
		return make_nonrepeat_rand_array_select(size, rand_min, rand_max);
	}
}
*/

// ----------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------
// D3DVECTOR2�^�̏�����(1.0f)
#define D3DVECTOR2_INI			D3DXVECTOR2(1.0f,1.0f)
// D3DVECTOR2�^�̏�����(0.0f)
#define D3DVECTOR2_ZERO			D3DXVECTOR2(0.0f,0.0f)
// D3DVECTOR3�^�̏�����(0.0f)
#define D3DVECTOR3_ZERO			D3DXVECTOR3(0.0f,0.0f,0.0f)
// D3DVECTOR3�^�̏�����(1.0f)
#define D3DVECTOR3_ONE			D3DXVECTOR3(1.0f,1.0f,1.0f)
// D3DVECTOR4�^�̏�����(0.0f)
#define D3DVECTOR4_ZERO			D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f)
// D3DXCOLOR�^�̏�����
#define D3DXCOLOR_INI			D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
// D3DXCOLOR�^�̏�����(��{�F)
#define D3DXCOLOR_C(col)		D3DXCOLOR(col,col,col,1.0f)
// D3DXCOLOR�^�̏�����(��{�F,�����x)
#define D3DXCOLOR_CA(col,alpha)	D3DXCOLOR(col,col,col,alpha)
// �t�@�C���ǂݍ��ݍő�s��
#define FILELINE_ERROW (1048576)

// ----------------------------------------------------------------------------------------------------
//
// Calculation���
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// �񋓌^��`
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// �\���̒�`
//
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
//
// ���O��`
//
// ----------------------------------------------------------------------------------------------------
namespace MYLIBLARY
{
	void in(void);
	// ���������s�̕����|�C���^�[
	typedef const char * P_CST_CHAR;

}

// �����^2��
typedef struct INTEGER2
{
	INTEGER2() {}
	INTEGER2(int X, int Y)
	{
		nMax = X;
		nMin = Y;
	}
	int nMax;
	int	nMin;
}INTEGER2, *PINTEGER2;

// �����^3��
typedef struct INTEGER3
{
public:
	INTEGER3() {}
	INTEGER3(int X, int Y, int Z)
	{
		nX = X;
		nY = Y;
		nZ = Z;
	}
	// �L���X�g
	inline operator int* ()
	{
		(int *)nX;
		(int *)nY;
		(int *)nX;
		return *this;
	}
	inline operator CONST int* () const
	{
		(CONST int *)nX;
		(CONST int *)nY;
		(CONST int *)nZ;
		return *this;
	}
	// ������Z�q
	INTEGER3& operator += (CONST INTEGER3& Source)
	{
		nX += Source.nX;
		nY += Source.nY;
		nZ += Source.nZ;
		return *this;
	}
	INTEGER3& operator -= (CONST INTEGER3& Source)
	{
		nX -= nX;
		nY -= nY;
		nZ -= nZ;
		return *this;
	}
	INTEGER3& operator *= (int Source)
	{
		nX *= Source;
		nY *= Source;
		nZ *= Source;
		return *this;
	}
	INTEGER3& operator /= (int Source)
	{
		nX /= Source;
		nY /= Source;
		nZ /= Source;
		return *this;
	}
	// 2�����Z�q
	INTEGER3 operator + (CONST INTEGER3& Source) const
	{
		// �l��n���ϐ�
		INTEGER3 variable;
		variable.nX = nX + Source.nX;
		variable.nY = nY + Source.nY;
		variable.nZ = nZ + Source.nZ;
		return variable;
	}
	INTEGER3 operator - (CONST INTEGER3& Source) const
	{
		// �l��n���ϐ�
		INTEGER3 variable;
		variable.nX = nX - Source.nX;
		variable.nY = nY - Source.nY;
		variable.nZ = nZ - Source.nZ;
		return variable;
	}
	bool operator == (CONST INTEGER3& Source) const
	{
		return Source == INTEGER3(nX, nY, nZ);
	}
	bool operator != (CONST INTEGER3& Source) const
	{
		return Source != INTEGER3(nX, nY, nZ);
	}

	int nX,		// X������
		nY,		// Y������
		nZ;		// Z������
} INTEGER3, *PINTEGER3;

// �����^4��
typedef struct INTEGER4
{
	INTEGER4() {}
	INTEGER4(
		int d_X, 
		int d_Y,
		int d_Z,
		int d_W
	)
	{
		X = d_X;
		Y = d_Y;
		Z = d_Z;
		W = d_W;
	}
	int X;
	int	Y;
	int Z;
	int	W;
}INTEGER4, *PINTEGER4;

// �z�u�I�u�W�F�N�g���(1:�^�C�v,2:�ʒu,3:��])
typedef struct ARRANGEMENTOBJ
{
	ARRANGEMENTOBJ() {}
	ARRANGEMENTOBJ(
		int d_nType,
		D3DXVECTOR3 d_pos,
		D3DXVECTOR3 d_rot
	)
	{
		nType = d_nType;
		pos = d_pos;
		rot = d_rot;
	}
	int			nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} ARRANGEMENTOBJ,*pARRANGEMENTOBJ;

// �z�u�|���S�����(1:�^�C�v,2:�ʒu,3:��],4:�T�C�YA,5:�T�C�YB)
typedef struct ARRANGEMENTPOLYGON
{
	ARRANGEMENTPOLYGON() {}
	ARRANGEMENTPOLYGON(
		int d_nType,
		D3DXVECTOR3 d_pos,
		D3DXVECTOR3 d_rot,
		float		d_fSizeA,
		float		d_fSizeB
	)
	{
		nType = d_nType;
		pos = d_pos;
		rot = d_rot;
		fSizeA = d_fSizeA;
		fSizeB = d_fSizeB;
	}
	int			nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float		fSizeA;
	float		fSizeB;
} ARRANGEMENTPOLYGON, *pARRANGEMENTPOLYGON;

// �z�u���b�V�����(1:�^�C�v,2:�ʒu,3:��]4:�c�u���b�N,5:���u���b�N,6:�T�C�YA,7:�T�C�YB)
typedef struct ARRANGEMENTMESH
{
	ARRANGEMENTMESH() {}
	ARRANGEMENTMESH(
		int d_nType,
		D3DXVECTOR3 d_pos,
		D3DXVECTOR3 d_rot,
		int			d_nBlockDepth,
		int			d_nBlockWidth,
		float		d_fSizeA,
		float		d_fSizeB
	)
	{
		nType = d_nType;
		pos = d_pos;
		rot = d_rot;
		nBlockDepth = d_nBlockDepth;
		nBlockWidth = d_nBlockWidth;
		fSizeA = d_fSizeA;
		fSizeB = d_fSizeB;
	}
	int			nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int			nBlockDepth;
	int			nBlockWidth;
	float		fSizeA;
	float		fSizeB;
} ARRANGEMENTMESH, *pARRANGEMENTMESH;

// �t�@�C���i�[�p�ϐ�
typedef struct CHARFILE
{
	char		cFile
		[64];		// ���f���̃t�@�C����
} CHARFILE;

// ----------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------
#define INTEGER4_INI			INTEGER4(1,1,1,1)				

// ----------------------------------------------------------------------------------------------------
//
// �N���X
//
// ---------------------------------------------------------------------------------------------------- 
class CCalculation
{
public:
	/* �֐� */
	// unique_ptr[int]�^�̏���Ԃ�
	// ����:�Ԃ�����std::move���g�p���邱��
	static unique_ptr<int> int_ptr(
		int const nNum = 0
	);
	// unique_ptr[bool]�^�̏���Ԃ�
	// ����:�Ԃ�����std::move���g�p���邱��
	static unique_ptr<bool> bool_ptr(void);
	// �����̌v�Z
	static D3DXVECTOR3 Difference_Between(
		D3DXVECTOR3 &posA,
		D3DXVECTOR3 &posB
	);
	// �Ԃ̍��̌v�Z(3D�p:�ʒu�A�ʒu)
	static float DiffPoint(
		D3DXVECTOR3 const & posA,
		D3DXVECTOR3 const & posB
	);
	// �Ԃ̍��̌v�Z(2D�p:�ʒu�A�ʒu)
	static float DiffPoint(
		D3DXVECTOR2 const & posA,
		D3DXVECTOR2 const & posB
	);
	// �Ԃ̍���2��v�Z(3D�p:�ʒu�A�ʒu)
	static float DiffPointSquare(
		D3DXVECTOR3 const & posA,
		D3DXVECTOR3 const & posB
	);
	// �Ԃ̍���2��v�Z(2D�p:�ʒu�A�ʒu)
	static float DiffPointSquare(
		D3DXVECTOR2 const & posA,
		D3DXVECTOR2 const & posB
	);

	// �O�ς̌v�Z
	static D3DXVECTOR3 Cross_product(
		D3DXVECTOR3 &VecA,
		D3DXVECTOR3 &VecB
	);
	// ���ς̌v�Z
	static float Dot_product(
		D3DXVECTOR3 &VecA,
		D3DXVECTOR3 &VecB
	);
	// �l�p�`�̒��ɓ����Ă��邩���Ȃ���
	static bool SquareBottom_Judg(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
		D3DXVECTOR3 rot,
		int			nBlock_W,
		int			nBlock_H,
		D3DXVECTOR3 worldpos
	);

	// �l�p�`�̒��ɓ����Ă��邩���Ȃ���
	static bool SquareSide_Judg(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
		D3DXVECTOR3 rot,
		int			nBlock_W,
		int			nBlock_H,
		D3DXVECTOR3 worldpos
	);

	// ���̑����Z
	static float Addition_Sphere(
		float Length_x,
		float Length_y,
		float Length_z
	);
	// �~�̓����蔻��
	static bool Collision_Circle(
		D3DXVECTOR2 &Me,
		float		fMeSize,
		D3DXVECTOR2 &Opponent,
		float		fOppSize
	);
	// ���̓����蔻��
	static bool Collision_Sphere(
		D3DXVECTOR3 const &Me,
		float const &fMeSize,
		D3DXVECTOR3 const &Opponent,
		float const &fOppSize
	);
	// ��]�ʂ̏�� //
	static float Rot_One_Limit(
		float &fRot
	);
	// �X�N���[�����W�����[���h���W�ɕϊ�
	static D3DXVECTOR3* CalcScreenToWorld(
		D3DXVECTOR3* pout,		// �}�E�X�|�C���g
		float Sx,				// �X�N���[��X���W
		float Sy,				// �X�N���[��Y���W
		float fZ,				// �ˉe��Ԃł�Z�l�i0�`1�j
		float Screen_w,			// �X�N���[���̉���
		float Screen_h,			// �X�N���[���̍���
		D3DXMATRIX* mtxView,	// �r���[�}�g���b�N�X
		D3DXMATRIX* mtxPrj	// �v���W�F�N�V�����}�g���b�N�X
	);
	// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
	static D3DXVECTOR3* CalcScreenToXZ(
		D3DXVECTOR3* pout,		// �}�E�X�|�C���g
		float Sx,				// �X�N���[��X���W
		float Sy,				// �X�N���[��Y���W
		float Screen_w,			// �X�N���[���̉���
		float Screen_h,			// �X�N���[���̍���
		D3DXMATRIX* mtxView,	// �r���[�}�g���b�N�X
		D3DXMATRIX* mtxPrj,		// �v���W�F�N�V�����}�g���b�N�X
		D3DXVECTOR3 obj			// �I�u�W�F�N�g�̈ʒu
	);	
	// ���[���h���W���X�N���[�����W�ɕϊ�(����)
	static D3DXVECTOR3* CalcWorldToScreen(
		D3DXVECTOR3* Obj,		// �I�u�W�F�N�g�̈ʒu
		float Sx,					// �X�N���[��X���W
		float Sy,					// �X�N���[��Y���W
		float fZ,				// �ˉe��Ԃł�Z�l�i0�`1�j
		float Screen_w,			// �X�N���[���̉���
		float Screen_h,			// �X�N���[���̍���
		D3DXMATRIX* mtxView,	// �r���[�}�g���b�N�X
		D3DXMATRIX* mtxPrj	// �v���W�F�N�V�����}�g���b�N�X
	);
	// �ꎟ�֐�
	static D3DXVECTOR2 Linear_function(
		D3DXVECTOR3 Apos,			// �n�_
		D3DXVECTOR3 Bpos			// �I�_
	);
	// 2�����̌�_(�A��������)
	static D3DXVECTOR3 TwoLine_Inse(
		D3DXVECTOR2 ALinear,	// ���@
		D3DXVECTOR2 BLinear	// ���A
	);
	// �r���̌v�Z
	static bool TlyCollision(
		D3DXVECTOR3 ObjectPos,
		D3DXVECTOR3,
		...
	);
	// �O�ς̓����蔻��
	static bool CrossCollision(
		D3DXVECTOR3 *ObjectPos,
		D3DXVECTOR3 *PosA,
		D3DXVECTOR3 *PosB,
		D3DXVECTOR3 *PosC
	);
	// �s��̈ʒu���擾
	// 1:�ʒu���,2:�s��
	static D3DXVECTOR3 Vector3ToMatrix(
		D3DXVECTOR3 &vector3Out,
		D3DXMATRIX const &mtx
	);
	// �s��̈ʒu���擾
	// 1:�s��
	static D3DXVECTOR3 Vector3ToMatrix(
		D3DXMATRIX const &mtx
	);
	// �����𑪂�(10�Ŋ�����@:�������Ȃ����ɗ��p)
	static unsigned GetDigit_Division(unsigned nNum);
	// �����𑪂�(��p�ΐ����@:�����s����ő傫�����ɗ��p)
	static unsigned GetDigit_CommonLogarithm(unsigned nNum);
	// �����𑪂�(��������@:�R�[�f�B���O������)
	static unsigned GetDigit_Char(unsigned nNum);
	// �r���{�[�h�̐ݒ�
	static void SetBillboard(
		D3DXMATRIX *Originmtx,	// ���ɂȂ�s����
		D3DXMATRIX *Viewmtx		// �r���[�s����
	);
	// ���b�Z�[�W����
	static void Messanger(
		const char * cMessa,	// ���b�Z�[�W���e
		HWND hWnd = NULL
	);
	// �L�[�����̔��f
	static void KeyString(
		int nKeyID,				// �L�[ID
		char *KeyName = NULL	// ����
	);
	// �t�@�C�������݂��Ă��邩
	static bool Existenceofscript(FILE * pFile);
	// �e�N�X�`���[��񂩂�e�N�X�`���[�T�C�Y�̎擾(2D)
	static bool GetTexSize(
		LPDIRECT3DTEXTURE9 pTex,
		D3DXVECTOR2 *pSize
	);
	// �e�N�X�`���[��񂩂�e�N�X�`���[�T�C�Y�̎擾(3D)
	static bool GetTexSize(
		LPDIRECT3DTEXTURE9 pTex,
		D3DXVECTOR3 * pSize
	);
	// ���������̋�؂育�ƂɎ擾����(1�s����)
	static vector<string> split(
		string& input,		// 1�s�̃X�g���[��
		char delimiter		// ��؂蕶��
	);
	// ���������̋�؂育�ƂɎ擾����(�t�@�C���S��)
	static vector<vector<string>> FileContens(
		char const * cns_cFile,	// �t�@�C����
		char delimiter			// ��؂蕶��
	);

	/* ImGui�p�֐� */
	// ImGui�ɂ��f�o�b�O���
	static void ImG_DebugInfo(void);

	// ImGui�ɂ����񏈗�
	static void ImG_Parallel(void);
protected:

private:
	/* �ϐ� */
	static bool m_bWire;
};

// ----------------------------------------------------------------------------------------------------
//
// �v���g�^�C�v�錾
//
// ----------------------------------------------------------------------------------------------------

#endif