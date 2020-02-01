#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class PrimitiveTopology : uint8_t
		{
			PointList,		// �_
			LineList,		// ��
			LineStrip,		// ��
			TriangleList,	// �O�p�`
			TriangleStrip,	// �O�p�`
			Patch,			// �p�b�`(�W�I���g���V�F�[�_�[�Q��)
		};

	}
}