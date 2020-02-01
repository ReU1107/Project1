#include "AccelerationStructure.h"
namespace Engine
{
	namespace GraphicsSystem
	{
		AccelerationStructure::AccelerationStructure()
			: m_interface(nullptr)
			, m_type()
		{
		}
		
		AccelerationStructure::~AccelerationStructure()
		{
			delete m_interface;
		}

		IAccelerationStructure* AccelerationStructure::GetInterface() const
		{
			return m_interface;
		}
	}
}