#pragma once
#include <cstdint>
#include <string>
#include "../Enumerations/ResourceViewType.h"

/*
copyable���g�p����ꍇ�̓f�[�^��VRAM��ɍ쐬���邽��
�R�}���h���X�g���g�p���ăR�s�[�������s���Ă�������
*/

namespace Engine
{

	namespace GraphicsSystem
	{
		
		// �O���錾
		class IResource;
		enum class ResourceStates : uint16_t;
		enum class ResourceFlags : uint8_t;
		class ResourceView;
		class ResourceDescriptor;

		class Buffer
		{
		protected:
			IResource* m_interface;			// ���\�[�X
			Buffer* m_copyable;				// �R�s�[�p
			ResourceView* m_view;			// 
			uint64_t m_stride;				// �X�g���C�h
			uint64_t m_count;				// ��
			uint64_t m_size;				// �T�C�Y
			ResourceStates m_states;		// �X�e�[�g
			ResourceFlags m_flags;			// �t���O
			ResourceViewType m_viewType;	// �r���[�^�C�v
			bool m_isDynamic;				// �悭CPU����A�N�Z�X���邩
			bool m_isRaw;					// ���̃f�[�^�Ƃ��ăA�N�Z�X���邩ByteAddressBuffer�Ȃ�true

		public:
			// �R���X�g���N�^
			Buffer(ResourceViewType type);
			// �f�X�g���N�^
			virtual ~Buffer();
		public:
			// �X�g���C�h�ݒ�
			void SetStride(uint64_t stride);
			// ���ݒ�
			void SetCount(uint64_t count);
			// �T�C�Y�ݒ�()
			void SetSize(uint64_t size);
			// �X�e�[�g�ݒ�
			void SetStates(ResourceStates states);

			// �t���O�ݒ�
			void SetFlags(ResourceFlags flags);

			void SetInterface(IResource* resource);

			void Dynamic(bool dynamic = true);

			void Raw(bool raw = true);

			// �X�g���C�h�擾
			uint64_t GetStride() const { return m_stride; }
			// ���擾
			uint64_t GetCount() const { return m_count; }
			// �T�C�Y�擾
			uint64_t GetSize() const { return m_size; }
			// ���\�[�X�擾
			IResource* GetInterface() const { return m_interface; }

			ResourceStates GetStates() const { return m_states; }

			Buffer* GetCopyable() const { return m_copyable; }

			// ���\�[�X�r���[�擾
			ResourceView* GetView() const { return m_view; }
			// 
			bool IsDynamic() { return m_isDynamic; }

			bool IsRaw() { return m_isRaw; }

			void RecreateResourceView(ResourceDescriptor* descriptor);

			// �쐬
			virtual void Create(void* data = nullptr);

			uint8_t* Map(uint64_t begin = 0, uint64_t end = 0);

			void Unmap(uint64_t begin = 0, uint64_t end = 0);

			// �o�b�t�@���X�V
			void Update(void* data, uint64_t begin = 0, uint64_t end = 0);

			void SetName(const std::wstring& name);
		};

	}

}