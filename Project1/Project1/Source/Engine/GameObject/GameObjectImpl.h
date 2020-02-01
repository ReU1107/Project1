#pragma once
#include "GameObject.h"
#include "Component/Component.h"

namespace Engine 
{
	template<class T>
	inline std::shared_ptr<T> GameObject::AddComponent()
	{
		std::shared_ptr<T> component = Component::Create<T>();
		component->SetOwner(shared_from_this());

		// ä˘Ç…ìoò^çœÇ›
		typename std::vector<std::shared_ptr<Component>>* vector = GetComponents<T>();
		if (vector) 
		{
			vector->push_back(component);
			return component;
		}
		typename std::vector<std::shared_ptr<Component>> components;
		components.push_back(component);

		m_components.insert({ T::ID(),std::move(components) });

		return component;
	}

	template<class T>
	inline uint32_t GameObject::GetComponentCount() const
	{
		auto it = m_components.find(T::ID());
		if (it != m_components.cend()) 
		{
			return (*it).second.size();
		}
		return 0;
	}

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponent(uint32_t index)
	{
		auto it = m_components.find(T::ID());

		if (it == m_components.cend())
		{
			return nullptr;
		}
		auto vector = &(*it).second;
		assert(vector);
		assert(!(index > vector->size()));
		// å^ämîF
		if (vector->at(index)->GetInstanceID() == T::ID()) 
		{
			return std::dynamic_pointer_cast<T>(vector->at(index));
		}
		return nullptr;
	}

	template<class T>
	inline std::vector<std::shared_ptr<Component>>* GameObject::GetComponents()
	{
		auto it = m_components.find(T::ID());

		if (it != m_components.cend()) 
		{
			if ((*it).second.front()->GetInstanceID() == T::ID()) 
			{
				return &(*it).second;
			}
		}
		return nullptr;
	}

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponentInParent()
	{
		if (m_parent)
			return m_parent->GetComponent<T>();

		return nullptr;
	}

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponentInChildren()
	{
		GameObjectPtr child = m_oldestChild;
		for (uint32_t i = 0; i < m_childCount; ++i) 
		{
			auto component = child->GetComponent<T>();
			if (component) 
			{
				return component;
			}
			child = child->GetNextSibling();
		}
		return nullptr;
	}

	template<class T>
	inline std::vector<std::shared_ptr<T>> GameObject::GetComponentsInChildren()
	{
		std::vector<std::shared_ptr<T>> componentList;
		GameObjectPtr child = m_oldestChild;
		for (uint32_t i = 0; i < m_childCount; ++i) 
		{
			auto component = child->GetComponent<T>();
			if (component) 
			{
				componentList.push_back(component);
			}
			child = child->GetNextSibling();
		}
		return std::move(componentList);
	}

	template<class T>
	inline std::vector<std::shared_ptr<T>> GameObject::GetComponentsInDescendant(SearchPriority priority) const
	{
		std::vector<std::shared_ptr<T>> componentList;
		GetComponentsInDescendantRecurse(componentList, shared_from_this(), priority);

		return std::move(componentList);
	}

	template<class T>
	inline void GameObject::GetComponentsInDescendantRecurse(std::vector<std::shared_ptr<T>>& componentList, GameObjectPtr object, SearchPriority priority) const
	{
		if (!object)
		{
			return;
		}
		auto component = object->GetComponent<T>();
		if (component) 
		{
			componentList.push_back(component);
		}
		// 
		if (priority == SearchPriority::DepthFirst) 
		{
			GetComponentsInDescendantRecurse(componentList, m_oldestChild, priority);

			GetComponentsInDescendantRecurse(componentList, m_nextSibling, priority);
		}
		else if (priority == SearchPriority::BreadthFirst)
		{
			GetComponentsInDescendantRecurse(componentList, m_nextSibling, priority);

			GetComponentsInDescendantRecurse(componentList, m_oldestChild, priority);
		}
	}

}