#pragma once
#include "Filter.h"
#include <iostream>

namespace Engine
{
	namespace GraphicsSystem
	{
		// 前方宣言
		class Mesh;
	}

	class MeshFilter final : public Filter
	{
	private:
		using base = Filter;
	private:
		std::shared_ptr<GraphicsSystem::Mesh> m_mesh;// メッシュ

	public:
		// コンストラクタ
		MeshFilter() noexcept;
		// デストラクタ
		virtual ~MeshFilter() noexcept;

	public:
		// メッシュ設定
		void SetMesh(std::shared_ptr<GraphicsSystem::Mesh> mesh);

	public:
		// メッシュ取得
		std::shared_ptr<GraphicsSystem::Mesh> GetMesh() const;
	};
}