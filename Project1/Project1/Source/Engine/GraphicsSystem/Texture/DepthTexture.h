#pragma once
#include "Texture.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		class ResourceDescriptor;

		class DepthTexture : public Texture
		{
		private:
			using base = Texture;
			using DepthTexturePtr = std::shared_ptr<DepthTexture>;

			static ResourceDescriptor* s_descriptor;
			static uint32_t s_descriptorCount;
			static uint32_t s_count;
		private:
			ResourceView* m_depthStencilView;
		public:
			// コンストラクタ
			DepthTexture(const std::string& name);
			// デストラクタ
			virtual ~DepthTexture();

			// インスタンスID
			static const InstanceID ID() { return InstanceID::DepthTexture; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const { return InstanceID::DepthTexture; }

			static DepthTexturePtr Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool shaderResource = true);


		public:
			ResourceView* GetDepthStencilView() const;

			// デプスステンシルビュー作成
			void CreateDepthStencilView();

		private:
			// デスクリプター作成
			static void CreateDescriptor();

		};
	}
}

using DepthTexturePtr = std::shared_ptr<Engine::GraphicsSystem::DepthTexture>;
