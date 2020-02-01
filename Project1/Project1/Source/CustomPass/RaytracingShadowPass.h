#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RaytracingPass.h"

// 最初のレイ生成シェーダー
static const wchar_t* RayGenerateShader = L"RayGenerateShader";
// ミスシェーダー
static const wchar_t* MissShader = L"MissShader";
// シャドウチェックシェーダー
static const wchar_t* ShadowCheckShader = L"ShadowCheckShader";
// シャドウチェックのみグループ
static const wchar_t* ShadowCheckGroup = L"ShadowCheckGroup";
// シャドウ、アルファチェックグループ
static const wchar_t* ShadowAlphaCheckGroup = L"ShadowAlphaCheckGroup";

// シャドウチェックなしシェーダー
static const wchar_t* NoneShadowCheckShader = L"NoneShadowCheckShader";
// シャドウチェックなしグループ
static const wchar_t* ShadowNoneCheckGroup = L"ShadowNoneCheckGroup";
// シャドウチェックなしアルファチェックありグループ
static const wchar_t* ShadowNoneAlphaCheckGroup = L"ShadowNoneAlphaCheckGroup";
// アルファチェックシェーダー
static const wchar_t* AlphaCheckShader = L"AlphaCheckShader";

// 何かに衝突したときのシェーダー
static const wchar_t* ShadowHitShader = L"ShadowHitShader";
// 何もヒットしなかったときのシェーダー
static const wchar_t* ShadowMissShader = L"ShadowMissShader";

// 何かに衝突したときのグループ
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
	// コンストラクタ
	RaytracingShadowPass();
	// デストラクタ
	virtual ~RaytracingShadowPass();

	// 初期化
	virtual void OnInitialize() override;

	// 実行
	virtual void OnDispatch() override;

};