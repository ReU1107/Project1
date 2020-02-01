#include "Texture.h"
#include "../Interface/IResource.h"

#include "DDSLoader.h"
#include "TGALoader.h"
#include "WICLoader.h"

#include "..//D3D12.h"
#include "..//D3D12/D3D12Device.h"
#include "..//Description/Include.h"
#include "..//Enumerations/Include.h"
#include "..//HardwareBuffer//Resource.h"
#include "..//HardwareBuffer//ResourceView.h"
#include "..//HardwareBuffer/ResourceDescriptor.h"

namespace Engine 
{
	
	namespace GraphicsSystem 
	{

		static WICLoader* s_wicLoader = nullptr;
		static TGALoader* s_tgaLoader = nullptr;
		static DDSLoader* s_ddsLoader = nullptr;

		Texture::Texture(const std::string& name)
			: base(name)
			, m_resource(nullptr)
			, m_shaderResourceView(nullptr)
			, m_unorderedAccessView(nullptr)
			, m_format()
		{
		}

		Texture::~Texture()
		{
			delete m_unorderedAccessView;
			delete m_shaderResourceView;
			delete m_resource;
		}

		Texture::TexturePtr Texture::Create(const std::string& fileName)
		{
			auto texture = std::make_shared<Texture>(fileName);
			static WICLoader s_wicLoader;
			static TGALoader s_tgaLoader;
			static DDSLoader s_ddsLoader;
			auto find = fileName.rfind(".");
			IResource* resource = nullptr;
			if (!fileName.compare(find, 4, ".tga") || !fileName.compare(find, 4, ".TGA"))
			{
				resource = s_tgaLoader.LoadTexture(fileName);
			}
			else if (
				!fileName.compare(find, 4, ".png") || !fileName.compare(find, 4, ".PNG") ||
				!fileName.compare(find, 4, ".jpg") || !fileName.compare(find, 4, ".JPG") ||
				!fileName.compare(find, 4, ".bmp") || !fileName.compare(find, 4, ".BMP") ||
				!fileName.compare(find, 4, ".spa") || !fileName.compare(find, 4, ".SPA") ||
				!fileName.compare(find, 4, ".sph") || !fileName.compare(find, 4, ".SPH") ||
				!fileName.compare(find, 4, ".gif") || !fileName.compare(find, 4, ".GIF") ||
				!fileName.compare(find, 5, ".tiff")|| !fileName.compare(find, 5, ".TIFF"))
			{
				resource = s_wicLoader.LoadTexture(fileName);
			}
			else if (!fileName.compare(find, 4, ".dds") || !fileName.compare(find, 4, ".DDS"))
			{
				resource = s_ddsLoader.LoadTexture(fileName);
			}
			
			Resource* r = new Resource();
			
			r->SetInterface(resource);
			texture->m_resource = r;
			Register(fileName, texture);

			return texture;
		}

		Texture::TexturePtr Texture::Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool renderTarget, bool depthStencil, bool unorderedAccess, bool shaderResource)
		{
			TextureDesc desc = TextureDesc::Default2D(width, height, format, renderTarget, depthStencil, unorderedAccess, shaderResource);
			desc.states = ResourceStates::CopySource;

			auto texture = std::make_shared<Texture>(name);
			texture->m_resource = Resource::Create(desc);
			texture->m_format = format;
			Register(name, texture);

			return texture;
		}

		void Texture::SetResource(Resource* resource)
		{
			m_resource = resource;
		}

		void Texture::SetFormat(ResourceFormat format)
		{
			m_format = format;
		}

		void Texture::CreateShaderResourceView()
		{
			m_shaderResourceView = ResourceView::Create(ResourceViewType::ShaderResource);
		}

		void Texture::CreateUnorderedAccessView()
		{
			m_unorderedAccessView = ResourceView::Create(ResourceViewType::UnorderedAccess);
		}

		void Texture::RecreateShaderResourceView(ResourceDescriptor* descriptor)
		{
			if (!m_shaderResourceView)
				CreateShaderResourceView();
			m_shaderResourceView->Recreate(descriptor, m_resource);
		}

		void Texture::RecreateUnorderedAccessView(ResourceDescriptor* descriptor)
		{
			if (!m_unorderedAccessView)
				CreateUnorderedAccessView();
			m_unorderedAccessView->Recreate(descriptor, m_resource);
		}

		void Texture::SetShaderResourceView(ResourceView* view)
		{
			m_shaderResourceView = view;
		}

		ResourceStates Texture::GetStates() const
		{
			return m_resource->GetStates();
		}

		Resource* Texture::GetResource() const
		{
			return m_resource;
		}

		ResourceView* Texture::GetShaderResourceView() const
		{
			return m_shaderResourceView;
		}

		ResourceView* Texture::GetUnorderedAccessView() const
		{
			return m_unorderedAccessView;
		}

		ResourceFormat Texture::GetFormat() const
		{
			return m_format;
		}

		void Texture::SetName(const std::wstring& name)
		{
			ID3D12Resource1* resource = (ID3D12Resource1*)m_resource->GetInterface()->GetNativeResource();
			resource->SetName(name.c_str());
		}

	}

}

