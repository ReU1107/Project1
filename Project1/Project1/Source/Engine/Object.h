#pragma once
#include <string>
#include <memory>
#include "InstanceID.h"

namespace Engine
{
	// �S�ẴI�u�W�F�N�g�̊��N���X
	class Object
	{
	private:
		std::string m_name;	// �I�u�W�F�N�g��
		uint32_t m_nameHash;	// �n�b�V���l
	public:
		// �R���X�g���N�^
		Object(const std::string& name) noexcept;
		// �f�X�g���N�^
		virtual ~Object() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Object; }
		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const { return InstanceID::Object; }

		// �Ⴄ�I�u�W�F�N�g���Q�Ƃ��Ă��邩
		bool operator!=(const Object* other) const;
		// �����I�u�W�F�N�g���Q�Ƃ��Ă��邩
		bool operator==(const Object* other) const;

	public:
		// ���O�ݒ�
		void SetName(const std::string& name);
		// ���O�擾
		const std::string& GetName() const;
		// �n�b�V���l�擾
		uint32_t GetNameHash() const;

		// �ϐ��A�h���X�擾
		virtual void* GetPropertyAddress(const std::string& name);

	};
}

/*
�I�u�W�F�N�g�̖��O��r������ꍇ��
�n�b�V���l���g�p������������
���R:
stricmp���̔�r�֐���
�����̃R�[�h�ԍ��𕶎��񕪔�r���Ă�������l��r�𕶎��������Ă���
�����l��r��1��ōς�
������Ɛ��l�ł͐��l�̕�����r���͂₢
*/
/*
GetProperty()
�����ɂ͎擾�������ϐ���
���O����v���Ă����炻�̕ϐ��̃A�h���X��Ԃ�
*/