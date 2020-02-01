#include "RenderTexture.h"
#include "..//D3D12.h"
#include "..//D3D12/D3D12Device.h"
#include "..//Description/TextureDesc.h"
#include "..//Enumerations/Include.h"
#include "..//HardwareBuffer/Resource.h"
#include "..//HardwareBuffer/ResourceView.h"
#include "../HardwareBuffer/ResourceDescriptor.h"
#include <cassert>

namespace Engine
{
	namespace GraphicsSystem
	{
		ResourceDescriptor* RenderTexture::s_descriptor;
		uint32_t RenderTexture::s_descriptorCount = 10;
		uint32_t RenderTexture::s_count = 0;

		RenderTexture::RenderTexture(const std::string& name)
			: base(name)
			, m_renderTargetView(nullptr)
		{
		}

		RenderTexture::~RenderTexture()
		{
			delete m_renderTargetView;
		}

		ResourceView* RenderTexture::GetRenderTargetView() const
		{
			return m_renderTargetView;
		}

		RenderTexture::RenderTexturePtr RenderTexture::Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, bool unorderedAccess, bool shaderResource)
		{
			TextureDesc desc = TextureDesc::Default2D(width, height, format, true, false, unorderedAccess, shaderResource);
			desc.states = ResourceStates::PixelShaderResource;

			auto texture = std::make_shared<RenderTexture>(name);
			texture->m_resource = Resource::Create(desc);
			texture->m_format = format;
			texture->CreateRenderTargetView();

			// 登録する
			Register(name, texture);
			return texture;
		}

		RenderTexture::RenderTexturePtr RenderTexture::Create(const std::string& name, uint32_t width, uint32_t height, ResourceFormat format, uint32_t multiSampleCount, float multiSampleQuality, bool shaderResource)
		{
			TextureDesc desc = TextureDesc::Default2D(width, height, format, true, false, false, shaderResource);
			desc.states = ResourceStates::RenderTarget;
			desc.multiSampleCount = multiSampleCount;
			desc.multiSampleQuality = (uint32_t)multiSampleQuality;

			auto texture = std::make_shared<RenderTexture>(name);
			texture->m_resource = Resource::Create(desc);
			texture->m_format = format;
			texture->CreateRenderTargetView();

			// 登録する
			Register(name, texture);
			return texture;
		}

		void RenderTexture::CreateRenderTargetView()
		{
			CreateDescriptor();
			m_renderTargetView = ResourceView::Create(s_descriptor, m_resource, ResourceViewType::RenderTarget);
			s_count++;
		}

		void RenderTexture::CreateDescriptor()
		{
			// デスクリプターがないから作成する
			if (!s_descriptor)
			{
				s_descriptor = ResourceDescriptor::CreateRenderTarget(s_descriptorCount);
			}
			// あるけど確保分を超えた作り直しこれまで確保していたものをコピーする
			else if (s_descriptor && s_count >= s_descriptorCount)
			{
				s_descriptorCount += 10;
				ResourceDescriptor* tmp = ResourceDescriptor::CreateRenderTarget(s_descriptorCount);
				for (auto& renderTexture : s_allObjects)
				{
					auto texture = renderTexture.second;
					if (texture->GetInstanceID() == InstanceID::RenderTexture)
					{
						auto render = std::dynamic_pointer_cast<RenderTexture>(texture);
						render->m_renderTargetView->Recreate(tmp, render->m_resource);
						s_count++;
					}
				}
				delete s_descriptor;
				s_descriptor = tmp;
			}
		}

	}
}