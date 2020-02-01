#pragma once
#include <string>

/*
D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE

*/

namespace Engine
{

	namespace GraphicsSystem 
	{

		// �V�F�[�_�[�Ƒ��̃T�u���\�[�X���o�C���h
		struct RaytracingAssociationDesc
		{
			const wchar_t** shaderNames;// �o�C���h����V�F�[�_�[
			uint32_t shaderCount;		// �o�C���h����V�F�[�_�[��
			uint32_t index;				// �o�C���h����T�u�X�e�[�g�̊i�[��
			
		};
	}

}
