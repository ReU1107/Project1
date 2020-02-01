#pragma once
#include <cstdint>

namespace Engine 
{

	/*
	Component Object Model 用
	マイクロソフト側で用意されている
	長ったらしい名前空間に入っています
	*/

	template<class Interface>
	class ComponentPtr
	{
	private:
		Interface* m_ptr;		// ポインタ
		uint64_t m_refCount;	// 参照カウント
	public:
		ComponentPtr();
		~ComponentPtr();

	public:
		uint64_t AddRef();

		uint64_t Release();

	};

}