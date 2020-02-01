#pragma once
#include <d3d12.h>
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		struct RaytracingAssociationDesc;
		struct RaytracingHitGroupDesc;
		struct RaytracingShaderLibraryDesc;
		struct ShaderResourceParameterDesc;
		struct ShaderResourceConstantsDesc;
		struct DepthStencilOperationDesc;
		struct DepthStencilDesc;
		struct InputLayoutDesc;
		struct InputElementDesc;
		struct RenderTargetBlendDesc;
		struct RasterizerDesc;
		struct BlendDesc;

		D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION D3D12SubObjectToExportAssociation(const RaytracingAssociationDesc& association, const D3D12_STATE_SUBOBJECT* subObject);

		D3D12_HIT_GROUP_DESC D3D12HitGroupDesc(const RaytracingHitGroupDesc& hitGroup);

		D3D12_DXIL_LIBRARY_DESC D3D12DXILLibrary(const RaytracingShaderLibraryDesc& library);

		D3D12_DESCRIPTOR_RANGE D3D12DescriptorRange(const ShaderResourceParameterDesc& parameter);

		D3D12_ROOT_CONSTANTS D3D12RootConstans(const ShaderResourceConstantsDesc& constans);

		D3D12_INPUT_ELEMENT_DESC D3D12InputElementDesc(const InputElementDesc& inputElement);

		D3D12_INPUT_LAYOUT_DESC D3D12InputLayoutDesc(const InputLayoutDesc& inputLayout);

		D3D12_RASTERIZER_DESC D3D12RasterizerDesc(const RasterizerDesc& rasterizer);

		D3D12_RENDER_TARGET_BLEND_DESC D3D12RenderTargetBlendDesc(const RenderTargetBlendDesc& renderTarget);

		D3D12_BLEND_DESC D3D12BlendDesc(const BlendDesc& blend);

		D3D12_DEPTH_STENCILOP_DESC D3D12DepthStencilOpDesc(const DepthStencilOperationDesc& depthStencilOperation);

		D3D12_DEPTH_STENCIL_DESC D3D12DepthStencilDesc(const DepthStencilDesc& depthStencil);

	}

}