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
			// �R���X�g���N�^
			StructuredBuffer(ResourceViewType type = ResourceViewType::UnorderedAccess);
			// �f�X�g���N�^
			virtual ~StructuredBuffer();

		};

	}
}