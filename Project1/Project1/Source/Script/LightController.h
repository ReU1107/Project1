#pragma once
#include "../Engine/GameObject/Include.h"

namespace Engine 
{
	class Transform;
}

// ��������
class LightController final : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:
	float m_longitude;		// �o�x(�P��:���W�A��)
	float m_latitude;		// �ܓx(�P��:���W�A��)
	float m_distance;		// ����
	float m_speed;			// ��]���x(�P��:���W�A��)
public:
	// �R���X�g���N�^
	LightController() noexcept;

	// �f�X�g���N�^
	virtual ~LightController() noexcept;
public:


};