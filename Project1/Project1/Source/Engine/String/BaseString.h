#pragma once
#include <cstring>
#include <cstdint>

/*
operator+=オーバーライド関数を
見たらわかると思うが
何度も String a;
	a+= "aiueo"のようにしないでくれると嬉しいです
理由:
追加分の最低限のメモリしか確保しない為
*/

namespace Engine
{
	template<class T>
	class BaseString
	{
	private:
		T* m_string;			// 文字列のポインタ
		uint32_t m_capacity;	// 確保したメモリ領域
		uint32_t m_length;		// 文字列の長さ

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

		// 最適化(確保分のサイズでも使っていない部分(0の部分)はないものとして扱う)
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