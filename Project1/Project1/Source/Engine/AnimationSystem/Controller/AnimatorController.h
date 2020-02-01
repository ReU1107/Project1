#pragma once
#include <vector>
#include <memory>
#include "../../Object.h"

/*
レイヤーの分け方unity参照
例:
身体を動かすステートマシーンが入っているなら
name Body; StateMachineに↑に検討するモーションを設定
顔(モーフィング等)のステートマシーンがあるなら
name Face; StateMachineに↑に検討するモーションを設定

*/
namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;
		class Avatar;
		class AnimatorControllerParameter;

		// 前方宣言
		class AnimatorControllerLayer;
		class AnimatorState;

		// アニメーター制御クラス
		class AnimatorController final : public Object
		{
		private:
			using base = Object;
			using LayerPtr = std::shared_ptr<AnimatorControllerLayer>;
			using Layers = std::vector<LayerPtr>;
			using ParameterPtr = std::shared_ptr<AnimatorControllerParameter>;
			using Parameters = std::vector<ParameterPtr>;
			using AnimatorStatePtr = std::shared_ptr<AnimatorState>;
			using MotionPtr = std::shared_ptr<Motion>;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using RemoveIndices = std::vector<int32_t>;
			using AnimatorControllerPtr = std::shared_ptr<AnimatorController>;
		private:
			Layers m_layers;					// レイヤー配列
			Parameters m_parameters;			// パラメーター配列
			RemoveIndices m_layerIndices;		// レイヤー配列内で削除した番号を記憶
			RemoveIndices m_parameterIndices;	// パラメータ配列内で削除した番号を記憶

		public:
			// コンストラクタ
			AnimatorController(const std::string& name) noexcept;
			// デストラクタ
			virtual ~AnimatorController() noexcept;

			static AnimatorControllerPtr Create(const std::string& name);

		public:
			// レイヤー追加
			LayerPtr AddLayer(const std::string& name);
			void AddLayer(LayerPtr layer);
			// パラメータ追加
			void AddParameter(ParameterPtr parameter);
			// 
			void MakeUniqueLayer(const std::string& name);
			// 
			void MakeUniqueParameter(const std::string& name);

			// モーション追加
			AnimatorStatePtr AddMotion(MotionPtr motion);
			AnimatorStatePtr AddMotion(MotionPtr motion, int32_t layerIndex);

			// レイヤー削除
			void RemoveLayer(int32_t index);
			void RemoveParameter(int32_t index);

			// レイヤー取得
			LayerPtr GetLayer(int32_t index);

			// 更新
			void Update(AvatarPtr avatar, float deltaTime);
		};
	}

}

using AnimatorControllerPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorController>;