#pragma once
#include "../Engine/Utility/BinaryReader.h"

// Resource Interchange File FormatƒoƒCƒiƒŠ“Ç‚İ‚İ
class RIFFBinaryReader final : public Engine::BinaryReader
{
private:
	using base = Engine::BinaryReader;
public:
	RIFFBinaryReader(const std::string& filePath);

	virtual ~RIFFBinaryReader();
};