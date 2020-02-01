#include "AnimationCurve.h"
#include "Keyframe.h"
#include "../../Math/CurveHelper.h"
#include "../../Math/MathF.h"
#include <algorithm>
#include <cassert>

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationCurve::AnimationCurve() noexcept
			: m_preWrapMode(WrapMode::Once)
			, m_postWrapMode(WrapMode::Once)
			, m_keyframesIsDirty(false)
			, m_endTime(0.0f)
		{
		}

		AnimationCurve::~AnimationCurve() noexcept
		{
		}

		uint32_t AnimationCurve::GetKeyframeCount() const
		{
			return m_keyframes.size();
		}

		void AnimationCurve::AddKeyframe(const Keyframe& key)
		{
			m_keyframes.push_back(key);
			m_keyframesIsDirty = true;
		}

		void AnimationCurve::RemoveKeyframe(uint32_t index)
		{
			uint32_t keyframeCount = m_keyframes.size();
			for (uint32_t i = index; i < keyframeCount; ++i)
			{
				m_keyframes.at(i) = m_keyframes.at(i + 1);
			}
			m_keyframesIsDirty = true;
		}

		void AnimationCurve::MoveKeyframe(uint32_t index, const Keyframe& keyframe)
		{
			m_keyframes.at(index) = keyframe;
			m_keyframesIsDirty = true;
		}

		float AnimationCurve::Sort()
		{
			if (m_keyframesIsDirty)
			{
				if (m_keyframes.size() > 0)
				{
					std::sort(m_keyframes.begin(), m_keyframes.end(),
						[](const Keyframe& lhs, const Keyframe& rhs)
						{
							return lhs.time < rhs.time;
						});

					m_endTime = m_keyframes.back().time;
				}
				m_keyframesIsDirty = false;
			}
			return m_endTime;
		}

		float AnimationCurve::Evaluate(float time) const
		{
			AdjacentKeyframes keyframes = GetAdjacentKeyframes(time);

			if (keyframes.isSingleKeyframe)
			{
				return keyframes.lhs.value;
			}

			// 引数値に最も近い値を返す
			float value = 0.0f;

			// 左右の値を補間
			const Keyframe& lhs = keyframes.lhs;
			const Keyframe& rhs = keyframes.rhs;

			float startTime = lhs.time;
			float startValue = lhs.GetValue();
			float startTangent = lhs.outTangent;

			float endTime = rhs.time;
			float endValue = rhs.GetValue();
			float endTangent = rhs.outTangent;

			// 補間方法はどうなるのか
			// 線形補間
			// イーズインイーズアウト
			InterpolationType m_type = InterpolationType::Linear;
			switch (m_type)
			{
			case InterpolationType::Constant:
				break;
			case InterpolationType::Linear:
				value = LinearInterpolation(time, startTime, startValue, endTime, endValue);
				break;
			case InterpolationType::EaseInOut:
				value = EaseInOutInterpolation(time, startTime, startValue, startTangent, endTime, endValue, endTangent);
				break;
			default:
				break;
			}

			return value;
		}

		AdjacentKeyframes AnimationCurve::GetAdjacentKeyframes(float time) const
		{
			AdjacentKeyframes result = {};
			result.isSingleKeyframe = false;

			uint32_t keyframeCount = m_keyframes.size();
			// キーフレームが1つしかないなら
			if (keyframeCount <= 1)
			{
				result.isSingleKeyframe = true;
				result.lhs = m_keyframes[0];
				result.rhs = m_keyframes[0];
				result.s = 0.0f;

				return result;
			}
			// 一番最後のキーフレームの時間を超えていたら
			if (time >= m_endTime + MathF::Epsilon)
			{
				result.isSingleKeyframe = true;
				result.lhs = m_keyframes.back();
				result.rhs = m_keyframes.back();
				result.s = 0.0f;

				return result;
			}

			/*
			KeyframeがSortされている(time順に並んでいる)と仮定
			2分探索ができる
			sort関数を必ず呼ぶためにダーティフラグをしようする??
			*/
			uint32_t left = 0;
			uint32_t middle = 0;
			uint32_t right = keyframeCount - 1;
			do
			{
				middle = (left + right) / 2;
				// middleの時間の方が大きい≒timeは真ん中より前にある≒最大値を減らす
				if (m_keyframes.at(middle).time > time)
				{
					right = middle;
				}
				else
				{
					left = middle;
				}

			} while (left + 1 < right);

			result.lhs = m_keyframes.at(left);
			result.rhs = m_keyframes.at(right);

			result.s = ((time - result.lhs.time) / (result.rhs.time - result.lhs.time));


			return result;
		}

		void AnimationCurve::Clear()
		{
			m_keyframes.clear();
			m_keyframesIsDirty = true;
		}

		Keyframe& AnimationCurve::At(uint32_t index)
		{
			assert(index < m_keyframes.size());
			return m_keyframes.at(index);
		}

		Keyframe& AnimationCurve::operator[](uint32_t index)
		{
			return m_keyframes[index];
		}

	}
}