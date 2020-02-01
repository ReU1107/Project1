#pragma once
#include "Behaviour.h"
#include <array>
#include <vector>
#include <list>
#include "Enumerations/LightEvent.h"
#include "Enumerations/LightType.h"
#include "Enumerations/ShadowResolution.h"
#include "../../../Math/Include.h"
#include <iostream>

namespace Engine
{

	class Light final : public  Behaviour
	{
	private:
		using base = Behaviour;
		using LightPtr = std::shared_ptr<Light>;
		using Lights = std::list<LightPtr>;
	public:
		static Lights allLights;					// �S�Ă̌���
		static uint32_t allLigthsCount;				// �S�Ă̌�����
		static LightPtr current;					// 
	private:
		mutable Matrix4x4 m_projectionMatrix;	// �v���W�F�N�V�����ϊ��s��
		mutable Matrix4x4 m_screenMatrix;		// �X�N���[��(�r���[�|�[�g�X�P�[�����O)�ϊ��s��
		Color3 m_color;							// �����F

		float m_intensity;						// �������x
		float m_nearRange;						// �L���͈�
		float m_farRange;						// �L���͈�
		float m_spotOuterAngle;					// �X�|�b�g���C�g�̊p�x(�O���R�[��)
		float m_spotInnerAngle;					// �X�|�b�g���C�g�̊p�x(�����R�[��)

		LightType m_type;
		mutable bool m_viewMatrixIsDirty;		// �r���[�ϊ��s��̐ݒ�(Transform�̒l)�ύX���X�V
		mutable bool m_projMatrixIsDirty;		// �v���W�F�N�V�����ϊ��s��̐ݒ�ύX���X�V
		mutable bool m_shadowMapIsDirty;		// �V���h�E�}�b�v�̐ݒ�ύX���X�V
	public:
		Light() noexcept;

		virtual ~Light() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Light; }
		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Light; }
	public:
		// �����F�ݒ�
		void SetColor(const Color3& color);
		void SetColor(float r, float g, float b);

		// �������e����^���鋗��(Directional���C�g�͖��֌W)
		void SetNearRange(float range);
		void SetFarRange(float range);
		// �X�|�b�g���C�g�̊O�p�ݒ�
		void SetSpotOuterCone(float outer);
		// �X�|�b�g���C�g�̓��p�ݒ�
		void SetSpotInnerCone(float inner);

		// �����̃^�C�v�ύX
		void ChangeType(LightType type);

	public:
		// �����F�擾
		const Color3& GetColor() const;

		// �������x�擾
		float GetIntensity() const;

		float GetNearRange() const;

		float GetFarRange() const;

		float GetSpotInnerAngle() const;

		float GetSpotOuterAngle() const;

		Vector3 GetPosition() const;

		Vector3 GetDirection() const;

		// �V���h�E�}�b�v�p�v���W�F�N�V�����ϊ��s��擾
		const Matrix4x4& GetProjectionMatrix() const;
		// �V���h�E�}�b�v�p�X�N���[��(�r���[�|�[�g�X�P�[�����O)�ϊ��s��擾
		const Matrix4x4& GetScreenMatrix() const;

	public:
		// ���C�g�̎�ގ擾
		LightType GetType() const;
	private:
		void CreateProjectionMatrix() const;
	};

	template<>
	inline std::shared_ptr<Light> Component::Create()
	{
		auto light = std::make_shared<Light>();

		Light::allLights.push_back(light);
		Light::allLigthsCount++;

		return light;
	}
}