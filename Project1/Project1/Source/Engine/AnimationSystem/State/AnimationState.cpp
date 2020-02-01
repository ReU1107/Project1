#include "AnimationState.h"
#include "../Motion/AnimationClip.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationState::AnimationState() noexcept
			: m_clip(nullptr)
			, m_speed(1.0f)
			, m_loopCount(1)
			, m_frameIndex(0)
		{
		}

		AnimationState::~AnimationState() noexcept
		{

		}

		void AnimationState::AddMixingTransform(Transform* transform, bool recursive)
		{

		}

		void AnimationState::SetAnimationClip(AnimationClip* clip)
		{
			m_clip = clip;
		}

		void AnimationState::SetSpeed(float speed)
		{
			m_speed = speed;
		}

		void AnimationState::RemoveMixingTransform(Transform* transform)
		{

		}

		void AnimationState::Update(float deltaTime)
		{
			m_clip->Update(nullptr, nullptr, deltaTime);
		}

		//void AnimationState::ForwardKinematics(GameObject * gameObject)
		//{
		//	if (m_isRecursive) {
		//		if (!gameObject) {
		//			return;
		//		}
		//		for (uint32_t i = 0; i < gameObject->GetChildCount(); ++i) {
		//			ForwardKinematics(gameObject->GetChildByIndex(i));
		//		}
		//	}
		//	// このオブジェクトを動かすアニメーションがあるか
		//	Keyframe keyframe;
		//	// キーフレームがないためこのオブジェクトは動かさない
		//	if (!m_clip->GetKeyframe(keyframe, gameObject->GetName(), m_frameIndex)) {
		//		return;
		//	}
		//
		//	Transform * transform = gameObject->GetTransform();
		//	transform->SetKeyPoseMatrix(keyframe.position, keyframe.rotation);
		//	transform->HasChanged(true);
		//}

		//void AnimationState::InverseKinematics(GameObject * gameObject)
		//{
		//	auto boneControllers = gameObject->GetComponentsInDescendant<BoneController>(true);
		//	for (auto & boneController : boneControllers) {
		//		if (!boneController->IsIKBone()) {
		//			continue;
		//		}
		//		// 単位radian
		//		float limitAngle = boneController->GetIKLimitAngle();
		//
		//		uint32_t iteratorCount = boneController->GetIKIteratorCount();
		//		for (uint32_t i = 0; i < iteratorCount; ++i) {
		//			uint32_t linkCount = boneController->GetIKLinkCount();
		//			for (uint32_t j = 0; j < linkCount; ++j) {
		//				IKLink & link = boneController->GetIKLink(j);
		//
		//				// ターゲット(IKボーン)のワールド座標
		//				const XMFLOAT3 worldPosOfTarget(boneController->GetTransform()->GetLocalToWorld().m[3]);
		//
		//				auto effector = boneController->GetIKEffectorObject();
		//				// エフェクターのワールド座標
		//				const XMFLOAT3 worldPosOfEffector(effector->GetTransform()->GetLocalToWorld().m[3]);
		//
		//				Transform * linkTransform = link.linkObject->GetTransform();
		//
		//				// リンクのローカル座標に変換
		//				const XMFLOAT3 localPosOfTarget = linkTransform->InverseTransformPoint(worldPosOfTarget);
		//				const XMFLOAT3 localPosOfEffector = linkTransform->InverseTransformPoint(worldPosOfEffector);
		//
		//				// リンクから見た向き
		//				const XMVECTOR localDirOfTarget = XMVector3Normalize(XMLoadFloat3(&localPosOfTarget));
		//				const XMVECTOR localDirOfEffector = XMVector3Normalize(XMLoadFloat3(&localPosOfEffector));
		//
		//				// 回転角度
		//				float dotValue = XMVectorGetX(XMVector3Dot(localDirOfTarget, localDirOfEffector));
		//				/*
		//				90度になる
		//				(1,1)・(-1,1)
		//				正規化
		//				(0.5,0.5)・(-0.5,0.5)
		//				答え 0 ≒ cosf(90)
		//				acosf(0) = 90
		//				*/
		//				//dotValue = clampf(dotValue, 1.0f, -1.0f);
		//				if (dotValue > 1.0f) {
		//					continue;
		//				}
		//				else if (dotValue < -1.0f) {
		//					continue;
		//				}
		//				// 内積結果より角度算出radian
		//				float innerAngle = acosf(dotValue);
		//				// 回転角度が0に限りなく近い
		//				if (fabsf(innerAngle) < Epsilon) {
		//					continue;
		//				}
		//
		//				// 回転角度制限
		//				innerAngle = Clampf(innerAngle, limitAngle, -limitAngle);
		//
		//				// 回転軸
		//				XMFLOAT3 axis;
		//				XMStoreFloat3(&axis, XMVector3Normalize(XMVector3Cross(localDirOfEffector, localDirOfTarget)));
		//				// 四元数を作る際に軸が(0,0,0)だとNotACountberになる為
		//				float length = XMVectorGetX(XMVector3Length(XMLoadFloat3(&axis)));
		//				// 限りなく0に近いEPSILIN
		//				if (length < Epsilon) {
		//					continue;
		//				}
		//
		//				// 
		//				XMVECTOR deltaRotation = XMQuaternionRotationAxis(XMLoadFloat3(&axis), innerAngle);
		//
		//				XMFLOAT4 quaternion;
		//				XMStoreFloat4(&quaternion, deltaRotation);
		//				// リンクオブジェクトを計算し子供(ターゲットオブジェクトに再計算させる
		//				linkTransform->LocalRotate(quaternion);
		//
		//				if (link.isUseLimit) {
		//					XMFLOAT4 localRotation = linkTransform->GetLocalRotation();
		//
		//					// x,y,z軸のそれぞれの回転角度radianを取得
		//					XMFLOAT3 angle = XMGetAngleByQuaternion(XMLoadFloat4(&localRotation));
		//					// 回転後の角度制限
		//					angle = Clamp3f(angle, link.upperLimitRadian, link.lowerLimitRadian);
		//
		//					quaternion;
		//					XMStoreFloat4(&quaternion, XMQuaternionRotationRollPitchYaw(angle.x, angle.y, angle.z));
		//					
		//					linkTransform->SetLocalRotation(quaternion);
		//				}
		//
		//				linkTransform->HasChanged(true);
		//
		//			}
		//		}
		//	}
		//}

		//void AnimationState::Play()
		//{
		//	m_timer.Start();
		//}

		//void AnimationState::Update(float deltaTime)
		//{
		//	if (m_timer.GetElapsedTime() > fpsChrono) {
		//		m_frameIndex++;
		//	}

		//	if (m_isUpdate) {
		//		// FK処理
		//		//ForwardKinematics(m_gameObject);

		//		// IK処理 rigidBodyに移動?
		//		//InverseKinematics(m_gameObject);
		//	}
		//}

		//void AnimationState::Stop()
		//{
		//	m_timer.Stop();
		//}
	}
}