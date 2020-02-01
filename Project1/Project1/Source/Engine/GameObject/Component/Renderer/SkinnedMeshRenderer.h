#pragma once
#include <vector>
#include "Renderer.h"
#include "../../../Math/Matrix4x4.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Mesh;
		class SkeletalMesh;
		class ConstantBuffer;
		class StructuredBuffer;
	}

	class Transform;
	class Bone;

	class SkinnedMeshRenderer final : public Renderer
	{
	private:
		using base = Renderer;
		using BonePtr = std::shared_ptr<Bone>;
		using SkinBones = std::vector<BonePtr>;
		using MeshPtr = std::shared_ptr<GraphicsSystem::SkeletalMesh>;
		using ConstantBufferPtr = GraphicsSystem::ConstantBuffer*;
		using StructuredBufferPtr = GraphicsSystem::StructuredBuffer*;
		using MatrixPalette = std::vector<Matrix4x4>;
		using SkinnedMeshRendererPtr = std::shared_ptr<SkinnedMeshRenderer>;
	public:
		static std::vector<SkinnedMeshRendererPtr> allSkinnedMeshRenderers;
	private:
		MeshPtr m_mesh;
		ConstantBufferPtr m_worldTransformBuffer;	// ���[���h�ϊ��s��萔�o�b�t�@
		ConstantBufferPtr m_paletteBuffer;			// �s��p���b�g�o�b�t�@
		SkinBones m_skinBones;						// �e�����󂯂�{�[���z��
		mutable MatrixPalette m_matrixPalette;		// �s��p���b�g

		bool m_updateWhenOffscreen;					// ��ʊO�ōX�V���邩
		bool m_blendShapeIsDirty;					// blendshape�̒l���ω�������
		mutable bool m_paletteIsDirty;				// �s��p���b�g�̒l���ω�������
	public:
		// �R���X�g���N�^
		SkinnedMeshRenderer() noexcept;
		// �f�X�g���N�^
		virtual ~SkinnedMeshRenderer() noexcept;

		// ID�擾
		static const InstanceID ID() { return InstanceID::SkinnedMeshRenderer; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::SkinnedMeshRenderer; }

	public:
		// �u�����h�V�F�C�v�e���l�ݒ�
		void SetBlendShapeWeight(uint32_t index, float weight);
		void SetBlendShapeWeight(const std::string& name, float weight);

		int32_t GetBlendShapeIndex(const std::string& name);
		// �u�����h�V�F�C�v�e���l�擾
		float GetBlendShapeWeight(uint32_t index);

		void CalculateBlendShape() const;
		
		void SetMesh(MeshPtr mesh);

		MeshPtr GetMesh() const;

		SkinBones& GetSkinBones();

		void PaletteIsDirty() { m_paletteIsDirty = true; }

	public:
	
		ConstantBufferPtr GetConstantBuffer() const;

		ConstantBufferPtr GetMatrixPaletteBuffer() const;
	};

	template<>
	inline std::shared_ptr<SkinnedMeshRenderer> Component::Create()
	{
		auto renderer = std::make_shared<SkinnedMeshRenderer>();

		SkinnedMeshRenderer::allSkinnedMeshRenderers.push_back(renderer);

		return renderer;
	}
}

using SkinnedMeshRendererPtr = std::shared_ptr<Engine::SkinnedMeshRenderer>;