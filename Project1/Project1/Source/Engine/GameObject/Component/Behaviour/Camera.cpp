#include "Camera.h"
#include "../../GameObject.h"
#include "../Transform.h"
#include "../../../Math/Include.h"
#include "../../../GraphicsSystem/Include.h"
#include "../../../CameraData.h"

using namespace DirectX;
namespace Engine
{
	using namespace GraphicsSystem;

	std::vector<std::shared_ptr<Camera>> Camera::allCameras;	// 全てのカメラ
	uint32_t Camera::allCamerasCount;								// 全てのカメラ数
	std::shared_ptr<Camera> Camera::main;						// メインカメラ
	std::shared_ptr<Camera> Camera::current;					// 現在有効になっているカメラ
	using namespace DirectX;
	
	Camera::Camera() noexcept
		: base("Camera")
		, m_constantBuffer(nullptr)
		, m_projectionMatrix(Matrix4x4::Identity)
		, m_fovAngle(XMConvertToRadians(45.0f))
		, m_width(1280.0f)
		, m_height(720.0f)
		, m_aspect(1280.0f / 720.0f)
		, m_nearClipPlane(1.0f)
		, m_farClipPlane(1000.0f)
		, m_backGroundColor(1.0f, 1.0f, 1.0f, 1.0f)
		, m_projectionType(ProjectionType::Perspective)
		, m_projectionIsDirty(true)
		, m_isActive(true)
		, m_depthTextureMode()
	{
		m_constantBuffer = new ConstantBuffer();
		m_constantBuffer->SetStride(sizeof(CameraData));
		m_constantBuffer->SetCount(1);
		m_constantBuffer->Create();
	}

	Camera::~Camera() noexcept
	{
		delete m_constantBuffer;
	}

	Camera::ConstantBufferPtr Camera::GetConstantBuffer() const
	{
		CameraData data = {};
		data.viewMatrix = GetViewMatrix();
		data.projectionMatrix = GetProjectionMatrix();
		Matrix4x4 viewProjectionMatrix = Matrix4x4::Identity;
		XMStoreFloat4x4(&viewProjectionMatrix, XMMatrixMultiply(XMLoadFloat4x4(&data.viewMatrix), XMLoadFloat4x4(&data.projectionMatrix)));

		data.viewProjectionMatrix = viewProjectionMatrix;
		Matrix4x4 projViewMatrix = Matrix4x4::Identity;
		XMStoreFloat4x4(&projViewMatrix, XMMatrixInverse(nullptr, XMLoadFloat4x4(&viewProjectionMatrix)));
		data.projViewMatrix = projViewMatrix;

		data.position = GetTransform()->GetWorldPosition();

		m_constantBuffer->Update(&data);

		return m_constantBuffer;
	}

	void Camera::SetFovAngle(float fovAngle)
	{
		m_fovAngle = fovAngle;
		m_projectionIsDirty = true;
	}

	void Camera::SetAspect(float aspect)
	{
		m_aspect = aspect;
		m_projectionIsDirty = true;
	}

	void Camera::SetNearClipPlane(float nearClipPlane)
	{
		m_nearClipPlane = nearClipPlane;
		m_projectionIsDirty = true;
	}

	void Camera::SetFarClipPlane(float farClipPlane)
	{
		m_farClipPlane = farClipPlane;
		m_projectionIsDirty = true;
	}

	void Camera::SetProjectionType(ProjectionType projectionType)
	{
		m_projectionType = projectionType;
	}

	void Camera::SetActive(bool isActive)
	{
		m_isActive = isActive;
	}

	void Camera::SetBackGroundColor(const Color4& color)
	{
		m_backGroundColor = color;
	}

	void Camera::SetBackGroundColor(float color)
	{
		m_backGroundColor.r = color;
		m_backGroundColor.g = color;
		m_backGroundColor.b = color;
	}

	const Matrix4x4& Camera::GetViewMatrix() const
	{
		auto transform = GetOwner()->GetTransform();
		return transform->GetWorldToLocal();
	}

	const Matrix4x4& Camera::GetProjectionMatrix() const
	{
		if (m_projectionIsDirty) 
		{
			bool isPerspective = IsPerspective();
			if (isPerspective)
			{
				XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(m_fovAngle, m_aspect, m_nearClipPlane, m_farClipPlane));
			}
			else
			{
				XMStoreFloat4x4(&m_projectionMatrix, XMMatrixOrthographicLH(m_width, m_height, m_nearClipPlane, m_farClipPlane));
			}
			m_projectionIsDirty = false;
		}
		return m_projectionMatrix;
	}

	bool Camera::IsPerspective() const
	{
		if (m_projectionType != ProjectionType::Perspective)
			return false;
		return true;
	}

	bool Camera::IsActive() const
	{
		return m_isActive;
	}

}