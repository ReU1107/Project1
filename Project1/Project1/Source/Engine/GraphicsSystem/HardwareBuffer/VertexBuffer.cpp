#include "VertexBuffer.h"
#include "../Description/BufferDesc.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Enumerations/BufferType.h"
#include "../Interface/IResource.h"
#include "../Enumerations/Include.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		VertexBuffer::VertexBuffer(ResourceViewType type)
			: base(type)
			, m_format(VertexFormat::Float32)
		{
		}

		VertexBuffer::~VertexBuffer()
		{
		}

		//void VertexBuffer::Create(void* data)
		//{
		//	BufferDesc desc = {};
		//	m_size = m_stride * m_count;
		//	desc.size = m_size;
		//	m_interface = GetD3D12Device()->CreateBuffer(desc);
		//	if (data) 
		//	{
		//		m_interface->Update(data, desc.size);
		//	}
		//}
	}
}