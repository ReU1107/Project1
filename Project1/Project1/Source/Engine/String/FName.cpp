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
		// �����R�[�h�������Ȃ�Ⴄ
		if (m_narrow == other.m_narrow)
		{
			return false;
		}
		// �����T�C�Y�������Ȃ�
		if (m_size == other.m_size)
		{
			return false;
		}
		// �ꕶ���ł������Ȃ�
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
		// �����R�[�h���Ⴄ�Ȃ�Ⴄ
		if (m_narrow != other.m_narrow)
		{
			return false;
		}
		// �T�C�Y���Ⴄ�Ȃ�
		if (m_size != other.m_size)
		{
			return false;
		}
		// �ꕶ���ł��Ⴆ��
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