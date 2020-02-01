#pragma once
#include <cstdint>
#include <vector>
#include <string>

/*
できることなら
ルートシグネチャのレイアウトを見ながら
勝手に設定してくれるようにはしたい
*/

namespace Engine 
{
	namespace GraphicsSystem 
	{
		class IResource;
		enum class ShaderTableType;
		class ShaderRecord;
		class StructuredBuffer;

		class ShaderTable
		{
		private:
			using ShaderRecords = std::vector<ShaderRecord*>;
		private:
			ShaderRecords m_records;	// シェーダーレコード配列
			StructuredBuffer* m_buffer;	// バッファ
			ShaderTableType m_type;		// タイプ
		public:
			// コンストラクタ
			ShaderTable();
			// デストラクタ
			~ShaderTable();
		public:
			// リソース取得
			IResource* GetInterface() const;
			// 一つのシェーダーレコードのサイズ取得
			uint32_t GetStride() const;
			// シェーダーレコードを内包するバッファのサイズ取得
			uint32_t GetSize() const;
			// シェーダーレコード登録
			void RegisterShaderRecord(ShaderRecord* record);

			void Create();

			void SetName(const std::wstring& name);

		};
	}
}

/*
最大
4096byteだったけ?
*/