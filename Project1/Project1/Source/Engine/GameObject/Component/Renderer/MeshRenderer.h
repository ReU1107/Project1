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
		// �R���X�g���N�^
		MeshRenderer() noexcept;
		// �f�X�g���N�^
		virtual ~MeshRenderer() noexcept;
		// ID�擾
		static const InstanceID ID() { return InstanceID::MeshRenderer; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::MeshRenderer; }

	public:

		// ���b�V���ݒ�
		void SetMesh(MeshPtr mesh);

		// ���b�V���擾
		MeshPtr GetMesh() const;

		// �萔�o�b�t�@�擾
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