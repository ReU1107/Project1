#pragma once
#include <vector>
#include "../Enumerations/WrapMode.h"
#include "Keyframe.h"

namespace Engine
{
	namespace AnimationSystem
	{

		enum class InterpolationType
		{
			Constant,	// 定数
			Linear,		// 線形
			EaseInOut,	// イーズインアウト
		};

		struct AdjacentKeyframes
		{
			Keyframe lhs;			// 
			Keyframe rhs;			// 
			float s;				// 2つのキーフレーム間の割合 s : (1 -s)
			bool isSingleKeyframe;	// キーフレームが一つしかないため補間不要(lhsのみ使用してください)

		};

		// キーフレームの集合体を持つ
		class AnimationCurve final
		{
		private:
			using Keyframes = std::vector<Keyframe>;
		private:
			Keyframes m_keyframes;		// キーフレーム配列
			float m_endTime;			// キーフレーム配列が終わる時間
			WrapMode m_preWrapMode;		// 
			WrapMode m_postWrapMode;	// 
			bool m_keyframesIsDirty;	// キーフレーム数が変化した
		public:
			// コンストラクタ
			AnimationCurve() noexcept;
			// デストラクタ
			~AnimationCurve() noexcept;

		public:
			// キーフレーム数取得
			uint32_t GetKeyframeCount() const;

			// キーフレーム追加
			void AddKeyframe(const Keyframe& key);
			// キーフレーム削除
			void RemoveKeyframe(uint32_t index);
			// キーフレーム入れ替え
			void MoveKeyframe(uint32_t index, const Keyframe& key);

			// キーフレームで設定したフレーム番号順に並び替え
			float Sort();
			// time時の値取得
			float Evaluate(float time) const;

			AdjacentKeyframes GetAdjacentKeyframes(float time) const;

			void Clear();
			// []
			Keyframe& At(uint32_t index);
			// operator[]演算子オーバーロード
			Keyframe& operator[](uint32_t index);

			//// 補間無し
			//static AnimationCurve* Constant(float timeStart, float timeEnd, float value);
			//// イーズインイーズアウト
			//static AnimationCurve* EaseInOut(float timeStart, float valueStart, float timeEnd, float valueEnd);
			//// 線形補間
			//static AnimationCurve* Linear(float timeStart, float valueStart, float timeEnd, float valueEnd);
		};
	}
}
