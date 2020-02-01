#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		/*
		8bit* 4
		*/

		// �F�����A�j���[�V��������ۂɎg�p
		class AnimationPropertyColor32 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
		public:
			// �R���X�g���N�^
			AnimationPropertyColor32() noexcept;
			// �f�X�g���N�^
			virtual ~AnimationPropertyColor32() noexcept;
		public:
			virtual void Update(float frame);
		};
	}
}