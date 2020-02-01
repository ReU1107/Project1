#pragma once
#include "../GameObject.h"
#include "Component.h"

namespace Engine
{
	template<class T>
	inline std::shared_ptr<T> Component::Create()
	{
		auto component = std::make_shared<T>();
		return component;
	}

	template<class T>
	inline std::shared_ptr<T> Component::AddComponent()
	{
		return m_owner->AddComponent<T>();
	}

	template<class T>
	inline uint32_t Component::GetComponentCount() const
	{
		return m_owner->GetComponentCount();
	}

	template<class T>
	inline std::shared_ptr<T> Component::GetComponent(uint32_t index)
	{
		return m_owner->GetComponent<T>();
	}

	template<class T>
	inline std::vector<std::shared_ptr<Component>>* Component::GetComponents()
	{
		return m_owner->GetComponents<T>();
	}

	template<class T>
	inline std::shared_ptr<T> Component::GetComponentInParent()
	{
		return m_owner->GetComponentInParent<T>();
	}

	template<class T>
	inline std::shared_ptr<T> Component::GetComponentInChildren()
	{
		return m_owner->GetComponentInChildren<T>();
	}

	template<class T>
	inline std::vector<std::shared_ptr<T>> Component::GetComponentsInChildren()
	{
		return m_owner->GetComponentsInChildren<T>();
	}

	template<class T>
	inline std::vector<std::shared_ptr<T>> Component::GetComponentsInDescendant(SearchPriority priority) const
	{
		return m_owner->GetComponentsInDescendant<T>(priority);
	}

}
