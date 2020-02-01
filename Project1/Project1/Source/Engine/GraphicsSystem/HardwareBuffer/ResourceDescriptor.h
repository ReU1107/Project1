#pragma once
#include <cstdint>
#include <string>

namespace Engine 
{

	namespace GraphicsSystem
	{

		class IDescriptorHeap;
		class IResourceView;
		class ResourceView;
		enum class DescriptorHeapType : uint8_t;

		class ResourceDescriptor
		{
		private:
			IDescriptorHeap* m_interface;	// ヒープ
			DescriptorHeapType m_type;		// タイプ
			uint32_t m_maxCount;			// 最大確保数
			uint32_t m_currentIndex;		// 現在の確保数
		public:
			// コンストラクタ
			ResourceDescriptor();
			// デストラクタ
			~ResourceDescriptor();
			// 
			static ResourceDescriptor* CreateShaderResource(uint32_t count, bool shaderAccess = true, uint32_t nodeMask = 0);
			// 
			static ResourceDescriptor* CreateRenderTarget(uint32_t count, uint32_t nodeMask = 0);
			// 
			static ResourceDescriptor* CreateDepthStencil(uint32_t count, uint32_t nodeMask = 0);

		private:
			static ResourceDescriptor* Create(DescriptorHeapType type, uint32_t count, bool shaderAccess = true, uint32_t nodeMask = 0);
		public:
			// 番号指定でリセット番号の後ろが無視されます
			void Reset(uint32_t index = 0);

			// 作成
			// ヒープ取得
			IDescriptorHeap* GetInterface() const { return m_interface; }

			void CopyView(ResourceView* view);
			void CopyView(IResourceView* view);


			void SetName(const std::wstring& name);
		};

	}

}