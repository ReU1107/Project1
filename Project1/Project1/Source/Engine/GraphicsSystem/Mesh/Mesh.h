#pragma once
#include <vector>
#include <array>
#include <cstdint>
#include <iostream>
#include "../../Math/Include.h"
#include "../../Utility/AccessObject.h"
#include "../Enumerations/ResourceViewType.h"

namespace Engine 
{
	namespace GraphicsSystem 
	{
		class VertexBuffer;
		class IndexBuffer;
		class ConstantBuffer;
		class Material;
		class SubMesh;
		class ResourceDescriptor;

		enum class VertexLayout : uint16_t
		{
			Positions = 0x01,		// 頂点シェーダーに流す位置座標
			Normals = 0x02,			// 法線
			Tangents = 0x04,		// 接線
			BoneWeights = 0x08,		// ボーン情報
			BasePositions = 0x10,	// 基本になる位置座標
			DeltaPositions = 0x20,	// 移動させる位置座標
			DeltaNormals = 0x40,	// 
			DeltaTangents = 0x80,	// 
			Texcoords0 = 0x100,		// テクスチャ座標
			Texcoords1 = 0x200,		// テクスチャ座標
			Texcoords2 = 0x400,		// テクスチャ座標
			Texcoords3 = 0x800,		// テクスチャ座標
		};

		enum class MeshType : uint8_t
		{
			Static,		// 
			Skeletal,	// 
		};

		class Mesh : public AccessObject<Mesh>
		{
		private:
			using base = AccessObject<Mesh>;
			using VertexBufferPtr = VertexBuffer*;
			using VertexBuffers = std::vector<VertexBufferPtr>;

			using Positions = std::vector<Vector3>;
			using Normals = std::vector<Vector3>;
			using Tangents = std::vector<Vector4>;
			using Texcoords = std::vector<float>;
			using Indices = std::vector<uint32_t>;
			using MeshPtr = std::shared_ptr<Mesh>;
			using SubMeshPtr = std::shared_ptr<SubMesh>;
			using SubMeshes = std::vector<SubMeshPtr>;
		protected:
			VertexBuffers m_vertexBuffers;	// 頂点バッファ配列
			Positions m_positions;			// 位置情報
			Normals m_normals;				// 法線情報
			Texcoords m_texcoords0;			// UV情報
			Indices m_indices;				// インデックス情報

			SubMeshes m_subMeshes;			// サブメッシュ配列

			uint32_t m_vertexBufferCount;	// 頂点バッファ数
			uint32_t m_textureCount;		// このメッシュが持つテクスチャの総数
			VertexLayout m_layout;			// 頂点レイアウト
			MeshType m_type;				// メッシュタイプ
			bool m_vertexCountIsDirty;		// 頂点数が変更されたらtrue
		public:
			// コンストラクタ
			Mesh(const std::string& name, MeshType type);
			// デストラクタ
			virtual ~Mesh();

		public:
			// 頂点数取得
			uint32_t GetVertexCount() const;
			
			// 頂点バッファ数取得
			uint32_t GetVertexBufferCount() const;

			// 頂点バッファ配列取得
			VertexBuffers& GetVertexBuffers();
			
			// 頂点バッファ取得
			VertexBuffer* GetVertexBuffer(uint32_t index) const;

			VertexBuffer* GetVertexBuffer(VertexLayout layout) const;

			// 位置配列取得
			Positions& GetPositions();

			// 位置配列取得
			Normals& GetNormals();

			// UV配列取得
			Texcoords& GetTexcoords0();

			// インデックス配列取得
			Indices& GetIndices();

			// マテリアル配列取得
			//std::vector<Material*>& GetMaterials();
			// サブメッシュカウント取得
			uint32_t GetSubMeshCount() const;
			// サブメッシュ配列取得
			SubMeshes& GetSubMeshes();

			// メッシュの種類
			MeshType GetMeshType() const;

			// テクスチャ数設定
			void SetTextureCount(uint32_t textureCount);

			// テクスチャ数取得
			uint32_t GetTextureCount() const;

			virtual void Update() = 0;

			virtual void CreateVertexBuffes() = 0;

			void CreateIndexBuffer();

			// 頂点レイアウト設定
			void SetVertexLayout(VertexLayout layout);
			// 頂点レイアウト追加
			void AddVertexLayout(VertexLayout layout);

		protected:
			// 頂点バッファ作成
			void CreateVertexBuffer(uint32_t size, uint32_t stride, void* data, bool gpuAccess = false, ResourceViewType type = ResourceViewType::ShaderResource);

			// 頂点バッファ更新
			void UpdateVertexBuffer(uint32_t index, void* data);

		};
	}
}

using MeshPtr = std::shared_ptr<Engine::GraphicsSystem::Mesh>;
