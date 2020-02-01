#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderType : uint8_t
		{
			All,		// �S��		Raytracing�͂���
			Vertex,		// ���_
			Hull,		// �n��
			Geometry,	// �W�I���g���[
			Domain,		// �h���C��
			Pixel,		// �s�N�Z��
		};
	}

}