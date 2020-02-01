#pragma once
#include "../Component.h"
#include <vector>
#include "../../../Math/Vector3.h"

class btGeneric6DofSpringConstraint;

namespace Engine
{
	enum class JointType : uint8_t
	{
		Spring,		// �΂�
		Hinge,		// �q���W(�h�A��)
	};

	// �֐�
	class Joint : public Component
	{
	private:
		using base = Component;
		using GameObjectPtr = std::shared_ptr<GameObject>;
		using ConnectedBones = std::vector<GameObjectPtr>;
		using JointPtr = std::shared_ptr<Joint>;
	public:
		static std::vector<JointPtr> allJoints;
	private:
		btGeneric6DofSpringConstraint* m_;
		ConnectedBones m_connectedBones;	// ���̃I�u�W�F�N�g���q���Ă���I�u�W�F�N�g
		Vector3 m_anchorPosition;			// 

		JointType m_type;					// 
		bool m_enableCollision;
	public:
		// �R���X�g���N�^
		Joint(const std::string& name, JointType type) noexcept;
		// �f�X�g���N�^
		virtual ~Joint() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Joint; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID()const override { return InstanceID::Joint; }

	public:
		// �A���J�[�ʒu�ݒ�
		void SetAnchorPosition(const Vector3& anchor);

		// �ڑ��I�u�W�F�N�g�ǉ�
		void AddConnectBone(GameObjectPtr bone);

		// �W���C���g�̎�ގ擾
		JointType GetType() const;
	};
}