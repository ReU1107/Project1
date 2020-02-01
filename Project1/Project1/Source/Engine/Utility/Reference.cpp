#include "Reference.h"

namespace Engine 
{
	Reference::Reference() noexcept
		: m_refCount(1)
	{
	}

	uint32_t Reference::AddRef()
	{
		return ++m_refCount;
	}

	uint32_t Reference::Release()
	{
		m_refCount--;
		if (m_refCount <= 0)
		{
			delete this;
			return 0;
		}
		return m_refCount;
	}
}