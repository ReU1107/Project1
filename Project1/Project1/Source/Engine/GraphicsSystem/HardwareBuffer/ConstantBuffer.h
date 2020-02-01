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
			// �R���X�g���N�^
			ConstantBuffer(ResourceViewType type = ResourceViewType::ConstantBuffer);
			// �f�X�g���N�^
			virtual ~ConstantBuffer();

		public:
			// �쐬
			virtual void Create(void* data = nullptr) override;

		};

	}

}