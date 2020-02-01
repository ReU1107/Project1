#pragma once
#include <vector>

/*

*/

namespace Engine
{

	namespace GraphicsSystem 
	{

		// 前方宣言
		class ShaderResource;
		class IResource;
		class IResourceView;
		class IDescriptorHeap;
		class Buffer;
		class Resource;
		class ResourceView;
		class ResourceDescriptor;
		class VertexBuffer;
		class Texture;
		
		enum class ShaderRecordType : uint8_t;

		enum class LocalRootArgumentType
		{
			Resource,			// リソース
			ResourceView,		// リソースビュー
			DescriptorTable,	// デスクリプターテーブル
		};

		struct LocalRootArgument {
			union
			{
				IResource* resource;	// 
				IResourceView* view;	// 
				IDescriptorHeap* heap;	// 
			};
			LocalRootArgumentType type;		// リソースかリソースビューか
		};

		class ShaderRecord
		{
		private:
			using LocalRootArguments = std::vector<LocalRootArgument>;
			
		private:
			void* m_identifier;					// シェーダー識別子
			LocalRootArguments m_arguments;		// このシェーダーで使用するリソース群
			uint32_t m_size;					// サイズ
			uint32_t m_registerIndex;			// シェーダーテーブル内での登録番号
			ShaderRecordType m_type;			// タイプ
		public:
			// コンストラクタ
			ShaderRecord();
			// デストラクタ
			~ShaderRecord();
		public:
			// シェーダー識別子設定
			void SetShaderIdentifier(void* identifier);
			// 登録番号設定
			void SetRegisterIndex(uint32_t index);

			// リソース追加
			void AddResource(Buffer* buffer);
			void AddResource(Resource* resource);
			void AddResource(IResource* resource);
			
			// リソースビュー追加
			void AddResourceView(ResourceView* resourceView);
			void AddResourceView(IResourceView* resourceView);

			// デスクリプターテーブル追加
			void AddDescriptorTable(ResourceDescriptor* descriptor);
			void AddDescriptorTable(IDescriptorHeap* descriptorTable);

			// シェーダー識別子取得
			void* GetShaderIdentifier() const;
			
			// ローカル数取得
			uint32_t GetLocalRootArgumentCount() const;
			// ローカル
			const LocalRootArgument& GetLocalRootArgument(uint32_t index) const;

			// 登録番号取得
			uint32_t GetRegisterIndex() const;

			// サイズ取得
			uint32_t GetSize() const;
		};

	}

}