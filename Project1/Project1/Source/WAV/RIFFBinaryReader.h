#pragma once
#include "../Engine/Utility/BinaryReader.h"

// Resource Interchange File Format�o�C�i���ǂݍ���
class RIFFBinaryReader final : public Engine::BinaryReader
{
private:
	using base = Engine::BinaryReader;
public:
	RIFFBinaryReader(const std::string& filePath);

	virtual ~RIFFBinaryReader();
};