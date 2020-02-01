#include "PMXBinaryReader.h"
#include "../Engine/String/StringHelper.h"
#include <cassert>

using namespace Engine;

PMXBinaryReader::PMXBinaryReader(const std::string& filePath)
	: base(filePath)
	, m_encoding(PMXEncoding::UTF16)
	, m_vertexIndexSize(0)
	, m_textureIndexSize(0)
	, m_materialIndexSize(0)
	, m_boneIndexSize(0)
	, m_morphIndexSize(0)
	, m_rigidBodyIndexSize(0)
{
}

PMXBinaryReader::~PMXBinaryReader()
{
}

void PMXBinaryReader::SetEncoding(PMXEncoding encoding)
{
	m_encoding = encoding;
}

void PMXBinaryReader::SetIndexSize(PMXIndexType indexType, uint8_t indexSize)
{
	assert(indexSize <= 4);
	switch (indexType)
	{
	case PMXIndexType::Vertex:
		m_vertexIndexSize = indexSize;
		break;
	case PMXIndexType::Texture:
		m_textureIndexSize = indexSize;
		break;
	case PMXIndexType::Material:
		m_materialIndexSize = indexSize;
		break;
	case PMXIndexType::Bone:
		m_boneIndexSize = indexSize;
		break;
	case PMXIndexType::Morph:
		m_morphIndexSize = indexSize;
		break;
	case PMXIndexType::RigidBody:
		m_rigidBodyIndexSize = indexSize;
		break;
	default:
		assert(!"");
		break;
	}
}

std::string PMXBinaryReader::ReadString()
{
	uint32_t length;
	length = ReadUInt32();
	std::string result;
	if (m_encoding == PMXEncoding::UTF16)
	{
		std::u16string utf16String(length / 2, u'\0');
		Read(&utf16String[0], length);

		// •ÏŠ·
		result = ConvertChar16_tToChar(&utf16String);
	}
	else if (m_encoding == PMXEncoding::UTF8)
	{
		std::string utf8String;
		Read(&utf8String[0], length);

		result = utf8String;
	}
	return result;
}

uint32_t PMXBinaryReader::ReadIndex(PMXIndexType indexType)
{
	uint32_t index = 0;
	switch (indexType)
	{
	case PMXIndexType::Vertex:
		Read(&index, m_vertexIndexSize);
		break;
	case PMXIndexType::Texture:
		Read(&index, m_textureIndexSize);
		break;
	case PMXIndexType::Material:
		Read(&index, m_materialIndexSize);
		break;
	case PMXIndexType::Bone:
		Read(&index, m_boneIndexSize);
		break;
	case PMXIndexType::Morph:
		Read(&index, m_morphIndexSize);
		break;
	case PMXIndexType::RigidBody:
		Read(&index, m_rigidBodyIndexSize);
		break;
	default:
		assert(!"");
		break;
	}
	return index;
}
