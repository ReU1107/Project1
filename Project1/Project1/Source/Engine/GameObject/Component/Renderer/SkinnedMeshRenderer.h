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
		ConstantBufferPtr m_worldTransformBuffer;	// ワールド変換行列定数バッファ
		ConstantBufferPtr m_paletteBuffer;			// 行列パレットバッファ
		SkinBones m_skinBones;						// 影響を受けるボーン配列
		mutable MatrixPalette m_matrixPalette;		// 行列パレット

		bool m_updateWhenOffscreen;					// 画面外で更新するか
		bool m_blendShapeIsDirty;					// blendshapeの値が変化したか
		mutable bool m_paletteIsDirty;				// 行列パレットの値が変化したか
	public:
		// コンストラクタ
		SkinnedMeshRenderer() noexcept;
		// デストラクタ
		virtual ~SkinnedMeshRenderer() noexcept;

		// ID取得
		static const InstanceID ID() { return InstanceID::SkinnedMeshRenderer; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::SkinnedMeshRenderer; }

	public:
		// ブレンドシェイプ影響値設定
		void SetBlendShapeWeight(uint32_t index, float weight);
		void SetBlendShapeWeight(const std::string& name, float weight);

		int32_t GetBlendShapeIndex(const std::string& name);
		// ブレンドシェイプ影響値取得
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