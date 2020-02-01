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
			// コンストラクタ
			Graphics();
			// デストラクタ
			~Graphics();

			void CreateDefaultTexture();

		};
	}
}