#pragma once
#include "Buffer.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class IndexFormat : uint8_t;

		class IndexBuffer final : public Buffer
		{
		private:
			using base = Buffer;
			IndexFormat m_format;
		public:
			// �R���X�g���N�^
			IndexBuffer(ResourceViewType type = ResourceViewType::UnorderedAccess);
			// �f�X�g���N�^
			virtual ~IndexBuffer();

		public:
			void SetFormat(IndexFormat format);

			IndexFormat GetFormat() const { return m_format; }
		};

	}

}