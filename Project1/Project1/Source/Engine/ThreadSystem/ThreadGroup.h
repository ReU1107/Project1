#pragma once
#include <thread>
#include <cstdint>
#include <vector>
#include "../Utility/SingletonHolder.h"
#include <Windows.h>

namespace Engine
{
	namespace ThreadSystem
	{
		struct WorkerThread
		{
			std::thread* thread;	// スレッド
			HANDLE completedHandle; // 完了イベント
		};

		// 全てのワーカースレッドを持ったクラス
		class ThreadGroup
		{
		private:
			using WorkerThreads = std::vector<WorkerThread>;
			using WakeUpHandles = std::vector<HANDLE>;
		private:
			uint32_t m_maxThreadCount;		// スレッド最大作成数
			WakeUpHandles m_wakeUpHandles;	// ハンドル配列
			WorkerThreads m_workerThreads;	// スレッド配列
		public:
			// コンストラクタ
			ThreadGroup();
			// デストラクタ
			~ThreadGroup();
		public:
			// ハンドルをシグナル状態にする
			void SetHandle(int32_t index = -1);

			void WaitAll();
		};

		using SingleThreadGroup = SingletonHolder<ThreadGroup>;
	}
}