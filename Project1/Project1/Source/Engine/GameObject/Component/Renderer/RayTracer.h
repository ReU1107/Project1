#pragma once
#include "Renderer.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class RaytracingMesh;
	}

	class RayTracer : public Renderer
	{
	private:
		using base = Renderer;
		using RaytracingMeshPtr = std::shared_ptr<GraphicsSystem::RaytracingMesh>;
		using HitGroupNames = std::vector<std::wstring>;
		using RayTracerPtr = std::shared_ptr<RayTracer>;
	public:
		static std::vector<RayTracerPtr> allRayTracers;
	private:
		RaytracingMeshPtr m_mesh;
		HitGroupNames m_hitGroupNames;	// �q�b�g�O���[�v���z��
		bool m_isRebuild;
	public:
		RayTracer() noexcept;
		
		virtual ~RayTracer() noexcept;
	public:
		static InstanceID ID() { return InstanceID::RayTracer; }

		virtual InstanceID GetInstanceID() const override { return InstanceID::RayTracer; }

	public:
		// �q�b�g�O���[�v���ǉ�
		void AddHitGroupName(const std::wstring& name);
		// ���b�V���ݒ�
		void SetMesh(RaytracingMeshPtr mesh);

		// ���b�V���擾
		RaytracingMeshPtr GetMesh() const;

		const HitGroupNames& GetHitGroupNames() const;

		void ReBuild(bool flag = true) { m_isRebuild = flag; }

		bool IsReBuild() const { return m_isRebuild; }

	};

	template<>
	inline std::shared_ptr<RayTracer> Component::Create()
	{
		auto tracer = std::make_shared<RayTracer>();
		RayTracer::allRayTracers.push_back(tracer);
		return tracer;
	}

}

using RayTracerPtr = std::shared_ptr<Engine::RayTracer>;