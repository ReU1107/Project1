#pragma once
#include "Mesh.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		// 動かないメッシュ
		class StaticMesh : public Mesh
		{
		private:
			using base = Mesh;

		public:
			// コンストラクタ
			StaticMesh(const std::string& name);
			// デストラクタ
			virtual ~StaticMesh();


			// バッファ更新
			virtual void Update() override;

			// 頂点バッファ作成
			virtual void CreateVertexBuffes() override;
		};
	}
}

using StaticMeshPtr = std::shared_ptr<Engine::GraphicsSystem::StaticMesh>;
