#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <DirectXMath.h>
#include "..//Engine/Math/Color3.h"
#include "..//Engine/Math/Color4.h"
#include "..//Engine/Math/Vector2.h"
#include "..//Engine/Math/Vector3.h"
#include "..//Engine/Math/Vector4.h"

// �O���錾
class PMXBinaryReader;

// �C���f�b�N�X�T�C�Y
enum class PMXIndexSize : uint8_t
{
	Int8 = 1,
	Int16 = 2,
	Int32 = 4
};

// PMX�w�b�_�[�f�[�^
struct PMXHeader
{
	char signature[4];				// PMX
	float version;					// �o�[�W����
	uint8_t indexSizeTableCount;	// �^�e�[�u���̃T�C�Y
	uint8_t encoding;				// �G���R�[�h����( 0:UTF16 1:UTF8)
	uint8_t additionalUVCount;		// �ǉ�UV�� (0�`4)
	uint8_t indexSizeTable[6];

	PMXHeader(PMXBinaryReader& reader);
};

// PMX���f���̐���
struct PMXModelInformation
{
	std::string name;				// ���f����
	std::string nameEnglish;		// ���f�����p
	std::string comment;			// �R�����g
	std::string commentEnglish;		// �R�����g�p
	PMXModelInformation(PMXBinaryReader& reader);
};

// �E�F�C�g�ό`����
enum class PMXWeightType : uint8_t
{
	BDEF1,	// BoneDefomation(�{�[���ό`) 
	BDEF2,
	BDEF4,
	SDEF	// SphereDefomation(���̕ό`)
};

// PMX���_�f�[�^
struct PMXVertex
{
	Engine::Vector3 position;			// �ʒu
	Engine::Vector3 normal;				// �@��
	Engine::Vector2 texcoord;			// �e�N�X�`���R�[�h(u,v)
	std::vector<Engine::Vector4> addTexcoord;	// �ǉ�UV
	PMXWeightType type;					// �E�F�C�g�ό`����

	static const uint32_t maxBone = 4;	// 1���_�ɉe����^����ő�{�[����
	uint32_t boneIndex[maxBone];		// �{�[���ԍ�
	float boneWeight[maxBone];			// �{�[���̃E�F�C�g�l
	Engine::Vector3 sdefC;				// SDEF-C�l(x,y,z)
	Engine::Vector3 sdefR0;				// SDEF-R0�l(x,y,z)
	Engine::Vector3 sdefR1;				// SDEF-R1�l(x,y,z)

	float edge;							// �G�b�W�{��

};

// PMX�ʃf�[�^
struct PMXIndex
{
	uint32_t index[3];		// �C���f�b�N�X�o�b�t�@�p
};

// PMX�e�N�X�`���f�[�^
struct PMXTexture
{
	std::string textureFileName;
};

// �`��t���O
enum class PMXRenderFlag : uint8_t
{
	Both = 0x01,				// ���ʕ`��
	GroundShadow = 0x02,		// �n�ʉe
	CasterSelfShadow = 0x04,	// �Z���t�V���h�E�}�b�v�ւ̕`��
	ReceviorSelfShadow = 0x08,	// �Z���t�V���h�E�̕`��
	RenderEdge = 0x10			// �G�b�W�`��
};

// �X�t�B�A���[�h
enum class PMXSphereMode : uint8_t
{
	None = 0,		// ����
	Sph = 1,		// ��Z
	Spa = 2,		// ���Z
	SubTexture = 3	// �T�u�e�N�X�`��(�ǉ�UV1��x,y��UV�Q�Ƃ��Ēʏ�e�N�X�`���`����s��)
};

// ���L�g�D�[���t���O
enum class PMXShareToonFlag : uint8_t
{
	Individual = 0,	// ��
	Share = 1		// ���L
};

// PMX�}�e���A���f�[�^
struct PMXMaterial
{
	std::string name;				// �ގ���
	std::string nameEnglish;		// �ގ����p
	Engine::Color4 diffuseCoeff;	// �f�B�t���[�Y�W��
	Engine::Color3 specularCoeff;	// �X�y�L�����[�W��
	float specularity;				// ���ʔ��ˋ��x
	Engine::Color3 ambientCoeff;	// �A���r�G�C�g�W��
	PMXRenderFlag renderFlag;		// �`��t���O
	Engine::Vector4 edge;					// �G�b�W�F
	float edgeSize;					// �G�b�W�T�C�Y

	uint32_t decalIndex;				// �ʏ�e�N�X�`��
	uint32_t sphereIndex;			// �X�t�B�A�e�N�X�`��

	PMXSphereMode sphereFlag;		// �X�t�B�A���[�h

	PMXShareToonFlag shareToonFlag;	// ���L�g�D�[���t���O
	uint32_t toonIndex;				// �g�D�[���e�N�X�`��
	uint8_t shereToonTexture;		// ���L�g�D�[���e�N�X�`��

