#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class DescriptorHeapType : uint8_t;

		class IDescriptorHeap
		{
		public:
			virtual ~IDescriptorHeap() {};

			virtual void* GetNativeHeap() const = 0;

			virtual DescriptorHeapType GetType() const = 0;

			virtual void Reset(uint32_t index) = 0;

			uint32_t operator++()
			{
				return 0;
			}


			//virtual void CreateRenderTargetView() = 0;

			//virtual void CreateView(IGraphicsResource* resource);
		};

	}

}