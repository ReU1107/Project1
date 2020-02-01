#include "RIFFDataModel.h"
#include "RIFFBinaryReader.h"
#include <cassert>

RIFFHeader::RIFFHeader(RIFFBinaryReader& reader)
{
	reader.Read(signature, sizeof(signature));
	reader.Read(&size, sizeof(size));
	reader.Read(type, sizeof(type));
}

RIFFChunk::RIFFChunk(RIFFBinaryReader& reader)
{
	reader.Read(id, sizeof(id));
	reader.Read(&size, sizeof(size));
}

WAVEFormat::WAVEFormat(RIFFBinaryReader& reader)
{
	reader.Read(&format, sizeof(format));
	reader.Read(&channelCount, sizeof(channelCount));
	reader.Read(&frequency, sizeof(frequency));
	reader.Read(&bytePerSec, sizeof(bytePerSec));
	reader.Read(&bytePerSam, sizeof(bytePerSam));
	reader.Read(&depth, sizeof(depth));
}

WAVEFormatEx::WAVEFormatEx(RIFFBinaryReader& reader)
	: defaultData(reader)
	, extensSize(0)
	, extensData(nullptr)
{
	reader.Read(&extensSize, sizeof(extensSize));
	reader.Seek(Engine::SeekPosition::Current, extensSize);
}

WAVEList::WAVEList(RIFFBinaryReader& reader)
{
	reader.Read(&listType, sizeof(listType));
}

WAVEISFT::WAVEISFT(RIFFBinaryReader& reader)
{
	reader.Read(&data, sizeof(data));
}
