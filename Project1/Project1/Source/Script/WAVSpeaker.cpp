#include "WAVSpeaker.h"
#include "../Engine/Include.h"

using namespace Engine;
using namespace Engine::AudioSystem;

WAVSpeaker::WAVSpeaker()
{
}

WAVSpeaker::~WAVSpeaker()
{
}

void WAVSpeaker::OnStart()
{
	auto source = AddComponent<AudioSource>();
	m_clip = m_loader.Open(m_filePath);

	source->SetClip(m_clip);

	auto buffer = m_clip->GetCurrentBuffer();
	uint32_t size = m_clip->GetLoadSize();
	m_loader.LoadBuffer(buffer, size);

	m_clip->CallBack = [&]()->void
	{
		auto buffer = m_clip->GetNextBuffer();
		uint32_t size = m_clip->GetLoadSize();
		m_loader.LoadBuffer(buffer, size);
	};
}

void WAVSpeaker::OnUpdate(float deltaTime)
{

	if (GetKeyState('V') & 0x8000)
	{
		m_clip->Start();
	}

}
