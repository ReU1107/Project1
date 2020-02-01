#pragma once

namespace Engine
{
	namespace AudioSystem
	{
		class AudioScene
		{
		private:


		public:
			// コンストラクタ
			AudioScene();
			// デストラクタ
			virtual ~AudioScene();

			// シミュレーション
			void Simulate(float step);

		};
	}
}