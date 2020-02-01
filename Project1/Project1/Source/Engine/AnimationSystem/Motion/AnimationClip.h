#pragma once
#include "Motion.h"
#include <unordered_map>
#include "../Enumerations/WrapMode.h"
#include "../../Utility/FrameRate.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// 前方宣言
		class AnimationCurve;
		class AnimationProperty;
		class AnimationEvent;
		class Avatar;
		class AvatarMask;
		struct BodyPart;

		class AnimationClip final : public Motion
		{
		private:
			using base = Motion;
			using AnimationProperties = std::unordered_map<std::string, AnimationProperty*>;
			using AnimationEvents = std::vector<AnimationEvent*>;
		private:
			AnimationProperties m_properties;	// アニメーションプロパティ配列
			AnimationEvents m_events;			// イベント配列

			float m_frameRate;					// フレームレート
			float m_startTime;					// アニメーション開始フレーム
			float m_endTime;					// アニメーション終了フレーム
			float m_lastTime;					// このアニメーションの最後のフレーム
			WrapMode m_wrapMode;				// フレーム外の
			FPS m_fps;							// 再生フレームレート
		public:
			// コンストラクタ
			AnimationClip(const std::string& name) noexcept;
			// デストラクタ
			virtual ~AnimationClip() noexcept;
		public:
			// アニメーションプロパティ追加
			void AddProperty(const std::string& relativePath, const std::string& propertyName, AnimationProperty* property);
			AnimationProperty* AddProperty(const std::string& relativePath, TypeID componentID, const std::string& propertyName);

			void AddProperty(const std::string& name, AnimationProperty* prop);

			// アニメーションイベント追加
			void AddEvent(AnimationEvent* animationEvent);

			// fps設定
			void SetFPS(FPS fps = FPS::Thirty);
			// 開始フレーム設定
			void SetStartTime(float startTime);
			// キーフレーム配列内の最後の時間設定
			void SetEndTime(float endTime);
			// 終了させる時間の設定
			void SetLastTime(float lastTime);

			// アニメーションプロパティ取得
			AnimationProperty* GetProperty(const std::string& name);

			// アニメーションプロパティ数取得
			uint32_t GetPropertyCount() const;

			// フレームレート取得
			float GetFrameRate() const;

			// アニメーションの長さ取得(単位:ミリ秒)
			float GetLength() const;

			// フレーム番号でソート
			void Sort();

			// プロパティ,カーブ削除
			void Clear();

			// 更新
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;

		};
	}
}
	//// ボーン名,フレーム番号よりモーションデータ取得
	//bool GetKeyframe(Keyframe & keyframe, const std::string & boneName, uint32_t frameIndex);