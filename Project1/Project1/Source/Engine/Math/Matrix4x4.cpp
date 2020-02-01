#include "Matrix4x4.h"

namespace Engine
{
	const Matrix4x4 Matrix4x4::Identity = Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
													0.0f, 1.0f, 0.0f, 0.0f,
													0.0f, 0.0f, 1.0f, 0.0f,
													0.0f, 0.0f, 0.0f, 1.0f);
	const Matrix4x4 Matrix4x4::Zero = Matrix4x4();
}