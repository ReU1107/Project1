#pragma once
#include "Behaviour.h"
#include <array>
#include <vector>
#include <list>
#include "Enumerations/LightEvent.h"
#include "Enumerations/LightType.h"
#include "Enumerations/ShadowResolution.h"
#include "../../../Math/Include.h"
#include <iostream>

namespace Engine
{

	class Light final : public  Behaviour
	{
	private:
		using base = Behaviour;
		using LightPtr = std::shared_ptr<Light>;
		using Lights = std::list<LightPtr>;
	public:
		static Lights allLights;					// 全ての光源
		static uint32_t allLigthsCount;				// 全ての光源数
		static LightPtr current;					// 
	private:
		mutable Matrix4x4 m_projectionMatrix;	// プロジェクション変換行列
		mutable Matrix4x4 m_screenMatrix;		// スクリーン(ビューポートスケーリング)変換行列
		Color3 m_color;							// 光源色

		float m_intensity;						// 光源強度
		float m_nearRange;						// 有効範囲
		float m_farRange;						// 有効範囲
		float m_spotOuterAngle;					// スポットライトの角度(外部コーン)
		float m_spotInnerAngle;					// スポットライトの角度(内部コーン)

		LightType m_type;
		mutable bool m_viewMatrixIsDirty;		// ビュー変換行列の設定(Transformの値)変更時更新
		mutable bool m_projMatrixIsDirty;		// プロジェクション変換行列の設定変更時更新
		mutable bool m_shadowMapIsDirty;		// シャドウマップの設定変更時更新
	public:
		Light() noexcept;

		virtual ~Light() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Light; }
		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Light; }
	public:
		// 光源色設定
		void SetColor(const Color3& color);
		void SetColor(float r, float g, float b);

		// 光源が影響を与える距離(Directionalライトは無関係)
		void SetNearRange(float range);
		void SetFarRange(float range);
		// スポットライトの外角設定
		void SetSpotOuterCone(float outer);
		// スポットライトの内角設定
		void SetSpotInnerCone(float inner);

		// 光源のタイプ変更
		void ChangeType(LightType type);

	public:
		// 光源色取得
		const Color3& GetColor() const;

		// 光源強度取得
		float GetIntensity() const;

		float GetNearRange() const;

		float GetFarRange() const;

		float GetSpotInnerAngle() const;

		float GetSpotOuterAngle() const;

		Vector3 GetPosition() const;

		Vector3 GetDirection() const;

		// シャドウマップ用プロジェクション変換行列取得
		const Matrix4x4& GetProjectionMatrix() const;
		// シャドウマップ用スクリーン(ビューポートスケーリング)変換行列取得
		const Matrix4x4& GetScreenMatrix() const;

	public:
		// ライトの種類取得
		LightType GetType() const;
	private:
		void CreateProjectionMatrix() const;
	};

	template<>
	inline std::shared_ptr<Light> Component::Create()
	{
		auto light = std::make_shared<Light>();

		Light::allLights.push_back(light);
		Light::allLigthsCount++;

		return light;
	}
}