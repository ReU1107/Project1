#pragma once
#include "Behaviour.h"
#include <unordered_map>
#include <string>
#include <cstdint>

namespace Engine 
{

	// �O���錾
	class Motion;
	class AnimationClip;
	class AnimationState;
	// ���̃I�u�W�F�N�g�ɂ��Ă���A�j���[�V�����̐�����s��
	class Animation final : public Behaviour
	{
	private:
		using base = Behaviour;
		using AnimationStates = std::unordered_map<std::string, AnimationState *>;
	private:
		AnimationStates m_states;			// �A�j���[�V�����X�e�[�g�z��
		AnimationClip * m_defaultClip;		// �f�t�H���g���[�V����	
		AnimationState * m_playingState;	// ���ݍĐ����̃Q�[���A�j���[�V����

		bool m_isPlaying;					// �A�j���[�V�������Đ����Ă��邩
	public:
		// �R���X�g���N�^
		Animation() noexcept;
		// �f�X�g���N�^
		~Animation() noexcept;
	private:

	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Animation; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID()const override { return InstanceID::Animation; }
	public:
		// ���[�V�����ǉ�
		AnimationState * AddClip(const std::string & name, Motion * clip);
		AnimationState * AddClip(const std::string & name, AnimationClip * clip);

		// ���[�V�����폜
		void RemoveClip(const std::string & name);

		// ���[�V�����J�n
		void Play(const std::string & name);

		// ���[�V������~
		void Stop(const std::string & name);
	public:
		AnimationState * GetState(const std::string & name);

		// �Đ����̃A�j���[�V�����X�e�[�g�擾
		AnimationState * GetPlayingState() const;

		bool IsPlaying() const { return m_isPlaying; }
	public:
		void Update(float deltaTime);
	};
}