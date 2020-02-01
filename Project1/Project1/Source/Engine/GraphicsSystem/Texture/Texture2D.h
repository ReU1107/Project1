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
			// �R���X�g���N�^
			Texture2D(const std::string& name);
			// �f�X�g���N�^
			virtual ~Texture2D();

			// �C���X�^���XID
			static const InstanceID ID() { return InstanceID::Texture2D; }
			// �C���X�^���XID�擾
			virtual InstanceID GetInstanceID() const { return InstanceID::Texture2D; }

		};

	}
}

using Texture2DPtr = std::shared_ptr<Engine::GraphicsSystem::Texture2D>;
