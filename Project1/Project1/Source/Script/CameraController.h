#pragma once
#include "../Engine/GameObject/Component/Include.h"

namespace Engine
{
	class Transform;
}

// �J��������
class CameraController final : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:
	std::shared_ptr<Engine::Transform> m_target;// �^�[�Q�b�g�ɂȂ�I�u�W�F�N�g(Follow)������
	float m_longitude;		// �o�x(�P��:���W�A��)
	float m_latitude;		// �ܓx(�P��:���W�A��)
	float m_distance;		// ����
	float m_speed;			// ��]���x(�P��:���W�A��)
public:
	// �R���X�g���N�^
	CameraController() noexcept;

	// �f�X�g���N�^
	virtual ~CameraController() noexcept;
public:
	virtual void OnAwake() override;

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;
};
