#pragma once
#include "../Engine/GameObject/Component/Include.h"
#include "../WAV/WAVLoader.h"

class WAVSpeaker : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:
	std::string m_filePath;
	WAVLoader m_loader;
	std::shared_ptr<Engine::AudioSystem::AudioClip> m_clip;
public:
	// コンストラクタ
	WAVSpeaker();
	// デストラクタ
	virtual ~WAVSpeaker();

public:

	void SetFilePath(const std::string& filePath) { m_filePath = filePath; }

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;

};
