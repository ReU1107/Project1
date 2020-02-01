#pragma once
#include "..//Interface/IResourceView.h"
#include <d3d12.h>
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class D3D12ResourceView : public IResourceView
		{
		public:
			D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle;	// cpu�n���h��
			D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle;	// gpu�n���h��
			uint32_t m_index;							// 
			bool m_isCopy;								// �ʂ̃f�X�N���v�^�[�q�[�v�ɃR�s�[���ꂽ(��Ŗ�肪�N���邩��)
			// ���̏ڍׁ@�p�C�v���C�����P��̃f�X�N���v�^�[�������Ă��邽�߂��ꂼ��̃p�C�v���C���Ŏg�p����Ƃ��ɃR�s�[���邩��
		public:
			// �R���X�g���N�^
			D3D12ResourceView();
			// �f�X�g���N�^
			virtual ~D3D12ResourceView();

		};


	}

}