#pragma once
#include <DirectXMath.h>
#include <vector>

namespace Engine
{
	namespace GraphicsSystem
	{
		/*
		こいつの形状はシェーダー側で決定してください
		*/
		// 
		struct AxisAlignedBoundingBox
		{
			float minX;
			float minY;
			float minZ;
			float maxX;
			float maxY;
			float maxZ;
		};
		class StructuredBuffer;
		class Material;
		class SubMesh;

		class ProceduralMesh
		{
			using AxisAlignedBoundingBoxes = std::vector<AxisAlignedBoundingBox>;
			using SubMeshes = std::vector<SubMesh*>;
		private:
			AxisAlignedBoundingBoxes m_aabbs;	// AABB配列
			SubMeshes m_subMeshes;				// サブメッシュ配列
			StructuredBuffer* m_buffer;

		public:
			// コンストラクタ
			ProceduralMesh();
			// デストラクタ
			~ProceduralMesh();
			// AABB追加
			void AddAABB(const DirectX::XMFLOAT3& min, const DirectX::XMFLOAT3& max);
			void AddSphere(const DirectX::XMFLOAT3& center, float radius);
			// サブメッシュ追加
			void AddSubMesh(SubMesh* subMesh);

			// サブメッシュ配列取得
			SubMeshes& GetSubMeshes();
			// 作成
			void Create();

			StructuredBuffer* GetBuffer() const;
		};

	}
}