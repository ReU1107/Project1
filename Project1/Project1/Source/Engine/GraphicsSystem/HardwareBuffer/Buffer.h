#pragma once
#include <cstdint>
#include <string>
#include "../Enumerations/ResourceViewType.h"

/*
copyableを使用する場合はデータをVRAM上に作成するため
コマンドリストを使用してコピー処理を行ってください
*/

namespace Engine
{

	namespace GraphicsSystem
	{
		
		// 前方宣言
		class IResource;
		enum class ResourceStates : uint16_t;
		enum class ResourceFlags : uint8_t;
		class ResourceView;
		class ResourceDescriptor;

		class Buffer
		{
		protected:
			IResource* m_interface;			// リソース
			Buffer* m_copyable;				// コピー用
			ResourceView* m_view;			// 
			uint64_t m_stride;				// ストライド
			uint64_t m_count;				// 数
			uint64_t m_size;				// サイズ
			ResourceStates m_states;		// ステート
			ResourceFlags m_flags;			// フラグ
			ResourceViewType m_viewType;	// ビュータイプ
			bool m_isDynamic;				// よくCPUからアクセスするか
			bool m_isRaw;					// 生のデータとしてアクセスするかByteAddressBufferならtrue

		public:
			// コンストラクタ
			Buffer(ResourceViewType type);
			// デストラクタ
			virtual ~Buffer();
		public:
			// ストライド設定
			void SetStride(uint64_t stride);
			// 数設定
			void SetCount(uint64_t count);
			// サイズ設定()
			void SetSize(uint64_t size);
			// ステート設定
			void SetStates(ResourceStates states);

			// フラグ設定
			void SetFlags(ResourceFlags flags);

			void SetInterface(IResource* resource);

			void Dynamic(bool dynamic = true);

			void Raw(bool raw = true);

			// ストライド取得
			uint64_t GetStride() const { return m_stride; }
			// 数取得
			uint64_t GetCount() const { return m_count; }
			// サイズ取得
			uint64_t GetSize() const { return m_size; }
			// リソース取得
			IResource* GetInterface() const { return m_interface; }

			ResourceStates GetStates() const { return m_states; }

			Buffer* GetCopyable() const { return m_copyable; }

			// リソースビュー取得
			ResourceView* GetView() const { return m_view; }
			// 
			bool IsDynamic() { return m_isDynamic; }

			bool IsRaw() { return m_isRaw; }

			void RecreateResourceView(ResourceDescriptor* descriptor);

			// 作成
			virtual void Create(void* data = nullptr);

			uint8_t* Map(uint64_t begin = 0, uint64_t end = 0);

			void Unmap(uint64_t begin = 0, uint64_t end = 0);

			// バッファ内更新
			void Update(void* data, uint64_t begin = 0, uint64_t end = 0);

			void SetName(const std::wstring& name);
		};

	}

}