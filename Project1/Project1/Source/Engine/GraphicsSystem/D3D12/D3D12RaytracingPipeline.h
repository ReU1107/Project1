#pragma once
#include "../Interface/IRaytracingPipeline.h"

struct ID3D12StateObject;
struct ID3D12StateObjectProperties;

namespace Engine 
{
	namespace GraphicsSystem 
	{

		class D3D12RaytracingPipeline : public IRaytracingPipeline
		{
		public:
			ID3D12StateObject* m_native;
			ID3D12StateObjectProperties* m_properties;
		public:
			// �R���X�g���N�^
			D3D12RaytracingPipeline();
			// �f�X�g���N�^
			virtual ~D3D12RaytracingPipeline();
		public:
			virtual void* GetNativePipeline() const override;

			virtual void* GetShaderIdentifier(const wchar_t* shaderName) const override;

			//DeclareIUnknownInterfaces();
		};
	}
}