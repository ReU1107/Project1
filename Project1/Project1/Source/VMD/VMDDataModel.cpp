#include "VMDDataModel.h"
#include "VMDBinaryReader.h"

VMDHeader::VMDHeader(VMDBinaryReader& reader)
{
	reader.Read(signature, sizeof(signature));
	reader.Read(motionName, sizeof(motionName));
}

