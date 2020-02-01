#pragma once
#include "Renderer.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class StaticMesh;
		class ConstantBuffer;
	}

	class MeshRenderer final : public Renderer
	{
	private:
		using base = Renderer;
		using MeshPtr = std::shared_ptr<GraphicsSystem::StaticMesh>;
		using ConstantBufferPtr = GraphicsSystem::ConstantBuffer*;
		using MeshRendererPtr = std::shared_ptr<MeshRenderer>;
	public:
		static std::vector<MeshRendererPtr> allMeshRenderers;

	private:
		MeshPtr m_mesh;
		ConstantBufferPtr m_constantBuffer;
	public:
		// コンストラクタ
		MeshRenderer() noexcept;
		// デストラクタ
		virtual ~MeshRenderer() noexcept;
		// ID取得
		static const InstanceID ID() { return InstanceID::MeshRenderer; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::MeshRenderer; }

	public:

		// メッシュ設定
		void SetMesh(MeshPtr mesh);

		// メッシュ取得
		MeshPtr GetMesh() const;

		// 定数バッファ取得
		ConstantBufferPtr GetConstantBuffer() const;

	};

	template<>
	inline std::shared_ptr<MeshRenderer> Component::Create()
	{
		auto renderer = std::make_shared<MeshRenderer>();
		MeshRenderer::allMeshRenderers.push_back(renderer);
		return renderer;
	}

}

using MeshRendererPtr = std::shared_ptr<Engine::MeshRenderer>;