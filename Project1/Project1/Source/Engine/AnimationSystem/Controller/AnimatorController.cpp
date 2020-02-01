#include "AnimatorController.h"
#include "AnimatorControllerLayer.h"
#include "AnimatorControllerParameter.h"
#include "../State/AnimatorState.h"
#include "../Motion/Motion.h"

namespace Engine
{
	namespace AnimationSystem
	{

		AnimatorController::AnimatorController(const std::string& name) noexcept
			: base(name)
		{
		}

		AnimatorController::~AnimatorController() noexcept
		{
			m_layers.clear();
			m_parameters.clear();
			m_layerIndices.clear();
			m_parameterIndices.clear();
		}

		AnimatorController::AnimatorControllerPtr AnimatorController::Create(const std::string& name)
		{
			auto controller = std::make_shared<AnimatorController>(name);

			return controller;
		}

		AnimatorController::LayerPtr AnimatorController::AddLayer(const std::string& name)
		{
			auto layer = std::make_shared<AnimatorControllerLayer>(name);
			// çÌèúÇµÇΩèÍèäÇ™Ç†ÇÈÇ»ÇÁóDêÊìIÇ…ë}ì¸
			int32_t size = m_layerIndices.size();
			if (size > 0) 
			{
				int32_t index = m_layerIndices[size];
				m_layerIndices.pop_back();
				m_layers[index] = layer;
			}
			else 
			{
				m_layers.push_back(layer);
			}
			return layer;
		}

		void AnimatorController::AddLayer(LayerPtr layer)
		{
			// çÌèúÇµÇΩèÍèäÇ™Ç†ÇÈÇ»ÇÁóDêÊìIÇ…ë}ì¸
			int32_t size = m_layerIndices.size();
			if (size > 0) 
			{
				int32_t index = m_layerIndices[size];
				m_layerIndices.pop_back();
				m_layers[index] = layer;
			}
			else 
			{
				m_layers.push_back(layer);
			}
		}

		void AnimatorController::AddParameter(ParameterPtr parameter)
		{
			// çÌèúÇµÇΩèÍèäÇ™Ç†ÇÈÇ»ÇÁóDêÊìIÇ…ë}ì¸
			int32_t size = m_parameterIndices.size();
			if (size > 0) 
			{
				int32_t index = m_parameterIndices[size];
				m_parameterIndices.pop_back();
				m_parameters[index] = parameter;
			}
			else 
			{
				m_parameters.push_back(parameter);
			}
		}

		void AnimatorController::MakeUniqueLayer(const std::string& name)
		{
			m_layers.push_back(std::make_shared<AnimatorControllerLayer>(name));
		}

		void AnimatorController::MakeUniqueParameter(const std::string& name)
		{
			m_parameters.push_back(std::make_shared<AnimatorControllerParameter>());
		}

		AnimatorController::AnimatorStatePtr AnimatorController::AddMotion(MotionPtr motion)
		{
			auto state = std::make_shared<AnimatorState>(motion->GetName());
			state->SetMotion(motion);
			return state;
		}

		AnimatorController::AnimatorStatePtr AnimatorController::AddMotion(MotionPtr motion, int32_t layerIndex)
		{
			auto state = std::make_shared<AnimatorState>(motion->GetName());
			state->SetMotion(motion);
			m_layers.at(layerIndex)->AddState(state);
			return state;
		}

		void AnimatorController::RemoveLayer(int32_t index)
		{
			m_layers[index] = nullptr;
			m_layerIndices.push_back(index);
		}

		void AnimatorController::RemoveParameter(int32_t index)
		{
			m_parameters[index] = nullptr;
			m_parameterIndices.push_back(index);
		}

		AnimatorController::LayerPtr AnimatorController::GetLayer(int32_t index)
		{
			// 0ÇÊÇËè¨Ç≥Ç¢Å‡-1Ç»ÇÁç≈èâÇÃlayer
			if (index < 0)
				index = 0;
			return m_layers.at(index);
		}

		void AnimatorController::Update(AvatarPtr avatar, float deltaTime)
		{
			// ëSÇƒÇÃÉåÉCÉÑÅ[ÇçXêV
			for (auto& layer : m_layers)
			{
				layer->Update(avatar, deltaTime);
			}
		}
	}
}