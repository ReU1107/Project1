#pragma once
#include "Renderer.h"
namespace Engine
{

	// ‘O•ûéŒ¾
	class Billboard;

	class BillboardRenderer final : public Renderer
	{
	private:
		using base = Renderer;
	private:
		Billboard* m_billboard;
	public:
		BillboardRenderer() noexcept;

		~BillboardRenderer() noexcept;

	public:
		void SetBillboard(Billboard* billboard);
	};
}

using BillboardRendererPtr = std::shared_ptr<Engine::BillboardRenderer>;