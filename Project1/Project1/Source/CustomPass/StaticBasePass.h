#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"

/*
よく使うものをメンバ変数で持っておく
*/

namespace Engine
{
	namespace GraphicsSystem
	{
		class ResourceDescriptor;
		class ResourceView;
		class RenderTexture;
		class DepthTexture;
		class ConstantBuffer;
	}
};

class StaticBasePass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;
	using DepthTexturePtr = std::shared_ptr<Engine::GraphicsSystem::DepthTexture>;
private:
	DepthTexturePtr m_depth;
	
public:
	// コンストラクタ
	StaticBasePass();
	// デストラクタ
	virtual ~StaticBasePass();

	virtual void OnInitialize() override;

	virtual void OnRender() override;
};