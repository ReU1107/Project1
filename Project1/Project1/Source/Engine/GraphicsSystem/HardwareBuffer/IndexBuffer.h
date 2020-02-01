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
			// コンストラクタ
			IndexBuffer(ResourceViewType type = ResourceViewType::UnorderedAccess);
			// デストラクタ
			virtual ~IndexBuffer();

		public:
			void SetFormat(IndexFormat format);

			IndexFormat GetFormat() const { return m_format; }
		};

	}

}