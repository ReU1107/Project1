#pragma once
#include <mutex>

namespace Engine
{
	class AsyncJob
	{
	private:
		std::condition_variable m_condition;	// �ʃX���b�h�ҋ@�p�����ϐ�
		std::mutex m_mutex;						// 
		bool m_end;								// �ҋ@�I��

	public:
		// �R���X�g���N�^
		AsyncJob();
		// �f�X�g���N�^
		virtual ~AsyncJob();
		// �����J�n�ʒm
		void Start();
		// �����I���ʒm
		void End();
		// �ҋ@
		void Wait();
		// �ҋ@���̃X���b�h���s
		void WakeUp();

	};
}
