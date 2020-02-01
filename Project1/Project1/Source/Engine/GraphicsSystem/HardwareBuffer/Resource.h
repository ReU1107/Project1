#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IResource;
		struct TextureDesc;

		enum class ResourceStates : uint16_t;
		/*
		�C���^�[�t�F�C�X�ƌ��݂�
		���\�[�X�̏�Ԃ�������������
		*/
		class Resource
		{
		private:
			IResource* m_interface;
			ResourceStates m_states;
		public:
			// �R���X�g���N�^
			Resource();
			// �f�X�g���N�^
			~Resource();
			static Resource* Create(const TextureDesc& desc);

			// �X�e�[�g�ݒ�
			void SetStates(ResourceStates states);
			// �C���^�[�t�F�C�X�ݒ�
			void SetInterface(IResource* resource);
			// �C���^�[�t�F�C�X�擾
			IResource* GetInterface() const;
			// �X�e�[�g�擾
			ResourceStates GetStates() const;

		};
	}
}