#pragma once
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <string>
#include <cassert>
#include "../Object.h"
#include <Windows.h>

namespace Engine
{
	template<class T>
	class AccessObject : public Object
	{
	private:
		using base = Object;
	protected:
		static std::unordered_map<std::string, std::shared_ptr<T>> s_allObjects;
		static std::mutex s_access;

	public:
		// 検索
		template<class U = T>
		static std::shared_ptr<U> Find(const std::string& name);

		// 作成関数
		template<class U = T>
		static std::shared_ptr<U> Create(const std::string& name);

		// 登録
		template<class U = T>
		static void Register(const std::string& name, std::shared_ptr<U> object);

		// 登録解除
		static void Unregister(const std::string& name);

		// 削除
		static void Clear();
	public:
		// コンストラクタ
		AccessObject<T>(const std::string& name);
		// デストラクタ
		virtual ~AccessObject<T>();

	};

	template<class T>
	typename std::unordered_map<std::string, std::shared_ptr<T>> AccessObject<T>::s_allObjects;
	template<class T>
	typename std::mutex AccessObject<T>::s_access;

	template<class T>
	template<class U>
	inline std::shared_ptr<U> AccessObject<T>::Find(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(s_access);
		const auto& it = s_allObjects.find(name);
		if (it == s_allObjects.cend())
		{
			return nullptr;
		}

		return std::dynamic_pointer_cast<U>((*it).second);
	}

	template<class T>
	template<class U>
	inline std::shared_ptr<U> AccessObject<T>::Create(const std::string& name)
	{
		auto object = std::make_shared<U>(name);
		Register<U>(name, object);

		return object;
	}

	template<class T>
	template<class U>
	inline void AccessObject<T>::Register(const std::string& name, std::shared_ptr<U> object)
	{
		std::lock_guard<std::mutex> lock(s_access);
		const auto& it = s_allObjects.find(name);
		if (it != s_allObjects.cend())
		{
			char str[MAX_PATH];
			sprintf_s(str, "アクセスオブジェクトの名前が被っています\n%s", name.c_str());
			MessageBox(nullptr, str, "エラー", MB_OK);
			assert(!"アクセスオブジェクトの名前が被っています");
		}
		s_allObjects.insert({ name,object });

	}

	template<class T>
	inline void AccessObject<T>::Unregister(const std::string& name)
	{
		//s_allObjects.erase(name);
	}

	template<class T>
	inline void AccessObject<T>::Clear()
	{
		std::lock_guard<std::mutex> lock(s_access);
		s_allObjects.clear();
	}

	template<class T>
	inline AccessObject<T>::AccessObject(const std::string& name)
		: base(name)
	{
	}

	template<class T>
	inline AccessObject<T>::~AccessObject()
	{
		Unregister(GetName());
	}
}