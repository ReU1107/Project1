#pragma once
#include "../../Object.h"
#include <vector>

namespace Engine
{
	namespace GraphicsSystem
	{

		// 前方宣言
		struct BlendShapeDeltaPosition;
		struct BlendShapeDeltaNormal;
		struct BlendShapeDeltaTangent;

		class BlendShape final : public Object
		{
		private:
			using base = Object;
			using DeltaPositions = std::vector<BlendShapeDeltaPosition>;
			using DeltaNormals = std::vector<BlendShapeDeltaNormal>;
			using DeltaTangents = std::vector<BlendShapeDeltaTangent>;

		private:
			DeltaPositions m_deltaPositions;// 差分
			DeltaNormals m_deltaNormals;	// 差分
			DeltaTangents m_deltaTangents;	// 差分
			mutable float m_weight;			// 影響度(0～100)
			mutable bool m_weightIsDirty;	// ウェイト値が変更したか

		public:
			// コンストラクタ
			BlendShape(const std::string& name);
			// デストラクタ
			virtual ~BlendShape();
		public:
			// インスタンスID
			static const InstanceID ID() { return InstanceID::BlendShape; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const override { return InstanceID::BlendShape; }

			virtual void* GetPropertyAddress(const std::string& name) override;

		public:

			// ウェイト設定
			void SetWeight(float weight);
		public:
			// 位置差分取得
			DeltaPositions& GetDeltaPositions();
			// 法線差分取得
			DeltaNormals& GetDeltaNormals();
			// 接線差分取得
			DeltaTangents& GetDeltaTangetns();
			// ウェイト取得
			float GetWeight() const;
			// 計算するか
			bool IsCalculated() const;

		};
	}
}

using BlendShapePtr = std::shared_ptr<Engine::GraphicsSystem::BlendShape>;