#pragma once
#include "BaseString.h"

namespace Engine
{
	template<class T>
	bool BaseString<T>::operator==(const BaseString<T>& other)
	{
		if (m_length != other.m_length)
		{
			return false;
		}

		for (uint32_t i = 0; i < m_length; ++i)
		{
			auto& lhs = m_string[i];
			auto& rhs = other.m_string[i];
			if (lhs != rhs)
			{
				return false;
			}

		}

		return true;
	}

	template<class T>
	inline bool BaseString<T>::operator!=(const BaseString<T>& other)
	{
		if (m_length == other.m_length)
		{
			return false;
		}

		for (uint32_t i = 0; i < m_length; ++i)
		{
			auto& lhs = m_string[i];
			auto& rhs = other.m_string[i];
			if (lhs == rhs)
			{
				return false;
			}

		}

		return true;
	}

	template<class T>
	inline BaseString<T>& BaseString<T>::operator+=(const T* string)
	{
		// �ǉ����悤�Ƃ��Ă��镶����̒���
		size_t length = strnlen_s(string, 256);
		uint32_t tmp = m_length + length;
		// ���݂ƒǉ����̕����̒������m�ە��𒴂�����V�����o�b�t�@���m�ۂ���
		if (tmp >= m_capacity)
		{
			m_capacity = tmp + 1;
			T* str = new T[m_capacity];
			// �V�����o�b�t�@�ɃR�s�[����
			for (size_t i = 0; i < m_length; ++i)
			{
				str[i] = m_string[i];
			}

			delete[] m_string;
			m_string = str;
		}
		// 
		for (uint32_t i = m_length; i < tmp; ++i)
		{
			m_string[i] = string[i];
		}
		m_length = tmp;

		return *this;
	}

	template<class T>
	inline BaseString<T>& BaseString<T>::operator+=(const BaseString<T>& other)
	{
		// �ǉ����悤�Ƃ��Ă��镶����̒���
		size_t length = other.m_length;
		uint32_t tmp = m_length + length;
		// ���݂ƒǉ����̕����̒������m�ە��𒴂�����V�����o�b�t�@���m�ۂ���
		if (tmp >= m_capacity)
		{
			m_capacity = tmp + 1;
			T* str = new T[m_capacity];
			// �V�����o�b�t�@�ɃR�s�[����
			for (size_t i = 0; i < m_length; ++i)
			{
				str[i] = m_string[i];
			}

			delete[] m_string;
			m_string = str;
		}
		// 
		for (uint32_t i = m_length; i < tmp; ++i)
		{
			m_string[i] = other.m_string[i];
		}
		m_length = tmp;

		return *this;
	}

	template<class T>
	inline void BaseString<T>::Optemaize()
	{
		for (uint32_t i = 0; i < m_length; ++i)
		{
			if (m_string[i] == 0)
			{
				m_length = i;
				break;
			}

		}
	}

}