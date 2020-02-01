#pragma once
#include "../Object.h"

namespace Engine
{
	template<class T>
	class SingletonObject
	{
	private:
		static T* s_instance;
	public:
		// �R���X�g���N�^
		SingletonObject()
		{
			assert(!s_instance);
			s_instance = static_cast<T*>(this);
		}
		// �f�X�g���N�^
		virtual ~SingletonObject()
		{
			assert(s_instance);
			s_instance = nullptr;
		};
	private:
		SingletonObject(const SingletonObject<T>&) = delete;
		SingletonObject(SingletonObject<T>&&) = delete;
		SingletonObject& operator = (const SingletonObject<T>&) = delete;

	public:

		static T* GetPtr()
		{
			return s_instance;
		}

		static T& Get()
		{
			return *s_instance;
		}

	};

	template<class T>
	typename T* SingletonObject<T>::s_instance = nullptr;
}