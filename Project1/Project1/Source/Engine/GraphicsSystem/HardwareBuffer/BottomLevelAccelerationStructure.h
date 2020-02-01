#pragma once
#include "AccelerationStructure.h"
#include <cstdint>
#include <vector>
#include "../Description/SubBottomLevelAccelerationStructureDesc.h"
#include "../../Math/Matrix4x4.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Buffer;
		class VertexBuffer;
		class IndexBuffer;
		class ConstantBuffer;
		class GraphicsCommandList;
		enum class BottomLevelAccelerationStructureFlags : uint8_t;
		enum class BottomLevelAccelerationBuildFlags : uint8_t;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		class BottomLevelAccelerationStructure : public AccelerationStructure
		{
		private:
			using base = AccelerationStructure;
			using Descs = std::vector<SubBottomLevelAccelerationStructureDesc>;
			using VertexBuffers = std::vector<VertexBuffer*>;
		private:
			Descs m_descs;					// デスク配列
			VertexBuffers m_vertexBuffers;	// 頂点バッファ配列

			uint32_t m_id;					// id
			uint32_t m_mask;				// レイトレースマスク値
			uint32_t m_contribution;

			uint32_t m_materialIndex;

			BottomLevelAccelerationStructureFlags m_flags;		// 
			BottomLevelAccelerationBuildFlags m_buildFlags;		// フラグ

			bool m_isDirty;
		public:
			// コンストラクタ
			BottomLevelAccelerationStructure();
			// デストラクタ
			virtual ~BottomLevelAccelerationStructure();

			void SetMaterialIndex(uint32_t index);
			// 
			void AddSubBottomLevelASDesc(const SubBottomLevelAccelerationStructureDesc& desc);
			// 三角形ポリゴン
			void AddTraianglesGeometry(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer = nullptr, ConstantBuffer* constantBuffer = nullptr);
			// 手続き型形状
			void AddProceduralGeometry(Buffer* buffer, ConstantBuffer* constantBuffer = nullptr);
			// 作成
			virtual void Create() override;
			virtual void Recreate() override;

			const VertexBuffers& GetVertexBuffers() const;

			// マテリアル取得
			uint32_t GetMaterialIndex() const;

			// ビルドフラグ設定
			void SetBuildFlags(BottomLevelAccelerationBuildFlags buildFlags);

			uint32_t GetContribution() const;

			uint32_t GetID() const;

			uint32_t GetMask() const;

			bool IsDirty() const;

			void Dirty(bool dirty);
		};

		using BottomLevelAS = BottomLevelAccelerationStructure;
	}
}