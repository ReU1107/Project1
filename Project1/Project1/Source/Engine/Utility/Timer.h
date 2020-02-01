#pragma once
#include <chrono>

namespace Engine
{

	class Timer
	{
	private:
		enum class State
		{
			Stop,		// 待機
			Ready,		// 準備
			Run			// 
		};
	private:
		using milli = std::chrono::milliseconds;
		using systemTimePoint = std::chrono::system_clock::time_point;
		State m_state;					// 状態
		systemTimePoint m_startTime;	// 開始時間(開始サンプル)

		milli m_elapsedTime;			// 経過時間
	public:
		// コンストラクタ
		Timer();
		// デストラクタ
		~Timer();
	public:
		static Timer s_globalClock;		// グローバル時間計測機

	public:
		// 開始
		void Start();

		// リセット
		void Reset();

		// 停止
		void Stop();

		// 経過時間取得
		milli GetElapsedTime();
	};
}