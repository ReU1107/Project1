#include "SkinnedMeshRenderer.h"
#include "../../../GraphicsSystem/Include.h"
#include "../../../ModelData.h"
#include "../Transform.h"
#include "../Bone/Bone.h"

using namespace DirectX;

namespace Engine
{
	using namespace GraphicsSystem;
	std::vector<SkinnedMeshRenderer::SkinnedMeshRendererPtr> SkinnedMeshRenderer::allSkinnedMeshRenderers;

	SkinnedMeshRenderer::SkinnedMeshRenderer() noexcept
		: base("SkinnedMeshRenderer")
		, m_mesh(nullptr)
		, m_worldTransformBuffer(nullptr)
		, m_paletteBuffer(nullptr)
		, m_updateWhenOffscreen(true)
		, m_blendShapeIsDirty(false)
		, m_paletteIsDirty(true)
	{
		SetShadowCastingMode(ShadowCastingMode::On);

		m_worldTransformBuffer = new ConstantBuffer();
		m_worldTransformBuffer->SetStride(sizeof(ModelData));
		m_worldTransformBuffer->SetCount(1);
		m_worldTransformBuffer->Create();

		m_paletteBuffer = new ConstantBuffer(ResourceViewType::ConstantBuffer);
		m_paletteBuffer->SetStride(sizeof(Matrix4x4));
		m_paletteBuffer->SetCount(512);
		m_paletteBuffer->Raw(false);
		m_paletteBuffer->Dynamic(false);
		m_paletteBuffer->SetFlags(ResourceFlags::AllowUnorderedAccess);
		m_paletteBuffer->Create();
		m_matrixPalette.resize(512);
	}

	SkinnedMeshRenderer::~SkinnedMeshRenderer() noexcept
	{
		delete m_paletteBuffer;
		delete m_worldTransformBuffer;
	}

	void SkinnedMeshRenderer::SetBlendShapeWeight(uint32_t index, float weight)
	{
		m_mesh->GetBlendShapeFrame(index)->SetWeight(weight);
	}

	void SkinnedMeshRenderer::SetBlendShapeWeight(const std::string& name, float weight)
	{
		m_mesh->GetBlendShapeFrame(name)->SetWeight(weight);
	}

	int32_t SkinnedMeshRenderer::GetBlendShapeIndex(const std::string& name)
	{
		return m_mesh->GetBlendShapeIndex(name);
	}

	float SkinnedMeshRenderer::GetBlendShapeWeight(uint32_t index)
	{
		return m_mesh->GetBlendShapeFrame(index)->GetWeight();
	}

	void SkinnedMeshRenderer::CalculateBlendShape() const
	{
		auto& blendShapes = m_mesh->GetBlendShapes();
		auto& deltaPositions = m_mesh->GetDeltaPositions();
		for (auto& deltaPosition : deltaPositions)
		{
			deltaPosition = Vector3::Zero;
		}

		for (auto& blendShape : blendShapes)
		{
			if (!blendShape->IsCalculated())
				continue;
			float weight = blendShape->GetWeight();
			auto& deltaValues = blendShape->GetDeltaPositions();

			for (auto& delta : deltaValues)
			{
				deltaPositions[delta.index] += delta.value * weight;
			}

		}

		m_mesh->SetDirtyFlags(VertexDirtyFlags::DeltaPositions);

	}

	void SkinnedMeshRenderer::SetMesh(MeshPtr mesh)
	{
		m_mesh = mesh;
	}

	SkinnedMeshRenderer::MeshPtr SkinnedMeshRenderer::GetMesh() const
	{
		return m_mesh;
	}

	SkinnedMeshRenderer::SkinBones& SkinnedMeshRenderer::GetSkinBones()
	{
		return m_skinBones;
	}

	SkinnedMeshRenderer::ConstantBufferPtr SkinnedMeshRenderer::GetConstantBuffer() const
	{
		ModelData data = {};
		data.worldMatrix = GetTransform()->GetLocalToWorld();
		m_worldTransformBuffer->Update(&data);

		return m_worldTransformBuffer;
	}

	SkinnedMeshRenderer::ConstantBufferPtr SkinnedMeshRenderer::GetMatrixPaletteBuffer() const
	{
		if (m_paletteIsDirty)
		{
			uint32_t size = m_skinBones.size();
			for (uint32_t i = 0; i < size; ++i)
			{
				auto& bone = m_skinBones[i];
				auto& matrix = m_matrixPalette[i];
				// ボーンの初期位置に移動させてからアニメーションを適用したボーンの位置に変更
				XMMATRIX offsetMatrix = XMLoadFloat4x4(&bone->GetOffsetMatrix());
				XMMATRIX keyPoseMatrix = XMLoadFloat4x4(&bone->GetKeyPoseMatrix());
				XMStoreFloat4x4(&matrix, offsetMatrix * keyPoseMatrix);
			}
			m_paletteBuffer->Update(m_matrixPalette.data());
			m_paletteIsDirty = false;
		}
		return m_paletteBuffer;
	}

}
