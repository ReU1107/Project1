#include "CopyCommandList.h"
#include "..//D3D12/D3D12Device.h"
#include "..//D3D12.h"
#include "..//Description/CommandListDesc.h"
#include "..//Enumerations/CommandListType.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		CopyCommandList::CopyCommandList()
			: base()
		{
		}
		
		CopyCommandList::~CopyCommandList()
		{
		}

		CopyCommandList::CopyCommandListPtr CopyCommandList::Create(const std::string& name)
		{
			auto device = GetD3D12Device();

			CommandListDesc desc = {};
			desc.type = CommandListType::Copy;

			auto list = std::make_shared<CopyCommandList>();
			list->m_interface = device->CreateCommandList(desc);
			list->SetName(name);

			Register(name, list);

			return list;
		}

		void CopyCommandList::CopyResource(Resource* source, Resource* destination) const
		{
			base::CopyResource(source, destination);
		}
	}
}