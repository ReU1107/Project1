#pragma once
#include "Behaviour.h"
#include "../../../Math/MathF.h"
#include <memory>
#include <vector>

namespace Engine
{
	namespace AnimationSystem
	{
		// 前方宣言
		class Avatar;
		class Motion;
		class AnimatorController;
	}

	class Transform;

	// アニメータークラス
	class Animator final : public Behaviour
	{
	private:
		using base = Behaviour;
		using TargetAvatar = std::shared_ptr<AnimationSystem::Avatar>;
		using ControllerPtr = std::shared_ptr<AnimationSystem::AnimatorController>;
		using AnimatorPtr = std::shared_ptr<Animator>;
	public:
		static std::vector<AnimatorPtr> allAnimators;
	private:
		TargetAvatar m_avatar;		// Animationを適用するオブジェクト
		ControllerPtr m_controller;	// コントローラー
		bool m_isPlay;				// 再生中か
	public:
		// コンストラクタ
		Animator() noexcept;
		// デストラクタ
		virtual ~Animator() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Animator; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Animator; }

	public:
		// アバター設定
		void SetAvatar(TargetAvatar avatar);
		// コントローラー設定
		void SetController(ControllerPtr controller);

		// アバター取得
		TargetAvatar GetAvatar() const;

		// コントローラー取得
		ControllerPtr GetController();

		// 再生
		void Play(const std::string& stateName, int32_t layerIndex = -1, float normalizedTime = MathF::NegativeInfinity);
		void Play(int32_t stateNameHash, int32_t layerIndex = -1, float normalizedTime = MathF::NegativeInfinity);

		bool IsPlay() const;

		// アニメーション更新
		void Update(float deltaTime);
	};


	template<>
	inline std::shared_ptr<Animator> Component::Create()
	{
		auto animator = std::make_shared<Animator>();

		Animator::allAnimators.push_back(animator);

		return animator;
	}

}