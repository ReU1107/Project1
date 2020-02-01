#pragma once
#include <cstdint>

/*
D3D12_HIT_GROUP_DESC
*/

namespace Engine 
{

	namespace GraphicsSystem
	{

		enum class BottomLevelType : uint8_t;

		struct RaytracingHitGroupDesc
		{
			const wchar_t* name;					// ���̃O���[�v�̖��O
			const wchar_t* hitShader;				// ���C�ƏՓ˂����ۂɌĂяo�����V�F�[�_�[
			const wchar_t* intersectShader;			// �Փ˔���p�V�F�[�_�[
			const wchar_t* anyHitShader;			// 
			BottomLevelType type;				// �Փˌ`��
			RaytracingHitGroupDesc()
				: name(nullptr), hitShader(nullptr), intersectShader(nullptr)
				, anyHitShader(nullptr), type()
			{
			}
		};

	}

}

/*
wchar_t*�Ŏ����R:
���̍\���̂�union�ň͂ނ���std::wstring�ł����Ƃ��ł��Ȃ�
*/