#pragma once
#include <cstdint>

/*
DirectX�̓�����
�ǂ̃o�[�W�������g�p���邩���肷��
����11,12�̂�

*/

namespace Engine
{

	namespace GraphicsSystem 
	{
	
		// �`��
		enum class API : uint8_t
		{
			DirectX,
			OpenGL
		};
	}
}