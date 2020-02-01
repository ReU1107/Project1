#include "ShaderTable.h"
#include "../D3D12/D3D12Device.h"
#include "../D3D12.h"
#include "../Description/Include.h"
#include "../Enumerations/Include.h"
#include "../Interface/IResource.h"
#include "../Interface/IResourceView.h"
#include "../../Utility/Utility.h"
#include "../D3D12/D3D12ResourceView.h"
#include "../D3D12/D3D12DescriptorHeap.h"
#include "ShaderRecord.h"
#include "..//HardwareBuffer/StructuredBuffer.h"
/*
仮ということでD3D12に依存
後で書き換える予定
*/

namespace Engine 
{
	namespace GraphicsSystem 
	{
		ShaderTable::ShaderTable()
			: m_buffer(nullptr)
			, m_type()
		{
			m_buffer = new StructuredBuffer();
		}

		ShaderTable::~ShaderTable()
		{
			delete m_buffer;
		}

		IResource* ShaderTable::GetInterface() const
		{
			return m_buffer->GetInterface();
		}

		uint32_t ShaderTable::GetStride() const
		{
			return (uint32_t)m_buffer->GetStride();
		}

		uint32_t ShaderTable::GetSize() const
		{
			return (uint32_t)m_buffer->GetSize();
		}

		void ShaderTable::Create()
		{
			static constexpr uint32_t ShaderIdentifierSize = D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

			// シェーダーID用のサイズを追加
			uint32_t stride = (uint32_t)m_buffer->GetStride();
			stride += ShaderIdentifierSize;
			// アライメント調整
			stride = Alignment(stride, D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT);
			
			// レコードの数分確保する
			uint32_t size = stride * (uint32_t)m_records.size();

			size = Alignment(size, D3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENT);

			// シェーダーテーブル用バッファ作成
			m_buffer->SetStride(stride);
			m_buffer->SetCount(m_records.size());
			m_buffer->SetSize(size);
			m_buffer->SetStates(ResourceStates::GenericRead);
			m_buffer->IsDynamic();
			m_buffer->Create();
			
			// バッファ内の先頭アドレス取得
			auto mapData = m_buffer->Map();
			uint64_t index = 0;
			// テーブルにレコード情報を書き込んでいく
			for (auto& record : m_records) 
			{
				// 書き込みがすべて同じサイズになるとは限らない為
				uint8_t* shaderEntry = mapData + (stride * index++);

				// シェーダー識別子登録
				void* id = record->GetShaderIdentifier();
				memcpy(shaderEntry, id, ShaderIdentifierSize);

				// バッファ内のアドレスを進める
				shaderEntry += ShaderIdentifierSize;

				// シェーダーに対してのリソース設定
				uint32_t count = record->GetLocalRootArgumentCount();
				for (uint32_t i = 0; i < count; ++i) {
					auto localRootArgument= record->GetLocalRootArgument(i);

					switch (localRootArgument.type)
					{
					case LocalRootArgumentType::Resource:
					{
						auto resource = (ID3D12Resource1*)localRootArgument.resource->GetNativeResource();
						(*(D3D12_GPU_VIRTUAL_ADDRESS*)shaderEntry) = resource->GetGPUVirtualAddress();
						// アドレスを進める
						shaderEntry += sizeof(D3D12_GPU_VIRTUAL_ADDRESS);

					}	break;
					case LocalRootArgumentType::ResourceView:
					{
						auto resourceView = (D3D12ResourceView*)localRootArgument.view;
						//memcpy(/*(D3D12_GPU_DESCRIPTOR_HANDLE*)*/shaderEntry, &(resourceView->m_gpuHandle), sizeof(D3D12_GPU_DESCRIPTOR_HANDLE));
						////*(D3D12_GPU_DESCRIPTOR_HANDLE*)shaderEntry = resourceView->m_gpuHandle;
						//// アドレスを進める
						//shaderEntry += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);
						uint64_t heap = resourceView->m_gpuHandle.ptr;
						(*(uint64_t*)shaderEntry) = heap;
						// アドレスを進める
						shaderEntry += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);

					}	break;
					case LocalRootArgumentType::DescriptorTable:
					{
						auto descriptorTable = (D3D12DescriptorHeap*)localRootArgument.heap;
						uint64_t heap = descriptorTable->m_native->GetGPUDescriptorHandleForHeapStart().ptr;
						(*(uint64_t*)shaderEntry) = heap;
						// アドレスを進める
						shaderEntry += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);

					}	break;
					default:
						break;
					}

				}
			}

			m_buffer->Unmap();
		}

		void ShaderTable::SetName(const std::wstring& name)
		{
			ID3D12Resource1* resource = (ID3D12Resource1*)m_buffer->GetInterface()->GetNativeResource();
			resource->SetName(name.c_str());
		}

		void ShaderTable::RegisterShaderRecord(ShaderRecord* record)
		{
			/*
			ここでレコードの最大サイズを取得する必要がある
			理由:
			シェーダーテーブルは固定長配列のため
			各々のバッファの大きさを均一にしておく必要がある為
			*/
			uint32_t size = record->GetSize();
			if (m_buffer->GetStride() < size)
				m_buffer->SetStride(size);

			// レコードに対して番号を設定する
			uint32_t index = (uint32_t)m_records.size();
			record->SetRegisterIndex(index);

			m_records.push_back(record);
		}

	}
}

/*
一つのレコードは
D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENTで境界をアライメントする必要がある
テーブルの大きさはD3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENTでアライメントされる???

*/

/*
このタイミングで全てのレコード設定を終わっておく必要がある
*/

/*
デスクリプターテーブルに登録したものは
そのデスクリプター内の登録場所を設定する必要がある
*/

/*
つくりとしては
一つのシェーダーテーブルに対して複数の種類のシェーダーレコードを設定できるようにしてある
主な使い道は
hitgroupにおいてLowLevelInstanceとShaderRecordが1対1の関係でテクスチャ等を変えるときに使用できる
これを使用するためには
メッシュオブジェクトにおいてテクスチャが変わる場合は別のインスタンスとして登録しておいたほうがいい
そのためMeshが複数のSubMeshとMaterialを持つのはよろしくない
というよりはそのほうがAO等の組み合わせの時に最適化がしやすいと思う
*/