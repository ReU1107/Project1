#pragma once
#include <string>
#include <cstdint>
#include "../../Utility/AccessObject.h"

namespace Engine 
{

	namespace GraphicsSystem
	{

		class Resource;
		class ResourceView;
		class ResourceDescriptor;
		enum class ResourceFormat : uint8_t;
		enum class ResourceStates : uint16_t;

		// 全てのテクスチャの基底クラス
		class Texture : public AccessObject<Texture>
		{
		private:
			using base = AccessObject<Texture>;
			using TexturePtr = std::shared_ptr<Texture>;
		public:
			Resource* m_resource;					// リソース
			ResourceView* m_shaderResourceView;		// シェーダーリソースビュー
			ResourceView* m_unorderedAccessView;	// アンオーダードアクセスビュー
			ResourceFormat m_format;
		public:
			// コンストラクタ
			Texture(const std::string& name);
			// デストラクタ
			virtual ~Texture();

			// インスタンスID
			static const InstanceID ID() { return InstanceID::Texture; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const { return InstanceID::Texture; }
		public:

			static TexturePtr Create(const std::string& fileName);
			static TexturePtr Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool renderTarget = false, bool depthStencil = false, bool unorderedAccess = false, bool shaderResource = true);
		
			// リソース設定
			void SetResource(Resource* resource);
			// フォーマット設定
			void SetFormat(ResourceFormat format);

			// シェーダーリソースビュー作成
			void CreateShaderResourceView();

			// アンオーダードアクセスビュー作成
			void CreateUnorderedAccessView();

			// シェーダーリソースビュー作成
			void RecreateShaderResourceView(ResourceDescriptor* descriptor);

			// アンオーダードアクセスビュー作成
			void RecreateUnorderedAccessView(ResourceDescriptor* descriptor);

			// ビュー設定
			void SetShaderResourceView(ResourceView* view);
			// ステート取得
			ResourceStates GetStates() const;
			// リソース取得
			Resource* GetResource() const;
			// シェーダーリソースビュー取得
			ResourceView* GetShaderResourceView() const;
			// アンオーダードアクセスビュー取得
			ResourceView* GetUnorderedAccessView() const;

			// フォーマット取得
			ResourceFormat GetFormat() const;

			void SetName(const std::wstring& name);
		};
	}
}

using TexturePtr = std::shared_ptr<Engine::GraphicsSystem::Texture>;
