#include "AnimationClip.h"
#include "../Property/AnimationProperty.h"
#include "../../Utility/FrameRate.h"
#include "../State/AnimationEvent.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationClip::AnimationClip(const std::string& name) noexcept
			: base(name)
			, m_frameRate(DeltaTime30)
			, m_startTime(0.0f)
			, m_endTime(0.0f)
			, m_lastTime(0.0f)
			, m_wrapMode(WrapMode::Once)
			, m_fps(FPS::Thirty)
		{
		}

		AnimationClip::~AnimationClip() noexcept
		{
			for (auto& property : m_properties)
			{
				delete property.second;
			}
			m_properties.clear();
			for (auto& event : m_events) 
			{
				delete event;
			}
			m_events.clear();
		}

		void AnimationClip::AddProperty(const std::string& relativePath, const std::string& propertyName, AnimationProperty* property)
		{
		}

		AnimationProperty* AnimationClip::AddProperty(const std::string& relativePath, TypeID componentID, const std::string& propertyName)
		{
			const auto& it = m_properties.find("");

			return nullptr;
		}

		void AnimationClip::AddProperty(const std::string& name, AnimationProperty* prop)
		{
			m_properties.insert({ name,prop });
		}

		void AnimationClip::AddEvent(AnimationEvent* animationEvent)
		{
			m_events.push_back(animationEvent);
		}

		void AnimationClip::SetFPS(FPS fps)
		{
			m_frameRate = fps == FPS::Thirty ? DeltaTime30 : DeltaTime60;
			m_fps = fps;
		}

		void AnimationClip::SetStartTime(float startTime)
		{
			// 0.0以上にクランプ
			m_startTime = (std::max)(startTime, 0.0f);
		}

		void AnimationClip::SetEndTime(float endTime)
		{
			m_endTime = endTime;
		}

		void AnimationClip::SetLastTime(float lastTime)
		{
			// end以下にクランプ
			m_lastTime = (std::min)(lastTime, m_endTime);
		}

		AnimationProperty* AnimationClip::GetProperty(const std::string& name)
		{
			const auto& it = m_properties.find(name);
			if (it != m_properties.cend()) 
			{
				return (*it).second;
			}
			return nullptr;
		}

		uint32_t AnimationClip::GetPropertyCount() const
		{
			return (uint32_t)m_properties.size();
		}

		float AnimationClip::GetFrameRate() const
		{
			return m_frameRate;
		}

		float AnimationClip::GetLength() const
		{
			return (m_lastTime - m_startTime);
		}

		void AnimationClip::Sort()
		{
			for (auto& property : m_properties) 
			{
				float endTime = property.second->Sort();
				if (endTime > m_endTime)
					m_endTime = endTime;
			}
		}

		void AnimationClip::Clear()
		{
			for (auto& property : m_properties)
			{
				property.second->Clear();
			}
		}

		void AnimationClip::Update(AvatarPtr avatar, AvatarMaskPtr mask, float localTime, float weight)
		{
			// パーツの所属がマスク対象なら無視する
			// 例: 左腕　avatarMask::LeftAramなら処理しない

			for (auto& property : m_properties)
			{
				const auto& targetName = property.first;
				property.second->Reset(avatar, mask);
			}

			for (auto& property : m_properties) 
			{
				const auto& targetName = property.first;
				property.second->Update(avatar, mask, localTime, weight);
			}
		}

	}
}
