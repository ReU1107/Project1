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
			std::thread* thread;	// �X���b�h
			HANDLE completedHandle; // �����C�x���g
		};

		// �S�Ẵ��[�J�[�X���b�h���������N���X
		class ThreadGroup
		{
		private:
			using WorkerThreads = std::vector<WorkerThread>;
			using WakeUpHandles = std::vector<HANDLE>;
		private:
			uint32_t m_maxThreadCount;		// �X���b�h�ő�쐬��
			WakeUpHandles m_wakeUpHandles;	// �n���h���z��
			WorkerThreads m_workerThreads;	// �X���b�h�z��
		public:
			// �R���X�g���N�^
			ThreadGroup();
			// �f�X�g���N�^
			~ThreadGroup();
		public:
			// �n���h�����V�O�i����Ԃɂ���
			void SetHandle(int32_t index = -1);

			void WaitAll();
		};

		using SingleThreadGroup = SingletonHolder<ThreadGroup>;
	}
}