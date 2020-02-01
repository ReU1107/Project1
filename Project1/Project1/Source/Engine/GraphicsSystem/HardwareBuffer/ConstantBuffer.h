#pragma once
#include "Buffer.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{
		class ResourceView;
		class ResourceDescriptor;

		class ConstantBuffer final : public Buffer
		{
		private:
			using base = Buffer;

		public:
			// コンストラクタ
			ConstantBuffer(ResourceViewType type = ResourceViewType::ConstantBuffer);
			// デストラクタ
			virtual ~ConstantBuffer();

		public:
			// 作成
			virtual void Create(void* data = nullptr) override;

		};

	}

}