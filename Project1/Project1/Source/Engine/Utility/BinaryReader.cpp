#include "BinaryReader.h"

namespace Engine
{

	BinaryReader::BinaryReader(const std::string& fileName)
		: m_stream()
	{
		m_stream.open(fileName, std::ios_base::binary);
		if (m_stream.fail())
		{
			assert(!"ファイルオープンに失敗しました");
		}

	}

	BinaryReader::~BinaryReader()
	{
		m_stream.close();
	}

	uint8_t BinaryReader::ReadUInt8()
	{
		uint8_t value;
		Read(&value, sizeof(value));
		return value;
	}

	uint16_t BinaryReader::ReadUInt16()
	{
		uint16_t value;
		Read(&value, sizeof(value));
		return value;
	}

	uint32_t BinaryReader::ReadUInt32()
	{
		uint32_t value;
		Read(&value, sizeof(value));
		return value;
	}

	int8_t BinaryReader::ReadInt8()
	{
		int8_t value;
		Read(&value, sizeof(value));
		return value;
	}

	int16_t BinaryReader::ReadInt16()
	{
		int16_t value;
		Read(&value, sizeof(value));
		return value;
	}

	int32_t BinaryReader::ReadInt32()
	{
		int32_t value;
		Read(&value, sizeof(value));
		return value;
	}

	Vector2 BinaryReader::ReadVector2()
	{
		Vector2 value;
		Read(&value, sizeof(value));
		return value;
	}

	Vector3 BinaryReader::ReadVector3()
	{
		Vector3 value;
		Read(&value, sizeof(value));
		return value;
	}

	Vector4 BinaryReader::ReadVector4()
	{
		Vector4 value;
		Read(&value, sizeof(value));
		return value;
	}

	void BinaryReader::Close()
	{
		m_stream.close();
	}

	size_t BinaryReader::Read(void* destination, size_t size)
	{
		if (m_stream.fail())
		{
			assert(!"");
		}
		m_stream.read(reinterpret_cast<char*>(destination), size);
		return size;
	}

	size_t BinaryReader::GetFileSize() const
	{
		//m_stream.seekg(0, std::ios_base::end);
		//size_t endPos = m_stream.tellg();
		//m_stream.clear();
		//m_stream.seekg(0, std::ios_base::beg);
		//size_t begPos = m_stream.tellg();

		//return endPos - begPos;
		return size_t();
	}

	void BinaryReader::Seek(SeekPosition position, uint32_t offset)
	{
		switch (position)
		{
		case SeekPosition::Begin:
			m_stream.seekg(offset, std::ios_base::beg);
			break;
		case SeekPosition::Current:
			m_stream.seekg(offset, std::ios_base::cur);
			break;
		case SeekPosition::End:
			m_stream.seekg(offset, std::ios_base::end);
			break;
		default:
			break;
		}
	}

	bool BinaryReader::IsFail()
	{
		return m_stream.fail();
	}
}