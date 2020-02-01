#include "Light.h"
#include "../Transform.h"

using namespace DirectX;
namespace Engine
{
	Light::Lights Light::allLights;	
	uint32_t Light::allLigthsCount = 0;		
	Light::LightPtr Light::current;	

	Light::Light() noexcept
		: base("Light")
		, m_projectionMatrix(Matrix4x4::Identity)
		, m_screenMatrix(Matrix4x4::Identity)
		, m_color(1.0f, 1.0f, 1.0f)
		, m_intensity(10.0f)
		, m_nearRange(1.0f)
		, m_farRange(1000.0f)
		, m_spotOuterAngle(XMConvertToRadians(45.0f))
		, m_spotInnerAngle(XMConvertToRadians(22.5f))
		, m_type(LightType::Directional)
		, m_viewMatrixIsDirty(true)
		, m_projMatrixIsDirty(true)
		, m_shadowMapIsDirty(true)
	{
	}

	Light::~Light() noexcept
	{

	}

	void Light::SetColor(const Color3& color)
	{
		m_color = color;
	}

	void Light::SetColor(float r, float g, float b)
	{
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
	}

	void Light::SetNearRange(float range)
	{
		m_nearRange = range;
		m_projMatrixIsDirty = true;
	}

	void Light::SetFarRange(float range)
	{
		m_farRange = range;
		m_projMatrixIsDirty = true;
	}

	void Light::SetSpotOuterCone(float outer)
	{
		m_spotOuterAngle = outer;
	}

	void Light::SetSpotInnerCone(float inner)
	{
		m_spotInnerAngle = inner;
	}

	void Light::ChangeType(LightType type)
	{
		m_type = type;
		m_shadowMapIsDirty = true;
	}

	const Color3& Light::GetColor() const
	{
		return m_color;
	}

	float Light::GetIntensity() const
	{
		return m_intensity;
	}

	float Light::GetNearRange() const
	{
		return m_nearRange;
	}

	float Light::GetFarRange() const
	{
		return m_farRange;
	}

	float Light::GetSpotInnerAngle() const
	{
		return m_spotInnerAngle;
	}

	float Light::GetSpotOuterAngle() const
	{
		return m_spotOuterAngle;
	}

	void Light::CreateProjectionMatrix() const
	{
		// ポイントライトは透視投影で
		// ディレクショナルライト,スポットライトは平行投影
		const float width = 1280;
		const float height = 960;
		const float aspect = width / height;
		if (m_type == LightType::Point)
		{
			XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), aspect, m_nearRange, m_farRange));
		}
		else
		{
			XMStoreFloat4x4(&m_projectionMatrix, XMMatrixOrthographicLH(width, height, m_nearRange, m_farRange));
		}
	}

	Vector3 Light::GetPosition() const
	{
		return GetTransform()->GetWorldPosition();
	}

	Vector3 Light::GetDirection() const
	{
		return GetTransform()->Forward();
	}

	const Matrix4x4& Light::GetProjectionMatrix() const
	{
		if (m_projMatrixIsDirty)
		{
			CreateProjectionMatrix();
			m_projMatrixIsDirty = false;
		}

		return m_projectionMatrix;
	}

	const Matrix4x4& Light::GetScreenMatrix() const
	{
		return m_screenMatrix;
	}

	LightType Light::GetType() const
	{
		return m_type;
	}

}