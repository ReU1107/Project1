#pragma once
#include <string>
#include <cstdint>
#include "../../Utility/AccessObject.h"

namespace Engine 
{

	namespace GraphicsSystem
	{

		class Resource;
		class ResourceView;
		class ResourceDescriptor;
		enum class ResourceFormat : uint8_t;
		enum class ResourceStates : uint16_t;

		// �S�Ẵe�N�X�`���̊��N���X
		class Texture : public AccessObject<Texture>
		{
		private:
			using base = AccessObject<Texture>;
			using TexturePtr = std::shared_ptr<Texture>;
		public:
			Resource* m_resource;					// ���\�[�X
			ResourceView* m_shaderResourceView;		// �V�F�[�_�[���\�[�X�r���[
			ResourceView* m_unorderedAccessView;	// �A���I�[�_�[�h�A�N�Z�X�r���[
			ResourceFormat m_format;
		public:
			// �R���X�g���N�^
			Texture(const std::string& name);
			// �f�X�g���N�^
			virtual ~Texture();

			// �C���X�^���XID
			static const InstanceID ID() { return InstanceID::Texture; }
			// �C���X�^���XID�擾
			virtual InstanceID GetInstanceID() const { return InstanceID::Texture; }
		public:

			static TexturePtr Create(const std::string& fileName);
			static TexturePtr Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool renderTarget = false, bool depthStencil = false, bool unorderedAccess = false, bool shaderResource = true);
		
			// ���\�[�X�ݒ�
			void SetResource(Resource* resource);
			// �t�H�[�}�b�g�ݒ�
			void SetFormat(ResourceFormat format);

			// �V�F�[�_�[���\�[�X�r���[�쐬
			void CreateShaderResourceView();

			// �A���I�[�_�[�h�A�N�Z�X�r���[�쐬
			void CreateUnorderedAccessView();

			// �V�F�[�_�[���\�[�X�r���[�쐬
			void RecreateShaderResourceView(ResourceDescriptor* descriptor);

			// �A���I�[�_�[�h�A�N�Z�X�r���[�쐬
			void RecreateUnorderedAccessView(ResourceDescriptor* descriptor);

			// �r���[�ݒ�
			void SetShaderResourceView(ResourceView* view);
			// �X�e�[�g�擾
			ResourceStates GetStates() const;
			// ���\�[�X�擾
			Resource* GetResource() const;
			// �V�F�[�_�[���\�[�X�r���[�擾
			ResourceView* GetShaderResourceView() const;
			// �A���I�[�_�[�h�A�N�Z�X�r���[�擾
			ResourceView* GetUnorderedAccessView() const;

			// �t�H�[�}�b�g�擾
			ResourceFormat GetFormat() const;

			void SetName(const std::wstring& name);
		};
	}
}

using TexturePtr = std::shared_ptr<Engine::GraphicsSystem::Texture>;
