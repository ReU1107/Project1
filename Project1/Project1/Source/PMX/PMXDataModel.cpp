#include "PMXDataModel.h"
#include "PMXBinaryReader.h"


PMXHeader::PMXHeader(PMXBinaryReader& reader)
{
	reader.Read(signature, sizeof(signature));
	reader.Read(&version, sizeof(version));
	reader.Read(&indexSizeTableCount, sizeof(indexSizeTableCount));
	reader.Read(&encoding, sizeof(encoding));
	reader.Read(&additionalUVCount, sizeof(additionalUVCount));

	reader.Read(indexSizeTable, sizeof(uint8_t) * (indexSizeTableCount - 2));
	reader.SetEncoding(encoding == 0 ? PMXEncoding::UTF16 : PMXEncoding::UTF8);
	reader.SetIndexSize(PMXIndexType::Vertex, indexSizeTable[(uint8_t)PMXIndexType::Vertex]);
	reader.SetIndexSize(PMXIndexType::Texture, indexSizeTable[(uint8_t)PMXIndexType::Texture]);
	reader.SetIndexSize(PMXIndexType::Material, indexSizeTable[(uint8_t)PMXIndexType::Material]);
	reader.SetIndexSize(PMXIndexType::Bone, indexSizeTable[(uint8_t)PMXIndexType::Bone]);
	reader.SetIndexSize(PMXIndexType::Morph, indexSizeTable[(uint8_t)PMXIndexType::Morph]);
	reader.SetIndexSize(PMXIndexType::RigidBody, indexSizeTable[(uint8_t)PMXIndexType::RigidBody]);
}

PMXModelInformation::PMXModelInformation(PMXBinaryReader& reader)
{
	name = std::move(reader.ReadString());
	nameEnglish = std::move(reader.ReadString());
	comment = std::move(reader.ReadString());
	commentEnglish = std::move(reader.ReadString());
}
