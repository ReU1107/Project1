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
			// �R���X�g���N�^
			DXGIAdapter();
			// �f�X�g���N�^
			virtual ~DXGIAdapter();

		};
	}
}