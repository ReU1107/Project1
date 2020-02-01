#include "D3D12Desc.h"
#include "..//Description/Include.h"
#include "..//Enumerations/Include.h"
#include "D3D12Enumeration.h"
#include "../../Utility/EnumOperator.h"
#include "D3D12Shader.h"

namespace Engine
{
	namespace GraphicsSystem 
	{

		D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION D3D12SubObjectToExportAssociation(const RaytracingAssociationDesc& association, const D3D12_STATE_SUBOBJECT* subObject)
		{
			D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION destination = {};
			destination.NumExports = association.shaderCount;
			destination.pExports = association.shaderNames;
			destination.pSubobjectToAssociate = subObject;
			return destination;
		}

		D3D12_HIT_GROUP_DESC D3D12HitGroupDesc(const RaytracingHitGroupDesc& hitGroup)
		{
			D3D12_HIT_GROUP_DESC desc = {};
			desc.Type = (hitGroup.type == BottomLevelType::Traiangles) ? D3D12_HIT_GROUP_TYPE_TRIANGLES : D3D12_HIT_GROUP_TYPE_PROCEDURAL_PRIMITIVE;
			desc.ClosestHitShaderImport = hitGroup.hitShader;
			desc.AnyHitShaderImport = hitGroup.anyHitShader;
			desc.IntersectionShaderImport = hitGroup.intersectShader;
			desc.HitGroupExport = hitGroup.name;
			return desc;
		}

		D3D12_DXIL_LIBRARY_DESC D3D12DXILLibrary(const RaytracingShaderLibraryDesc& library)
		{
			uint32_t count = library.shaderCount;
			D3D12_EXPORT_DESC* exports = new D3D12_EXPORT_DESC[count];

			for (uint32_t i = 0; i < count; ++i)
			{
				auto& exp = exports[i];
				exp.ExportToRename = nullptr;
				exp.Name = library.shaderNames[i];
				exp.Flags = D3D12_EXPORT_FLAG_NONE;
			}

			D3D12_DXIL_LIBRARY_DESC libraryDesc = {};
			libraryDesc.DXILLibrary.pShaderBytecode = library.shader->GetBuffer();
			libraryDesc.DXILLibrary.BytecodeLength = library.shader->GetSize();
			libraryDesc.NumExports = count;
			libraryDesc.pExports = exports;

			return libraryDesc;
		}

		D3D12_DESCRIPTOR_RANGE D3D12DescriptorRange(const ShaderResourceParameterDesc& parameter)
		{
			D3D12_DESCRIPTOR_RANGE range = {};
			range.RangeType = D3D12DescriptorRangeType(parameter.type);
			range.NumDescriptors = parameter.count;
			range.BaseShaderRegister = parameter.index;
			range.RegisterSpace = parameter.space;
			range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			return range;
		}

		D3D12_ROOT_CONSTANTS D3D12RootConstans(const ShaderResourceConstantsDesc& constans)
		{
			D3D12_ROOT_CONSTANTS destination = {};
			destination.Num32BitValues = constans.size;
			destination.ShaderRegister = constans.index;
			destination.RegisterSpace = constans.space;

			return destination;
		}

		D3D12_INPUT_ELEMENT_DESC D3D12InputElementDesc(const InputElementDesc& inputElement)
		{
			D3D12_INPUT_ELEMENT_DESC element = {};
			element.SemanticName = inputElement.semanticName;
			element.SemanticIndex = inputElement.semanticIndex;
			element.Format = DXGIFormat(inputElement.format);
			element.InputSlot = inputElement.inputSlot;
			element.AlignedByteOffset = inputElement.aligneOffset;
			element.InputSlotClass = D3D12InputClassification(inputElement.classification);
			element.InstanceDataStepRate = inputElement.instanceCount;

			return element;
		}

		D3D12_INPUT_LAYOUT_DESC D3D12InputLayoutDesc(const InputLayoutDesc& inputLayout)
		{
			D3D12_INPUT_LAYOUT_DESC destination = {};
			destination.NumElements = inputLayout.elementCount;
			D3D12_INPUT_ELEMENT_DESC* elements = new D3D12_INPUT_ELEMENT_DESC[inputLayout.elementCount];
			for (uint32_t i = 0; i < inputLayout.elementCount; ++i)
			{
				auto& element = elements[i];
				element = D3D12InputElementDesc(inputLayout.elements[i]);
			}
			destination.pInputElementDescs = elements;
			return destination;
		}
		
