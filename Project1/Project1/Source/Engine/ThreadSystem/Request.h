#pragma once
#include <functional>
namespace Engine
{
	namespace ThreadSystem
	{
		// �d�����e(�񓯊��ł�)�ʖ�AsyncJob
		class Request
		{
		private:
			using Work = std::function<void()>;
		private:
			Work m_work;
		public:
			// �R���X�g���N�^
			Request();
			Request(const std::function<void()>& func);

			// �f�X�g���N�^
			~Request();
		public:
			//
			void SetFunction(const std::function<void()>& func);
			// ���s
			void Excute();
		};
	}
}