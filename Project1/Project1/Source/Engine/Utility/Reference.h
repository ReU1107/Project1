#pragma once
#include <cstdint>

namespace Engine 
{
	/*
	AddRef Additional ReferenceCount
	DirectXと同じように名前を付ける
	*/
	// 参照カウント
	class Reference
	{
	private:
		uint32_t m_refCount;	// 参照カウント
	public:
		// コンストラクタ
		Reference() noexcept;
		// 仮想デストラクタ
		virtual ~Reference() noexcept {}
	public:

		// 参照カウント増加
		uint32_t AddRef();

		// 解放
		uint32_t Release();
	};
}
