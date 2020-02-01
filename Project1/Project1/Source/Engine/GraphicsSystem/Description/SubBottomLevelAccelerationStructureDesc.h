#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IResource;
		enum class VertexFormat : uint8_t;
		enum class IndexFormat : uint8_t;
		enum class BottomLevelType : uint8_t;

		struct SubBottomLevelAccelerationStructureDesc
		{
			union
			{
				struct
				{
					IResource* vertexBuffer;	// 頂点バッファ
					uint32_t vertexCount;		// 頂点数
					uint32_t vertexStride;		// 頂点ストライド
				};
				struct
				{
					IResource* aabbBuffer;		// Axis Align Bounding Boxバッファ
					uint32_t aabbCount;			// Axis Align Bounding Box数
					uint32_t aabbStride;		// 
				};

			};

			IResource* indexBuffer;				// インデックスバッファ
			uint32_t indexCount;				// インデックス数
			IResource* constantBuffer;			// 定数バッファ
			VertexFormat vertexFormat;			// 頂点フォーマット
			IndexFormat indexFormat;			// インデックスフォーマット

			BottomLevelType type;				// タイプ
			SubBottomLevelAccelerationStructureDesc()
				: vertexBuffer(nullptr)
				, vertexCount(0)
				, vertexStride(0)
				, vertexFormat()
				, indexBuffer(nullptr)
				, indexCount(0)
				, indexFormat()
				, constantBuffer(nullptr)
				, type()
			{
			}
		};
	}
}