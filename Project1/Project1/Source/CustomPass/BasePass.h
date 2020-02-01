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

/*
G-Buffer生成パス
*/
class BasePass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;
	using DepthTexturePtr = std::shared_ptr<Engine::GraphicsSystem::DepthTexture>;
private:
	DepthTexturePtr m_depth;

public:
	// コンストラクタ
	BasePass();
	// デストラクタ
	virtual ~BasePass();

	virtual void OnInitialize() override;

	virtual void OnRender() override;
};