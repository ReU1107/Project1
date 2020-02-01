#pragma once
#include "Buffer.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class StructuredBuffer : public Buffer
		{
		private:
			using base = Buffer;

		public:
			// コンストラクタ
			StructuredBuffer(ResourceViewType type = ResourceViewType::UnorderedAccess);
			// デストラクタ
			virtual ~StructuredBuffer();

		};

	}
}