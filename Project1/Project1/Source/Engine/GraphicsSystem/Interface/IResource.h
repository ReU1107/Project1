#pragma once
//#include "../..//IUnknown.h"
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class IResource// : public IUnknown
		{
		public:
			// 仮想デストラクタ
			virtual ~IResource() {}

			// 
			virtual void* GetNativeResource() const = 0;

			// 更新
			virtual void Update(void* data, uint64_t size, uint64_t begin = 0, uint64_t end = 0) = 0;

			// 外部で書き込みをさせる際に使用(呼出し後は必ずUnmapを読んでください)
			virtual uint8_t* Map(uint64_t begin = 0, uint64_t end = 0) = 0;
			// 外部で書き込みをさせる際に使用(Map後に必ず読んでください)
			virtual void Unmap(uint64_t begin = 0, uint64_t end = 0) = 0;
		};

	}

}