#pragma once
#include "../Interface/IRootSignature.h"

struct ID3D12RootSignature;

namespace Engine
{

	namespace GraphicsSystem
	{

		class D3D12RootSignature : public IRootSignature
		{
		public:
			ID3D12RootSignature* m_native;

		public:
			// コンストラクタ
			D3D12RootSignature();
			// デストラクタ
			virtual ~D3D12RootSignature();

			virtual void* GetNativeSignature() const override;

		};
	}
}