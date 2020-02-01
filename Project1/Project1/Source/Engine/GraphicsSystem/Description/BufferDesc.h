#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem
	{

		enum class BufferType : uint8_t;
		enum class ResourceFlags : uint8_t;
		enum class ResourceStates : uint16_t;

		struct BufferDesc
		{
			uint64_t size;			// サイズ
			ResourceStates state;	// 状態
			//BufferType type;		// タイプ
			ResourceFlags flags;	// フラグ
			bool isDynamic;			// 頻繁にCPUからアクセスするか
			// タイプに応じたデフォルト値設定
		};

	}

}