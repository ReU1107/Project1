#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class IComputePipeline;
		class Shader;
		class RootSignature;

		class ComputePipeline
		{
		private:
			IComputePipeline* m_interface;
			RootSignature* m_rootSignature;	// ルートシグネチャ
			Shader* m_computeShader;		// コンピュートシェーダー
		public:
			// コンストラクタ
			ComputePipeline();
			// デストラクタ
			~ComputePipeline();

			// ルートシグネチャ設定
			void SetRootSignature(RootSignature* rootSignature);

			// コンピュートシェーダー設定
			void SetComputeShader(Shader* shader);

			void Create();

			// インターフェイス取得
			IComputePipeline* GetInterface() const;

			// ルートシグネチャ取得
			RootSignature* GetRootSignature() const;

		};
	}
}