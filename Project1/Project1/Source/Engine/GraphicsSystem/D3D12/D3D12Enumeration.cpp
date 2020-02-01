#include "D3D12Enumeration.h"
#include "..//Enumerations/Include.h"
#include "../../Utility/EnumOperator.h"
#include <cassert>

namespace Engine
{
	namespace GraphicsSystem 
	{
		D3D12_COMMAND_QUEUE_PRIORITY D3D12CommandQueuePriority(CommandQueuePriority priority)
		{
			switch (priority)
			{
			case CommandQueuePriority::Normal:
				return D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
				break;
			case CommandQueuePriority::High:
				return D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
				break;
			default:
				break;
			}
			return D3D12_COMMAND_QUEUE_PRIORITY();
		}

		D3D12_COMMAND_LIST_TYPE D3D12CommandListType(CommandListType type)
		{
			switch (type)
			{
			case CommandListType::General:
				return D3D12_COMMAND_LIST_TYPE_DIRECT;
				break;
			case CommandListType::Copy:
				return D3D12_COMMAND_LIST_TYPE_COPY;
				break;
			case CommandListType::Compute:
				return D3D12_COMMAND_LIST_TYPE_COMPUTE;
				break;
			default:
				break;
			}
			return D3D12_COMMAND_LIST_TYPE();
		}
		
		D3D12_DESCRIPTOR_RANGE_TYPE D3D12DescriptorRangeType(ShaderResourceType type)
		{
			switch (type)
			{
			case ShaderResourceType::ConstantBuffer:
				return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
				break;
			case ShaderResourceType::ShaderResource:
				return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				break;
			case ShaderResourceType::ReadWriteResource:
				return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
				break;
			case ShaderResourceType::Sampler:
				return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
				break;
			default:

				break;
			}

			return D3D12_DESCRIPTOR_RANGE_TYPE();
		}
		D3D12_ROOT_PARAMETER_TYPE D3D12RootParamerterType(ShaderResourceType type)
		{
			switch (type)
			{
			case ShaderResourceType::ConstantBuffer:
				return D3D12_ROOT_PARAMETER_TYPE_CBV;
				break;
			case ShaderResourceType::ShaderResource:
				return D3D12_ROOT_PARAMETER_TYPE_SRV;
				break;
			case ShaderResourceType::ReadWriteResource:
				return D3D12_ROOT_PARAMETER_TYPE_UAV;
				break;
			case ShaderResourceType::Sampler:
				break;
			default:
				break;
			}

			return D3D12_ROOT_PARAMETER_TYPE();
		}
		D3D12_SHADER_VISIBILITY D3D12ShaderVisibiliy(ShaderType type)
		{
			switch (type)
			{
			case ShaderType::All:
				return D3D12_SHADER_VISIBILITY_ALL;
				break;
			case ShaderType::Vertex:
				return D3D12_SHADER_VISIBILITY_VERTEX;
				break;
			case ShaderType::Hull:
				return D3D12_SHADER_VISIBILITY_HULL;
				break;
			case ShaderType::Geometry:
				return D3D12_SHADER_VISIBILITY_GEOMETRY;
				break;
			case ShaderType::Domain:
				return D3D12_SHADER_VISIBILITY_DOMAIN;
				break;
			case ShaderType::Pixel:
				return D3D12_SHADER_VISIBILITY_PIXEL;
				break;
			default:
				break;
			}
			return D3D12_SHADER_VISIBILITY();
		}
		DXGI_FORMAT DXGIFormat(ResourceFormat format)
		{
			switch (format)
			{
			case ResourceFormat::RGBA32UInt:
				return DXGI_FORMAT_R8G8B8A8_UINT;
				break;
			case ResourceFormat::RGBA32SInt:
				return DXGI_FORMAT_R8G8B8A8_SINT;
				break;
			case ResourceFormat::RGBAFloat:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			case ResourceFormat::RGBAHalf:
				return DXGI_FORMAT_R16G16B16A16_FLOAT;
				break;
			case ResourceFormat::RGBAUnorm:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case ResourceFormat::RGBFloat:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case ResourceFormat::RGFloat:
				return DXGI_FORMAT_R32G32_FLOAT;
				break;
			case ResourceFormat::RFloat:
				return DXGI_FORMAT_R32_FLOAT;
				break;
			case ResourceFormat::RGHalf:
				return DXGI_FORMAT_R16G16_FLOAT;
				break;
			case ResourceFormat::RHalf:
				return DXGI_FORMAT_R16_FLOAT;
				break;
			case ResourceFormat::Depth32:
				return DXGI_FORMAT_D32_FLOAT;
				break;
			case ResourceFormat::Depth16:
				return DXGI_FORMAT_D16_UNORM;
				break;
			case ResourceFormat::Depth24Stencil8:
				return DXGI_FORMAT_D24_UNORM_S8_UINT;
				break;
			case ResourceFormat::RGB10A2Unorm:
				return DXGI_FORMAT_R10G10B10A2_UNORM;
				break;
			default:
				break;
			}

			return DXGI_FORMAT_R8G8B8A8_UINT;
		}

