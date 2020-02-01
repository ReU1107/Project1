#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class ResourceDescriptor;
		// グラフィックスに関連するパス
		class GraphicsPass
		{
		protected:
			ResourceDescriptor* m_shaderResourceDescriptor;	// CBV,SRV,UAV登録先
			bool m_isActive;

		public:
			// コンストラクタ
			GraphicsPass();
			// デストラクタ
			virtual ~GraphicsPass();

			// 
			void Active(bool active = true);

			// 
			bool IsActive() const { return m_isActive; }

			// 初期化処理
			virtual void OnInitialize() = 0;

		};
	}
}