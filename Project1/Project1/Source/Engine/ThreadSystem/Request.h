#pragma once
#include <functional>
namespace Engine
{
	namespace ThreadSystem
	{
		// 仕事内容(非同期での)別名AsyncJob
		class Request
		{
		private:
			using Work = std::function<void()>;
		private:
			Work m_work;
		public:
			// コンストラクタ
			Request();
			Request(const std::function<void()>& func);

			// デストラクタ
			~Request();
		public:
			//
			void SetFunction(const std::function<void()>& func);
			// 実行
			void Excute();
		};
	}
}