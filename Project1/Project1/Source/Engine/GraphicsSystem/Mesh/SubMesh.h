#pragma once
#include <cstdint>
#include <string>
#include <iostream>

namespace Engine 
{
	namespace GraphicsSystem
	{
		class IndexBuffer;
		class Material;

		class SubMesh
		{
		private:
			using MaterialPtr = std::shared_ptr<Material>;
		private:
			std::string m_name;				// デバッグ用名前
			MaterialPtr m_material;			// マテリアル
			IndexBuffer* m_indexBuffer;		// インデックスバッファのみを分割する
			uint32_t m_startIndexLocation;	// 頂点インデックス開始位置
			uint32_t m_useIndexCount;		// 自身が使用する頂点インデックス数
		public:
			// コンストラクタ
			SubMesh(const std::string& name = "");
			// デストラクタ
			~SubMesh();
		public:
			// マテリアル設定
			void SetMaterial(MaterialPtr material);
			// インデックスバッファ設定
			void SetIndexBuffer(IndexBuffer* indexBuffer);

			// インデックス開始位置設定
			void SetStartIndexLocation(uint32_t startLocation);
			// 使用する頂点インデックス数設定
			void SetUseIndexCount(uint32_t indexCount);

			// マテリアル取得
			MaterialPtr GetMaterial() const;

			IndexBuffer* GetIndexBuffer() const;

			// インデックス開始位置取得
			uint32_t GetStartIndexLocation() const;
			// 使用インデックス数取得
			uint32_t GetUseIndexCount() const;
		};

		// メッシュを構成する部品(メッシュの分割)
		//class SubMesh final// : public Object
		//{
		//private:
		//	//using base = Object;
		//private:
		//	uint32_t m_startIndexLocation;	// 頂点インデックス開始位置
		//	uint32_t m_useIndexCount;		// 自身が使用する頂点インデックス数

		//public:
		//	// コンストラクタ
		//	SubMesh(const std::string& name);
		//	// デストラクタ
		//	~SubMesh();
		////public:
		////	// インスタンスID
		////	static const InstanceID ID() { return InstanceID::SubMesh; }
		////	// インスタンスID取得
		////	virtual InstanceID GetInstanceID() const override { return InstanceID::SubMesh; }

		//public:
		//	// インデックス開始位置設定
		//	void SetStartIndexLocation(uint32_t startLocation);
		//	// 使用する頂点インデックス数設定
		//	void SetUseIndexCount(uint32_t indexCount);
		//public:
		//	// インデックス開始位置取得
		//	uint32_t GetStartIndexLocation() const;
		//	// 使用インデックス数取得
		//	uint32_t GetUseIndexCount() const;
		//};
	}
}

using SubMeshPtr = std::shared_ptr<Engine::GraphicsSystem::SubMesh>;