		D3D12_RASTERIZER_DESC D3D12RasterizerDesc(const RasterizerDesc& rasterizer)
		{
			D3D12_RASTERIZER_DESC destination = {};
			destination.AntialiasedLineEnable = rasterizer.antialiasedLineEnable;
			destination.ConservativeRaster = D3D12ConservativeRasterizationMode(rasterizer.conservativeMode);
			destination.CullMode = D3D12CullMode(rasterizer.cullType);
			destination.DepthBias = rasterizer.depthBias;
			destination.DepthBiasClamp = rasterizer.depthBiasClamp;
			destination.DepthClipEnable = rasterizer.depthClipEnable;
			destination.FillMode = D3D12FillMode(rasterizer.fillType);
			destination.ForcedSampleCount = rasterizer.forcedSampleCount;
			destination.FrontCounterClockwise = rasterizer.frontCounterClockwise;
			destination.MultisampleEnable = rasterizer.multisampleEnable;
			destination.SlopeScaledDepthBias = rasterizer.slopeScaledDepthBias;

			return destination;
		}

		D3D12_RENDER_TARGET_BLEND_DESC D3D12RenderTargetBlendDesc(const RenderTargetBlendDesc& renderTarget)
		{
			D3D12_RENDER_TARGET_BLEND_DESC destination = {};
			destination.BlendEnable = renderTarget.blendEnable;
			destination.BlendOp = D3D12BlendOp(renderTarget.colorBlendOperation);
			destination.BlendOpAlpha = D3D12BlendOp(renderTarget.alphaBlendOperation);
			destination.SrcBlend = D3D12Blend(renderTarget.sourceColorBlendFactor);
			destination.DestBlend = D3D12Blend(renderTarget.destinationColorBlendFactor);
			destination.SrcBlendAlpha = D3D12Blend(renderTarget.sourceAlphaBlendFactor);
			destination.DestBlendAlpha = D3D12Blend(renderTarget.destinationAlphaBlendFactor);
			destination.LogicOp = D3D12LogicOp(renderTarget.logicOperation);
			destination.LogicOpEnable = renderTarget.logicOperationEnable;
			destination.RenderTargetWriteMask = renderTarget.renderTargetWriteMask;

			return destination;
		}

		D3D12_BLEND_DESC D3D12BlendDesc(const BlendDesc& blend)
		{
			D3D12_BLEND_DESC destination = {};
			destination.AlphaToCoverageEnable = blend.alphaToCoverageEnable;
			destination.IndependentBlendEnable = blend.independentBlendEnable;
			for (uint32_t i = 0; i < 8; ++i)
			{
				destination.RenderTarget[i] = D3D12RenderTargetBlendDesc(blend.renderTargets[i]);
			}
			return destination;
		}

		D3D12_DEPTH_STENCILOP_DESC D3D12DepthStencilOpDesc(const DepthStencilOperationDesc& depthStencilOperation)
		{
			D3D12_DEPTH_STENCILOP_DESC destination = {};
			destination.StencilDepthFailOp = D3D12StencilOp(depthStencilOperation.stencilDepthFailOperation);
			destination.StencilFailOp = D3D12StencilOp(depthStencilOperation.stencilFailOperation);
			destination.StencilPassOp = D3D12StencilOp(depthStencilOperation.stencilPassOperation);
			destination.StencilFunc = D3D12ComparisonFunc(depthStencilOperation.stencilFunction);
			return destination;
		}
		
		D3D12_DEPTH_STENCIL_DESC D3D12DepthStencilDesc(const DepthStencilDesc& depthStencil)
		{
			D3D12_DEPTH_STENCIL_DESC destination = {};
			destination.BackFace = D3D12DepthStencilOpDesc(depthStencil.backFace);
			destination.FrontFace = D3D12DepthStencilOpDesc(depthStencil.frontFace);
			destination.DepthEnable = depthStencil.depthEnable;
			destination.DepthFunc = D3D12ComparisonFunc(depthStencil.depthFunction);
			destination.DepthWriteMask = D3D12DepthWriteMask(depthStencil.depthWriteMask);
			destination.StencilEnable = depthStencil.stencilEnable;
			destination.StencilReadMask = depthStencil.stencilReadMask;
			destination.StencilWriteMask = depthStencil.stencilWriteMask;

			return destination;
		}
	}
}