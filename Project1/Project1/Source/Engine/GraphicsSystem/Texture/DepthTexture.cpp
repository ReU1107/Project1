#include "DepthTexture.h"
#include "..//HardwareBuffer/Resource.h"
#include "..//Description/TextureDesc.h"
#include "..//Enumerations/Include.h"
#include "..//HardwareBuffer/ResourceView.h"
#include "../HardwareBuffer/ResourceDescriptor.h"
#include <cassert>

namespace Engine
{
	namespace GraphicsSystem
	{
		ResourceDescriptor* DepthTexture::s_descriptor;
		uint32_t DepthTexture::s_descriptorCount = 10;
		uint32_t DepthTexture::s_count = 0;

		DepthTexture::DepthTexture(const std::string& name)
			: base(name)
			, m_depthStencilView(nullptr)
		{
		}

		DepthTexture::~DepthTexture()
		{
			delete m_depthStencilView;
		}

		DepthTexture::DepthTexturePtr DepthTexture::Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool shaderResource)
		{
			TextureDesc desc = TextureDesc::Default2D(width, height, format, false, true, false, shaderResource);
			desc.states = ResourceStates::DepthWrite;

			auto texture = std::make_shared<DepthTexture>(name);
			texture->m_resource = Resource::Create(desc);
			texture->m_format = format;
			texture->CreateDepthStencilView();

			// 登録する
			Register(name, texture);

			return texture;
		}

		ResourceView* DepthTexture::GetDepthStencilView() const
		{
			return m_depthStencilView;
		}


		void DepthTexture::CreateDepthStencilView()
		{
			CreateDescriptor();
			m_depthStencilView = ResourceView::Create(s_descriptor, m_resource, ResourceViewType::DepthStencil);
			s_count++;
		}

		void DepthTexture::CreateDescriptor()
		{
			// デスクリプターがないから作成する
			if (!s_descriptor)
			{
				s_descriptor = ResourceDescriptor::CreateDepthStencil(s_descriptorCount);
			}
			// あるけど確保分を超えた作り直しこれまで確保していたものをコピーする
			else if (s_descriptor && s_count >= s_descriptorCount)
			{
				s_descriptorCount += 10;
				ResourceDescriptor* tmp = ResourceDescriptor::CreateRenderTarget(s_descriptorCount);
				for (auto& depthTexture : s_allObjects)
				{
					auto texture = depthTexture.second;

					if (texture->GetInstanceID() == InstanceID::DepthTexture)
					{
						auto depth = std::dynamic_pointer_cast<DepthTexture>(texture);
						depth->m_depthStencilView->Recreate(tmp, depth->m_resource);
					}
				}
				delete s_descriptor;
				s_descriptor = tmp;
			}
		}

	}
}