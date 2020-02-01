#include "ShaderRecord.h"
#include "../Enumerations/ShaderRecordType.h"
#include "..//HardwareBuffer/Buffer.h"
#include "..//HardwareBuffer/Resource.h"
#include "..//HardwareBuffer/ResourceView.h"
#include "..//HardwareBuffer/ResourceDescriptor.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		static constexpr uint32_t LocalRootArgumentSize = sizeof(uint64_t);

		ShaderRecord::ShaderRecord()
			: m_identifier(nullptr)
			, m_size(0)
			, m_registerIndex(0)
			, m_type()
		{

		}

		ShaderRecord::~ShaderRecord()
		{
			m_identifier = nullptr;
		}

		void ShaderRecord::SetShaderIdentifier(void* identifier)
		{
			m_identifier = identifier;
		}

		void ShaderRecord::SetRegisterIndex(uint32_t index)
		{
			m_registerIndex = index;
		}

		void ShaderRecord::AddResource(Buffer* buffer)
		{
			AddResource(buffer->GetInterface());
		}

		void ShaderRecord::AddResource(Resource* resource)
		{
			AddResource(resource->GetInterface());
		}

		void ShaderRecord::AddResource(IResource* resource)
		{
			LocalRootArgument arg = {};
			arg.type = LocalRootArgumentType::Resource;
			arg.resource = resource;
			m_size += LocalRootArgumentSize;
			m_arguments.push_back(arg);
		}

		void ShaderRecord::AddResourceView(ResourceView* resourceView)
		{
			AddResourceView(resourceView->GetInterface());
		}

		void ShaderRecord::AddResourceView(IResourceView* resourceView)
		{
			LocalRootArgument arg = {};
			arg.type = LocalRootArgumentType::ResourceView;
			arg.view = resourceView;
			m_size += LocalRootArgumentSize;
			m_arguments.push_back(arg);
		}

		void ShaderRecord::AddDescriptorTable(ResourceDescriptor* descriptor)
		{
			AddDescriptorTable(descriptor->GetInterface());
		}

		void ShaderRecord::AddDescriptorTable(IDescriptorHeap* descriptorTable)
		{
			LocalRootArgument arg = {};
			arg.type = LocalRootArgumentType::DescriptorTable;
			arg.heap = descriptorTable;
			m_size += LocalRootArgumentSize;
			m_arguments.push_back(arg);
		}

		void* ShaderRecord::GetShaderIdentifier() const
		{
			return m_identifier;
		}

		uint32_t ShaderRecord::GetLocalRootArgumentCount() const
		{
			return (uint32_t)m_arguments.size();
		}

		const LocalRootArgument& ShaderRecord::GetLocalRootArgument(uint32_t index) const
		{
			return m_arguments.at(index);
		}

		uint32_t ShaderRecord::GetRegisterIndex() const
		{
			return m_registerIndex;
		}

		uint32_t ShaderRecord::GetSize() const
		{
			return m_size;
		}
	}
}