#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"

/*
�悭�g�����̂������o�ϐ��Ŏ����Ă���
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
G-Buffer�����p�X
*/
class BasePass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;
	using DepthTexturePtr = std::shared_ptr<Engine::GraphicsSystem::DepthTexture>;
private:
	DepthTexturePtr m_depth;

public:
	// �R���X�g���N�^
	BasePass();
	// �f�X�g���N�^
	virtual ~BasePass();

	virtual void OnInitialize() override;

	virtual void OnRender() override;
};