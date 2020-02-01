#pragma once
#include "GraphicsPass.h"
#include <mutex>
#include <string>
#include <unordered_map>
#include "../../Utility/AsyncJob.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class ComputePipeline;
		class Texture;

		// 非同期に行う処理のパス
		class ComputePass : public GraphicsPass, public AsyncJob
		{
		private:
			using base = GraphicsPass;
			using TexturePtr = std::shared_ptr<Texture>;
			static std::unordered_map<std::wstring, ComputePass*> s_allComputePasses;
			static std::mutex s_computePassAccess;
		protected:
			ComputePipeline* m_pipeline;			// パイプライン
			TexturePtr m_resultTexture;

		public:
			// コンストラクタ
			ComputePass();
			// デストラクタ
			virtual ~ComputePass();

			// 登録
			static void Register(const std::wstring& name, ComputePass* pass);

			// コンピュートパス取得
			static ComputePass* Find(const std::wstring& name);

			// パス情報送信
			virtual void OnDispatch() = 0;
		};

	}
}