#pragma once
#include "Buffer.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class VertexFormat : uint8_t;

		class VertexBuffer final : public Buffer
		{
		private:
			using base = Buffer;
			VertexFormat m_format;
		public:
			// �R���X�g���N�^
			VertexBuffer(ResourceViewType type = ResourceViewType::UnorderedAccess);
			// �f�X�g���N�^
			virtual ~VertexBuffer();

		public:
			// 
			void SetFormat(VertexFormat format) { m_format = format; }
			// 
			VertexFormat GetFormat() const { return m_format; }
		};

	}

}