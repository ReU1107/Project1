#pragma once

namespace Engine
{
	namespace AudioSystem
	{
		class AudioScene
		{
		private:


		public:
			// �R���X�g���N�^
			AudioScene();
			// �f�X�g���N�^
			virtual ~AudioScene();

			// �V�~�����[�V����
			void Simulate(float step);

		};
	}
}