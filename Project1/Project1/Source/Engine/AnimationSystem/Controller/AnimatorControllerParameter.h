#pragma once
#include <string>
#include "../Enumerations/AnimatorControllerParameterType.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// �R���g���[���[�Ŏg�p����p�����[�^�[
		class AnimatorControllerParameter
		{
			void* m_parameter;						// �p�����[�^�[�̃|�C���^�[
			float m_defaultFloat;					// 
			int32_t m_defaultInt;					// 
			bool m_defaultBool;						// 
			AnimatorControllerParameterType m_type;	// 
		public:
			// �R���X�g���N�^
			AnimatorControllerParameter() noexcept;
			// �f�X�g���N�^
			~AnimatorControllerParameter() noexcept;
		};
	}
}

using AnimatorControllerParameterPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorControllerParameter>;