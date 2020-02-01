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
			// コンストラクタ
			VertexBuffer(ResourceViewType type = ResourceViewType::UnorderedAccess);
			// デストラクタ
			virtual ~VertexBuffer();

		public:
			// 
			void SetFormat(VertexFormat format) { m_format = format; }
			// 
			VertexFormat GetFormat() const { return m_format; }
		};

	}

}