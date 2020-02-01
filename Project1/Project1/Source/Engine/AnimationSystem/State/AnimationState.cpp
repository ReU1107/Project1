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
		//	// ���̃I�u�W�F�N�g�𓮂����A�j���[�V���������邩
		//	Keyframe keyframe;
		//	// �L�[�t���[�����Ȃ����߂��̃I�u�W�F�N�g�͓������Ȃ�
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
		//		// �P��radian
		//		float limitAngle = boneController->GetIKLimitAngle();
		//
		//		uint32_t iteratorCount = boneController->GetIKIteratorCount();
		//		for (uint32_t i = 0; i < iteratorCount; ++i) {
		//			uint32_t linkCount = boneController->GetIKLinkCount();
		//			for (uint32_t j = 0; j < linkCount; ++j) {
		//				IKLink & link = boneController->GetIKLink(j);
		//
		//				// �^�[�Q�b�g(IK�{�[��)�̃��[���h���W
		//				const XMFLOAT3 worldPosOfTarget(boneController->GetTransform()->GetLocalToWorld().m[3]);
		//
		//				auto effector = boneController->GetIKEffectorObject();
		//				// �G�t�F�N�^�[�̃��[���h���W
		//				const XMFLOAT3 worldPosOfEffector(effector->GetTransform()->GetLocalToWorld().m[3]);
		//
		//				Transform * linkTransform = link.linkObject->GetTransform();
		//
		//				// �����N�̃��[�J�����W�ɕϊ�
		//				const XMFLOAT3 localPosOfTarget = linkTransform->InverseTransformPoint(worldPosOfTarget);
		//				const XMFLOAT3 localPosOfEffector = linkTransform->InverseTransformPoint(worldPosOfEffector);
		//
		//				// �����N���猩������
		//				const XMVECTOR localDirOfTarget = XMVector3Normalize(XMLoadFloat3(&localPosOfTarget));
		//				const XMVECTOR localDirOfEffector = XMVector3Normalize(XMLoadFloat3(&localPosOfEffector));
		//
		//				// ��]�p�x
		//				float dotValue = XMVectorGetX(XMVector3Dot(localDirOfTarget, localDirOfEffector));
		//				/*
		//				90�x�ɂȂ�
		//				(1,1)�E(-1,1)
		//				���K��
		//				(0.5,0.5)�E(-0.5,0.5)
		//				���� 0 �� cosf(90)
		//				acosf(0) = 90
		//				*/
		//				//dotValue = clampf(dotValue, 1.0f, -1.0f);
		//				if (dotValue > 1.0f) {
		//					continue;
		//				}
		//				else if (dotValue < -1.0f) {
		//					continue;
		//				}
		//				// ���ό��ʂ��p�x�Z�oradian
		//				float innerAngle = acosf(dotValue);
		//				// ��]�p�x��0�Ɍ���Ȃ��߂�
		//				if (fabsf(innerAngle) < Epsilon) {
		//					continue;
		//				}
		//
		//				// ��]�p�x����
		//				innerAngle = Clampf(innerAngle, limitAngle, -limitAngle);
		//
		//				// ��]��
		//				XMFLOAT3 axis;
		//				XMStoreFloat3(&axis, XMVector3Normalize(XMVector3Cross(localDirOfEffector, localDirOfTarget)));
		//				// �l���������ۂɎ���(0,0,0)����NotACountber�ɂȂ��
		//				float length = XMVectorGetX(XMVector3Length(XMLoadFloat3(&axis)));
		//				// ����Ȃ�0�ɋ߂�EPSILIN
		//				if (length < Epsilon) {
		//					continue;
		//				}
		//
		//				// 
		//				XMVECTOR deltaRotation = XMQuaternionRotationAxis(XMLoadFloat3(&axis), innerAngle);
		//
		//				XMFLOAT4 quaternion;
		//				XMStoreFloat4(&quaternion, deltaRotation);
		//				// �����N�I�u�W�F�N�g���v�Z���q��(�^�[�Q�b�g�I�u�W�F�N�g�ɍČv�Z������
		//				linkTransform->LocalRotate(quaternion);
		//
		//				if (link.isUseLimit) {
		//					XMFLOAT4 localRotation = linkTransform->GetLocalRotation();
		//
		//					// x,y,z���̂��ꂼ��̉�]�p�xradian���擾
		//					XMFLOAT3 angle = XMGetAngleByQuaternion(XMLoadFloat4(&localRotation));
		//					// ��]��̊p�x����
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
		//		// FK����
		//		//ForwardKinematics(m_gameObject);

		//		// IK���� rigidBody�Ɉړ�?
		//		//InverseKinematics(m_gameObject);
		//	}
		//}

		//void AnimationState::Stop()
		//{
		//	m_timer.Stop();
		//}
	}
}