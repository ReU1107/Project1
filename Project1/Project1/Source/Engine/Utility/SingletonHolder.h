#pragma once
#include <cassert>
namespace Engine 
{
	/*
	保持しているクラスはヒープ領域に
	確保してあるアドレスは静的領域に確保
	*/
	// Baseクラスをシングルトンとして保持
	template<class Base>
	class SingletonHolder final
	{
	private:
		static Base* s_instance;		// インスタンス

	public:
		// コンストラクタ
		SingletonHolder() = delete;
		// デストラクタ
		~SingletonHolder() {};
		// ムーブコンストラクタ
		SingletonHolder(SingletonHolder&&) = delete;
		// コピーコンストラクタ
		SingletonHolder(const SingletonHolder&) = delete;
		// 代入演算子
		SingletonHolder& operator=(const SingletonHolder&) = delete;

	public:
		// システム起動
		static void Startup()
		{
			assert(!s_instance);
			// Baseのコンストラクタ
			s_instance = new Base();
		}

		// システム終了
		static void Shutdown()
		{
			assert(s_instance);
			delete s_instance;
			s_instance = nullptr;
		}
		// インスタンス取得
		static Base* GetPtr() { assert(s_instance); return s_instance; }

		static Base& Get() { assert(s_instance); return *s_instance; }

	};

	template<class Base>
	typename Base* SingletonHolder<Base>::s_instance = nullptr;
}
/*
typenameで
テンプレートのBaseがクラス型であるとコンパイラーに明示的に示している
これがないとBaseが何か分からずエラーになる
*/

// https://mickey24.hatenablog.com/entry/20110103/1294065116