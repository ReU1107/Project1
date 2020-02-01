#pragma once
#include <string>
#include "../Enumerations/AnimatorControllerParameterType.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// コントローラーで使用するパラメーター
		class AnimatorControllerParameter
		{
			void* m_parameter;						// パラメーターのポインター
			float m_defaultFloat;					// 
			int32_t m_defaultInt;					// 
			bool m_defaultBool;						// 
			AnimatorControllerParameterType m_type;	// 
		public:
			// コンストラクタ
			AnimatorControllerParameter() noexcept;
			// デストラクタ
			~AnimatorControllerParameter() noexcept;
		};
	}
}

using AnimatorControllerParameterPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorControllerParameter>;