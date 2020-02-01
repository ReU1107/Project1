#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class ResourceFormat : uint8_t;
		enum class InputClassification;

		struct InputElementDesc
		{
			const char* semanticName;				// セマンティクス名
			uint32_t semanticIndex;					// セマンティクス番号(名前が被った時に使用する基本的には０)
			ResourceFormat format;					// フォーマット
			uint32_t inputSlot;						// 
			uint32_t aligneOffset;					// 基本0xffffffff
			InputClassification classification;		// 分類

			uint32_t instanceCount;					// インスタンスの時に使用(それ以外の時は0固定)
		};
	}
}