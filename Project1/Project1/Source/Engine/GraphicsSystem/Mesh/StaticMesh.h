#pragma once
#include "Mesh.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		// �����Ȃ����b�V��
		class StaticMesh : public Mesh
		{
		private:
			using base = Mesh;

		public:
			// �R���X�g���N�^
			StaticMesh(const std::string& name);
			// �f�X�g���N�^
			virtual ~StaticMesh();


			// �o�b�t�@�X�V
			virtual void Update() override;

			// ���_�o�b�t�@�쐬
			virtual void CreateVertexBuffes() override;
		};
	}
}

using StaticMeshPtr = std::shared_ptr<Engine::GraphicsSystem::StaticMesh>;
