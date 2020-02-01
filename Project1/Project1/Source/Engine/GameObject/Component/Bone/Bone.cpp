#include "Bone.h"
#include "../Transform.h"

using namespace DirectX;

namespace Engine
{
	Bone::Bone(const std::string& name, BoneType type) noexcept
		: base(name)
		, m_keyPosePosition(Vector3::Zero)
		, m_keyPoseRotation(Vector4::Identity)
		, m_fixedAxis(Vector3::Zero)
		, m_offsetMatrix(Matrix4x4::Identity)
		, m_keyPoseLocalMatrix(Matrix4x4::Identity)
		, m_keyPoseWorldMatrix(Matrix4x4::Identity)
		, m_keyPoseIsDirty(true)
		, m_type(type)
	{
	}

	Bone::~Bone() noexcept
	{
	}

	void* Bone::GetPropertyAddress(const std::string& name)
	{
		if (name == "keyPosePosition")
		{
			m_keyPoseIsDirty = true;
			return &m_keyPosePosition;
		}
		else if (name == "keyPoseRotation")
		{
			m_keyPoseIsDirty = true;
			return &m_keyPoseRotation;
		}
		return nullptr;
	}

	void Bone::SetOffsetMatrix(const Matrix4x4& offset)
	{
		m_offsetMatrix = offset;
	}

	void Bone::SetFixedAxis(const Vector3& axis)
	{
		m_fixedAxis = axis;
	}

	void Bone::Reset()
	{
		m_keyPosePosition = Vector3::Zero;
		m_keyPoseRotation = Vector4::Identity;

		m_keyPoseIsDirty = true;
	}

	void Bone::LocalRotate(const Vector3& euler)
	{
		auto q1 = XMLoadFloat4(&m_keyPoseRotation);
		auto q2 = XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&euler));
		XMStoreFloat4(&m_keyPoseRotation, XMQuaternionMultiply(q1, q2));

		m_keyPoseIsDirty = true;
	}

	void Bone::LocalRotate(const Vector3& axis, float angle)
	{
		auto q1 = XMLoadFloat4(&m_keyPoseRotation);
		auto q2 = XMQuaternionRotationAxis(XMLoadFloat3(&axis), angle);
		XMStoreFloat4(&m_keyPoseRotation, XMQuaternionMultiply(q1, q2));

		m_keyPoseIsDirty = true;
	}

	void Bone::LocalRotate(const Vector4& rotation)
	{
		auto q1 = XMLoadFloat4(&m_keyPoseRotation);
		auto q2 = XMLoadFloat4(&rotation);
		XMStoreFloat4(&m_keyPoseRotation, XMQuaternionMultiply(q1, q2));

		m_keyPoseIsDirty = true;
	}

	void Bone::LocalRotate(const Matrix4x4& mat)
	{
		auto q1 = XMLoadFloat4(&m_keyPoseRotation);
		auto q2 = XMQuaternionRotationMatrix(XMLoadFloat4x4(&mat));
		XMStoreFloat4(&m_keyPoseRotation, XMQuaternionMultiply(q1, q2));

		m_keyPoseIsDirty = true;
	}

	const Matrix4x4& Bone::GetOffsetMatrix() const
	{
		return m_offsetMatrix;
	}

	const Matrix4x4& Bone::GetKeyPoseMatrix() const
	{
		CalculateMatrix();
		return m_keyPoseWorldMatrix;
	}

	Vector3 Bone::GetWorldPosition() const
	{
		Vector3 vec;
		auto matrix = GetKeyPoseMatrix();
		vec.x = matrix._41;
		vec.y = matrix._42;
		vec.z = matrix._43;
		return vec;
	}

	BoneType Bone::GetType() const
	{
		return m_type;
	}

	void Bone::CalculateMatrix() const
	{
		XMMATRIX keyPoseMatrix = XMLoadFloat4x4(&m_keyPoseLocalMatrix);

		if (m_keyPoseIsDirty)
		{
			const XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&m_keyPoseRotation));
	
			const XMMATRIX translation = XMMatrixTranslationFromVector(XMLoadFloat3(&m_keyPosePosition));

			const XMMATRIX localMatrix = XMLoadFloat4x4(&GetTransform()->GetLocalMatrix());
			keyPoseMatrix = rotation * translation * localMatrix;

			XMStoreFloat4x4(&m_keyPoseLocalMatrix, keyPoseMatrix);
			m_keyPoseIsDirty = false;
		}

		// 親がボーンコンポーネントを持っているならば
		auto parent = GetParent();
		if (parent)
		{
			auto bone = parent->GetComponent<Bone>();
			if (bone)
			{
				const XMMATRIX parentMatrix = XMLoadFloat4x4(&bone->GetKeyPoseMatrix());
				keyPoseMatrix *= parentMatrix;
			}
		}

		XMStoreFloat4x4(&m_keyPoseWorldMatrix, keyPoseMatrix);
	}
}