#pragma once
#include <type_traits>

/*
�r�b�g���Z���s���K�v������
�񋓌^�̑O�ŃC���N���[�h���Ă�������
*/

/*
enum class
�̃I�y���[�^�[���Z���ȒP�ɂ��邽��
underlying_type���񋓌^�̊�{�^��Ԃ��Ă����
*/

// �񋓂���{�^�ɃL���X�g
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
