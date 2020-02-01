#pragma once
#include <cstdint>
#include <string>

namespace Engine 
{

	namespace GraphicsSystem
	{

		class IDescriptorHeap;
		class IResourceView;
		class ResourceView;
		enum class DescriptorHeapType : uint8_t;

		class ResourceDescriptor
		{
		private:
			IDescriptorHeap* m_interface;	// �q�[�v
			DescriptorHeapType m_type;		// �^�C�v
			uint32_t m_maxCount;			// �ő�m�ې�
			uint32_t m_currentIndex;		// ���݂̊m�ې�
		public:
			// �R���X�g���N�^
			ResourceDescriptor();
			// �f�X�g���N�^
			~ResourceDescriptor();
			// 
			static ResourceDescriptor* CreateShaderResource(uint32_t count, bool shaderAccess = true, uint32_t nodeMask = 0);
			// 
			static ResourceDescriptor* CreateRenderTarget(uint32_t count, uint32_t nodeMask = 0);
			// 
			static ResourceDescriptor* CreateDepthStencil(uint32_t count, uint32_t nodeMask = 0);

		private:
			static ResourceDescriptor* Create(DescriptorHeapType type, uint32_t count, bool shaderAccess = true, uint32_t nodeMask = 0);
		public:
			// �ԍ��w��Ń��Z�b�g�ԍ��̌�낪��������܂�
			void Reset(uint32_t index = 0);

			// �쐬
			// �q�[�v�擾
			IDescriptorHeap* GetInterface() const { return m_interface; }

			void CopyView(ResourceView* view);
			void CopyView(IResourceView* view);


			void SetName(const std::wstring& name);
		};

	}

}