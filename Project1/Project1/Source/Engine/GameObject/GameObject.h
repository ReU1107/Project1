#pragma once
#include <vector>
#include <list>
#include <unordered_map>
#include "../InstanceID.h"
#include "../Object.h"
#include "SearchPriority.h"

namespace Engine
{
	class Component;
	class Transform;

	class GameObject final : public std::enable_shared_from_this<GameObject>, public Object
	{
	private:
		using base = Object;
		using Components = std::unordered_map<InstanceID, std::vector<std::shared_ptr<Component>>>;
		using GameObjectPtr = std::shared_ptr<GameObject>;
	private:
		static std::unordered_map<std::string, GameObjectPtr> allObjects;
	private:
		Components m_components;				// �R���|�[�l���g�z��
		std::weak_ptr<Engine::Transform> m_transform;
		GameObjectPtr m_root;					// ��c�I�u�W�F�N�g
		GameObjectPtr m_parent;					// �e�I�u�W�F�N�g
		GameObjectPtr m_oldestChild;			// ���j�I�u�W�F�N�g
		GameObjectPtr m_youngestChild;			// ���q�I�u�W�F�N�g
		GameObjectPtr m_prevSibling;			// �Z�I�u�W�F�N�g
		GameObjectPtr m_nextSibling;			// ��I�u�W�F�N�g

		uint32_t m_childCount;					// �q�I�u�W�F�N�g�l��
		uint32_t m_siblingIndex;				// �Z��ԍ�(���g�����Ԗڂ̎q����)
	public:
		// �R���X�g���N�^
		GameObject() noexcept;
		GameObject(const std::string& name) noexcept;
		// �f�X�g���N�^
		virtual ~GameObject() noexcept;

	public:
		// �Q�[���I�u�W�F�N�g�쐬�֐�
		static GameObjectPtr Create(const std::string& name, bool isRegister = true);
		// ����
		static GameObjectPtr Find(const std::string& name);

	private:
		// �e�I�u�W�F�N�g�ݒ�
		void SetParent(GameObjectPtr parent);

		// ���j�I�u�W�F�N�g�ݒ�
		void SetOldestChild(GameObjectPtr oldestChild);

		// �����q�I�u�W�F�N�g�ݒ�
		void SetYoungestChild(GameObjectPtr youngestChild);

		// �Z�I�u�W�F�N�g�ݒ�
		void SetPrevSibling(GameObjectPtr prevSibling);

		// ��I�u�W�F�N�g�ݒ�
		void SetNextSibling(GameObjectPtr nextSibling);

		// �Z��ԍ��ݒ�
		void SetSiblingIndex(uint32_t siblingIndex);

	public:
		// �q�I�u�W�F�N�g�ǉ�
		void AddChild(GameObjectPtr child);

		// �e�I�u�W�F�N�g�擾
		GameObjectPtr GetParent() const;

		// ���j�I�u�W�F�N�g�擾
		GameObjectPtr GetOldestChild() const;

		// ��I�u�W�F�N�g�擾
		GameObjectPtr GetNextSibling() const;

		// �q�I�u�W�F�N�g���擾
		uint32_t GetChildCount() const;

		// �q�I�u�W�F�N�g�擾
		GameObjectPtr GetChildByName(const std::string& name);

		// �q�I�u�W�F�N�g�擾
		GameObjectPtr GetChildByIndex(uint32_t index);

		// �q�I�u�W�F�N�g�擾
		GameObjectPtr GetChild(GameObjectPtr search);

		// �q�I�u�W�F�N�g�������Ă��邩
		bool HasChild(GameObjectPtr search);

		// �q���I�u�W�F�N�g�擾
		GameObjectPtr GetDescendantByName(const std::string& name);
	private:
		// �q���I�u�W�F�N�g�擾�ċA�֐�
		GameObjectPtr GetDescendantRecurse(GameObjectPtr object, const std::string& name) const;

	public:
		// �q�I�u�W�F�N�g�폜
		void RemoveChild(GameObjectPtr child);

		// �q�I�u�W�F�N�g�؂藣��
		void DetachChildren(GameObjectPtr child);

		template<class T>
		inline std::shared_ptr<T> AddComponent();

		// T�^�̃R���|�[�l���g���擾
		template<class T>
		inline uint32_t GetComponentCount() const;


	public:
		// �g�����X�t�H�[���擾
		std::shared_ptr<Transform> GetTransform() const;

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
	private:
		template<class T>
		void GetComponentsInDescendantRecurse(std::vector<std::shared_ptr<T>>& componentList, GameObjectPtr object, SearchPriority priority) const;

	public:
		// �쐬���ɂ�肽������(������)
		void Start();

		// �X�V���ɂ�肽������
		void Update(float deltaTime);

		void FixedUpdate();

		void LateUpdate(float deltaTime);

	};
}

// template�֘A
#include "GameObjectImpl.h"