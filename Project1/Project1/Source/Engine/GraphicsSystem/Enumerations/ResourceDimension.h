#pragma once
#include <cstdint>
namespace Engine
{
	namespace GraphicsSystem 
	{
		enum class ResourceDimension : uint8_t
		{
			Unknown,	// �e�N�X�`���^�C�v������������Ă��Ȃ����A�s���ł��B
			None,		// �e�N�X�`�����w�肳��Ă��܂���B
			Any,		// ���ׂẴe�N�X�`���^�C�v�B
			Tex1D,		// 1D�e�N�X�`��
			Tex2D,		// 2D�e�N�X�`��(Texture2D)�B
			Tex3D,		// 3D�{�����[���e�N�X�`��(Texture3D)�B
			Cube,		// �L���[�u�}�b�v �e�N�X�`���B
			Tex2DArray,	// 2D�z��e�N�X�`��(Texture2DArray)�B
			CubeArray,	// Cubemap array texture(CubemapArray).
		};
	}
}