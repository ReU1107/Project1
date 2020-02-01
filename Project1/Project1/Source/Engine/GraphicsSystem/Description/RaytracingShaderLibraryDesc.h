#pragma once
#include <string>

/*
D3D12_DXIL_LIBRARY
*/

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class IShader;

		struct RaytracingShaderLibraryDesc
		{
			IShader* shader;				// �V�F�[�_�[���C�u�����[�I�u�W�F�N�g
			const wchar_t** shaderNames;	// ���C�u�����[���̃V�F�[�_�[�̂��ꂼ��̊֐���
			uint32_t shaderCount;			// ���̃V�F�[�_�[��
		};

	}

}
