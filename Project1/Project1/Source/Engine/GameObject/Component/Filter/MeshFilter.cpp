#include "MeshFilter.h"
namespace Engine
{

	MeshFilter::MeshFilter() noexcept
		: base("MeshFilter")
		, m_mesh(nullptr)
	{
	}

	MeshFilter::~MeshFilter() noexcept
	{
	}

	void MeshFilter::SetMesh(std::shared_ptr<GraphicsSystem::Mesh> mesh)
	{
		m_mesh = mesh;
	}

	std::shared_ptr<GraphicsSystem::Mesh> MeshFilter::GetMesh() const
	{
		return m_mesh;
	}
}