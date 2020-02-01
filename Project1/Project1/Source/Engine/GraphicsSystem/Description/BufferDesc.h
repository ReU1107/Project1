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
			uint64_t size;			// �T�C�Y
			ResourceStates state;	// ���
			//BufferType type;		// �^�C�v
			ResourceFlags flags;	// �t���O
			bool isDynamic;			// �p�ɂ�CPU����A�N�Z�X���邩
			// �^�C�v�ɉ������f�t�H���g�l�ݒ�
		};

	}

}