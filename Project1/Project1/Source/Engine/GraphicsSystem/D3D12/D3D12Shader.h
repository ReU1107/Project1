#pragma once
#include "../Interface/IShader.h"
#include <d3d12.h>

namespace Engine 
{
	namespace GraphicsSystem 
	{

		class D3D12Shader : public IShader
		{
		public:
			ID3DBlob* m_blob;
		public:
			// コンストラクタ
			D3D12Shader();
			// デストラクタ
			virtual ~D3D12Shader();

			virtual void* GetNativeShader() const override;

			// 
			virtual void* GetBuffer() const override;
			// 
			virtual uint64_t GetSize() const override;
		};
	}
}