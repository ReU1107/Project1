#include "MonoBehaviour.h"
#include "../../../Utility/Utility.h"

namespace Engine 
{
	MonoBehaviour::MonoBehaviour(const std::string & name) noexcept
		: base(name)
	{
	}

	MonoBehaviour::~MonoBehaviour() noexcept
	{
		// �������Ȃ�
	}

	void MonoBehaviour::OnUpdate(float deltaTime)
	{
		UnusedArgment(deltaTime);
	}

	void MonoBehaviour::OnLateUpdate(float deltaTime)
	{
		UnusedArgment(deltaTime);
	}

	void MonoBehaviour::OnFixedUpdate(float deltaTime)
	{
		UnusedArgment(deltaTime);
	}
}
