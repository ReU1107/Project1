#pragma once
#include <cstdint>

/*
���\�[�X���V�F�[�_�[�̂ǂ��ɑ΂��ĉ���u������
�L�q��������
*/

/*
D3D12_ROOT_PARAMETER
*/
namespace Engine 
{

	namespace GraphicsSystem 
	{

		// �O���錾
		struct ShaderResourceParameterDesc;
		struct ShaderResourceConstantsDesc;
		struct ShaderResourceDescriptorDesc;
		enum class ShaderResourceLayoutType : uint8_t;
		enum class ShaderType : uint8_t;

		// �V�F�[�_�[���\�[�X�̔z�u���L�q
		struct ShaderResourceLayoutDesc
		{
			union
			{
				struct {
					ShaderResourceParameterDesc* parameters;// �p�����[�^�[�z��
					uint32_t parameterCount;				// �p�����[�^�[��
				}descriptorTable;
				ShaderResourceConstantsDesc constans;		// �萔
				ShaderResourceDescriptorDesc descriptor;	// �C�ӂ̃��\�[�X�r���[

			};
			ShaderResourceLayoutType layoutType;			// ���C�A�E�g�̎��
			ShaderType shaderType;							// �g�p����V�F�[�_�[�^�C�v
		};
	}

}