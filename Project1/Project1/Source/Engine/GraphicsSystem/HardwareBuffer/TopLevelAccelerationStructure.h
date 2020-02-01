#pragma once
#include "AccelerationStructure.h"
#include <vector>
#include <iostream>
#include "../Description/SubTopLevelAccelerationStructureDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class BottomLevelAccelerationStructure;
		class ResourceView;
		class ResourceDescriptor;
		struct TopLevelAccelerationStructureDesc;

		class TopLevelAccelerationStructure : public AccelerationStructure
		{
		private:
			using base = AccelerationStructure;
			//using ResourceViewPtr = std::shared_ptr<ResourceView>;
			using ResourceViewPtr = ResourceView*;
			using ResourceDescriptorPtr = ResourceDescriptor*;
		private:
			ResourceViewPtr m_view;				// 
			uint32_t m_count;

		public:
			// コンストラクタ
			TopLevelAccelerationStructure();
			// デストラクタ
			virtual ~TopLevelAccelerationStructure();

			virtual void Create() override;

			virtual void Recreate() override {};

			void Recreate(uint32_t count);

			void Update(const TopLevelAccelerationStructureDesc& desc);

			void CreateResourceView();

			void RecreateResourceView(ResourceDescriptorPtr descriptor);
		};

		using TopLevelAS = TopLevelAccelerationStructure;
	}
}
