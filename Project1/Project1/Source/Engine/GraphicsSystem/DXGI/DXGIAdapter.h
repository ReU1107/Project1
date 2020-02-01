#pragma once
#include "..//Interface/IAdapter.h"

struct IDXGIAdapter4;

namespace Engine
{
	namespace GraphicsSystem
	{
		class DXGIAdapter : public IAdapter
		{
		public:
			IDXGIAdapter4* m_nativeAdapter;	// 

		public:
			// コンストラクタ
			DXGIAdapter();
			// デストラクタ
			virtual ~DXGIAdapter();

		};
	}
}