#pragma once
#include "../Component.h"
#include "Enumerations/ShadowCastingMode.h"
#include <iostream>

namespace Engine
{
	// 全てのレンダラーの基底クラス
	class Renderer : public Component
	{
	private:
		using base = Component;
	private:
		ShadowCastingMode m_shadowCastingMode;	// シャドウキャスティング方法
		bool m_enabled;							// 表示するか否か
	public:
		// コンストラクタ
		Renderer(const std::string& name) noexcept;
		// デストラクタ
		virtual ~Renderer() noexcept;
	public:
		// ID取得
		static const InstanceID ID() { return InstanceID::Renderer; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Renderer; }

		// 影
		void SetShadowCastingMode(ShadowCastingMode mode);

		// 影を落とすか
		bool CastingShadow();
		// 表示されるか
		bool IsView();

		void Enable(bool enable);

		// 影を落とすか
		ShadowCastingMode GetShadowCastingMode() const;

	};
}