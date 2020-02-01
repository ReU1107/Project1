#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// �F�����A�j���[�V��������ۂɎg�p
		class AnimationPropertyColor4 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
		public:
			// �R���X�g���N�^
			AnimationPropertyColor4() noexcept;
			// �f�X�g���N�^
			virtual ~AnimationPropertyColor4() noexcept;
		public:
			virtual void Update(float frame);
		};

	}
}