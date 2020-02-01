#pragma once
#include "Filter.h"
#include <iostream>

namespace Engine
{
	namespace GraphicsSystem
	{
		// �O���錾
		class Mesh;
	}

	class MeshFilter final : public Filter
	{
	private:
		using base = Filter;
	private:
		std::shared_ptr<GraphicsSystem::Mesh> m_mesh;// ���b�V��

	public:
		// �R���X�g���N�^
		MeshFilter() noexcept;
		// �f�X�g���N�^
		virtual ~MeshFilter() noexcept;

	public:
		// ���b�V���ݒ�
		void SetMesh(std::shared_ptr<GraphicsSystem::Mesh> mesh);

	public:
		// ���b�V���擾
		std::shared_ptr<GraphicsSystem::Mesh> GetMesh() const;
	};
}