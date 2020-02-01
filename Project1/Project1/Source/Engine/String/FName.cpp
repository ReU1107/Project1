#include "FName.h"
namespace Engine
{
	FName::FName(const std::string& name)
		: m_name()
		, m_size(0)
		, m_nameHash(0)
		, m_narrow(true)
	{
		m_size = name.size();
		m_name.narrowString = new char[m_size];
		for (uint32_t i = 0; i < m_size; ++i)
		{
			m_name.narrowString[i] = name.at(i);
		}
	}

	FName::FName(const std::wstring& name)
		: m_name()
		, m_size(0)
		, m_nameHash(0)
		, m_narrow(false)
	{
		m_size = name.size();
		m_name.wideString = new wchar_t[m_size];
		for (uint32_t i = 0; i < m_size; ++i)
		{
			m_name.wideString[i] = name.at(i);
		}
	}

	FName::~FName()
	{
		delete m_name.wideString;
	}
	
	bool FName::operator!=(const FName& other)
	{
		// 文字コードが同じなら違う
		if (m_narrow == other.m_narrow)
		{
			return false;
		}
		// 文字サイズが同じなら
		if (m_size == other.m_size)
		{
			return false;
		}
		// 一文字でも同じなら
		if (m_narrow)
		{
			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_name.narrowString[i] == other.m_name.narrowString[i])
				{
					return false;
				}
			}
		}
		else
		{
			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_name.wideString[i] == other.m_name.wideString[i])
				{
					return false;
				}
			}
		}

		return true;
	}

	bool FName::operator==(const FName& other)
	{
		// 文字コードが違うなら違う
		if (m_narrow != other.m_narrow)
		{
			return false;
		}
		// サイズが違うなら
		if (m_size != other.m_size)
		{
			return false;
		}
		// 一文字でも違えば
		if (m_narrow)
		{
			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_name.narrowString[i] != other.m_name.narrowString[i])
				{
					return false;
				}
			}
		}
		else
		{
			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_name.wideString[i] != other.m_name.wideString[i])
				{
					return false;
				}
			}
		}
		return true;
	}
}