#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		// �V�F�[�_�[�e�[�u�����
		enum class ShaderTableType : uint8_t
		{
			Miss,			// ����������Ȃ��������Ă΂��V�F�[�_�[
			Hit,			// �����ɓ����������Ă΂��V�F�[�_�[
			Callable,		// 
		};

	}

}
