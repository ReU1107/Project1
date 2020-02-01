#pragma once
#include "../Engine//Utility/BinaryReader.h"
// エンコード方式
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
	PMXEncoding m_encoding;			// 現在のモデルのエンコード方式

	uint8_t m_vertexIndexSize;		// 現在の頂点型サイズ
	uint8_t m_textureIndexSize;		// 現在のテクスチャ型サイズ
	uint8_t m_materialIndexSize;	// 現在のマテリアル型サイズ
	uint8_t m_boneIndexSize;		// 現在のボーン型サイズ
	uint8_t m_morphIndexSize;		// 現在のモーフ型サイズ
	uint8_t m_rigidBodyIndexSize;	// 現在の剛体型サイズ
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