#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include "../../Math/Matrix4x4.h"

namespace Engine
{

	namespace GraphicsSystem
	{

		// 前方宣言
		class IRaytracingGeometry;
		class BottomLevelAccelerationStructure;
		class ShaderRecord;
		class GraphicsCommandList;
		class Material;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		class RaytracingSubMesh
		{
		private:
			using ShaderRecords = std::vector<ShaderRecord*>;
			using MaterialPtr = std::shared_ptr<Material>;
			using BottomLevelASPtr = std::shared_ptr<BottomLevelAccelerationStructure>;

		private:
			BottomLevelASPtr m_bottomLevelAS;
			MaterialPtr m_sharedMaterial;
			ShaderRecords m_shaderRecords;					// シェーダーレコード
			Matrix4x4 m_matrix;								// 変換行列
			uint32_t m_id;									// id
			uint32_t m_mask;								// レイトレースマスク値

			SubTopLevelAccelerationStructureFlags m_flags;
			bool m_dirty;									// 変更があったか

		public:
			// コンストラクタ
			RaytracingSubMesh();
			// デストラクタ
			~RaytracingSubMesh();
		public:

			void CreateShaderRecord(uint32_t recordCount = 1);

			// 表示する形状設定
			void SetBottomLevelAS(BottomLevelASPtr bottomLevelAS);

			// 
			void SetSharedMaterial(MaterialPtr material);

			void SetFlags(SubTopLevelAccelerationStructureFlags flags);

			// マスク値設定
			void SetMask(uint32_t mask = 0xff);

			// 変換行列設定
			void SetTransformMatrix(const Matrix4x4& matrix);

		public:
			// 形状取得
			BottomLevelASPtr GetBottomLevelAS() const { return m_bottomLevelAS; };

			// シェーダーレコード取得
			ShaderRecord* GetShaderRecord(uint32_t index = 0) const;

			// シェーダーレコード配列番号取得
			uint32_t GetShaderRecordIndex(uint32_t index = 0)const;

			SubTopLevelAccelerationStructureFlags GetFlags() const;

			// ID取得
			uint32_t GetID() const;

			// マスク値取得
			uint32_t GetMask() const;

			// 変換行列取得
			const Matrix4x4& GetTransformMatrix() const;
			// 値の変更があったか
			bool IsDirty() const { return m_dirty; }

			void Build(GraphicsCommandList* list) {};

			void SetName(const std::wstring& name);
		};

	}

}
/*
m_shaderRecordIndex
このインスタンスに使用するリソースなどが入った配列の番号

*/