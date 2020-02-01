#pragma once
#include "Bone.h"
#include "../../../Math/Vector3.h"

namespace Engine
{
	// Inverse Kinematics (�t�^���w)

	struct IKLink
	{
		std::shared_ptr<Bone> bone;
		Vector3 lowerLimitAngle;		// �����p�x
		Vector3 upperLimitAngle;		// �����p�x
		bool isLimit;
	};


	class IKBone : public Bone
	{
	private:
		using base = Bone;
		using BonePtr = std::shared_ptr<Bone>;
		using Links = std::vector<IKLink>;
	private:
		BonePtr m_effectorBone;			// ���̃{�[���𓮂���
		Links m_links;					// �����N�z��
		uint32_t m_iterationCount;		// ���̏����łł��郋�[�v�ő吔
		float m_iterationLimitAngle;	// 
	public:
		// �R���X�g���N�^
		IKBone();
		// �f�X�g���N�^
		virtual ~IKBone();

	public:
		// �G�t�F�N�^�[�{�[���ݒ�
		void SetEffectorBone(BonePtr bone);

		// �����N�ǉ�
		void AddLink(const IKLink& link);

		void SetIterationCount(uint32_t count);

		void SetIterationLimitAngle(float angle);

		BonePtr GetEffectorBone() const;

		uint32_t GetIterationCount() const;

		float GetIterationLimitAngle() const;

		const Links& GetLinks() const;

	};

}
