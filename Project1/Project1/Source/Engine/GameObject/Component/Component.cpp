#include "Component.h"
#include "../GameObject.h"

namespace Engine 
{

	Component::Component(const std::string& name) noexcept
		: base(name)
		, m_owner(nullptr)
	{
		//m_owner->AddRef();
	}

	Component::~Component() noexcept
	{
		//m_owner->Release();
	}

	void Component::SetOwner(GameObjectPtr owner)
	{
		m_owner = owner;
	}

	Component::GameObjectPtr Component::GetOwner() const
	{
		return m_owner;
	}

	Component::GameObjectPtr Component::GetParent() const
	{
		return m_owner->GetParent();
	}

	Component::GameObjectPtr Component::GetOldestChild() const
	{
		return m_owner->GetOldestChild();
	}

	Component::GameObjectPtr Component::GetNextSibling() const
	{
		return m_owner->GetNextSibling();
	}

	std::shared_ptr<Transform> Component::GetTransform() const
	{
		return m_owner->GetTransform();
	}

}