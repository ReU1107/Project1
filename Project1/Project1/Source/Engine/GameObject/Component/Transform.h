#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include <iostream>
#include <memory>
#include "../../Math/Include.h"

namespace Engine
{
	class Transform final : public Component
	{
	private:
		using base = Component;
	private:
		// �v�Z�̍œK��
		mutable Matrix4x4 m_localToWorld;		// ���[�J�������[���h�ϊ��s��
		mutable Matrix4x4 m_worldToLocal;		// ���[���h�����[�J���ϊ��s��

		Vector4 m_localRotation;				// ��](�l����)

		Vector3 m_localPosition;				// �ʒu		�e����݂����ΓI�Ȉʒu
		Vector3 m_localScale;					// �X�P�[�����O

		// �_�[�e�B�p�^�[��
		mutable bool m_localToWorldIsDirty;		// �Čv�Z(���[���h�ϊ��s��쐬�ɕK�v�Ȑ��l���ς������true)
	public:
		// �R���X�g���N�^
		Transform() noexcept;
		// �f�X�g���N�^
		virtual ~Transform() noexcept;
	public:
		// �C���X�^���XID�擾
		static const InstanceID ID() { return InstanceID::Transform; }
		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Transform; }

		virtual void* GetPropertyAddress(const std::string& name) override;

	public:
		// ���[�J����ԓ��̈ʒu�ݒ�
		void SetLocalPosition(const Vector3& position);
		void SetLocalPosition(float x, float y, float z);

		// ���[���h��ԓ��̈ʒu�ݒ�
		void SetWorldPosition(const Vector3& position);
		void SetWorldPosition(float x, float y, float z);

		// ���[�J����ԓ��̃X�P�[���l�ݒ�
		void SetLocalScale(const Vector3& scale);
		void SetLocalScale(float x, float y, float z);

		// ���[�J����ԓ��̉�]�p�x�ݒ�
		void SetLocalRotation(const Vector3& euler);
		void SetLocalRotation(const Vector4& rotation);

		// ���[���h��ԓ��̉�]�p�x�ݒ�
		void SetWorldRotation(const Vector4& rotation);

		// �Čv�Z�ʒm
		void HasChanged(bool recurse);
	public:
		// ���[�J����ԓ��̈ʒu�擾
		Vector3 GetLocalPosition() const;
		// ���[���h��ԓ��̈ʒu�擾
		Vector3 GetWorldPosition() const;

		// ���[�J����ԓ��̉�]�l�擾
		Vector4 GetLocalRotation() const;
		// ���[���h��ԓ��̉�]�l�擾
		Vector4 GetWorldRotation() const;

		// ���[�J�������[���h�ϊ��s��擾
		const Matrix4x4& GetLocalToWorld() const;
		// ���[���h�����[�J���ϊ��s��擾(���[���h�ϊ��̋t�s��)
		const Matrix4x4& GetWorldToLocal() const;

		// �l�̕ύX����������
		bool IsDirty() const;

	public:
		// ���[�J����Ԃł̕��s�ړ�
		void LocalTranslate(const Vector3& displacement);
		// ���[���h��Ԃł̕��s�ړ�
		void WorldTranslate(const Vector3& displacement);

		// ���[�J����Ԃł̉�]
		void LocalRotate(const Vector3& euler);
		void LocalRotate(const Vector3& axis, float angle);
		void LocalRotate(const Vector4& rotation);
		// ���[���h��Ԃł̉�]
		void WorldRotate(const Vector3& euler);
		void WorldRotate(const Vector3& axis, float angle);
		//void WorldRotate(const Vector4 & rotate);

		// �^�[�Q�b�g�̕���������悤�ɉ�]
		void LookAt(const Vector3& worldPosition, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(float x, float y, float z, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(std::shared_ptr<GameObject> gameObject, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(std::shared_ptr<Transform> transform, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));

		// �w�莲��]
		void RotateAround(const Vector3& point, const Vector3& axis, float radian);
	public:
		// ���[���h���W�n��Z���擾
		Vector3 Forward() const;
		Vector3 Backward() const;
		// ���[���h���W�n��X���擾
		Vector3 Right() const;
		Vector3 Left() const;
		// ���[���h���W�n��Y���擾
		Vector3 Up() const;
		Vector3 Down() const;

		// ���g�̃��[���h��Ԃɕ�����ϊ��擾
		Vector3 TransformDirection(const Vector3& direction);
		// ���g�̃��[���h��ԂɈʒu��ϊ��擾
		Vector3 TransformPoint(const Vector3& point);
		// ���g�̃��[���h��ԂɃx�N�g����ϊ��擾
		Vector3 TransformVector(const Vector3& vector);

		// ���g�̃��[�J����Ԃɕ�����ϊ��擾
		Vector3 InverseTransformDirection(const Vector3& direction);
		// ���g�̃��[�J����ԂɈʒu��ϊ��擾
		Vector3 InverseTransformPoint(const Vector3& point);
		// ���g�̃��[�J����ԂɃx�N�g����ϊ��擾
		Vector3 InverseTransformVector(const Vector3& vector);

		// 
		const Matrix4x4 GetLocalMatrix() const;
	private:

		// �v�Z
		void CalculateMatrix() const;

	};
}

using TransformPtr = std::shared_ptr<Engine::Transform>;