		D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS D3D12RaytracingAccelerationBuildFlags(BottomLevelAccelerationBuildFlags flags)
		{
			D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS nativeFlags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;

			if ((flags & BottomLevelAccelerationBuildFlags::AllowCompaction) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_COMPACTION;
			}
			if ((flags & BottomLevelAccelerationBuildFlags::AllowUpdate) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE;
			}
			if ((flags & BottomLevelAccelerationBuildFlags::MinimizeMemory) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_MINIMIZE_MEMORY;
			}
			if ((flags & BottomLevelAccelerationBuildFlags::PerformUpdate) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE;
			}
			if ((flags & BottomLevelAccelerationBuildFlags::PreferFastBuild) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_BUILD;
			}
			if ((flags & BottomLevelAccelerationBuildFlags::PreferFastTrace) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;
			}
			return nativeFlags;
		}

		D3D12_RAYTRACING_GEOMETRY_FLAGS D3D12RaytracingGeometryFlags(BottomLevelAccelerationStructureFlags flags)
		{
			D3D12_RAYTRACING_GEOMETRY_FLAGS nativeFlags = D3D12_RAYTRACING_GEOMETRY_FLAG_NONE;
			if ((flags & BottomLevelAccelerationStructureFlags::Opaque) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
			}
			D3D12_RAYTRACING_GEOMETRY_FLAG_NO_DUPLICATE_ANYHIT_INVOCATION;

			return nativeFlags;
		}

		D3D12_RAYTRACING_INSTANCE_FLAGS D3D12RaytracingInstanceFlags(SubTopLevelAccelerationStructureFlags flags)
		{
			D3D12_RAYTRACING_INSTANCE_FLAGS nativeFlags = D3D12_RAYTRACING_INSTANCE_FLAG_NONE;

			if ((flags & SubTopLevelAccelerationStructureFlags::CullDisable) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE;
			}
			if ((flags & SubTopLevelAccelerationStructureFlags::FrontCounterClockwise) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_FRONT_COUNTERCLOCKWISE;
			}
			if ((flags & SubTopLevelAccelerationStructureFlags::Opaque) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE;
			}
			if ((flags & SubTopLevelAccelerationStructureFlags::NonOpaque) != 0)
			{
				nativeFlags |= D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE;
			}
			return nativeFlags;
		}

		D3D12_ROOT_SIGNATURE_FLAGS D3D12RootSignatureFlags(RootSignatureFlags flags)
		{
			D3D12_ROOT_SIGNATURE_FLAGS nativeFlags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
			if ((flags & RootSignatureFlags::AllowInputAssemblerInputLayout) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
			}
			if ((flags & RootSignatureFlags::DenyVertexShaderRootAccess) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS;
			}
			if ((flags & RootSignatureFlags::DenyHullShaderRootAccess) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;
			}
			if ((flags & RootSignatureFlags::DenyDomaionShaderRootAccess) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
			}
			if ((flags & RootSignatureFlags::DenyGeometryShaderRootAccess) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
			}
			if ((flags & RootSignatureFlags::DenyPixelShaderRootAccess) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
			}
			if ((flags & RootSignatureFlags::AllowStreamOutput) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
			}
			if ((flags & RootSignatureFlags::LocalRootSignature) != 0) {
				nativeFlags |= D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE;
			}
			return nativeFlags;
		}

