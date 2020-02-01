#pragma once
#include "ComputePass.h"
#include <vector>
#include <iostream>

namespace Engine
{
	namespace SceneManagement
	{
		class Scene;
	}

	namespace GraphicsSystem
	{
		class RenderTexture;
		class RaytracingPipeline;
		class RaytracingMesh;
		class RaytracingSubMesh;
		class RootSignature;
		class ShaderTable;
		class ShaderRecord;
		class CommandList;
		class GraphicsCommandList;
		class TopLevelAccelerationStructure;
		struct SubTopLevelAccelerationStructureDesc;

		struct ShaderTables
		{
			union
			{
				struct
				{
					ShaderTable* rayGenerateTable;	// レイ生成用テーブル
					ShaderTable* hitGroupTable;		// ヒットグループテーブル
					ShaderTable* missTable;			// ミステーブル
				}each;
				struct
				{
					ShaderTable* table;				// 共有テーブル
					uint64_t hitGroupCount;			// ヒットグループの数
					uint64_t missCount;				// ミスの数
				}share;
			};
			bool isShare;
			ShaderTables()
				: each()
				, isShare(false)
			{
			}
		};

		// レイトレーシングの処理を行う
		class RaytracingPass : public ComputePass
		{
		private:
			using base = ComputePass;
			using TopLevelASPtr = std::shared_ptr<TopLevelAccelerationStructure>;
			using RenderTextures = std::vector<RenderTexture*>;
			using RootSignatures = std::vector<RootSignature*>;
			using ShaderRecords = std::vector<ShaderRecord*>;
			using SubDescs = std::vector<SubTopLevelAccelerationStructureDesc>;

		protected:
			ShaderRecord* m_rayRecord;
			ShaderRecords m_missRecords;
			SubDescs m_subDescs;

			TopLevelASPtr m_topLevelAS;
			ShaderTables m_tables;
			SceneManagement::Scene* m_belongScene;					// 所属シーン

			RaytracingPipeline* m_pipeline;			// パイプライン
			RootSignature* m_globalRootSignature;	// グローバルシグネチャだけ別においておく
			RootSignatures m_localRootSignatures;	// ルートシグネチャ配列

			uint32_t m_subMeshCount;				// サブメッシュ総数
			bool m_active;							// 
		public:
			// コンストラクタ
			RaytracingPass();
			// デストラクタ
			virtual ~RaytracingPass();

			void SetScene(SceneManagement::Scene* scene) { m_belongScene = scene; }

			// シェーダーテーブル作成
			void CreateShaderTable(bool share = false);
			// レイ作成シェーダー登録
			void RegisterRayGenerateRecord(void* identifier);
			// ミスシェーダー登録
			void RegisterMissRecord(void* identifier);

			// ヒットグループテーブル取得
			ShaderTable* GetHitGroupTable() const;
			// レイ生成用テーブル取得
			ShaderTable* GetRayGenerateTable() const;
			// ミスシェーダーテーブル取得
			ShaderTable* GetMissTable() const;

			void SetName(const std::wstring& name);
		};
	}
}