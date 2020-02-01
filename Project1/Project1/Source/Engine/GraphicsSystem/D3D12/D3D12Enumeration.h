#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderResourceType : uint8_t;
		enum class ShaderType : uint8_t;
		enum class ResourceFormat : uint8_t;
		enum class RaytracingAccelerationBuildFlags : uint8_t;
		enum class RaytracingInstanceFlags : uint8_t;
		enum class RootSignatureFlags : uint8_t;
		enum class DescriptorHeapType : uint8_t;
		enum class IndexFormat : uint8_t;
		enum class VertexFormat : uint8_t;
		enum class ResourceDimension : uint8_t;
		enum class ResourceFlags : uint8_t;
		enum class ResourceStates : uint16_t;
		enum class InputClassification;
		enum class BlendFactor : uint8_t;
		enum class BlendOperation : uint8_t;
		enum class LogicOperation : uint8_t;
		enum class StencilOperation : uint8_t;
		enum class ComparisonFunction : uint8_t;
		enum class DepthWriteMask : uint8_t;
		enum class FillType : uint8_t;
		enum class CullType : uint8_t;
		enum class PrimitiveTopology : uint8_t;
		enum class ConservativeMode : uint8_t;
		enum class CommandQueuePriority : uint8_t;
		enum class CommandListType : uint8_t;
		enum class BottomLevelAccelerationStructureFlags : uint8_t;
		enum class BottomLevelAccelerationBuildFlags : uint8_t;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		D3D12_COMMAND_QUEUE_PRIORITY D3D12CommandQueuePriority(CommandQueuePriority priority);

		D3D12_COMMAND_LIST_TYPE D3D12CommandListType(CommandListType type);

		D3D12_DESCRIPTOR_RANGE_TYPE D3D12DescriptorRangeType(ShaderResourceType type);

		D3D12_ROOT_PARAMETER_TYPE D3D12RootParamerterType(ShaderResourceType type);

		D3D12_SHADER_VISIBILITY D3D12ShaderVisibiliy(ShaderType type);

		DXGI_FORMAT DXGIFormat(ResourceFormat format);
		
		D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS D3D12RaytracingAccelerationBuildFlags(BottomLevelAccelerationBuildFlags flags);

		D3D12_RAYTRACING_GEOMETRY_FLAGS D3D12RaytracingGeometryFlags(BottomLevelAccelerationStructureFlags flags);

		D3D12_RAYTRACING_INSTANCE_FLAGS D3D12RaytracingInstanceFlags(SubTopLevelAccelerationStructureFlags flags);

		D3D12_ROOT_SIGNATURE_FLAGS D3D12RootSignatureFlags(RootSignatureFlags flags);

		D3D12_DESCRIPTOR_HEAP_TYPE D3D12DescriptorHeapType(DescriptorHeapType heapType);

		DXGI_FORMAT DXGIIndexFormat(IndexFormat format);

		DXGI_FORMAT DXGIVertexFormat(VertexFormat format);

		D3D12_RESOURCE_DIMENSION D3D12ResourceDimension(ResourceDimension dimension);

		D3D12_RESOURCE_FLAGS D3D12ResourceFlags(ResourceFlags flags);

		D3D12_RESOURCE_STATES D3D12ResourceStates(ResourceStates states);

		D3D12_PRIMITIVE_TOPOLOGY_TYPE D3D12PrimitiveTopologyType(PrimitiveTopology topology);

		D3D12_PRIMITIVE_TOPOLOGY D3D12PrimitiveTopology(PrimitiveTopology topology);

		D3D12_CONSERVATIVE_RASTERIZATION_MODE D3D12ConservativeRasterizationMode(ConservativeMode mode);

		D3D12_FILL_MODE D3D12FillMode(FillType type);

		D3D12_CULL_MODE D3D12CullMode(CullType type);

		D3D12_INPUT_CLASSIFICATION D3D12InputClassification(InputClassification classification);

		D3D12_BLEND D3D12Blend(BlendFactor factor);

		D3D12_BLEND_OP D3D12BlendOp(BlendOperation operation);

		D3D12_LOGIC_OP D3D12LogicOp(LogicOperation operation);

		D3D12_STENCIL_OP D3D12StencilOp(StencilOperation operation);

		D3D12_COMPARISON_FUNC D3D12ComparisonFunc(ComparisonFunction function);

		D3D12_DEPTH_WRITE_MASK D3D12DepthWriteMask(DepthWriteMask mask);
	}

}