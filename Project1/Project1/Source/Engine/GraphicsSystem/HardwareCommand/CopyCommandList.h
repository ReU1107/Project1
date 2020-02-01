#pragma once
#include "CommandList.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		// �R�s�[���������ł��Ȃ��N���X
		class CopyCommandList : public CommandList
		{
		private:
			using base = CommandList;
			using CopyCommandListPtr = std::shared_ptr<CopyCommandList>;
		public:
			// �R���X�g���N�^
			CopyCommandList();
			// �f�X�g���N�^
			virtual ~CopyCommandList();

			static CopyCommandListPtr Create(const std::string& name);
		public:
			// ���\�[�X�R�s�[
			virtual void CopyResource(Resource* source, Resource* destination) const override;

		};
	}
}