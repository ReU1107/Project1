#pragma once
#include <queue>
#include <mutex>
#include "../Utility/SingletonHolder.h"
#include "Request.h"

namespace Engine
{
	namespace ThreadSystem
	{
		class Request;

		class RequestManager
		{
		private:
			using Requests = std::queue<Request*>;
			using Recycles = std::vector<Request*>;
		private:
			std::mutex m_mutex;
			Requests m_requests;	// 関数リクエスト配列
			Recycles m_recycles;	// 使いまわしよう
		public:
			// コンストラクタ
			RequestManager();
			// デストラクタ
			~RequestManager();

		public:
			// 別スレッドで行いたい関数設定
			void PushRequest(const std::function<void()>& function);

			// 別スレッドでやりたい関数設定(クラス関数)
			template<class T>
			void PushRequest(T* object, void(T::* callFunction)());

			// リクエスト取得
			Request* PopRequest();

		private:
			// ヘッダーでのインクルード防止
			void CallThreadGroup();
		};

		template<class T>
		inline void RequestManager::PushRequest(T* object, void(T::* callFunction)())
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			Request* request = nullptr;
			if (!m_recycles.empty())
			{
				request = m_recycles.back();
				m_recycles.pop_back();
				request->SetFunction(std::bind(callFunction, object));
			}
			else
			{
				request = new Request(std::bind(callFunction, object));
			}
			m_requests.push(request);
			CallThreadGroup();
		}

		using SingleRequestManager = SingletonHolder<RequestManager>;
	}
}