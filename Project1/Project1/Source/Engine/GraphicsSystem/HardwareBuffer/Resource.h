#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IResource;
		struct TextureDesc;

		enum class ResourceStates : uint16_t;
		/*
		インターフェイスと現在の
		リソースの状態を持ちたかった
		*/
		class Resource
		{
		private:
			IResource* m_interface;
			ResourceStates m_states;
		public:
			// コンストラクタ
			Resource();
			// デストラクタ
			~Resource();
			static Resource* Create(const TextureDesc& desc);

			// ステート設定
			void SetStates(ResourceStates states);
			// インターフェイス設定
			void SetInterface(IResource* resource);
			// インターフェイス取得
			IResource* GetInterface() const;
			// ステート取得
			ResourceStates GetStates() const;

		};
	}
}