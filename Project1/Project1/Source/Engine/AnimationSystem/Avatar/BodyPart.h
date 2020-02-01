#pragma once
#include <string>
#include <memory>
#include "../../InstanceID.h"
#include "../../Math/Include.h"

namespace Engine
{
	// �O���錾
	class Object;
	namespace AnimationSystem
	{
		// �A�o�^�[���\�����镔�i
		struct BodyPart
		{
			std::string name;		// ���O

			//Vector4 bindRotation;	// ��]
			//Vector3 bindPosition;	// �ʒu
			//Vector3 bindScale;		// �X�P�[��

			std::shared_ptr<Object> targetObject;
			InstanceID id;				// �A�j���[�V��������I�u�W�F�N�gID

			BodyPart() noexcept;
		};

	}
}