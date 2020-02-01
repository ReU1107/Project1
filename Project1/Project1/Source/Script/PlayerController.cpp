#include "PlayerController.h"
#include "../Engine/Include.h"
#include "../CustomPass/RaytracingShadowPass.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;
using namespace Engine::AnimationSystem;

PlayerController::PlayerController() noexcept
	: base("PlayerController")
	, m_cameraTransform(nullptr)
	, m_shift(false)
{
}

PlayerController::~PlayerController() noexcept
{
}

void PlayerController::OnStart()
{
	auto renderer = GetComponent<SkinnedMeshRenderer>();
	auto mesh = renderer->GetMesh();

	auto rMesh = RaytracingMesh::Create(mesh, 2);
	auto tracer = AddComponent<RayTracer>();
	tracer->SetMesh(rMesh);
	tracer->AddHitGroupName(ShadowCheckGroup);
	tracer->AddHitGroupName(ShadowHitGroup);

	auto motion1 = Motion::Find(m_motionFile);
	auto motion2 = Motion::Find(m_morphFile);

	auto controller = AnimatorController::Create("コントローラー");

	auto body = AnimatorControllerLayer::Create("body");
	auto danceState1 = AnimatorState::Create("dance");

	auto facial = AnimatorControllerLayer::Create("facial");
	auto danceState2 = AnimatorState::Create("dance");

	danceState1->SetMotion(motion1);
	danceState1->SetSpeed(1.0f);
	body->AddState(danceState1);

	danceState2->SetMotion(motion2);
	danceState2->SetSpeed(1.0f);
	facial->AddState(danceState2);
	
	controller->AddLayer(body);
	controller->AddLayer(facial);

	auto anim = GetComponent<Animator>();
	anim->SetController(controller);

}

void PlayerController::OnUpdate(float deltaTime)
{
	auto anim = GetComponent<Animator>();
	if (GetKeyState(VK_SHIFT) & 0x8000)
	{
		m_shift = true;
	}

	if (GetKeyState('V') & 0x8000)
	{
		anim->Play("dance", 0);
		anim->Play("dance", 1);
	}

	auto a = GetComponent<SkinnedMeshRenderer>();
	a->PaletteIsDirty();

	GetComponent<RayTracer>()->ReBuild();

}


