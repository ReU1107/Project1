#pragma once
#include "Collider.h"
#include <DirectXMath.h>
namespace Engine 
{

	// メッシュコライダー(衝突装置)(離散方向ポリトープ)
	class MeshCollider final : public Collider
	{
	private:
		using base = Collider;
	private:
		DirectX::XMFLOAT3 m_localCenter;	// 中心座標(ローカル)
		DirectX::XMFLOAT3 m_localSize;		// サイズ(ローカル)
	public:
		// コンストラクタ
		MeshCollider() noexcept;
		// デストラクタ
		~MeshCollider() noexcept;

	};
}