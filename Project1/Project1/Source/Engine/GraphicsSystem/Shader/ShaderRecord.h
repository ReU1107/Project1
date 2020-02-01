#pragma once
#include <vector>

/*

*/

namespace Engine
{

	namespace GraphicsSystem 
	{

		// �O���錾
		class ShaderResource;
		class IResource;
		class IResourceView;
		class IDescriptorHeap;
		class Buffer;
		class Resource;
		class ResourceView;
		class ResourceDescriptor;
		class VertexBuffer;
		class Texture;
		
		enum class ShaderRecordType : uint8_t;

		enum class LocalRootArgumentType
		{
			Resource,			// ���\�[�X
			ResourceView,		// ���\�[�X�r���[
			DescriptorTable,	// �f�X�N���v�^�[�e�[�u��
		};

		struct LocalRootArgument {
			union
			{
				IResource* resource;	// 
				IResourceView* view;	// 
				IDescriptorHeap* heap;	// 
			};
			LocalRootArgumentType type;		// ���\�[�X�����\�[�X�r���[��
		};

		class ShaderRecord
		{
		private:
			using LocalRootArguments = std::vector<LocalRootArgument>;
			
		private:
			void* m_identifier;					// �V�F�[�_�[���ʎq
			LocalRootArguments m_arguments;		// ���̃V�F�[�_�[�Ŏg�p���郊�\�[�X�Q
			uint32_t m_size;					// �T�C�Y
			uint32_t m_registerIndex;			// �V�F�[�_�[�e�[�u�����ł̓o�^�ԍ�
			ShaderRecordType m_type;			// �^�C�v
		public:
			// �R���X�g���N�^
			ShaderRecord();
			// �f�X�g���N�^
			~ShaderRecord();
		public:
			// �V�F�[�_�[���ʎq�ݒ�
			void SetShaderIdentifier(void* identifier);
			// �o�^�ԍ��ݒ�
			void SetRegisterIndex(uint32_t index);

			// ���\�[�X�ǉ�
			void AddResource(Buffer* buffer);
			void AddResource(Resource* resource);
			void AddResource(IResource* resource);
			
			// ���\�[�X�r���[�ǉ�
			void AddResourceView(ResourceView* resourceView);
			void AddResourceView(IResourceView* resourceView);

			// �f�X�N���v�^�[�e�[�u���ǉ�
			void AddDescriptorTable(ResourceDescriptor* descriptor);
			void AddDescriptorTable(IDescriptorHeap* descriptorTable);

			// �V�F�[�_�[���ʎq�擾
			void* GetShaderIdentifier() const;
			
			// ���[�J�����擾
			uint32_t GetLocalRootArgumentCount() const;
			// ���[�J��
			const LocalRootArgument& GetLocalRootArgument(uint32_t index) const;

			// �o�^�ԍ��擾
			uint32_t GetRegisterIndex() const;

			// �T�C�Y�擾
			uint32_t GetSize() const;
		};

	}

}