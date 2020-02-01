#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		enum class ResourceStates : uint16_t
		{
			Common = 0x00,					// �Ȃ�
			VertexConstantBuffer = 0x01,	// ���_,�萔�o�b�t�@
			IndexBuffer = 0x02,				// �C���f�b�N�X�o�b�t�@
			RenderTarget = 0x04,			// �����_�[�^�[�Q�b�g
			UnorderedAccess = 0x08,			// �A���I�[�_�[�h�A�N�Z�X
			DepthWrite = 0x10,				// �[�x��������
			DepthRead = 0x20,				// �[�x�ǂݍ���
			NonPixelShaderResource = 0x40,	// �s�N�Z���V�F�[�_�[���ł̃��\�[�X�Ƃ��Ĉ���Ȃ�
			PixelShaderResource = 0x80,		// �s�N�Z���V�F�[�_�[���Ń��\�[�X�Ƃ��Ĉ���
			StreamOut = 0x100,				// �X�g���[���A�E�g
			IndirectArgument = 0x200,		// ����
			CopyDestination = 0x400,		// �R�s�[��
			CopySource = 0x800,				// �R�s�[��
			ResolveDestination = 0x1000,	// 
			ResolveSource = 0x2000,			// 
			RaytracingStructure = 0x4000,	// ���C�g���[�V���O�\����
			GenericRead = ((((				// ��ʓI�ȓǂݍ��ݗp�̃X�e�[�g
				(VertexConstantBuffer | IndexBuffer)
				| NonPixelShaderResource)
				| PixelShaderResource)
				| IndirectArgument) | CopySource),
			Present = 0x8000,				// �v���[���g

		};

	}

}

/*
	D3D12_RESOURCE_STATE_COMMON	= 0,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER	= 0x1,
		D3D12_RESOURCE_STATE_INDEX_BUFFER	= 0x2,
		D3D12_RESOURCE_STATE_RENDER_TARGET	= 0x4,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS	= 0x8,
		D3D12_RESOURCE_STATE_DEPTH_WRITE	= 0x10,
		D3D12_RESOURCE_STATE_DEPTH_READ	= 0x20,
		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE	= 0x40,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE	= 0x80,
		D3D12_RESOURCE_STATE_STREAM_OUT	= 0x100,
		D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT	= 0x200,
		D3D12_RESOURCE_STATE_COPY_DEST	= 0x400,
		D3D12_RESOURCE_STATE_COPY_SOURCE	= 0x800,
		D3D12_RESOURCE_STATE_RESOLVE_DEST	= 0x1000,
		D3D12_RESOURCE_STATE_RESOLVE_SOURCE	= 0x2000,
		D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE	= 0x400000,
		D3D12_RESOURCE_STATE_SHADING_RATE_SOURCE	= 0x1000000,
		D3D12_RESOURCE_STATE_GENERIC_READ	= ( ( ( ( ( 0x1 | 0x2 )  | 0x40 )  | 0x80 )  | 0x200 )  | 0x800 ) ,
		D3D12_RESOURCE_STATE_PRESENT	= 0,
		D3D12_RESOURCE_STATE_PREDICATION	= 0x200,
		D3D12_RESOURCE_STATE_VIDEO_DECODE_READ	= 0x10000,
		D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE	= 0x20000,
		D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ	= 0x40000,
		D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE	= 0x80000,
		D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ	= 0x200000,
		D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE	= 0x800000
*/