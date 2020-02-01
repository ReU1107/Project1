#pragma once
#include "Behaviour.h"
#include <unordered_map>
#include <string>
#include <cstdint>

namespace Engine 
{

	// 前方宣言
	class Motion;
	class AnimationClip;
	class AnimationState;
	// このオブジェクトについているアニメーションの制御を行う
	class Animation final : public Behaviour
	{
	private:
		using base = Behaviour;
		using AnimationStates = std::unordered_map<std::string, AnimationState *>;
	private:
		AnimationStates m_states;			// アニメーションステート配列
		AnimationClip * m_defaultClip;		// デフォルトモーション	
		AnimationState * m_playingState;	// 現在再生中のゲームアニメーション

		bool m_isPlaying;					// アニメーションを再生しているか
	public:
		// コンストラクタ
		Animation() noexcept;
		// デストラクタ
		~Animation() noexcept;
	private:

	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Animation; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID()const override { return InstanceID::Animation; }
	public:
		// モーション追加
		AnimationState * AddClip(const std::string & name, Motion * clip);
		AnimationState * AddClip(const std::string & name, AnimationClip * clip);

		// モーション削除
		void RemoveClip(const std::string & name);

		// モーション開始
		void Play(const std::string & name);

		// モーション停止
		void Stop(const std::string & name);
	public:
		AnimationState * GetState(const std::string & name);

		// 再生中のアニメーションステート取得
		AnimationState * GetPlayingState() const;

		bool IsPlaying() const { return m_isPlaying; }
	public:
		void Update(float deltaTime);
	};
}