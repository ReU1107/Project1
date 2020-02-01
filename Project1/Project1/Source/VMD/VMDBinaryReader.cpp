#include "VMDBinaryReader.h"

uint8_t GetBit(VMDType type)
{
	return uint8_t(type);
}

VMDBinaryReader::VMDBinaryReader(const std::string& filePath)
	: base(filePath)
	, m_type(0)
{
}

VMDBinaryReader::~VMDBinaryReader()
{
}

void VMDBinaryReader::AddVMDType(VMDType type)
{
	m_type |= GetBit(type);
}

uint8_t VMDBinaryReader::GetVMDType() const
{
	return m_type;
}

