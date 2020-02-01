#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		enum class ResourceStates : uint16_t
		{
			Common = 0x00,					// なし
			VertexConstantBuffer = 0x01,	// 頂点,定数バッファ
			IndexBuffer = 0x02,				// インデックスバッファ
			RenderTarget = 0x04,			// レンダーターゲット
			UnorderedAccess = 0x08,			// アンオーダードアクセス
			DepthWrite = 0x10,				// 深度書き込み
			DepthRead = 0x20,				// 深度読み込み
			NonPixelShaderResource = 0x40,	// ピクセルシェーダー内でのリソースとして扱わない
			PixelShaderResource = 0x80,		// ピクセルシェーダー内でリソースとして扱う
			StreamOut = 0x100,				// ストリームアウト
			IndirectArgument = 0x200,		// 即時
			CopyDestination = 0x400,		// コピー先
			CopySource = 0x800,				// コピー元
			ResolveDestination = 0x1000,	// 
			ResolveSource = 0x2000,			// 
			RaytracingStructure = 0x4000,	// レイトレーシング構造体
			GenericRead = ((((				// 一般的な読み込み用のステート
				(VertexConstantBuffer | IndexBuffer)
				| NonPixelShaderResource)
				| PixelShaderResource)
				| IndirectArgument) | CopySource),
			Present = 0x8000,				// プレゼント

		};

	}

}

/*
	D3D12_RESOURCE_STATE_COMMON	= 0,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER	= 0x1,
		D3D12_RESOURCE_STATE_INDEX_BUFFER	= 0x2,
		D3D12_RESOURCE_STATE_RENDER_TARGET	= 0x4,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS	= 0x8,
		D3D12_RESOURCE_STATE_DEPTH_WRITE	= 0x10,
		D3D12_RESOURCE_STATE_DEPTH_READ	= 0x20,
		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE	= 0x40,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE	= 0x80,
		D3D12_RESOURCE_STATE_STREAM_OUT	= 0x100,
		D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT	= 0x200,
		D3D12_RESOURCE_STATE_COPY_DEST	= 0x400,
		D3D12_RESOURCE_STATE_COPY_SOURCE	= 0x800,
		D3D12_RESOURCE_STATE_RESOLVE_DEST	= 0x1000,
		D3D12_RESOURCE_STATE_RESOLVE_SOURCE	= 0x2000,
		D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE	= 0x400000,
		D3D12_RESOURCE_STATE_SHADING_RATE_SOURCE	= 0x1000000,
		D3D12_RESOURCE_STATE_GENERIC_READ	= ( ( ( ( ( 0x1 | 0x2 )  | 0x40 )  | 0x80 )  | 0x200 )  | 0x800 ) ,
		D3D12_RESOURCE_STATE_PRESENT	= 0,
		D3D12_RESOURCE_STATE_PREDICATION	= 0x200,
		D3D12_RESOURCE_STATE_VIDEO_DECODE_READ	= 0x10000,
		D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE	= 0x20000,
		D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ	= 0x40000,
		D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE	= 0x80000,
		D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ	= 0x200000,
		D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE	= 0x800000
*/