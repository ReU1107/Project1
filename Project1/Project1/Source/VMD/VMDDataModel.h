#pragma once
#include <cstdint>
#include <vector>
#include "../Engine/Math/Vector3.h"
#include "../Engine/Math/Vector4.h"
#include "../Engine/Math/Color3.h"

// https://blog.goo.ne.jp/torisu_tetosuki/e/bc9f1c4d597341b394bd02b64597499d
// VMD�t�@�C���t�H�[�}�b�g
// PMD,PMX�p���[�V�����f�[�^

// �O���錾
class VMDBinaryReader;

// VMD�w�b�_�[�f�[�^
struct VMDHeader
{
	char signature[30];			// 
	char motionName[20];		// ���[�V����,�J����,�Ɩ�,�c
	VMDHeader(VMDBinaryReader& reader);
};

// VMD�g�̂𓮂������[�V����
struct VMDBodyMotion
{
	char boneName[15];					// �{�[����
	uint32_t frameIndex;				// �t���[���ԍ�
	Engine::Vector3 position;			// �ʒu
	Engine::Vector4 rotataion;			// ��](�l����)
	uint8_t bezierControllPoint[64];	// �x�W�F�Ȑ��p����_
};

// VMD���[�t�𓮂������[�V����
struct VMDMorphMotion
{
	char name[15];				// ���[�t�Ώۖ�
	uint32_t frameIndex;		// �t���[���ԍ�
	float weight;				// ���[�t�̐ݒ�l
};

// VMD�J�����𓮂������[�V����
struct VMDCameraMotion
{
	uint32_t frameIndex;		// �t���[���ԍ�
	float length;				// ����
	Engine::Vector3 position;			// �ʒu
	Engine::Vector3 rotation;			// ��]
	uint8_t interpolation[24];	// ���
	uint32_t angle;				// ����p
	uint8_t perspectiveFlag;	// �ˉe�ϊ��t���O
};

// �Ɩ��𓮂������[�V����
struct VMDLightMotion
{
	uint32_t frameIndex;	// �t���[���ԍ�
	Engine::Color3 color;			// �F(0�`256)
	Engine::Vector3 position;		// �ʒu
};

// �Z���t�V���h�E�𓮂������[�V����
struct VMDSelfShadowMotion
{
	uint32_t frameIndex;	// �t���[���ԍ�
	uint8_t mode;			// ���[�h
	float distance;			// ����
};
