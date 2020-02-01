#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RaytracingPass.h"

// �ŏ��̃��C�����V�F�[�_�[
static const wchar_t* RayGenerateShader = L"RayGenerateShader";
// �~�X�V�F�[�_�[
static const wchar_t* MissShader = L"MissShader";
// �V���h�E�`�F�b�N�V�F�[�_�[
static const wchar_t* ShadowCheckShader = L"ShadowCheckShader";
// �V���h�E�`�F�b�N�̂݃O���[�v
static const wchar_t* ShadowCheckGroup = L"ShadowCheckGroup";
// �V���h�E�A�A���t�@�`�F�b�N�O���[�v
static const wchar_t* ShadowAlphaCheckGroup = L"ShadowAlphaCheckGroup";

// �V���h�E�`�F�b�N�Ȃ��V�F�[�_�[
static const wchar_t* NoneShadowCheckShader = L"NoneShadowCheckShader";
// �V���h�E�`�F�b�N�Ȃ��O���[�v
static const wchar_t* ShadowNoneCheckGroup = L"ShadowNoneCheckGroup";
// �V���h�E�`�F�b�N�Ȃ��A���t�@�`�F�b�N����O���[�v
static const wchar_t* ShadowNoneAlphaCheckGroup = L"ShadowNoneAlphaCheckGroup";
// �A���t�@�`�F�b�N�V�F�[�_�[
static const wchar_t* AlphaCheckShader = L"AlphaCheckShader";

// �����ɏՓ˂����Ƃ��̃V�F�[�_�[
static const wchar_t* ShadowHitShader = L"ShadowHitShader";
// �����q�b�g���Ȃ������Ƃ��̃V�F�[�_�[
static const wchar_t* ShadowMissShader = L"ShadowMissShader";

// �����ɏՓ˂����Ƃ��̃O���[�v
static const wchar_t* ShadowHitGroup = L"ShadowHitGroup";

namespace Engine
{
	namespace GraphicsSystem
	{
		class ResourceView;
	}
}

class RaytracingShadowPass : public Engine::GraphicsSystem::RaytracingPass
{
private:
	using base = Engine::GraphicsSystem::RaytracingPass;
	using ResourceViewPtr = Engine::GraphicsSystem::ResourceView*;
private:

public:
	// �R���X�g���N�^
	RaytracingShadowPass();
	// �f�X�g���N�^
	virtual ~RaytracingShadowPass();

	// ������
	virtual void OnInitialize() override;

	// ���s
	virtual void OnDispatch() override;

};