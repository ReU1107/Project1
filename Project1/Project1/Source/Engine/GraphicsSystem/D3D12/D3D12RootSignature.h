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
			// �R���X�g���N�^
			D3D12RootSignature();
			// �f�X�g���N�^
			virtual ~D3D12RootSignature();

			virtual void* GetNativeSignature() const override;

		};
	}
}