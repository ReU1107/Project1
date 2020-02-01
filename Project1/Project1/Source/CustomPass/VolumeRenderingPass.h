#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/ComputePass.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Texture;
		class ConstantBuffer;
	}
}

class VolumeRenderingPass : Engine::GraphicsSystem::ComputePass
{
private:
	using base = Engine::GraphicsSystem::ComputePass;
	using TexturePtr = std::shared_ptr<Engine::GraphicsSystem::Texture>;
private:
	TexturePtr m_result;
	Engine::GraphicsSystem::ConstantBuffer* m_sceneBuffer;

public: 
	// コンストラクタ
	VolumeRenderingPass();
	// デストラクタ
	virtual ~VolumeRenderingPass();

	// 初期化処理
	virtual void OnInitialize() override;

	// パス情報送信
	virtual void OnDispatch() override;

};