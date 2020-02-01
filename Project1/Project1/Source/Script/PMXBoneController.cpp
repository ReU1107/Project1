#include "PMXBoneController.h"
#include "../Engine/Include.h"
using namespace Engine;
using namespace Engine::GraphicsSystem;
using namespace DirectX;

PMXBoneController::PMXBoneController()
{
}

PMXBoneController::~PMXBoneController()
{
}

void PMXBoneController::OnStart()
{
	auto bone = GetComponent<IKBone>();
	if (bone->GetType() == BoneType::InverseKinematics)
	{
		m_ik = bone;
	}
}

void PMXBoneController::OnUpdate(float deltaTime)
{

}

void PMXBoneController::OnLateUpdate(float deltaTime)
{
	if (!m_ik)
		return;

	const uint32_t iterationCount = m_ik->GetIterationCount();
	const float limitAngle = m_ik->GetIterationLimitAngle();
	auto effector = m_ik->GetEffectorBone();

	const auto targetPosition = m_ik->GetWorldPosition();

	auto links = m_ik->GetLinks();

	for (auto& link : links)
	{
		link.bone->Reset();
	}

	this;

	for (uint32_t i = 0; i < iterationCount; ++i)
	{
		for (uint32_t j = 0; j < links.size(); ++j)
		{
			auto& link = links[j];

			const auto effectorPosition = effector->GetWorldPosition();

			const auto linkPosition = link.bone->GetWorldPosition();

			const auto mat = link.bone->GetParent()->GetComponent<Bone>()->GetKeyPoseMatrix();

			// ƒGƒtƒFƒNƒ^[‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹
			const auto v1 = Vector3Normalize(effectorPosition - linkPosition);
			// –Ú•WˆÊ’u‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹
			const auto v2 = Vector3Normalize(targetPosition - linkPosition);

			// ‰ñ“]Ž²
			Vector3 axis = Vector3Cross(v1, v2);
			XMStoreFloat3(&axis, XMVector3TransformNormal(XMLoadFloat3(&axis), XMMatrixInverse(nullptr, XMLoadFloat4x4(&mat))));

			axis = Vector3Normalize(axis);

			if (Vector3IsNotANumber(axis))
			{
				continue;
			}

			// ŽlŒ³”‚ªì‚ê‚È‚¢‚½‚ß–³Ž‹
			if (MathF::NearZero(axis.LengthSq()))
			{
				continue;
			}

			// ‰ñ“]Šp“x(0`180‹‚Ü‚Å)
			const float theta = MathF::Min(Vector3Dot(v1, v2), 1.0f);
			const float limit = limitAngle * (j + 1);
			const float angle = MathF::Clamp(acosf(theta), limit, -limit);

			// 
			if (MathF::NearZero(angle))
			{
				continue;
			}

			// —‘z‰ñ“]
			auto ideal = XMQuaternionRotationAxis(XMLoadFloat3(&axis), angle);

			if (link.isLimit)
			{
				Quaternion quaternion;
				quaternion.imaginary.x = XMVectorGetX(ideal);
				quaternion.imaginary.y = XMVectorGetY(ideal);
				quaternion.imaginary.z = XMVectorGetZ(ideal);
				quaternion.real = XMVectorGetW(ideal);

				auto vec = QuaternionAngle(quaternion);

				Matrix4x4 mat;
				XMStoreFloat4x4(&mat, XMMatrixRotationQuaternion(XMVectorSet(quaternion.imaginary.x, quaternion.imaginary.y, quaternion.imaginary.z, quaternion.real)));

				Vector3 result;
				RotationOrder order = RotationOrder::XYZ;
				if (!Matrix4x4EulerAnglesXYZ(mat, &result))
				{
					order = RotationOrder::YZX;

					if (!Matrix4x4EulerAnglesYZX(mat, &result))
					{
						RotationOrder order = RotationOrder::ZXY;

						if (!Matrix4x4EulerAnglesZXY(mat, &result))
						{
							result = Vector3::Zero;
						}
					}
				}

				vec = Vector3NormalizeEuler(vec);

				vec = Vector3Clamp(vec, link.upperLimitAngle, link.lowerLimitAngle);

				XMMATRIX remaining = XMMatrixIdentity();
				XMMATRIX xRot = XMMatrixRotationX(vec.x);
				XMMATRIX yRot = XMMatrixRotationY(vec.y);
				XMMATRIX zRot = XMMatrixRotationZ(vec.z);
				switch (order)
				{
				case Engine::RotationOrder::XYZ:
					remaining = xRot * yRot * zRot;
					break;
				case Engine::RotationOrder::YZX:
					remaining = yRot * zRot * xRot;
					break;
				case Engine::RotationOrder::ZXY:
					remaining = zRot * xRot * yRot;
					break;
				default:
					break;
				}

				Matrix4x4 rot;
				XMStoreFloat4x4(&rot, remaining);

				link.bone->LocalRotate(rot);

			}
			else
			{
				Vector4 q;
				XMStoreFloat4(&q, ideal);

				link.bone->LocalRotate(q);
			}
		}

	}
}


