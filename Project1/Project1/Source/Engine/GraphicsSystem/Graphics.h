#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class IDevice;

		class Graphics
		{
		private:
			IDevice* m_device;
		public:
			// �R���X�g���N�^
			Graphics();
			// �f�X�g���N�^
			~Graphics();

			void CreateDefaultTexture();

		};
	}
}