		D3D12_DESCRIPTOR_HEAP_TYPE D3D12DescriptorHeapType(DescriptorHeapType heapType)
		{
			D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;

			switch (heapType)
			{
			case DescriptorHeapType::Constant:
				type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				break;
			case DescriptorHeapType::RenderTarget:
				type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				break;
			case DescriptorHeapType::DepthStencil:
				type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				break;
			case DescriptorHeapType::ShaderResource:
				type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				break;
			case DescriptorHeapType::UnorderedAccess:
				type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				break;
			case DescriptorHeapType::Sampler:
				type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
				break;

			default:
				assert(!"デスクリプターヒープのタイプがおかしいです");
				break;
			}
			return type;
		}

		DXGI_FORMAT DXGIIndexFormat(IndexFormat format)
		{
			switch (format)
			{
			case IndexFormat::UInt16:
				return DXGI_FORMAT_R16_UINT;
				break;
			case IndexFormat::UInt32:
				return DXGI_FORMAT_R32_UINT;
				break;
			default:
				break;
			}

			return DXGI_FORMAT_R32_UINT;
		}

		DXGI_FORMAT DXGIVertexFormat(VertexFormat format)
		{
			switch (format)
			{
			case VertexFormat::Float16:
				assert(!"Float16を設定しないでください");
				break;
			case VertexFormat::Float32:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			default:
				break;
			}

			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		D3D12_RESOURCE_DIMENSION D3D12ResourceDimension(ResourceDimension dimension)
		{

			D3D12_RESOURCE_DIMENSION nativeDimension = D3D12_RESOURCE_DIMENSION_UNKNOWN;
			switch (dimension)
			{
			case ResourceDimension::Tex1D:
				nativeDimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
				break;
			case ResourceDimension::Tex2D:
				nativeDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				break;
			case ResourceDimension::Tex3D:
				nativeDimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
				break;				
			default:
				assert(!"テクスチャの次元がおかしいです");
				break;
			}
			return nativeDimension;
		}

		D3D12_RESOURCE_FLAGS D3D12ResourceFlags(ResourceFlags flags)
		{
			D3D12_RESOURCE_FLAGS resourceFlags = D3D12_RESOURCE_FLAG_NONE;
			{
				if ((flags & ResourceFlags::AllowRenderTarget) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
				}
				if ((flags & ResourceFlags::AllowDepthStencil) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
				}
				if ((flags & ResourceFlags::AllowUnorderedAccess) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
				}
				if ((flags & ResourceFlags::DenyShaderResource) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
				}
				if ((flags & ResourceFlags::AllowCrossAdapter) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER;
				}
				if ((flags & ResourceFlags::AllowSimultaneousAccess) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
				}
				if ((flags & ResourceFlags::DecodeReferenceOnly) != 0) {
					resourceFlags |= D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY;
				}
			}
			return resourceFlags;
		}

		D3D12_RESOURCE_STATES D3D12ResourceStates(ResourceStates states)
		{
			D3D12_RESOURCE_STATES resourceStates = D3D12_RESOURCE_STATE_COMMON;

			if ((states & ResourceStates::VertexConstantBuffer) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
			}
			if ((states & ResourceStates::IndexBuffer) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_INDEX_BUFFER;
			}
			if ((states & ResourceStates::RenderTarget) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_RENDER_TARGET;
			}
			if ((states & ResourceStates::UnorderedAccess) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			}
			if ((states & ResourceStates::DepthWrite) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_DEPTH_WRITE;
			}
			if ((states & ResourceStates::DepthRead) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_DEPTH_READ;
			}
			if ((states & ResourceStates::NonPixelShaderResource) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
			}
			if ((states & ResourceStates::PixelShaderResource) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			}
			if ((states & ResourceStates::StreamOut) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_STREAM_OUT;
			}
			if ((states & ResourceStates::IndirectArgument) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
			}
			if ((states & ResourceStates::CopyDestination) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_COPY_DEST;
			}
			if ((states & ResourceStates::CopySource) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_COPY_SOURCE;
			}
			if ((states & ResourceStates::ResolveDestination) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_RESOLVE_DEST;
			}
			if ((states & ResourceStates::ResolveSource) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
			}
			if ((states & ResourceStates::RaytracingStructure) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE;
			}
			if ((states & ResourceStates::Present) != 0)
			{
				resourceStates |= D3D12_RESOURCE_STATE_PRESENT;
			}
			//if ((states & ResourceStates::GenericRead) != 0)
			//{
			//	resourceStates |= D3D12_RESOURCE_STATE_GENERIC_READ;
			//}

			return resourceStates;
		}
		D3D12_PRIMITIVE_TOPOLOGY_TYPE D3D12PrimitiveTopologyType(PrimitiveTopology topology)
		{
			switch (topology)
			{
			case Engine::GraphicsSystem::PrimitiveTopology::PointList:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::LineList:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::LineStrip:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::TriangleList:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::TriangleStrip:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::Patch:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
				break;
			default:
				break;
			}
		
			return D3D12_PRIMITIVE_TOPOLOGY_TYPE();
		}

		D3D12_PRIMITIVE_TOPOLOGY D3D12PrimitiveTopology(PrimitiveTopology topology)
		{
			switch (topology)
			{
			case Engine::GraphicsSystem::PrimitiveTopology::PointList:
				return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::LineList:
				return D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::LineStrip:
				return D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::TriangleList:
				return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::TriangleStrip:
				return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
				break;
			case Engine::GraphicsSystem::PrimitiveTopology::Patch:
				break;
			default:
				break;
			}

			return D3D12_PRIMITIVE_TOPOLOGY();
		}

		D3D12_CONSERVATIVE_RASTERIZATION_MODE D3D12ConservativeRasterizationMode(ConservativeMode mode)
		{
			if(mode == ConservativeMode::On)
			{
				return D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON;
			}
			if (mode == ConservativeMode::Off)
			{
				return D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
			}
			return D3D12_CONSERVATIVE_RASTERIZATION_MODE();
		}
		
		D3D12_FILL_MODE D3D12FillMode(FillType type)
		{
			if (type == FillType::WireFrame)
			{
				return D3D12_FILL_MODE_WIREFRAME;
			}
			if (type == FillType::Solid)
			{
				return D3D12_FILL_MODE_SOLID;
			}
			return D3D12_FILL_MODE();
		}
		
		D3D12_CULL_MODE D3D12CullMode(CullType type)
		{
			switch (type)
			{
			case Engine::GraphicsSystem::CullType::None:
				return D3D12_CULL_MODE_NONE;
				break;
			case Engine::GraphicsSystem::CullType::Front:
				return D3D12_CULL_MODE_FRONT;
				break;
			case Engine::GraphicsSystem::CullType::Back:
				return D3D12_CULL_MODE_BACK;
				break;
			default:
				break;
			}

			return D3D12_CULL_MODE();
		}

		D3D12_INPUT_CLASSIFICATION D3D12InputClassification(InputClassification classification)
		{
			if (classification == InputClassification::Vertex)
			{
				return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			}
			if (classification == InputClassification::Instance)
			{
				return D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
			}
			return D3D12_INPUT_CLASSIFICATION();
		}

		D3D12_BLEND D3D12Blend(BlendFactor factor)
		{
			switch (factor)
			{
			case Engine::GraphicsSystem::BlendFactor::Zero:
				return D3D12_BLEND_ZERO;
				break;
			case Engine::GraphicsSystem::BlendFactor::One:
				return D3D12_BLEND_ONE;
				break;
			case Engine::GraphicsSystem::BlendFactor::SourceColor:
				return D3D12_BLEND_SRC_COLOR;
				break;
			case Engine::GraphicsSystem::BlendFactor::InverseSourceColor:
				return D3D12_BLEND_INV_SRC_COLOR;
				break;
			case Engine::GraphicsSystem::BlendFactor::SourceAlpha:
				return D3D12_BLEND_SRC_ALPHA;
				break;
			case Engine::GraphicsSystem::BlendFactor::InverseSourceAlpha:
				return D3D12_BLEND_INV_SRC_ALPHA;
				break;
			case Engine::GraphicsSystem::BlendFactor::DestinationColor:
				return D3D12_BLEND_DEST_COLOR;
				break;
			case Engine::GraphicsSystem::BlendFactor::InverseDestinationColor:
				return D3D12_BLEND_INV_DEST_COLOR;
				break;
			case Engine::GraphicsSystem::BlendFactor::DestinationAlpha:
				return D3D12_BLEND_DEST_ALPHA;
				break;
			case Engine::GraphicsSystem::BlendFactor::InverseDestinationAlpha:
				return D3D12_BLEND_INV_DEST_ALPHA;
				break;
			case Engine::GraphicsSystem::BlendFactor::SourceAlphaSaturate:
				return D3D12_BLEND_SRC_ALPHA_SAT;
				break;
			case Engine::GraphicsSystem::BlendFactor::PresetFactor:
				return D3D12_BLEND_BLEND_FACTOR;
				break;
			case Engine::GraphicsSystem::BlendFactor::InversePresetFactor:
				return D3D12_BLEND_INV_BLEND_FACTOR;
				break;
			default:
				break;
			}

			return D3D12_BLEND();
		}
		
		D3D12_BLEND_OP D3D12BlendOp(BlendOperation operation)
		{
			switch (operation)
			{
			case Engine::GraphicsSystem::BlendOperation::Addition:
				return D3D12_BLEND_OP_ADD;
				break;
			case Engine::GraphicsSystem::BlendOperation::Subtract:
				return D3D12_BLEND_OP_SUBTRACT;
				break;
			case Engine::GraphicsSystem::BlendOperation::ReverseSubtract:
				return D3D12_BLEND_OP_REV_SUBTRACT;
				break;
			case Engine::GraphicsSystem::BlendOperation::Min:
				return D3D12_BLEND_OP_MIN;
				break;
			case Engine::GraphicsSystem::BlendOperation::Max:
				return D3D12_BLEND_OP_MAX;
				break;
			default:
				break;
			}
		
			return D3D12_BLEND_OP();
		}

		D3D12_LOGIC_OP D3D12LogicOp(LogicOperation operation)
		{
			switch (operation)
			{
			case Engine::GraphicsSystem::LogicOperation::Clear:
				return D3D12_LOGIC_OP_CLEAR;
				break;
			case Engine::GraphicsSystem::LogicOperation::Set:
				return D3D12_LOGIC_OP_SET;
				break;
			case Engine::GraphicsSystem::LogicOperation::Copy:
				return D3D12_LOGIC_OP_COPY;
				break;
			case Engine::GraphicsSystem::LogicOperation::InvertedCopy:
				return D3D12_LOGIC_OP_COPY_INVERTED;
				break;
			case Engine::GraphicsSystem::LogicOperation::None:
				return D3D12_LOGIC_OP_NOOP;
				break;
			case Engine::GraphicsSystem::LogicOperation::Inverted:
				return D3D12_LOGIC_OP_INVERT;
				break;
			case Engine::GraphicsSystem::LogicOperation::And:
				return D3D12_LOGIC_OP_AND;
				break;
			case Engine::GraphicsSystem::LogicOperation::NotAnd:
				return D3D12_LOGIC_OP_NAND;
				break;
			case Engine::GraphicsSystem::LogicOperation::Or:
				return D3D12_LOGIC_OP_OR;
				break;
			case Engine::GraphicsSystem::LogicOperation::NotOr:
				return D3D12_LOGIC_OP_NOR;
				break;
			case Engine::GraphicsSystem::LogicOperation::ExclusiveOr:
				return D3D12_LOGIC_OP_XOR;
				break;
			case Engine::GraphicsSystem::LogicOperation::Equivalent:
				return D3D12_LOGIC_OP_EQUIV;
				break;
			case Engine::GraphicsSystem::LogicOperation::AndReverse:
				return D3D12_LOGIC_OP_AND_REVERSE;
				break;
			case Engine::GraphicsSystem::LogicOperation::AndInverted:
				return D3D12_LOGIC_OP_AND_INVERTED;
				break;
			case Engine::GraphicsSystem::LogicOperation::OrReverse:
				return D3D12_LOGIC_OP_OR_REVERSE;
				break;
			case Engine::GraphicsSystem::LogicOperation::OrInverted:
				return D3D12_LOGIC_OP_OR_INVERTED;
				break;
			default:
				break;
			}

			return D3D12_LOGIC_OP();
		}

		D3D12_STENCIL_OP D3D12StencilOp(StencilOperation operation)
		{
			switch (operation)
			{
			case Engine::GraphicsSystem::StencilOperation::Keep:
				return D3D12_STENCIL_OP_KEEP;
				break;
			case Engine::GraphicsSystem::StencilOperation::Zero:
				return D3D12_STENCIL_OP_ZERO;
				break;
			case Engine::GraphicsSystem::StencilOperation::Replace:
				return D3D12_STENCIL_OP_REPLACE;
				break;
			case Engine::GraphicsSystem::StencilOperation::IncrementClamp:
				return D3D12_STENCIL_OP_INCR_SAT;
				break;
			case Engine::GraphicsSystem::StencilOperation::DecrementClamp:
				return D3D12_STENCIL_OP_DECR_SAT;
				break;
			case Engine::GraphicsSystem::StencilOperation::Invert:
				return D3D12_STENCIL_OP_INVERT;
				break;
			case Engine::GraphicsSystem::StencilOperation::IncrementWrap:
				return D3D12_STENCIL_OP_INCR;
				break;
			case Engine::GraphicsSystem::StencilOperation::DecrementWrap:
				return D3D12_STENCIL_OP_DECR;
				break;
			default:
				break;
			}

			return D3D12_STENCIL_OP();
		}

		D3D12_COMPARISON_FUNC D3D12ComparisonFunc(ComparisonFunction function)
		{
			switch (function)
			{
			case Engine::GraphicsSystem::ComparisonFunction::Never:
				return D3D12_COMPARISON_FUNC_NEVER;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::Less:
				return D3D12_COMPARISON_FUNC_LESS;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::Equal:
				return D3D12_COMPARISON_FUNC_EQUAL;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::LessEqual:
				return D3D12_COMPARISON_FUNC_LESS_EQUAL;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::Greater:
				return D3D12_COMPARISON_FUNC_GREATER;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::NotEqual:
				return D3D12_COMPARISON_FUNC_NOT_EQUAL;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::GreaterEqual:
				return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
				break;
			case Engine::GraphicsSystem::ComparisonFunction::Always:
				return D3D12_COMPARISON_FUNC_ALWAYS;
				break;
			default:
				break;
			}

			return D3D12_COMPARISON_FUNC();
		}

		D3D12_DEPTH_WRITE_MASK D3D12DepthWriteMask(DepthWriteMask mask)
		{
			switch (mask)
			{
			case Engine::GraphicsSystem::DepthWriteMask::Zero:
				return D3D12_DEPTH_WRITE_MASK_ZERO;
				break;
			case Engine::GraphicsSystem::DepthWriteMask::All:
				return D3D12_DEPTH_WRITE_MASK_ALL;
				break;
			default:
				break;
			}
			
			return D3D12_DEPTH_WRITE_MASK();
		}
	}
}