#pragma once
#include <chrono>

namespace Engine
{

	class Timer
	{
	private:
		enum class State
		{
			Stop,		// �ҋ@
			Ready,		// ����
			Run			// 
		};
	private:
		using milli = std::chrono::milliseconds;
		using systemTimePoint = std::chrono::system_clock::time_point;
		State m_state;					// ���
		systemTimePoint m_startTime;	// �J�n����(�J�n�T���v��)

		milli m_elapsedTime;			// �o�ߎ���
	public:
		// �R���X�g���N�^
		Timer();
		// �f�X�g���N�^
		~Timer();
	public:
		static Timer s_globalClock;		// �O���[�o�����Ԍv���@

	public:
		// �J�n
		void Start();

		// ���Z�b�g
		void Reset();

		// ��~
		void Stop();

		// �o�ߎ��Ԏ擾
		milli GetElapsedTime();
	};
}