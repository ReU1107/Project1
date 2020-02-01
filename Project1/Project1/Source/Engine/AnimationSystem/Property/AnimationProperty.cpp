#include "AnimationProperty.h"
#include "../Motion/AnimationCurve.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationProperty::AnimationProperty(size_t elementCount) noexcept
			: m_curves()
		{
			// —v‘f”•ªŠm•Û‚µ‚Ä‚¨‚­
			m_curves.resize(elementCount);
			for (auto& curve : m_curves)
			{
				curve = new AnimationCurve();
			}
		}

		AnimationProperty::~AnimationProperty() noexcept
		{
			Clear();
		}

		AnimationProperty::AnimationCurves& AnimationProperty::GetCurves()
		{
			return m_curves;
		}

		float AnimationProperty::Sort()
		{
			float endTime = 0.0f;
			for (auto& curve : m_curves)
			{
				float frame = curve->Sort();
				if (frame > endTime)
					endTime = frame;
			}
			return endTime;
		}

		void AnimationProperty::Clear()
		{
			for (auto& curve : m_curves) 
			{
				curve->Clear();
			}
		}

		void AnimationProperty::SetTargetPropertyName(const std::string& name)
		{
			m_propertyName = name;
		}

		AnimationCurve* AnimationProperty::GetCurve(const std::string& name) const
		{
			return nullptr;
		}

		AnimationCurve* AnimationProperty::GetCurve(uint32_t index) const
		{
			return m_curves[index];
		}

	}
}