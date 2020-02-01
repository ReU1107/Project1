#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IResource;
		enum class VertexFormat : uint8_t;
		enum class IndexFormat : uint8_t;
		enum class BottomLevelType : uint8_t;

		struct SubBottomLevelAccelerationStructureDesc
		{
			union
			{
				struct
				{
					IResource* vertexBuffer;	// ���_�o�b�t�@
					uint32_t vertexCount;		// ���_��
					uint32_t vertexStride;		// ���_�X�g���C�h
				};
				struct
				{
					IResource* aabbBuffer;		// Axis Align Bounding Box�o�b�t�@
					uint32_t aabbCount;			// Axis Align Bounding Box��
					uint32_t aabbStride;		// 
				};

			};

			IResource* indexBuffer;				// �C���f�b�N�X�o�b�t�@
			uint32_t indexCount;				// �C���f�b�N�X��
			IResource* constantBuffer;			// �萔�o�b�t�@
			VertexFormat vertexFormat;			// ���_�t�H�[�}�b�g
			IndexFormat indexFormat;			// �C���f�b�N�X�t�H�[�}�b�g

			BottomLevelType type;				// �^�C�v
			SubBottomLevelAccelerationStructureDesc()
				: vertexBuffer(nullptr)
				, vertexCount(0)
				, vertexStride(0)
				, vertexFormat()
				, indexBuffer(nullptr)
				, indexCount(0)
				, indexFormat()
				, constantBuffer(nullptr)
				, type()
			{
			}
		};
	}
}