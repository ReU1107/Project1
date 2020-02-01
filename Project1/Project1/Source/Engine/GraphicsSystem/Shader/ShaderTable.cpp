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
���Ƃ������Ƃ�D3D12�Ɉˑ�
��ŏ���������\��
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

			// �V�F�[�_�[ID�p�̃T�C�Y��ǉ�
			uint32_t stride = (uint32_t)m_buffer->GetStride();
			stride += ShaderIdentifierSize;
			// �A���C�����g����
			stride = Alignment(stride, D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT);
			
			// ���R�[�h�̐����m�ۂ���
			uint32_t size = stride * (uint32_t)m_records.size();

			size = Alignment(size, D3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENT);

			// �V�F�[�_�[�e�[�u���p�o�b�t�@�쐬
			m_buffer->SetStride(stride);
			m_buffer->SetCount(m_records.size());
			m_buffer->SetSize(size);
			m_buffer->SetStates(ResourceStates::GenericRead);
			m_buffer->IsDynamic();
			m_buffer->Create();
			
			// �o�b�t�@���̐擪�A�h���X�擾
			auto mapData = m_buffer->Map();
			uint64_t index = 0;
			// �e�[�u���Ƀ��R�[�h������������ł���
			for (auto& record : m_records) 
			{
				// �������݂����ׂē����T�C�Y�ɂȂ�Ƃ͌���Ȃ���
				uint8_t* shaderEntry = mapData + (stride * index++);

				// �V�F�[�_�[���ʎq�o�^
				void* id = record->GetShaderIdentifier();
				memcpy(shaderEntry, id, ShaderIdentifierSize);

				// �o�b�t�@���̃A�h���X��i�߂�
				shaderEntry += ShaderIdentifierSize;

				// �V�F�[�_�[�ɑ΂��Ẵ��\�[�X�ݒ�
				uint32_t count = record->GetLocalRootArgumentCount();
				for (uint32_t i = 0; i < count; ++i) {
					auto localRootArgument= record->GetLocalRootArgument(i);

					switch (localRootArgument.type)
					{
					case LocalRootArgumentType::Resource:
					{
						auto resource = (ID3D12Resource1*)localRootArgument.resource->GetNativeResource();
						(*(D3D12_GPU_VIRTUAL_ADDRESS*)shaderEntry) = resource->GetGPUVirtualAddress();
						// �A�h���X��i�߂�
						shaderEntry += sizeof(D3D12_GPU_VIRTUAL_ADDRESS);

					}	break;
					case LocalRootArgumentType::ResourceView:
					{
						auto resourceView = (D3D12ResourceView*)localRootArgument.view;
						//memcpy(/*(D3D12_GPU_DESCRIPTOR_HANDLE*)*/shaderEntry, &(resourceView->m_gpuHandle), sizeof(D3D12_GPU_DESCRIPTOR_HANDLE));
						////*(D3D12_GPU_DESCRIPTOR_HANDLE*)shaderEntry = resourceView->m_gpuHandle;
						//// �A�h���X��i�߂�
						//shaderEntry += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);
						uint64_t heap = resourceView->m_gpuHandle.ptr;
						(*(uint64_t*)shaderEntry) = heap;
						// �A�h���X��i�߂�
						shaderEntry += sizeof(D3D12_GPU_DESCRIPTOR_HANDLE);

					}	break;
					case LocalRootArgumentType::DescriptorTable:
					{
						auto descriptorTable = (D3D12DescriptorHeap*)localRootArgument.heap;
						uint64_t heap = descriptorTable->m_native->GetGPUDescriptorHandleForHeapStart().ptr;
						(*(uint64_t*)shaderEntry) = heap;
						// �A�h���X��i�߂�
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
			�����Ń��R�[�h�̍ő�T�C�Y���擾����K�v������
			���R:
			�V�F�[�_�[�e�[�u���͌Œ蒷�z��̂���
			�e�X�̃o�b�t�@�̑傫�����ψ�ɂ��Ă����K�v�������
			*/
			uint32_t size = record->GetSize();
			if (m_buffer->GetStride() < size)
				m_buffer->SetStride(size);

			// ���R�[�h�ɑ΂��Ĕԍ���ݒ肷��
			uint32_t index = (uint32_t)m_records.size();
			record->SetRegisterIndex(index);

			m_records.push_back(record);
		}

	}
}

/*
��̃��R�[�h��
D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT�ŋ��E���A���C�����g����K�v������
�e�[�u���̑傫����D3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENT�ŃA���C�����g�����???

*/

/*
���̃^�C�~���O�őS�Ẵ��R�[�h�ݒ���I����Ă����K�v������
*/

/*
�f�X�N���v�^�[�e�[�u���ɓo�^�������̂�
���̃f�X�N���v�^�[���̓o�^�ꏊ��ݒ肷��K�v������
*/

/*
����Ƃ��Ă�
��̃V�F�[�_�[�e�[�u���ɑ΂��ĕ����̎�ނ̃V�F�[�_�[���R�[�h��ݒ�ł���悤�ɂ��Ă���
��Ȏg������
hitgroup�ɂ�����LowLevelInstance��ShaderRecord��1��1�̊֌W�Ńe�N�X�`������ς���Ƃ��Ɏg�p�ł���
������g�p���邽�߂ɂ�
���b�V���I�u�W�F�N�g�ɂ����ăe�N�X�`�����ς��ꍇ�͕ʂ̃C���X�^���X�Ƃ��ēo�^���Ă������ق�������
���̂���Mesh��������SubMesh��Material�����̂͂�낵���Ȃ�
�Ƃ������͂��̂ق���AO���̑g�ݍ��킹�̎��ɍœK�������₷���Ǝv��
*/