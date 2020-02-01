#include "Timer.h"
using namespace std::chrono;
namespace Engine
{
	Timer Timer::s_globalClock;

	Timer::Timer()
		: m_state(State::Ready)
		, m_elapsedTime()
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::Start()
	{
		if (m_state == State::Ready) {
			Reset();
			m_state = State::Run;
		}
	}

	void Timer::Reset()
	{
		m_elapsedTime = milli(0);
		m_startTime = system_clock::now();
		m_state = State::Ready;
	}

	void Timer::Stop()
	{
		if (m_state == State::Run) {
			m_state = State::Stop;
			m_elapsedTime = duration_cast<milli>(system_clock::now() - m_startTime);
		}
	}

	Timer::milli Timer::GetElapsedTime()
	{
		return duration_cast<milli>(system_clock::now() - m_startTime);
	}
}