	std::string memo;				// �����@�X�N���v�g,�G�t�F�N�g�̃p�����[�^�z�u
	uint32_t indexCount;				// ���̃}�e���A�����g�p���钸�_��(�K��3�̔{��)

};

// �{�[���t���O
enum class PMXBoneFlag : uint16_t
{
	AccessShowMode = 0x0001,			// �ڑ���(PMD�q�{�[���w��)�\�����@ -> 0:���W�I�t�Z�b�g�Ŏw�� 1:�{�[���Ŏw��

	VailableRotation = 0x0002,			// ��]�\
	VailableTranslation = 0x0004,		// �ړ��\
	Visible = 0x0008,					// �\��
	VailableControl = 0x0010,			// ����\

	IK = 0x0020,						// IK

	RotateAppend = 0x0100,				// ��]�t��
	TranlateAppend = 0x0200,			// �ړ��t��

	FixedAxis = 0x0400,					// ���Œ�
	LocalAxis = 0x0800,					// ���[�J����

	DeformationPhysical = 0x1000,		// ������ό`
	DeformOuterParent = 0x2000			// �O���e�ό`
};

// �p�x�����t���O
enum class PMXLimitFlag : uint8_t
{
	OFF = 0,
	ON = 1
};

struct PMXIKLink
{
	uint32_t linkIndex;				// �����N�{�[���ԍ�
	PMXLimitFlag limitFlag;			// �p�x�����t���O()

	// �p�x����1
	Engine::Vector3 lowerLimitAngle;			// ����(x,y,z)���W�A���p
	Engine::Vector3 upperLimitAngle;			// ���(x,y,z)���W�A���p

};

// PMX�{�[���f�[�^
struct PMXBone
{
	std::string name;				// ���O
	std::string nameEnglish;		// ���O�p��
	Engine::Vector3 position;				// �ʒu
	uint32_t parentIndex;			// �e�{�[���ԍ�
	uint32_t transformHierarchy;	// �ό`�K�w

	PMXBoneFlag boneFlag;			// �{�[���t���O

	// �ڑ���0
	Engine::Vector3 offsetPosition;			// ���W�I�t�Z�b�g
	// �ڑ���1
	uint32_t connectIndex;			// �ڑ���{�[���ԍ�
	// ��]�t�^1,�ړ��t�^1
	uint32_t influenceTargetIndex;	// �e����^����{�[���ԍ�
	float influenceCoeff;			// �e���x(�t�^��)(�ǂ̒��x�e����^���邩)

	// ���Œ�1
	Engine::Vector3 axisVector;				// ���̕����x�N�g��
	// ���[�J����1
	Engine::Vector3 xAxis;					// X���̕����x�N�g��
	Engine::Vector3 zAxis;					// Z���̕����x�N�g��

	// �O���e�ό`1
	uint32_t key;					// key�l

	// IK1
	uint32_t ikTargetIndex;			// IK�^�[�Q�b�g�{�[���ԍ�
	uint32_t ikLoopCount;			// IK���[�v��
	float ikLimitAngle;				// IK���[�v�v�Z��1�񂠂���̐����p�x(���W�A��)
	uint32_t ikLinkCount;			// IK�����N��

	std::vector<PMXIKLink> ikLink;	// IK�����N

};

// ���[�t����p�l��
enum class PMXMorphOperation : uint8_t
{
	None = 0,		// 
	Eyebrow = 1,	// ��(����)
	Eye = 2,		// ��(����)
	Mouth = 3,		// ��(�E��)
	Other = 4,		// ���̑�(�E��)
};

// ���[�t���
enum class PMXMorphType : uint8_t
{
	Group = 0,			// �O���[�v
	Vertex = 1,			// ���_
	Bone = 2,			// �{�[��
	Texcoord = 3,		// UV
	AddTexcoord1 = 4,	// �ǉ�UV
	AddTexcoord2 = 5,	// �ǉ�UV
	AddTexcoord3 = 6,	// �ǉ�UV
	AddTexcoord4 = 7,	// �ǉ�UV
	Material = 8		// �ގ�
};

// ���_���[�t
struct PMXVertexMorph
{
	uint32_t index;
	Engine::Vector3 offset;

};

// UV���[�t
struct PMXTexcoordMorph
{
	uint32_t index;
	Engine::Vector4 offset;

};

// �{�[�����[�t
struct PMXBoneMorph
{
	uint32_t index;
	Engine::Vector3 displacement;
	Engine::Vector4 rotation;

};

enum class PMXOffsetOperation : uint8_t
{
	Multi = 0,// ��Z
	Add = 1// ���Z
};

// �ގ����[�t
struct PMXMaterialMorph
{
	uint32_t index;					// -1�S�ގ��Ώ�
	PMXOffsetOperation operation;	// ���Z�`��
	Engine::Vector4 diffuse;				// 
	Engine::Vector3 specular;				// 
	float specularity;				// 
	Engine::Vector3 ambient;				// 
	Engine::Vector4 edge;					// 
	float edgeSize;					// �G�b�W�T�C�Y
	Engine::Vector4 textureCoeff;			// �e�N�X�`���W��
	Engine::Vector4 sphereTexCoeff;			// �X�t�B�A�e�N�X�`���W��
	Engine::Vector4 toonTexCoeff;			// �g�D�[���e�N�X�`���W��

};

