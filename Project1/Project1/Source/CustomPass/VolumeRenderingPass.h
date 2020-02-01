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
	// �R���X�g���N�^
	VolumeRenderingPass();
	// �f�X�g���N�^
	virtual ~VolumeRenderingPass();

	// ����������
	virtual void OnInitialize() override;

	// �p�X��񑗐M
	virtual void OnDispatch() override;

};