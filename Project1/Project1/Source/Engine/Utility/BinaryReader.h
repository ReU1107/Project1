#pragma once
#include <fstream>
#include <cstdint>
#include "../Math/Include.h"
#include <string>

namespace Engine
{
	enum class SeekPosition : uint8_t
	{
		Begin,	// ��ԑO
		Current,// ����
		End		// ��Ԍ��
	};

	class BinaryReader
	{
	private:
		std::ifstream m_stream;
	public:
		BinaryReader(const std::string& fileName);
		virtual ~BinaryReader();
	public:
		uint8_t ReadUInt8();
		uint16_t ReadUInt16();
		uint32_t ReadUInt32();

		int8_t ReadInt8();
		int16_t ReadInt16();
		int32_t ReadInt32();

		Vector2 ReadVector2();
		Vector3 ReadVector3();
		Vector4 ReadVector4();

		void Close();

		size_t Read(void* destination, size_t size);

		// �t�@�C���T�C�Y�擾
		size_t GetFileSize() const;

		// �t�@�C���ʒu�ύX
		void Seek(SeekPosition position, uint32_t offset);

		bool IsFail();
	};

}
