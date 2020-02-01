#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class IShader
		{
		public:
			virtual ~IShader() {}

			// SDK�ˑ��V�F�[�_�[�擾
			virtual void* GetNativeShader() const = 0;
			// �o�b�t�@�|�C���^�擾
			virtual void* GetBuffer() const = 0;
			// �o�b�t�@�T�C�Y�擾
			virtual uint64_t GetSize() const = 0;
		};
	}
}