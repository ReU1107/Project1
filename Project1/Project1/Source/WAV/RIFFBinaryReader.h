#pragma once
#include "../Engine/Utility/BinaryReader.h"

// Resource Interchange File Formatバイナリ読み込み
class RIFFBinaryReader final : public Engine::BinaryReader
{
private:
	using base = Engine::BinaryReader;
public:
	RIFFBinaryReader(const std::string& filePath);

	virtual ~RIFFBinaryReader();
};