#pragma once
#include "Texture.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		class RenderTexture : public Texture
		{
		private:
			using base = Texture;
			using RenderTexturePtr = std::shared_ptr<RenderTexture>;
			static ResourceDescriptor* s_descriptor;
			static uint32_t s_descriptorCount;
			static uint32_t s_count;
		private:
			ResourceView* m_renderTargetView;
		public:
			// コンストラクタ
			RenderTexture(const std::string& name);
			// デストラクタ
			virtual ~RenderTexture();

			// インスタンスID
			static const InstanceID ID() { return InstanceID::RenderTexture; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const { return InstanceID::RenderTexture; }

			static RenderTexturePtr Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool unorderedAccess = false, bool shaderResource = true);
			static RenderTexturePtr Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, uint32_t multiSampleCount = 1, float multiSampleQuality = 0.0f, bool shaderResource = true);

		public:

			ResourceView* GetRenderTargetView() const;

			// レンダーターゲットビュー作成
			void CreateRenderTargetView();

		private:
			// デスクリプター作成
			static void CreateDescriptor();

		};
	}
}

using RenderTexturePtr = std::shared_ptr<Engine::GraphicsSystem::RenderTexture>;