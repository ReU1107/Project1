#pragma once
#include "Mesh.h"
#include "BoneWeight.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class BlendShape;
		enum class VertexDirtyFlags : uint16_t
		{
			Positions = 0x01,		// 
			Normals = 0x02,			// 
			Tangents = 0x04,		// 
			BoneWeights = 0x08,		// 
			BasePositions = 0x10,	// 
			DeltaPositions = 0x20,	// 
			DeltaNormals = 0x40,	// 
			DeltaTangents = 0x80,	// 
			Texcoords0 = 0x100,		// 
			Texcoords1 = 0x200,		// 
			Texcoords2 = 0x400,		// 
			Texcoords3 = 0x800,		// 
		};

		class SkeletalMesh : public Mesh
		{
		private:
			using base = Mesh;
			using BoneWeights = std::vector<BoneWeight>;
			using Texcoords = std::vector<float>;
			using Indices = std::vector<uint32_t>;
			using BlendShapePtr = std::shared_ptr<BlendShape>;
			using BlendShapes = std::vector<BlendShapePtr>;
			using DeltaPositions = std::vector<Vector3>;
			using DeltaNormals = std::vector<Vector3>;
			using DeltaTangents = std::vector<Vector3>;
			using Positions = std::vector<Vector3>;

		private:
			BoneWeights m_boneWeights;			// 頂点ボーンウェイト値配列
			Texcoords m_texcoords1;				// 頂点UV位置配列
			Texcoords m_texcoords2;				// 頂点UV位置配列
			Texcoords m_texcoords3;				// 頂点UV位置配列
			Positions m_basePositions;			// 位置情報

			DeltaPositions m_deltaPositions;	// 頂点差分位置配列
			DeltaNormals m_deltaNormals;		// 頂点差分位置配列
			DeltaTangents m_deltaTangents;		// 頂点差分位置配列

			BlendShapes m_blendShapes;			// ブレンド

			VertexDirtyFlags m_dirtyFlags;		// 配列の更新があったら呼び出す

			bool m_vertexDataIsDirty;			// 何かしらの頂点情報の中身が変更したらtrue

		public:
			// コンストラクタ
			SkeletalMesh(const std::string& name);
			// デストラクタ
			virtual ~SkeletalMesh();
		public:
			// インスタンスID
			static const InstanceID ID() { return InstanceID::Mesh; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const override { return InstanceID::Mesh; }

			// ブレンドシェイプフレーム追加
			void AddBlendShapeFrame(BlendShapePtr blendShape);

			// ブレンドシェイプ数取得
			uint32_t GetBlendShapeFrameCount() const;

			// ブレンドシェイプ配列取得
			BlendShapes& GetBlendShapes();
			
			// ブレンドシェイプ取得
			BlendShapePtr GetBlendShapeFrame(const std::string& name) const;
			BlendShapePtr GetBlendShapeFrame(uint32_t index) const;

			// ブレンドシェイプ番号取得
			int32_t GetBlendShapeIndex(const std::string& name) const;

			void SetDirtyFlags(VertexDirtyFlags flags);

		public:
			// UV配列取得
			Texcoords& GetTexcoords0();
			// UV配列取得
			Texcoords& GetTexcoords1();
			// UV配列取得
			Texcoords& GetTexcoords2();
			// UV配列取得
			Texcoords& GetTexcoords3();

			Positions& GetBasePositions();

			// 差分位置配列取得
			DeltaPositions& GetDeltaPositions();

			// ボーン情報配列取得
			BoneWeights& GetBoneWeights();

			// バッファ更新
			virtual void Update() override;
			
			// 頂点バッファ作成
			virtual void CreateVertexBuffes() override;

		};
	}
}

using SkeletalMeshPtr = std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh>;

//// 頂点UV配列設定
//void SetTexcoords1(const Texcoords&& texcoords);
//// 頂点UV配列設定
//void SetTexcoords2(const Texcoords&& texcoords);
//// 頂点UV配列設定
//void SetTexcoords3(const Texcoords&& texcoords);

//// 差分位置配列設定
//void SetDeltaPositions(const DeltaPositions&& deltaPositions);

//// 頂点ウェイト配列設定
//void SetBoneWeights(const BoneWeights&& boneWeights);


//// 頂点UV配列設定
//void SetTexcoords4(const Texcoords&& texcoords);
//// 頂点UV配列設定
//void SetTexcoords5(const Texcoords&& texcoords);
//// 頂点UV配列設定
//void SetTexcoords6(const Texcoords&& texcoords);
//// 頂点UV配列設定
//void SetTexcoords7(const Texcoords&& texcoords);

			//// UV配列取得
			//Texcoords& GetTexcoords4();
			//// UV配列取得
			//Texcoords& GetTexcoords5();
			//// UV配列取得
			//Texcoords& GetTexcoords6();
			//// UV配列取得
			//Texcoords& GetTexcoords7();

			//// 差分法線配列取得
			//DeltaNormals & GetDeltaNormals();
			//// 差分接線配列取得
			//DeltaTangents & GetDeltaTangents();