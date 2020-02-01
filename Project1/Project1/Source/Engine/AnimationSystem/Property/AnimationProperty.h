#pragma once
#include <vector>
#include <string>
#include <memory>

namespace Engine
{
	class Object;

	namespace AnimationSystem
	{
		// 前方宣言
		class Avatar;
		class AvatarMask;
		class AnimationCurve;

		// アニメーションプロパティ(アニメーション属性)
		class AnimationProperty
		{
		private:
			using AnimationCurves = std::vector<AnimationCurve*>;
			using ObjectPtr = std::shared_ptr<Object>;
		protected:
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;

		protected:
			AnimationCurves m_curves;	// アニメーションカーブ配列
			std::string m_propertyName;	// 
			std::string m_targetName;	// 
			ObjectPtr m_targetObject;	// 
		public:
			// コンストラクタ
			AnimationProperty(size_t elementCount) noexcept;
			// デストラクタ
			virtual ~AnimationProperty() noexcept;
		public:
			// ソート
			float Sort();

			// クリア
			void Clear();

			// 動かす予定のオブジェクトの変数名設定
			void SetTargetPropertyName(const std::string& name);

			// 
			void SetTargetName(const std::string& name) { m_targetName = name; }

			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) = 0;

			virtual void Reset(AvatarPtr avatar, AvatarMaskPtr mask) = 0;

			// アニメーションカーブ取得
			AnimationCurve* GetCurve(const std::string& name) const;

			// アニメーションカーブ取得
			AnimationCurve* GetCurve(uint32_t index) const;

			// アニメーションカーブ配列取得
			AnimationCurves& GetCurves();

		};
	}
}

/*
	private:
		using AnimationCurves = std::unordered_map<std::string, AnimationCurve *>;
	private:
		AnimationCurves m_curves;	// カーブ配列
*/

		//// 
		//void TransformUpdate(const BodyPart & part, float frame);
		//// 
		//void SkinnedMeshRendererUpdate(const BodyPart & part, float frame);

		//void BlendShapeUpdate();

		//// マテリアルの値を変更
		//void MaterialUpdate();

