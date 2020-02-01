#pragma once
#include <cstdint>

/*
D3D12_ROOT_SIGNATURE_DESC

*/

namespace Engine 
{

	namespace GraphicsSystem 
	{
		class IShader;
		enum class RootSignatureFlags : uint8_t;
		struct ShaderResourceLayoutDesc;

		struct RootSignatureDesc
		{
			ShaderResourceLayoutDesc* layouts;	// ���C�A�E�g�z��
			IShader* shader;					// �V�F�[�_�[
			uint32_t layoutCount;				// ���C�A�E�g�̐�
			RootSignatureFlags flags;			// �t���O
			bool staticSampler;					// �T���v���[���g�p���邩
			bool isShader;						
		};
	}

}