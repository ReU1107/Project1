#pragma once
#include <cstdint>
#include <iostream>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IResource;
		class IResourceView;
		class IDescriptorHeap;
		class ResourceDescriptor;
		class Resource;
		class Buffer;
		enum class ResourceViewType : uint8_t;

		class ResourceView
		{
		private:
			using ResourceViewPtr = ResourceView*;
			//using ResourceViewPtr = std::shared_ptr<ResourceView>;

		private:
			IResourceView* m_interface;
			ResourceViewType m_type;
		public:
			// コンストラクタ
			ResourceView();
			// デストラクタ
			~ResourceView();

		public:
			static ResourceView* Create(ResourceDescriptor* descriptor, Resource* resource, ResourceViewType type);
			static ResourceView* Create(ResourceDescriptor* descriptor, Buffer* buffer, ResourceViewType type);
			static ResourceView* Create(IDescriptorHeap* heap, IResource* lowResource, ResourceViewType type);
			static ResourceView* Create(ResourceViewType type);

		public:
			// インターフェイス作り直し
			void Recreate(ResourceDescriptor* descriptor, Resource* resource);
			void Recreate(ResourceDescriptor* descriptor, Buffer* buffer);
			void Recreate(IDescriptorHeap* heap, IResource* lowResource);

			// タイプ設定
			//void SetType(ResourceViewType type);

			//void Create(ResourceDescriptor* descriptor, Resource* resource);

			IResourceView* GetInterface() const;
		};
	}
}