#include "Object.h"
#include <functional>

namespace Engine
{
	Object::Object(const std::string& name) noexcept
		: m_name(name)
		, m_nameHash(std::hash<std::string>{}(name))
	{
	}

	Object::~Object() noexcept
	{
		m_name.clear();
	}

	bool Object::operator!=(const Object* other) const
	{
		return this != other;
	}

	bool Object::operator==(const Object* other) const
	{
		return this == other;
	}

	void Object::SetName(const std::string& name)
	{
		m_name = name;
	}

	const std::string& Object::GetName() const
	{
		return m_name;
	}

	uint32_t Object::GetNameHash() const
	{
		return m_nameHash;
	}

	void* Object::GetPropertyAddress(const std::string& name)
	{
		if (name == "nameHash")
		{
			return &m_nameHash;
		}

		return nullptr;
	}

}