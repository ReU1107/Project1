#pragma once
#include <string>
#include <vector>
#include "..///Description/RaytracingPipelineDesc.h"

namespace Engine
{

	namespace GraphicsSystem 
	{

		class IRaytracingPipeline;
		class IShader;
		class ShaderLibrary;
		class RootSignature;
		struct RaytracingPipelineParameterDesc;

		class RaytracingPipeline
		{
			using Parameters = std::vector<RaytracingPipelineParameterDesc>;
		private:
			Parameters m_parameters;
			IRaytracingPipeline* m_interface;
		public:
			// コンストラクタ
			RaytracingPipeline();
			// デストラクタ
			~RaytracingPipeline();

		public:
			// パラメーターデスク追加
			void AddParameterDesc(const RaytracingPipelineParameterDesc& desc);

			// レイトレース最大回数設定
			void SetRaytraceMaxCount(uint32_t maxCount);

			// シェーダー情報設定
			void SetShaderConfig(uint32_t attributeSize, uint32_t payloadSize);

			// 組み合わせ設定
			void AddAssociation(const wchar_t** shaderNames, uint32_t shaderCount, int32_t index = -1);

			// シェーダーライブラリ追加
			void AddShaderLibrary(ShaderLibrary* shaderLibrary);

			// ローカルルートシグネチャ設定
			void AddLocalRootSignature(RootSignature* localRootSignature, const wchar_t** usedShaders, uint32_t shaderCount);
			// グローバルルートシグネチャ設定
			void AddGlobalRootSignature(RootSignature* globalRootSignature);
			
			// ヒットグループ追加
			void AddHitGroup(const wchar_t* groupName, const wchar_t* hitShaderName, const wchar_t* intersectShaderName = nullptr, const wchar_t* anyHitShaderName = nullptr);

			// パイプライン作成
			void Create();

			// シェーダー識別子取得
			void* GetShaderIdentifier(const wchar_t* exportName) const;

			IRaytracingPipeline* GetInterface() const;

			void SetName(const std::wstring& name);
		};

	}

}