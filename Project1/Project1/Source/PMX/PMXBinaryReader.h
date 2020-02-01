#pragma once
#include "../Engine//Utility/BinaryReader.h"
// �G���R�[�h����
enum class PMXEncoding : uint8_t
{
	UTF16 = 0,
	UTF8 = 1
};

enum class PMXIndexType
{
	Vertex,
	Texture,
	Material,
	Bone,
	Morph,
	RigidBody
};

class PMXBinaryReader final : public Engine::BinaryReader
{
private:
	using base = Engine::BinaryReader;
private:
	PMXEncoding m_encoding;			// ���݂̃��f���̃G���R�[�h����

	uint8_t m_vertexIndexSize;		// ���݂̒��_�^�T�C�Y
	uint8_t m_textureIndexSize;		// ���݂̃e�N�X�`���^�T�C�Y
	uint8_t m_materialIndexSize;	// ���݂̃}�e���A���^�T�C�Y
	uint8_t m_boneIndexSize;		// ���݂̃{�[���^�T�C�Y
	uint8_t m_morphIndexSize;		// ���݂̃��[�t�^�T�C�Y
	uint8_t m_rigidBodyIndexSize;	// ���݂̍��̌^�T�C�Y
public:
	PMXBinaryReader(const std::string& filePath);
	virtual ~PMXBinaryReader();
public:
	// 
	void SetEncoding(PMXEncoding encoding);

	void SetIndexSize(PMXIndexType indexType, uint8_t indexSize);

	std::string ReadString();

	uint32_t ReadIndex(PMXIndexType indexType);
};