#include "TextureDesc.h"
#include "..//Enumerations/Include.h"
#include "..//../Utility/EnumOperator.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		TextureDesc TextureDesc::Default2D(uint32_t width, uint32_t height, ResourceFormat format, bool renderTarget, bool depthStencil, bool unorderedAccess, bool shaderResource)
		{
			TextureDesc desc = {};
			desc.width = width;
			desc.height = height;
			desc.arrayCount = 1;
			desc.dimension = ResourceDimension::Tex2D;

			desc.flags |= (renderTarget) ? ResourceFlags::AllowRenderTarget : ResourceFlags::None;
			desc.flags |= (depthStencil) ? ResourceFlags::AllowDepthStencil : ResourceFlags::None;
			desc.flags |= (unorderedAccess) ? ResourceFlags::AllowUnorderedAccess : ResourceFlags::None;
			desc.flags |= (!shaderResource) ? ResourceFlags::DenyShaderResource : ResourceFlags::None;

			if (depthStencil)
			{
				desc.states = ResourceStates::DepthWrite;
				desc.clearValue.depth = 1.0f;
				desc.clearValue.stencil = 0;
			}
			else
			{
				desc.clearValue.color[0] = 0.0f;
				desc.clearValue.color[1] = 0.0f;
				desc.clearValue.color[2] = 0.0f;
				desc.clearValue.color[3] = 1.0f;
			}

			desc.format = format;
			desc.multiSampleCount = 1;
			desc.multiSampleQuality = 0;
			desc.mipLevel = 1;

			return desc;
		}
	}
}