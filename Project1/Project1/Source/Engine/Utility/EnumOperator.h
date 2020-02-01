#pragma once
#include <type_traits>

/*
ビット演算を行う必要がある
列挙型の前でインクルードしてください
*/

/*
enum class
のオペレーター演算を簡単にするため
underlying_typeが列挙型の基本型を返してくれる
*/

// 列挙を基本型にキャスト
template<class T>
inline std::underlying_type_t<T> CovertToBaseType(T e)
{
	return static_cast<std::underlying_type_t<T>>(e);
}
// 
template<class T>
inline T operator |(T l, T r)
{
	return static_cast<T>(CovertToBaseType(l) | CovertToBaseType(r));
}
// 
template<class T>
inline T operator ^(T l, T r)
{
	return static_cast<T>(CovertToBaseType(l) ^ CovertToBaseType(r));
}

template<class T>
inline bool operator &(T l, T r)
{
	return CovertToBaseType(l) & CovertToBaseType(r);
}

template<class T>
inline T operator |=(T& l, T r)
{
	l = l | r;
	return l;
}

template<class T>
inline T operator ^=(T& l, T r)
{
	l = l ^ r;
	return l;
}
