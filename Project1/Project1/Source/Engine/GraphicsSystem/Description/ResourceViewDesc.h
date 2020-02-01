#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		class IResource;
		class IDescriptorHeap;
		enum class ResourceViewType : uint8_t;

		struct ResourceViewDesc
		{
			IResource* resource;				// 
			IDescriptorHeap* descriptorHeap;	// 
			uint32_t stride;					// 
			ResourceViewType type;				// 
			bool isRaw;							// ByteAddressBufferÇÃèÍçáÇÕtrue

		};

	}

}