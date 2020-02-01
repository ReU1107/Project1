#pragma once
#include "Texture.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Texture2D : public Texture
		{
		private:
			using base = Texture;

		public:
			// コンストラクタ
			Texture2D(const std::string& name);
			// デストラクタ
			virtual ~Texture2D();

			// インスタンスID
			static const InstanceID ID() { return InstanceID::Texture2D; }
			// インスタンスID取得
			virtual InstanceID GetInstanceID() const { return InstanceID::Texture2D; }

		};

	}
}

using Texture2DPtr = std::shared_ptr<Engine::GraphicsSystem::Texture2D>;
