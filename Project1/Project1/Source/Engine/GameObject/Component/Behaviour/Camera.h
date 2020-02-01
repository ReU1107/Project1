#pragma once
#include <vector>
#include "Behaviour.h"
#include "../../../Math/Color4.h"
#include "../../../Math/Matrix4x4.h"
#include "Enumerations/CameraEvent.h"
#include "Enumerations/DepthTextureMode.h"
#include <iostream>

namespace Engine
{

	// �O���錾
	namespace GraphicsSystem
	{
		class RenderTexture;
		class ConstantBuffer;
	}

	// ���e�@
	enum class ProjectionType : uint8_t
	{
		Orthographic,	// ���s���e�@
		Perspective		// �������e�@
	};

	class Camera final : public Behaviour, public std::enable_shared_from_this<Camera>
	{
	private:
		using base = Behaviour;
		using CameraPtr = std::shared_ptr<Camera>;
		using ConstantBufferPtr = GraphicsSystem::ConstantBuffer*;
		using Cameras = std::vector<CameraPtr>;
	public:
		static Cameras allCameras;			// �S�ẴJ����
		static uint32_t allCamerasCount;	// �S�ẴJ������
		static CameraPtr main;				// ���C���J����
		static CameraPtr current;			// ���ݗL���ɂȂ��Ă���J����
		
	private:
		ConstantBufferPtr m_constantBuffer;
		mutable Matrix4x4 m_projectionMatrix;			// �ˉe�ϊ��s��

		Color4 m_backGroundColor;						// �e�N�X�`���̃N���A�F

		float m_fovAngle;								// ����pfiled of view(�P��:���W�A��)
		float m_width;									// ��
		float m_height;									// ����
		float m_aspect;									// �A�X�y�N�g��(��/����)
		float m_nearClipPlane;							// �ŋߖ�
		float m_farClipPlane;							// �ŉ���

		DepthTextureMode m_depthTextureMode;
		ProjectionType m_projectionType;				// ���e���@
		mutable bool m_projectionIsDirty;				// �_�[�e�B�[�t���O(�v���W�F�N�V�����ϊ��s��)
		bool m_isActive;								// �J�������L����

	public:
		// �R���X�g���N�^
		Camera() noexcept;
		// �f�X�g���N�^
		virtual ~Camera() noexcept;

	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Camera; }
		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Camera; }

	public:
		ConstantBufferPtr GetConstantBuffer() const;

		// ����p�ݒ�(�P��:���W�A��)
		void SetFovAngle(float fovAngle);

		// �A�X�y�N�g��ݒ�
		void SetAspect(float aspect);

		// �ŋߖʂ̈ʒu�ݒ�
		void SetNearClipPlane(float nearClipPlane);

		// �ŉ��ʂ̈ʒu�ݒ�
		void SetFarClipPlane(float farClipPlane);

		// ���e�@�ݒ�
		void SetProjectionType(ProjectionType projectionType);

		// ��Ԑݒ�
		void SetActive(bool isActive);

		// �w�i�F�ݒ�
		void SetBackGroundColor(const Color4& color);
		void SetBackGroundColor(float color);

		// �r���[�ϊ��s��擾
		const Matrix4x4& GetViewMatrix() const;
		// �ˉe�ϊ��s��擾
		const Matrix4x4& GetProjectionMatrix() const;

		// ���e�@��������
		bool IsPerspective() const;

		// �ғ����Ă��邩
		bool IsActive() const;
		// �R�}���h�o�b�t�@�擾
		//std::vector<CommandBuffer*>& GetCommandBuffer(CameraEvent evt);
		// �R�}���h�o�b�t�@���s
		//void ExecuteCommandBuffer(CameraEvent evt);
	};

	template<>
	inline std::shared_ptr<Camera> Component::Create()
	{
		auto camera = std::make_shared<Camera>();
		if (!Camera::main)
			Camera::main = camera;
		Camera::allCameras.push_back(camera);

		return camera;
	}
}