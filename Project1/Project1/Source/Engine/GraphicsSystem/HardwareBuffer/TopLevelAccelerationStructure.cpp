#include "TopLevelAccelerationStructure.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Description/Include.h"
#include "../../Utility/EnumOperator.h"
#include "..//Enumerations/Include.h"
#include "../Interface/IAccelerationStructure.h"
#include "BottomLevelAccelerationStructure.h"
#include "ResourceView.h"
#include "ResourceDescriptor.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		TopLevelAccelerationStructure::TopLevelAccelerationStructure()
			: base()
			, m_view()
			, m_count(0)
		{
		}

		TopLevelAccelerationStructure::~TopLevelAccelerationStructure()
		{
		}

		void TopLevelAccelerationStructure::Create()
		{
			m_interface = GetD3D12Device()->CreateTopLevelAccelerationStructure();
		}

		void TopLevelAccelerationStructure::Recreate(uint32_t count)
		{
			if (m_count != count)
			{
				if (!m_interface)
					Create();
				m_count = count;
				TopLevelAccelerationStructureDesc desc = {};
				desc.bottomCount = m_count;
				GetD3D12Device()->RecreateTopLevelAccelerationStructure(m_interface, desc);
			}
		}

		void TopLevelAccelerationStructure::Update(const TopLevelAccelerationStructureDesc& desc)
		{
			m_interface->Update(desc);
		}

		void TopLevelAccelerationStructure::CreateResourceView()
		{
			m_view = ResourceView::Create(ResourceViewType::Raytracing);
		}

		void TopLevelAccelerationStructure::RecreateResourceView(ResourceDescriptorPtr descriptor)
		{
			if (!m_view)
				CreateResourceView();
			m_view->Recreate(descriptor->GetInterface(), (IResource*)m_interface);
		}
	}
}