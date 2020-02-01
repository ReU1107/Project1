#include "AsyncJob.h"

namespace Engine
{
	AsyncJob::AsyncJob()
		: m_condition()
		, m_mutex()
		, m_end(true)
	{
	}
	
	AsyncJob::~AsyncJob()
	{
	}
	
	void AsyncJob::Start()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_end = false;
	}

	void AsyncJob::End()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_end = true;
		WakeUp();
	}
	
	void AsyncJob::Wait()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condition.wait(lock, [this] { return m_end; });
	}

	void AsyncJob::WakeUp()
	{
		// この条件変数で待機しているスレッド全てを起動する
		m_condition.notify_all();
	}
}