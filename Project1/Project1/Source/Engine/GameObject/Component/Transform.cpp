#include "Transform.h"
#include "../../Math/Include.h"
#include "../GameObject.h"

using namespace DirectX;

namespace Engine
{

	Transform::Transform() noexcept
		: base("Transform")
		, m_localToWorld(Matrix4x4::Identity)
		, m_worldToLocal(Matrix4x4::Identity)
		, m_localRotation(Vector4::Identity)
		, m_localPosition(Vector3::Zero)
		, m_localScale(1.0f, 1.0f, 1.0f)
		, m_localToWorldIsDirty(true)
	{
	}

	Transform::~Transform() noexcept
	{

	}

	void* Transform::GetPropertyAddress(const std::string& name)
	{
		return nullptr;
	}

	void Transform::SetLocalPosition(const Vector3& position)
	{
		m_localPosition = position;
		m_localToWorldIsDirty = true;
	}

	void Transform::SetLocalPosition(float x, float y, float z)
	{
		m_localPosition.x = x;
		m_localPosition.y = y;
		m_localPosition.z = z;
		m_localToWorldIsDirty = true;
	}

	void Transform::SetWorldPosition(const Vector3& position)
	{
		auto parent = GetOwner()->GetParent();
		if (parent) 
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				transform->InverseTransformPoint(position);
			}
		}
		SetLocalPosition(position);
	}

	void Transform::SetWorldPosition(float x, float y, float z)
	{
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				transform->InverseTransformPoint(Vector3(x, y, z));
			}
		}
		SetLocalPosition(Vector3(x, y, z));
	}

	void Transform::SetLocalScale(const Vector3& scale)
	{
		m_localScale = scale;
		m_localToWorldIsDirty = true;
	}

	void Transform::SetLocalScale(float x, float y, float z)
	{
		m_localScale.x = x;
		m_localScale.y = y;
		m_localScale.z = z;
		m_localToWorldIsDirty = true;
	}

	void Transform::SetLocalRotation(const Vector3& euler)
	{
		XMStoreFloat4(&m_localRotation, XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&euler)));
	}

	void Transform::SetLocalRotation(const Vector4& rotation)
	{
		m_localRotation = rotation;
		m_localToWorldIsDirty = true;
	}

	void Transform::SetWorldRotation(const Vector4& rotation)
	{
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				Matrix4x4 localToWorld = transform->GetLocalToWorld();
				XMVECTOR worldScale;
				XMVECTOR worldRotation;
				XMVECTOR worldPosition;

				XMMatrixDecompose(&worldScale, &worldRotation, &worldPosition, XMLoadFloat4x4(&localToWorld));
				XMVECTOR inverseRotation = XMQuaternionInverse(worldRotation);

				Vector4 localRotation;
				XMStoreFloat4(&localRotation, XMQuaternionMultiply(XMLoadFloat4(&rotation), inverseRotation));
				SetLocalRotation(localRotation);
			}
			else
			{
				SetLocalRotation(rotation);
			}
		}
		else
		{
			SetLocalRotation(rotation);
		}
	}

	void Transform::HasChanged(bool recurse)
	{
		m_localToWorldIsDirty = true;
		if (recurse) 
		{
			uint32_t childCount = GetOwner()->GetChildCount();
			for (uint32_t i = 0; i < childCount; ++i) 
			{
				GetOwner()->GetChildByIndex(i)->GetTransform()->HasChanged(true);
			}
		}
	}

	Vector3 Transform::GetLocalPosition() const
	{
		return m_localPosition;
	}

	Vector3 Transform::GetWorldPosition() const
	{
		auto parent = GetOwner()->GetParent();
		if (parent) 
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				// 親を含めた再計算を行う
				Matrix4x4 localToWorld = GetLocalToWorld();
				return Vector3(localToWorld._41, localToWorld._42, localToWorld._43);
			}
			else
			{
				return GetLocalPosition();
			}
		}
		else 
		{
			return GetLocalPosition();
		}
	}

	Vector4 Transform::GetLocalRotation() const
	{
		return m_localRotation;
	}

	Vector4 Transform::GetWorldRotation() const
	{
		Matrix4x4 localToWorld = GetLocalToWorld();

		XMVECTOR worldScale;
		XMVECTOR worldRotation;
		XMVECTOR worldPosition;
		XMMatrixDecompose(&worldScale, &worldRotation, &worldPosition, XMLoadFloat4x4(&localToWorld));

		Vector4 rotation;
		XMStoreFloat4(&rotation, worldRotation);

		return rotation;
	}

	const Matrix4x4& Transform::GetLocalToWorld() const
	{
		CalculateMatrix();
		return m_localToWorld;
	}

	const Matrix4x4& Transform::GetWorldToLocal() const
	{
		CalculateMatrix();
		return m_worldToLocal;
	}

	bool Transform::IsDirty() const
	{
		return m_localToWorldIsDirty;
	}

	void Transform::LocalTranslate(const Vector3& displacement)
	{
		m_localPosition += displacement;
		m_localToWorldIsDirty = true;
	}

	void Transform::WorldTranslate(const Vector3& displacement)
	{
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				// 親のローカル→ワールド変換行列を掛ける
				// 親のローカル変位に変更
				Matrix4x4 parentWorldToLocal = transform->GetWorldToLocal();

				Vector3 localDisplacement;
				XMStoreFloat3(&localDisplacement, XMVector3TransformCoord(XMLoadFloat3(&displacement), XMLoadFloat4x4(&parentWorldToLocal)));
				LocalTranslate(localDisplacement);
			}
		}
		else
		{
			LocalTranslate(displacement);
		}
	}

	void Transform::LocalRotate(const Vector3& euler)
	{
		XMVECTOR quaternion1 = XMLoadFloat4(&m_localRotation);
		XMVECTOR quaternion2 = XMQuaternionRotationRollPitchYaw(euler.x, euler.y, euler.z);
		XMStoreFloat4(&m_localRotation, XMQuaternionMultiply(quaternion2, quaternion1));

		m_localToWorldIsDirty = true;
	}

	void Transform::LocalRotate(const Vector3& axis, float angle)
	{
		XMVECTOR quaternion1 = XMLoadFloat4(&m_localRotation);
		XMVECTOR quaternion2 = XMQuaternionRotationAxis(XMLoadFloat3(&axis), angle);
		XMStoreFloat4(&m_localRotation, XMQuaternionMultiply(quaternion2, quaternion1));

		m_localToWorldIsDirty = true;
	}

	void Transform::LocalRotate(const Vector4& rotation)
	{
		XMVECTOR quaternion1 = XMLoadFloat4(&m_localRotation);
		XMVECTOR quaternion2 = XMLoadFloat4(&rotation);
		XMStoreFloat4(&m_localRotation, XMQuaternionMultiply(quaternion2, quaternion1));

		m_localToWorldIsDirty = true;
	}

	void Transform::WorldRotate(const Vector3& euler)
	{
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				// 親のローカル空間に変換
				XMMATRIX parentWorldToLocal = XMLoadFloat4x4(&transform->GetWorldToLocal());
				XMStoreFloat4(&m_localRotation, XMVector3TransformCoord(XMLoadFloat4(&m_localRotation), parentWorldToLocal));
			}
		}
		LocalRotate(euler);
	}

	void Transform::WorldRotate(const Vector3& axis, float angle)
	{
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				// 親のローカル空間に変換
				XMMATRIX parentWorldToLocal = XMLoadFloat4x4(&transform->GetWorldToLocal());
				XMStoreFloat4(&m_localRotation, XMVector3TransformCoord(XMLoadFloat4(&m_localRotation), parentWorldToLocal));
			}
		}
		LocalRotate(axis, angle);
	}

	void Transform::LookAt(const Vector3& worldPosition, const Vector3& worldUp)
	{
		XMVECTOR targetLocalPosition = {};
		XMVECTOR localUp = {};
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				XMMATRIX parentWorldToLocal = XMLoadFloat4x4(&transform->GetWorldToLocal());
				targetLocalPosition = XMVector3TransformCoord(XMLoadFloat3(&worldPosition), parentWorldToLocal);

				localUp = XMVector3TransformNormal(XMLoadFloat3(&worldUp), parentWorldToLocal);
			}
		}
		else
		{
			targetLocalPosition = XMLoadFloat3(&worldPosition);
			localUp = XMLoadFloat3(&worldUp);
		}

		XMVECTOR myLocalPosition = XMLoadFloat4(&Vector4(GetLocalPosition().x, GetLocalPosition().y, GetLocalPosition().z, 1.0f));

		// Z軸ベクトル
		// 向きベクトル情報(ターゲットの位置より自身の移動成分を引く)
		XMVECTOR zAxis = XMVectorSubtract(targetLocalPosition, myLocalPosition);
		zAxis = XMVector3Normalize(zAxis);

		// 仮のY軸ベクトル
		XMVECTOR yAxis = XMVector3Normalize(localUp);

		// X軸ベクトル
		XMVECTOR xAxis = XMVector3Cross(yAxis, zAxis);
		xAxis = XMVector3Normalize(xAxis);

		// 真のY軸ベクトル
		yAxis = XMVector3Cross(zAxis, xAxis);
		yAxis = XMVector3Normalize(yAxis);

		// 回転行列
		XMMATRIX rotationMatrix;
		rotationMatrix.r[0] = xAxis;
		rotationMatrix.r[1] = yAxis;
		rotationMatrix.r[2] = zAxis;
		rotationMatrix.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		// 回転用四元数取り出し
		XMVECTOR localRotation = XMQuaternionRotationMatrix(rotationMatrix);
		XMStoreFloat4(&m_localRotation, localRotation);

		m_localToWorldIsDirty = true;
	}

	void Transform::LookAt(float x, float y, float z, const Vector3& worldUp)
	{
		LookAt(Vector3(x, y, z), worldUp);
	}

	void Transform::LookAt(std::shared_ptr<GameObject> gameObject, const Vector3& worldUp)
	{
		LookAt(gameObject->GetTransform(), worldUp);
	}

	void Transform::LookAt(std::shared_ptr<Transform> transform, const Vector3& worldUp)
	{
		LookAt(transform->GetWorldPosition(), worldUp);
	}

	void Transform::RotateAround(const Vector3& point, const Vector3& axis, float radian)
	{
		XMMATRIX pointMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&point));
		XMMATRIX pointInverseMatrix = XMMatrixInverse(&XMLoadFloat3(&point), pointMatrix);

		// 回転行列
		XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(XMQuaternionRotationAxis(XMLoadFloat3(&axis), radian));

		Matrix4x4 localMatrix = GetLocalMatrix();

		// 指定空間に変換
		XMMATRIX compositionMatrix = XMMatrixMultiply(XMLoadFloat4x4(&localMatrix), pointInverseMatrix);
		auto parent = GetOwner()->GetParent();
		if (parent)
		{
			auto transform = parent->GetTransform();
			if (transform)
 {
				// この時に親のローカル→ワールドを使っている為
				// 親がいる場合は逆行列を掛けて打ち消す
				Matrix4x4 parentWorldToLocal = transform->GetWorldToLocal();
				compositionMatrix = XMMatrixMultiply(compositionMatrix, XMLoadFloat4x4(&parentWorldToLocal));
			}
		}
		// 回転
		compositionMatrix = XMMatrixMultiply(compositionMatrix, rotationMatrix);
		// 
		compositionMatrix = XMMatrixMultiply(compositionMatrix, pointMatrix);

		// 移動成分取り出し
		XMStoreFloat3(&m_localPosition, compositionMatrix.r[3]);
		// 回転成分取り出し
		XMStoreFloat4(&m_localRotation, XMQuaternionRotationMatrix(compositionMatrix));

		m_localToWorldIsDirty = true;
	}

	Vector3 Transform::Forward() const
	{
		Matrix4x4 matrix = GetLocalToWorld();
		XMVECTOR zVector = XMVectorSet(matrix._31, matrix._32, matrix._33, 1.0f);
		Vector3 value;
		XMStoreFloat3(&value, XMVector3Normalize(zVector));
		return value;
	}

	Vector3 Transform::Backward() const
	{
		Vector3 backward = Forward() * -1.0f;
		return backward;
	}

	Vector3 Transform::Right() const
	{
		Matrix4x4 matrix = GetLocalToWorld();
		XMVECTOR xVector = XMVectorSet(matrix._11, matrix._12, matrix._13, 1.0f);
		Vector3 value;
		XMStoreFloat3(&value, XMVector3Normalize(xVector));
		return value;
	}

	Vector3 Transform::Left() const
	{
		Vector3 left = Right() * -1.0f;
		return left;
	}

	Vector3 Transform::Up() const
	{
		Matrix4x4 matrix = GetLocalToWorld();
		XMVECTOR yVector = XMVectorSet(matrix._21, matrix._22, matrix._23, 1.0f);
		Vector3 value;
		XMStoreFloat3(&value, XMVector3Normalize(yVector));
		return value;
	}

	Vector3 Transform::Down() const
	{
		Vector3 down = Up() * -1.0f;
		return down;
	}

	Vector3 Transform::TransformDirection(const Vector3& direction)
	{
		Matrix4x4 matrix = GetLocalToWorld();
		// 移動成分除去
		matrix._41 = 0;
		matrix._42 = 0;
		matrix._43 = 0;

		// スケーリング成分正規化
		XMVECTOR xVector = XMVectorSet(matrix._11, matrix._12, matrix._13, 0.0f);
		XMVECTOR yVector = XMVectorSet(matrix._21, matrix._22, matrix._23, 0.0f);
		XMVECTOR zVector = XMVectorSet(matrix._31, matrix._32, matrix._33, 0.0f);

		XMVector3Normalize(xVector);
		XMVector3Normalize(yVector);
		XMVector3Normalize(zVector);

		XMMATRIX tmp;
		tmp.r[0] = xVector;
		tmp.r[1] = xVector;
		tmp.r[2] = zVector;
		tmp.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		Vector3 transform;
		XMStoreFloat3(&transform, XMVector3TransformCoord(XMLoadFloat3(&direction), tmp));

		return transform;
	}

	Vector3 Transform::TransformPoint(const Vector3& point)
	{
		Matrix4x4 matrix = GetLocalToWorld();

		Vector3 transform;

		XMStoreFloat3(&transform, XMVector3TransformCoord(XMLoadFloat3(&point), XMLoadFloat4x4(&matrix)));

		return transform;
	}

	Vector3 Transform::TransformVector(const Vector3& vector)
	{
		Matrix4x4 matrix = GetLocalToWorld();
		// 移動成分除去
		matrix._41 = 0;
		matrix._42 = 0;
		matrix._43 = 0;

		Vector3 transform;

		XMStoreFloat3(&transform, XMVector3TransformCoord(XMLoadFloat3(&vector), XMLoadFloat4x4(&matrix)));

		return transform;
	}

	Vector3 Transform::InverseTransformDirection(const Vector3& direction)
	{
		Matrix4x4 matrix = GetWorldToLocal();
		// 移動成分除去
		matrix._41 = 0;
		matrix._42 = 0;
		matrix._43 = 0;

		// スケーリング成分正規化
		XMVECTOR xVector = XMVectorSet(matrix._11, matrix._12, matrix._13, 0.0f);
		XMVECTOR yVector = XMVectorSet(matrix._21, matrix._22, matrix._23, 0.0f);
		XMVECTOR zVector = XMVectorSet(matrix._31, matrix._32, matrix._33, 0.0f);

		XMVector3Normalize(xVector);
		XMVector3Normalize(yVector);
		XMVector3Normalize(zVector);

		XMMATRIX tmp;
		tmp.r[0] = xVector;
		tmp.r[1] = xVector;
		tmp.r[2] = zVector;
		tmp.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		Vector3 transform;
		XMStoreFloat3(&transform, XMVector3TransformCoord(XMLoadFloat3(&direction), tmp));

		return transform;
	}

	Vector3 Transform::InverseTransformPoint(const Vector3& point)
	{
		Matrix4x4 matrix = GetWorldToLocal();

		Vector3 transform;

		XMStoreFloat3(&transform, XMVector3TransformCoord(XMLoadFloat3(&point), XMLoadFloat4x4(&matrix)));

		return transform;
	}

	Vector3 Transform::InverseTransformVector(const Vector3& vector)
	{
		Matrix4x4 matrix = GetWorldToLocal();
		// 移動成分除去
		matrix._41 = 0;
		matrix._42 = 0;
		matrix._43 = 0;

		Vector3 transform;

		XMStoreFloat3(&transform, XMVector3TransformCoord(XMLoadFloat3(&vector), XMLoadFloat4x4(&matrix)));

		return transform;
	}

	const Matrix4x4 Transform::GetLocalMatrix() const
	{
		// スケーリング行列
		const XMMATRIX scalingMatrix = XMMatrixScaling(m_localScale.x, m_localScale.y, m_localScale.z);
		// 回転行列
		const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&m_localRotation));
		// 移動行列
		const XMMATRIX translationMatrix = XMMatrixTranslation(m_localPosition.x, m_localPosition.y, m_localPosition.z);

		// 合成行列
		XMMATRIX composite;
		composite = XMMatrixMultiply(scalingMatrix, rotationMatrix);
		composite = XMMatrixMultiply(composite, translationMatrix);

		Matrix4x4 localMatrix;
		XMStoreFloat4x4(&localMatrix, composite);

		return localMatrix;
	}
	
	void Transform::CalculateMatrix() const
	{
		// 再計算必要
		if (m_localToWorldIsDirty) 
		{
			XMMATRIX composite = XMLoadFloat4x4(&GetLocalMatrix());

			auto parent = GetOwner()->GetParent();
			if (parent)
			{
				auto parentTransform = parent->GetTransform();
				if (parentTransform)
				{
					XMMATRIX parentLocalToWorld = XMLoadFloat4x4(&parentTransform->GetLocalToWorld());
					// 親のローカル→ワールド変換行列考慮
					composite = XMMatrixMultiply(composite, parentLocalToWorld);
				}
			}

			// ローカル→ワールド合成変換行列
			XMStoreFloat4x4(&m_localToWorld, composite);

			// ワールド→ローカル変換行列
			XMStoreFloat4x4(&m_worldToLocal, XMMatrixInverse(nullptr, composite));

			m_localToWorldIsDirty = false;
		}
	}
}