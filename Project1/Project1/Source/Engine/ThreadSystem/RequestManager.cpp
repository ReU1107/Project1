#include "RequestManager.h"
#include "Request.h"
#include "ThreadGroup.h"

namespace Engine
{
	namespace ThreadSystem
	{
		RequestManager::RequestManager()
			: m_requests()
			, m_mutex()
		{
		}

		RequestManager::~RequestManager()
		{
			for (; m_requests.size();) {
				m_requests.pop();
			}
		}

		void RequestManager::PushRequest(const std::function<void()>& function)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			Request* request = nullptr;
			if (!m_recycles.empty())
			{
				request = m_recycles.back();
				m_recycles.pop_back();
				request->SetFunction(function);
			}
			else
			{
				request = new Request(function);
			}
			m_requests.push(request);
			CallThreadGroup();
		}

		Request* RequestManager::PopRequest()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_requests.empty())
				return nullptr;
			Request* request = m_requests.front();
			m_recycles.push_back(request);
			m_requests.pop();
			return request;
		}

		void RequestManager::CallThreadGroup()
		{
			SingleThreadGroup::GetPtr()->SetHandle();
		}

	}

}