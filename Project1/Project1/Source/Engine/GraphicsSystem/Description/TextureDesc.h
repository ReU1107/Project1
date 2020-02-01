#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		enum class ResourceFlags : uint8_t;
		enum class ResourceFormat : uint8_t;
		enum class ResourceDimension : uint8_t;
		enum class ResourceStates : uint16_t;

		struct TextureDesc
		{
			uint32_t width;					// ��
			uint32_t height;				// ����
			union {
				uint32_t arrayCount;
				uint32_t depth;
			};
			uint32_t mipLevel;				// �~�b�v�}�b�v���x��
			uint32_t multiSampleCount;		// �}���`�T���v���J�E���g
			uint32_t multiSampleQuality;	// �}���`�T���v���N�I���e�B
			ResourceStates states;			// ���\�[�X�̏������
			ResourceDimension dimension;	// ���\�[�X�̎���
			ResourceFlags flags;			// �t���O
			ResourceFormat format;			// �t�H�[�}�b�g
			union
			{
				float color[4];				// 
				struct
				{
					float depth;			// 
					uint8_t stencil;		// 
				};

			}clearValue;					// 

			static TextureDesc Default2D(uint32_t width, uint32_t height, ResourceFormat format, bool renderTarget = false, bool depthStencil = false, bool unorderedAccess = false, bool shaderResource = true);
		};


	}

}