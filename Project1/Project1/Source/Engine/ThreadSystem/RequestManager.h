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
			Requests m_requests;	// �֐����N�G�X�g�z��
			Recycles m_recycles;	// �g���܂킵�悤
		public:
			// �R���X�g���N�^
			RequestManager();
			// �f�X�g���N�^
			~RequestManager();

		public:
			// �ʃX���b�h�ōs�������֐��ݒ�
			void PushRequest(const std::function<void()>& function);

			// �ʃX���b�h�ł�肽���֐��ݒ�(�N���X�֐�)
			template<class T>
			void PushRequest(T* object, void(T::* callFunction)());

			// ���N�G�X�g�擾
			Request* PopRequest();

		private:
			// �w�b�_�[�ł̃C���N���[�h�h�~
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