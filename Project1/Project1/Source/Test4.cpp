#include "Test4.h"
#include "Engine/Include.h"
#include "CustomPass/BasePass.h"
#include "CustomPass/VolumeRenderingPass.h"
#include "CustomPass/PreZPass.h"
#include "CustomPass/LightingPass.h"
#include "PMX/PMXLoader.h"
#include "Script/CameraController.h"
#include "Script/PlayerController.h"
#include "Script/TerrainController.h"
#include "VMD/VMDLoader.h"
#include "CustomPass/StaticBasePass.h"
#include "CustomPass/LineRenderPass.h"
#include "Script/PMXBoneController.h"
#include "CustomPass/TestPass.h"
#include "WAV/WAVLoader.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Script/WAVSpeaker.h"
#include "Script/BoneDisplay.h"
#include "Script/GroupController.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;
using namespace Engine::SceneManagement;
Scene* s_scene = nullptr;

void Test4::Init(void* hWnd)
{
	Engine::SceneManagement::Startup();
	Engine::ThreadSystem::Startup();
	Engine::GraphicsSystem::Startup(hWnd, 1280, 960);
	Engine::AudioSystem::Startup();

	//SceneManager::Get().RegisterScene<TitleScene>("Title");
	//SceneManager::Get().RegisterScene<GameScene>("Game");

	//auto s = SceneManager::Get().Find("Title");

	GraphicsCommandQueue::Create("Graphics2");
	GraphicsCommandList::Create("Graphics2");
	GraphicsCommandQueue::Create("Graphics3");
	GraphicsCommandList::Create("Graphics3");

	VMDLoader vmdLoader;
	vmdLoader.Load("Assets/ハッピーシンセサイザ配布用モーション/GUMI.vmd");
	//vmdLoader.Load("Assets/SCREAMモーション/1.vmd");
	//vmdLoader.Load("Assets/SCREAMモーション/2.vmd");
	//vmdLoader.Load("Assets/SCREAMモーション/3.vmd");
	//vmdLoader.Load("Assets/SCREAMモーション/リップモーション.vmd");
	//vmdLoader.Load("Assets/極楽浄土/極楽上半身ボーンが長い用.vmd");

	s_scene = new Scene("Test");

	// このようにレンダリングパスを処理する順番に追加していく
	//s_scene->AddRenderingPass(new PreZPass());
	s_scene->AddRenderingPass(new StaticBasePass());
	s_scene->AddRenderingPass(new BasePass());
	s_scene->AddRenderingPass(new LightingPass());
	//s_scene->AddRenderingPass(new TestPass());
	PMXLoader loader;

	//auto test = loader.LoadModel("Assets/AliceX034X5MK5/アリスV034_X5MK5.pmx", true);
	auto test = loader.LoadModel("Assets/どっと式初音ミク_V3_ver.2.02/どっと式初音ミク_V3.pmx", true);
	auto testCon = test->AddComponent<PlayerController>();
	testCon->m_motionFile = "GUMI_N式ver1.06";
	testCon->m_morphFile = "GUMI_N式ver1.06Morph";
	//test->AddComponent<BoneDisplay>();

	//auto test2 = loader.LoadModel("Assets/MarisaV12/魔理沙Ver12.pmx", true);
	//auto test2Con = test2->AddComponent<PlayerController>();
	//test2Con->m_motionFile = "scream2";
	//test2Con->m_morphFile = "scream2Morph";
	//test2->AddComponent<BoneDisplay>();

	//auto test3 = loader.LoadModel("Assets/パチュリーVer2.00/Model/パチュリーVer2.00_Type-C(フル_ポニテB_ミニスカ_ハイヒール)_あずき.pmx", true);
	//auto test3Con = test3->AddComponent<PlayerController>();
	//test3Con->m_motionFile = "scream3";
	//test3Con->m_morphFile = "scream3Morph";
	//test3->AddComponent<BoneDisplay>();

	auto test4 = loader.LoadModel("Assets/神霊廟 ver0.90/神霊廟.pmx");
	test4->AddComponent<TerrainController>();

	auto camera = GameObject::Create("メインカメラ");
	camera->AddComponent<CameraController>();

	auto speaker = GameObject::Create("スピーカー");
	//speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/極楽浄土.wav");
	//speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/fantasy1.wav");
	speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/ハッピーシンセサイザ.wav");
	//speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/scream.wav");

	//auto lightObject = GameObject::Create("メインライト");
	//auto light = lightObject->AddComponent<Light>();
	//light->SetFarRange(400.0f);
	//lightObject->GetTransform()->SetWorldPosition(Vector3(100, 200, -100));

	auto lightObject2 = GameObject::Create("ライト2");
	auto light2 = lightObject2->AddComponent<Light>();
	light2->SetFarRange(400.0f);
	lightObject2->GetTransform()->SetWorldPosition(Vector3(500, 500, -500));

	auto group = GameObject::Create("グループ");
	group->AddChild(test);
	//group->AddChild(test2);
	//group->AddChild(test3);
	group->AddComponent<GroupController>();

	s_scene->AddObject(group);
	s_scene->AddObject(test4);
	s_scene->AddObject(camera);
	s_scene->AddObject(speaker);
	//s_scene->AddObject(lightObject);
	s_scene->AddObject(lightObject2);

	s_scene->Initialize();
}

void Test4::Update(float deltaTime)
{
	s_scene->Update(deltaTime);
}

void Test4::Render()
{
	s_scene->Render();
	auto list = CommandList::Find<GraphicsCommandList>("Graphics");
	auto queue = CommandQueue::Find<GraphicsCommandQueue>("Graphics");

	DBGSTR(" ====== D \n");

	std::shared_ptr<GraphicsCommandList> lists[] = { list };
	queue->ExecuteCommandLists(lists, 1);

	DBGSTR(" ====== E \n");

	queue->WaitExecutionList();

	DBGSTR(" ====== F \n");

	list->Reset();
	DBGSTR(" ====== G \n");

	//GUISystem::W();
	Present();

	DBGSTR(" ====== H \n");

}

void Test4::Fin()
{
	delete s_scene;
	Engine::AudioSystem::Shutdown();
	Engine::GraphicsSystem::Shutdown();
	Engine::ThreadSystem::Shutdown();
	Engine::SceneManagement::Shutdown();

}
