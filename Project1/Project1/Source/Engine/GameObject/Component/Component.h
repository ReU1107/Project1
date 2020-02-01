#pragma once
#include <vector>
#include "../../Object.h"
#include <string>
#include <memory>
#include "../SearchPriority.h"

namespace Engine
{
	// �O���錾
	class GameObject;
	class Transform;

	// �U�镑��
	class Component : public Object
	{
	private:
		using base = Object;
		using GameObjectPtr = std::shared_ptr<GameObject>;
	private:
		GameObjectPtr m_owner;
	protected:
		// �R���X�g���N�^
		Component(const std::string& name) noexcept;
		// ���z�f�X�g���N�^
		virtual ~Component() noexcept;
	public:
		// �I�u�W�F�N�gID
		static const InstanceID ID() { return InstanceID::Component; }

		template<class T>
		static std::shared_ptr<T> Create();

		// ���g�����Q�[���I�u�W�F�N�g
		void SetOwner(GameObjectPtr owner);
	public:

		// ���L�Ҏ擾
		GameObjectPtr GetOwner() const;

		// �e�I�u�W�F�N�g�擾
		GameObjectPtr GetParent() const;

		// ���j�I�u�W�F�N�g�擾
		GameObjectPtr GetOldestChild() const;

		// ��I�u�W�F�N�g�擾
		GameObjectPtr GetNextSibling() const;

		std::shared_ptr<Engine::Transform> GetTransform() const;

		template<class T>
		std::shared_ptr<T> AddComponent();

		// T�^�̃R���|�[�l���g���擾
		template<class T>
		inline uint32_t GetComponentCount() const;

	public:
		// T�^�̃R���|�[�l���g�擾
		template<class T>
		inline std::shared_ptr<T> GetComponent(uint32_t index = 0);

		// T�^�̃R���|�[�l���g�z��擾
		template<class T>
		inline std::vector<std::shared_ptr<Component>>* GetComponents();

		// �e����T�^�̃R���|�[�l���g�擾
		template<class T>
		inline std::shared_ptr<T> GetComponentInParent();

		// �q������T�^�̃R���|�[�l���g�擾
		template<class T>
		inline std::shared_ptr<T> GetComponentInChildren();

		// T�^�̃R���|�[�l���g�����S�Ă̎q�I�u�W�F�N�g�̃R���|�[�l���g�擾
		template<class T>
		inline std::vector<std::shared_ptr<T>> GetComponentsInChildren();

		// T�^�̃R���|�[�l���g���S�Ă̎q���̃R���|�[�l���g�擾
		template<class T>
		inline std::vector<std::shared_ptr<T>> GetComponentsInDescendant(SearchPriority priority = SearchPriority::DepthFirst) const;
	};
}
using ComponentPtr = std::shared_ptr<Engine::Component>;

#include "ComponentImpl.h"