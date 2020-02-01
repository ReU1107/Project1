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
			// ���z�f�X�g���N�^
			virtual ~IResource() {}

			// 
			virtual void* GetNativeResource() const = 0;

			// �X�V
			virtual void Update(void* data, uint64_t size, uint64_t begin = 0, uint64_t end = 0) = 0;

			// �O���ŏ������݂�������ۂɎg�p(�ďo����͕K��Unmap��ǂ�ł�������)
			virtual uint8_t* Map(uint64_t begin = 0, uint64_t end = 0) = 0;
			// �O���ŏ������݂�������ۂɎg�p(Map��ɕK���ǂ�ł�������)
			virtual void Unmap(uint64_t begin = 0, uint64_t end = 0) = 0;
		};

	}

}