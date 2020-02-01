#pragma once
#include "CommandList.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		// コピー処理しかできないクラス
		class CopyCommandList : public CommandList
		{
		private:
			using base = CommandList;
			using CopyCommandListPtr = std::shared_ptr<CopyCommandList>;
		public:
			// コンストラクタ
			CopyCommandList();
			// デストラクタ
			virtual ~CopyCommandList();

			static CopyCommandListPtr Create(const std::string& name);
		public:
			// リソースコピー
			virtual void CopyResource(Resource* source, Resource* destination) const override;

		};
	}
}