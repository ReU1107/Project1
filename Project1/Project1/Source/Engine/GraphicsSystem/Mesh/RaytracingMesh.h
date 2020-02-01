#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include "../../Math/Matrix4x4.h"
/*
クリエイト関数のseparateにおいての説明
separateは部品ごとを分解するかいなかの情報でseparateがtrueの場合はサブメッシュごとに分割を行う
falseの場合は全てを一つにしてもっておくことになる
trueの使い道としてボーンアニメーションの適用する際に必要不可欠になる
逆にアニメーションがないものはfalseにしておいたほうがいい
*/

namespace Engine
{
	namespace GraphicsSystem
	{
		class RaytracingSubMesh;
		class Mesh;
		class Material;
		class ProceduralMesh;
		class ShaderTable;
		class Resource;
		class ResourceView;
		class GraphicsCommandList;
		enum class RaytracingInstanceFlags : uint8_t;

		class RaytracingMesh
		{
		private:
			using SubMeshPtr = std::shared_ptr<RaytracingSubMesh>;
			using SubMeshes = std::vector<SubMeshPtr>;
			using ShaderIdentifiers = std::vector<void*>;
			using RaytracingMeshPtr = std::shared_ptr<RaytracingMesh>;
			using MaterialPtr = std::shared_ptr<Material>;
			using MeshPtr = std::shared_ptr<Mesh>;
			using ProceduralMeshPtr = std::shared_ptr<ProceduralMesh>;
		private:
			SubMeshes m_subMeshes;					// サブメッシュ配列
			ShaderIdentifiers m_identifiers;		// シェーダー識別配列
			MeshPtr m_baseMesh;					// 基本メッシュ
			ProceduralMeshPtr m_proceduralMesh;	// プロシージャルメッシュ
			bool m_isProcedural;		

		public:
			// コンストラクタ
			RaytracingMesh();
			// デストラクタ
			~RaytracingMesh();

		public:
			static RaytracingMeshPtr Create(MeshPtr mesh, uint32_t shaderCount = 1, bool isReBuild = false);
			static RaytracingMeshPtr Create(MeshPtr mesh, MaterialPtr material, uint32_t shaderCount = 1, bool isReBuild = false);
			static RaytracingMeshPtr Create(ProceduralMeshPtr mesh, uint32_t shaderCount = 1, bool isReBuild = false);
			static RaytracingMeshPtr Create(ProceduralMeshPtr mesh, MaterialPtr material, uint32_t shaderCount = 1, bool isReBuild = false);

		public:
			// サブメッシュ追加
			void AddSubMesh(SubMeshPtr subMesh);

			// 
			SubMeshes& GetSubMeshes();

			// サブメッシュ取得
			SubMeshPtr GetSubMesh(uint32_t index) const;
			// サブメッシュ数取得
			uint32_t GetSubMeshCount() const;

			void SetTransformMatrix(const Matrix4x4& matrix);

			void SetMask(uint32_t mask);

			// シェーダーテーブル内での自分の番号を登録するため
			void AddShader(void* identifier);
			// AddShader後に必ず呼ぶ
			void SetShader(ShaderTable* hitGroupTable);

			void Build(GraphicsCommandList* list);

			// ベースのメッシュの頂点情報に変化があったら読んでください
			// 作り直し
			void ReBuild();

			MeshPtr GetBaseMesh() const;

			ProceduralMeshPtr GetBaseProceduralMesh() const;

		};

	}
}

using RaytracingMeshPtr = std::shared_ptr<Engine::GraphicsSystem::RaytracingMesh>;
