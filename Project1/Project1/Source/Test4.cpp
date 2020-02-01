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
	vmdLoader.Load("Assets/�n�b�s�[�V���Z�T�C�U�z�z�p���[�V����/GUMI.vmd");
	//vmdLoader.Load("Assets/SCREAM���[�V����/1.vmd");
	//vmdLoader.Load("Assets/SCREAM���[�V����/2.vmd");
	//vmdLoader.Load("Assets/SCREAM���[�V����/3.vmd");
	//vmdLoader.Load("Assets/SCREAM���[�V����/���b�v���[�V����.vmd");
	//vmdLoader.Load("Assets/�Ɋy��y/�Ɋy�㔼�g�{�[���������p.vmd");

	s_scene = new Scene("Test");

	// ���̂悤�Ƀ����_�����O�p�X���������鏇�Ԃɒǉ����Ă���
	//s_scene->AddRenderingPass(new PreZPass());
	s_scene->AddRenderingPass(new StaticBasePass());
	s_scene->AddRenderingPass(new BasePass());
	s_scene->AddRenderingPass(new LightingPass());
	//s_scene->AddRenderingPass(new TestPass());
	PMXLoader loader;

	//auto test = loader.LoadModel("Assets/AliceX034X5MK5/�A���XV034_X5MK5.pmx", true);
	auto test = loader.LoadModel("Assets/�ǂ��Ǝ������~�N_V3_ver.2.02/�ǂ��Ǝ������~�N_V3.pmx", true);
	auto testCon = test->AddComponent<PlayerController>();
	testCon->m_motionFile = "GUMI_N��ver1.06";
	testCon->m_morphFile = "GUMI_N��ver1.06Morph";
	//test->AddComponent<BoneDisplay>();

	//auto test2 = loader.LoadModel("Assets/MarisaV12/������Ver12.pmx", true);
	//auto test2Con = test2->AddComponent<PlayerController>();
	//test2Con->m_motionFile = "scream2";
	//test2Con->m_morphFile = "scream2Morph";
	//test2->AddComponent<BoneDisplay>();

	//auto test3 = loader.LoadModel("Assets/�p�`�����[Ver2.00/Model/�p�`�����[Ver2.00_Type-C(�t��_�|�j�eB_�~�j�X�J_�n�C�q�[��)_������.pmx", true);
	//auto test3Con = test3->AddComponent<PlayerController>();
	//test3Con->m_motionFile = "scream3";
	//test3Con->m_morphFile = "scream3Morph";
	//test3->AddComponent<BoneDisplay>();

	auto test4 = loader.LoadModel("Assets/�_��_ ver0.90/�_��_.pmx");
	test4->AddComponent<TerrainController>();

	auto camera = GameObject::Create("���C���J����");
	camera->AddComponent<CameraController>();

	auto speaker = GameObject::Create("�X�s�[�J�[");
	//speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/�Ɋy��y.wav");
	//speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/fantasy1.wav");
	speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/�n�b�s�[�V���Z�T�C�U.wav");
	//speaker->AddComponent<WAVSpeaker>()->SetFilePath("Assets/scream.wav");

	//auto lightObject = GameObject::Create("���C�����C�g");
	//auto light = lightObject->AddComponent<Light>();
	//light->SetFarRange(400.0f);
	//lightObject->GetTransform()->SetWorldPosition(Vector3(100, 200, -100));

	auto lightObject2 = GameObject::Create("���C�g2");
	auto light2 = lightObject2->AddComponent<Light>();
	light2->SetFarRange(400.0f);
	lightObject2->GetTransform()->SetWorldPosition(Vector3(500, 500, -500));

	auto group = GameObject::Create("�O���[�v");
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
