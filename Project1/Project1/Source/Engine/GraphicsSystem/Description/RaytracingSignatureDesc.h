#pragma once
#include <cstdint>
/*
���C�g���[�V���O�ƃV�O�l�`�����֘A�t����
*/

/*
D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE
D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE
*/

namespace Engine 
{

	namespace GraphicsSystem 
	{
		class IRootSignature;
		enum class RootSignatureType : uint8_t;

		struct RaytracingSignatureDesc
		{
			IRootSignature* rootSignature;	// �V�O�l�`��
			RootSignatureType type;			// 
		};
	}

}

