#include "IndexBuffer.h"
#include "../Description/BufferDesc.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Enumerations/BufferType.h"
#include "../Interface/IResource.h"
#include "../Enumerations/IndexFormat.h"

namespace Engine
{

	namespace GraphicsSystem
	{
		IndexBuffer::IndexBuffer(ResourceViewType type)
			: base(type)
			, m_format(IndexFormat::UInt32)
		{
			m_stride = sizeof(uint32_t);
		}

		IndexBuffer::~IndexBuffer()
		{
		}

		void IndexBuffer::SetFormat(IndexFormat format)
		{
			m_format = format;
			if (m_format == IndexFormat::UInt16)
			{
				m_stride = sizeof(uint16_t);
			}
			else if (m_format == IndexFormat::UInt32)
			{
				m_stride = sizeof(uint32_t);
			}
		}
	}
}