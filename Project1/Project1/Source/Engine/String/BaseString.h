#pragma once
#include <cstring>
#include <cstdint>

/*
operator+=�I�[�o�[���C�h�֐���
������킩��Ǝv����
���x�� String a;
	a+= "aiueo"�̂悤�ɂ��Ȃ��ł����Ɗ������ł�
���R:
�ǉ����̍Œ���̃����������m�ۂ��Ȃ���
*/

namespace Engine
{
	template<class T>
	class BaseString
	{
	private:
		T* m_string;			// ������̃|�C���^
		uint32_t m_capacity;	// �m�ۂ����������̈�
		uint32_t m_length;		// ������̒���

	public:
		BaseString(uint32_t capacity = 8)
			: m_string(nullptr)
			, m_capacity(capacity)
			, m_length(0)
		{
		}

		~BaseString()
		{
			delete[] m_string;
		}

		bool operator==(const BaseString<T>& other);

		bool operator!=(const BaseString<T>& other);

		struct Hash;

		BaseString<T>& operator +=(const T* other);

		BaseString<T>& operator +=(const BaseString<T>& other);

		// �œK��(�m�ە��̃T�C�Y�ł��g���Ă��Ȃ�����(0�̕���)�͂Ȃ����̂Ƃ��Ĉ���)
		void Optemaize();

		uint32_t GetLength() const { return m_length; }

	};

	template<class T>
	struct BaseString<T>::Hash
	{
		std::size_t operator()(const BaseString<T> key) const;
	};

	template<class T>
	inline std::size_t BaseString<T>::Hash::operator()(const BaseString<T> key) const
	{
		return std::hash<T>()(key.m_string);
	}

	using String = BaseString<char>;
	using WString = BaseString<wchar_t>;
	using U16String = BaseString<char16_t>;
	using U32String = BaseString<char32_t>;

}

#include "BaseStringImpl.h"