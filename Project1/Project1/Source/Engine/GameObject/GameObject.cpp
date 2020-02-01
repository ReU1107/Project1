#include "GameObject.h"
#include "Component/Transform.h"
#include "Component/Behaviour/Camera.h"
#include "Component/Behaviour/MonoBehaviour.h"
#include "Component/Renderer/Renderer.h"

namespace Engine
{
	std::unordered_map<std::string, GameObject::GameObjectPtr> GameObject::allObjects;

	GameObject::GameObject() noexcept
		: base("")
		, m_components()
		, m_transform()
		, m_root(nullptr)
		, m_parent(nullptr)
		, m_oldestChild(nullptr)
		, m_youngestChild(nullptr)
		, m_prevSibling(nullptr)
		, m_nextSibling(nullptr)
		, m_childCount(0)
		, m_siblingIndex(0)
	{
	}

	GameObject::GameObject(const std::string& name) noexcept
		: base(name)
		, m_components()
		, m_transform()
		, m_root(nullptr)
		, m_parent(nullptr)
		, m_oldestChild(nullptr)
		, m_youngestChild(nullptr)
		, m_prevSibling(nullptr)
		, m_nextSibling(nullptr)
		, m_childCount(0)
		, m_siblingIndex(0)
	{
	}

	GameObject::~GameObject() noexcept
	{
	}

	GameObject::GameObjectPtr GameObject::Create(const std::string& name, bool isRegister)
	{
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name);
		gameObject->m_transform = gameObject->AddComponent<Transform>();
		if (isRegister)
		{
			allObjects.insert({ name,gameObject });
		}
		return gameObject;
	}

	GameObject::GameObjectPtr GameObject::Find(const std::string& name)
	{
		const auto& it = allObjects.find(name);

		if (it == allObjects.cend())
		{
			return nullptr;
		}

		return (*it).second;
	}

	void GameObject::SetParent(GameObjectPtr parent)
	{
		m_parent = parent;
	}

	void GameObject::SetOldestChild(GameObjectPtr oldestChild)
	{
		m_oldestChild = oldestChild;
	}

	void GameObject::SetYoungestChild(GameObjectPtr youngestChild)
	{
		m_youngestChild = youngestChild;
	}

	void GameObject::SetPrevSibling(GameObjectPtr prevSibling)
	{
		m_prevSibling = prevSibling;
	}

	void GameObject::SetNextSibling(GameObjectPtr nextSibling)
	{
		m_nextSibling = nextSibling;
	}

	void GameObject::SetSiblingIndex(uint32_t siblingIndex)
	{
		m_siblingIndex = siblingIndex;
	}

	void GameObject::AddChild(GameObjectPtr child)
	{
		child->SetParent(shared_from_this());
		child->SetPrevSibling(this->m_youngestChild);

		if (m_youngestChild)
		{
			// 今現在の末子の弟設定
			m_youngestChild->SetNextSibling(child);
		}
		else
		{
			// 最後の子供がいない ≒ 子供が1人もいない
			this->SetOldestChild(child);
		}
		// 末子を更新
		this->SetYoungestChild(child);
		child->SetSiblingIndex(m_childCount++);
	}

	GameObject::GameObjectPtr GameObject::GetParent() const
	{
		return m_parent;
	}

	GameObject::GameObjectPtr GameObject::GetOldestChild() const
	{
		return m_oldestChild;
	}

	GameObject::GameObjectPtr GameObject::GetNextSibling() const
	{
		return m_nextSibling;
	}

	uint32_t GameObject::GetChildCount() const
	{
		return m_childCount;
	}

	GameObject::GameObjectPtr GameObject::GetChildByName(const std::string& name)
	{
		auto child = m_oldestChild;
		while (child)
		{
			if (child->GetName() == name)
			{
				return child;
			}
			child = child->m_nextSibling;
		}
		return nullptr;
	}

	GameObject::GameObjectPtr GameObject::GetChildByIndex(uint32_t index)
	{
		assert(!(index > m_childCount));
		auto child = m_oldestChild;
		for (uint32_t i = 0; i < index; ++i)
		{
			child = child->m_nextSibling;
		}
		return child;
	}

	GameObject::GameObjectPtr GameObject::GetChild(GameObjectPtr search)
	{
		auto child = m_oldestChild;
		while (child)
		{
			if (child == search)
			{
				return child;
			}
			child = child->m_nextSibling;
		}
		return nullptr;
	}

	bool GameObject::HasChild(GameObjectPtr search)
	{
		auto child = m_oldestChild;
		while (child)
		{
			if (child == search)
			{
				return true;
			}
			child = child->m_nextSibling;
		}
		return false;
	}

	GameObject::GameObjectPtr GameObject::GetDescendantByName(const std::string& name)
	{
		return GetDescendantRecurse(m_oldestChild, name);
	}

	GameObject::GameObjectPtr GameObject::GetDescendantRecurse(GameObjectPtr object, const std::string& name) const
	{
		auto gameObject = object;
		if (!gameObject)
		{
			return nullptr;
		}
		if (gameObject->GetName().c_str() == name)
		{
			return gameObject;
		}
		if (!object)
		{
			object = GetDescendantRecurse(gameObject->m_oldestChild, name);
		}
		if (!object)
		{
			object = GetDescendantRecurse(gameObject->m_nextSibling, name);
		}
		return object;
	}

	void GameObject::RemoveChild(GameObjectPtr child)
	{
		// 見つからなかった
		if (!HasChild(child)) 
		{
			return;
		}
		// 兄に弟を
		child->m_prevSibling->SetNextSibling(child->m_nextSibling);
		// 弟に兄をつける
		child->m_nextSibling->SetPrevSibling(child->m_prevSibling);
	}

	void GameObject::DetachChildren(GameObjectPtr child)
	{
		auto search = m_oldestChild;
		while (search)
		{
			if (search == child) 
			{

			}
			search = search->m_nextSibling;
		}
	}

	std::shared_ptr<Transform> GameObject::GetTransform() const
	{
		return m_transform.lock();
	}
	
	void GameObject::Start()
	{
		auto monoBehaviours = GetComponents<MonoBehaviour>();
		if (!monoBehaviours)
			return;
		for (auto& monoBehaviour : *monoBehaviours)
		{
			std::dynamic_pointer_cast<MonoBehaviour>(monoBehaviour)->OnStart();
		}
	}

	void GameObject::Update(float deltaTime)
	{
		auto monoBehaviours = GetComponents<MonoBehaviour>();
		if (!monoBehaviours)
			return;
		for (auto& monoBehaviour : *monoBehaviours)
		{
			std::dynamic_pointer_cast<MonoBehaviour>(monoBehaviour)->OnUpdate(deltaTime);
		}
	}

	void GameObject::LateUpdate(float deltaTime)
	{
		auto monoBehaviours = GetComponents<MonoBehaviour>();
		if (!monoBehaviours)
			return;
		for (auto& monoBehaviour : *monoBehaviours)
		{
			std::dynamic_pointer_cast<MonoBehaviour>(monoBehaviour)->OnLateUpdate(deltaTime);
		}
	}
}