//auto linkParentTransform = link.bone->GetParent()->GetTransform();

//auto mat = linkParentTransform->GetWorldToLocal();

//auto effectorPos = XMVector3TransformCoord(XMLoadFloat3(&effectorPosition), XMLoadFloat4x4(&mat));
//auto targetPos = XMVector3TransformCoord(XMLoadFloat3(&targetPosition), XMLoadFloat4x4(&mat));
//auto linkPos = XMVector3TransformCoord(XMLoadFloat3(&linkPosition), XMLoadFloat4x4(&mat));

//Vector3 v1;
//XMStoreFloat3(&v1, XMVector3Normalize(effectorPos - linkPos));

//Vector3 v2;
//XMStoreFloat3(&v2, XMVector3Normalize(targetPos - linkPos));

//auto Ang = [&]()->Vector3
//{
//	Vector3 vec;
//	vec.x = asinf(-mat._32);
//	//if (fabsf(vec.x) > 1.535889f)
//	//{
//	//	vec.x = ((vec.x < 0.0f) ? -1.535889f : 1.535889f);
//	//}
//	vec.y = atan2f(mat._31, mat._33);
//	vec.z = atan2f(mat._12, mat._22);
//	return vec;
//};

//vec = Ang();

				//// ŽÀÛ‰ñ“]
				//XMVECTOR actual = /*XMQuaternionNormalize*/(XMQuaternionRotationRollPitchYaw(vec2.x, vec2.y, vec2.z));

				//// Žc‘¶‰ñ“]—‘z‰ñ“]/ŽÀÛ‰ñ“]
				////XMVECTOR remaining = ideal * XMQuaternionConjugate(actual);

				//XMVECTOR remaining = XMQuaternionInverse(XMLoadFloat4(&Vector4::Identity)) * actual;

/*	if (vec.x < link.lowerLimitAngle.x)
	{
		float num = 2.0f * link.lowerLimitAngle.x - vec.x;
		vec.x = ((num <= link.upperLimitAngle.x) ? num : link.lowerLimitAngle.x);
	}
	else if (vec.x > link.upperLimitAngle.x)
	{
		float num = 2.0f * link.upperLimitAngle.x - vec.x;
		vec.x = ((num >= link.lowerLimitAngle.x) ? num : link.upperLimitAngle.x);
	}
	if (vec.y < link.lowerLimitAngle.y)
	{
		float num = 2.0f * link.lowerLimitAngle.y - vec.y;
		vec.y = ((num <= link.upperLimitAngle.y) ? num : link.lowerLimitAngle.y);
	}
	else if (vec.y > link.upperLimitAngle.y)
	{
		float num = 2.0f * link.upperLimitAngle.y - vec.y;
		vec.y = ((num >= link.lowerLimitAngle.y) ? num : link.upperLimitAngle.y);
	}
	if (vec.y < link.lowerLimitAngle.z)
	{
		float num = 2.0f * link.lowerLimitAngle.z - vec.z;
		vec.z = ((num <= link.upperLimitAngle.z) ? num : link.lowerLimitAngle.z);
	}
	if (vec.z > link.upperLimitAngle.z)
	{
		float num = 2.0f * link.upperLimitAngle.z - vec.z;
		vec.z = ((num >= link.lowerLimitAngle.z) ? num : link.upperLimitAngle.z);
	}*/