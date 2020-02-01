#pragma once
#include "../Component.h"
#include "../../../Math/Include.h"

// �L�[�|�[�Y�s��̓g�����X�t�H�[���̒l���l����������

namespace Engine
{
	enum class BoneType : uint8_t
	{
		ForwardKinematics,	// 
		InverseKinematics,	// 
	};

	// �{�[���N���X
	class Bone : public Component
	{
	private:
		using base = Component;

	private:
		Vector3 m_keyPosePosition;				// �ړ�
		Vector4 m_keyPoseRotation;				// ��]
		Vector3 m_fixedAxis;					// �Œ莲(��]�̎����Œ�)
		Matrix4x4 m_offsetMatrix;				// �I�t�Z�b�g�s��
		mutable Matrix4x4 m_keyPoseLocalMatrix;	// �s��
		mutable Matrix4x4 m_keyPoseWorldMatrix;	// �s��
		mutable bool m_keyPoseIsDirty;			// �_�[�e�B�t���O
		BoneType m_type;
	public:
		// �R���X�g���N�^
		Bone(const std::string& name, BoneType type) noexcept;
		// �f�X�g���N�^
		virtual ~Bone() noexcept;

		virtual void* GetPropertyAddress(const std::string& name) override;

		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Bone; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Bone; }

		// �I�t�Z�b�g�s��ݒ�
		void SetOffsetMatrix(const Matrix4x4& offset);

		// �Œ莲�ݒ�
		void SetFixedAxis(const Vector3& axis);

		// 
		void Reset();

		// ���[�J����Ԃł̉�]
		void LocalRotate(const Vector3& euler);
		void LocalRotate(const Vector3& axis, float angle);
		void LocalRotate(const Vector4& rotation);
		void LocalRotate(const Matrix4x4& mat);


	public:
		// �I�t�Z�b�g�s��擾
		const Matrix4x4& GetOffsetMatrix() const;
		// �L�[�|�[�Y�s��擾
		const Matrix4x4& GetKeyPoseMatrix() const;

		// �A�j���[�V�����K�p��̈ʒu�擾
		Vector3 GetWorldPosition() const;

		BoneType GetType() const;

	private:
		void CalculateMatrix() const;
	};

}