// �O���[�v���[�t
struct PMXGroupMorph
{
	uint32_t index;	// 
	float coeff;	// ���[�t��

};

// PMX���[�t�f�[�^
struct PMXMorph
{
	std::string name;
	std::string nameEnglish;

	PMXMorphOperation operation;	// ����p�l��

	PMXMorphType type;				// ���[�t���

	uint32_t offsetCount;				// ���[�t�I�t�Z�b�g��

	std::vector<PMXVertexMorph> vertexData;		// �I�t�Z�b�g�f�[�^
	std::vector<PMXTexcoordMorph> texcoordData;	// 
	std::vector<PMXBoneMorph> boneData;			// 
	std::vector<PMXMaterialMorph> materialData;	// 
	std::vector<PMXGroupMorph> groupData;		// 
};

// ����g�t���O
enum class PMXFrameFlag : uint8_t
{
	Default = 0,	// �ʏ�g
	Special = 1		// ����g
};

enum class PMXFrameTarget : uint8_t
{
	Bone = 0,
	Morph = 1
};

// �g���v�f
struct PMXFrameworkElement
{
	PMXFrameTarget target;
	uint32_t index;
};
/*
�\���g�Ƃ������I�u�W�F�N�g�̑�����m�邱�Ƃ��o����
Bone�Ȃ�ǂ�ȃ{�[�������ɏ������铙
��:
�S�Ẵ��f�������ꂳ��Ă���Ȃ�g�p���Ă���
*/
// PMX�\���g
struct PMXDisplayFrame
{
	std::string name;
	std::string nameEnglish;
	PMXFrameFlag flag;
	uint32_t elementCount;
	std::vector<PMXFrameworkElement> elements;

};

// �`��
enum class PMXShape : uint8_t
{
	Sphere = 0,
	Box = 1,
	Capsule = 2
};

// �������Z
enum class PMXPhysicsOperation : uint8_t
{
	Static = 0,			// �{�[���Ǐ]
	Dynamic = 1,		// �������Z
	BoneRegistration = 2// �������Z + Bone�ʒu���킹
};

// PMX����
struct PMXRigidBody
{
	std::string name;
	std::string nameEnglish;

	int32_t index;				// �֘A�{�[��Index - �֘A�Ȃ��̏ꍇ��-1
	uint8_t group;				// �O���[�v
	uint16_t collisionGroup;	// ��Փ˃O���[�v�t���O
	PMXShape shape;				// �`�� - 0:�� 1:�� 2:�J�v�Z��
	Engine::Vector3 size;				// �T�C�Y(x,y,z)
	Engine::Vector3 position;			// �ʒu(x,y,z)
	Engine::Vector3 rotation;			// ��](x,y,z) -> ���W�A���p

	float mass;					// ����
	float translationAtten;		// �ړ�����
	float rotationAtten;		// ��]����
	float repulsive;			// ������
	float friction;				// ���C��
	PMXPhysicsOperation operation;	// ���̂̕������Z - 0:�{�[���Ǐ](static) 1:�������Z(dynamic) 2:�������Z + Bone�ʒu���킹

};

/*
collisionGroup
65535

0 = 0
1 = -1
2 = -2
3 = -4
4 = -8
5 = -16
6 = -32
7 = -64
8 = -128
9 = -256
10 = -512
11 = -1024
12 = -2048
13 = -4096
14 = -8192
15 = -16384
16 = -32768
*/

enum class PMXJointType : uint8_t
{
	Spring = 0
};

// PMX�W���C���g
struct PMXJoint
{
	std::string name;
	std::string nameEnglish;

	PMXJointType type;

	// type��0
	uint32_t indexA;				// �֘A����A��Index - �֘A�Ȃ��̏ꍇ��-1
	uint32_t indexB;				// �֘A����B��Index - �֘A�Ȃ��̏ꍇ��-1

	Engine::Vector3 position;			// �ʒu(x,y,z)
	Engine::Vector3 rotation;			// ��](x,y,z) -> ���W�A���p

	Engine::Vector3 lowerTranslation;	// �ړ�����-����(x,y,z)
	Engine::Vector3 upperTranslation;	// �ړ�����-���(x,y,z)
	Engine::Vector3 lowerRotation;		// ��]����-����(x,y,z) -> ���W�A���p
	Engine::Vector3 upperRotation;		// ��]����-���(x,y,z) -> ���W�A���p

	Engine::Vector3 constantTranslatin;	// �o�l�萔-�ړ�(x,y,z)
	Engine::Vector3 constantRotation;	// �o�l�萔-��](x,y,z)

};
