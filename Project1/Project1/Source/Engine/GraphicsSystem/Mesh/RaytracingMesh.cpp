#include "RaytracingMesh.h"
#include "RaytracingSubMesh.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/SubMesh.h"
#include "../Mesh/Material.h"
#include "../Shader/ShaderRecord.h"
#include "..//HardwareBuffer//ConstantBuffer.h"
#include "..//HardwareBuffer//IndexBuffer.h"
#include "..//HardwareBuffer//VertexBuffer.h"
#include "..//HardwareBuffer//StructuredBuffer.h"
#include "..//HardwareBuffer/BottomLevelAccelerationStructure.h"
#include "../Texture/Texture.h"
#include "..//Shader/ShaderTable.h"
#include "..//HardwareBuffer//ResourceView.h"
#include "..//HardwareBuffer//Resource.h"
#include "..//Mesh/ProceduralMesh.h"
#include "..//../Utility/EnumOperator.h"
#include "..//Enumerations/Include.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		RaytracingMesh::RaytracingMesh()
			: m_baseMesh(nullptr)
			, m_isProcedural(false)
		{
		}

		RaytracingMesh::~RaytracingMesh()
		{

		}

		RaytracingMesh::RaytracingMeshPtr RaytracingMesh::Create(MeshPtr mesh, uint32_t shaderCount, bool isReBuild)
		{
			auto rayMesh = std::make_shared<RaytracingMesh>();
			rayMesh->m_baseMesh = mesh;

			auto& subMeshes = mesh->GetSubMeshes();
			uint32_t count = (uint32_t)subMeshes.size();

			for (uint32_t i = 0; i < count; ++i)
			{
				auto subMesh = subMeshes[i];
				auto material = subMesh->GetMaterial();

				auto bottomLevelAS = std::make_shared<BottomLevelAccelerationStructure>();
				bottomLevelAS->AddTraianglesGeometry(mesh->GetVertexBuffer(0), subMesh->GetIndexBuffer());

				bottomLevelAS->Recreate();

				auto raySubMesh = std::make_shared<RaytracingSubMesh>();

				raySubMesh->SetBottomLevelAS(bottomLevelAS);

				// ���̃T�u���b�V����`�悷��ɓ������ĕK�v�ȏ�����������
				// �V�F�[�_�[���R�[�h�쐬
				raySubMesh->CreateShaderRecord(shaderCount);

				for (uint32_t j = 0; j < shaderCount; ++j)
				{
					ShaderRecord* record = raySubMesh->GetShaderRecord(j);

					// �}�e���A��������������
					ConstantBuffer* constantBuffer = material->GetConstantBuffer();
					//record->AddResource(constantBuffer);

					VertexBuffer* normalBuffer = mesh->GetVertexBuffer(1);
					record->AddResource(normalBuffer);

					VertexBuffer* uvBuffer = mesh->GetVertexBuffer(2);
					//record->AddResource(uvBuffer);

					IndexBuffer* indexBuffer = subMesh->GetIndexBuffer();
					record->AddResource(indexBuffer);

					auto texture = material->GetDecalTexture();
					if (texture)
					{
						texture->CreateShaderResourceView();
						//record->AddResourceView(texture->GetShaderResourceView());
					}
					else
					{
						// �e�N�X�`���Ȃ��̃O���[�v�ɏ�������K�v������
					}
				}

				rayMesh->AddSubMesh(raySubMesh);

			}

			return rayMesh;
		}

		RaytracingMesh::RaytracingMeshPtr RaytracingMesh::Create(MeshPtr mesh, MaterialPtr material, uint32_t shaderCount, bool isReBuild)
		{
			auto rayMesh = std::make_shared<RaytracingMesh>();
			rayMesh->m_baseMesh = mesh;

			auto& subMeshes = mesh->GetSubMeshes();
			uint32_t count = (uint32_t)subMeshes.size();

			auto bottomLevelAS = std::make_shared<BottomLevelAccelerationStructure>();

			for (uint32_t i = 0; i < count; ++i)
			{
				auto subMesh = subMeshes[i];

				bottomLevelAS->AddTraianglesGeometry(mesh->GetVertexBuffer(0), subMesh->GetIndexBuffer());

				bottomLevelAS->Create();

			}

			auto raySubMesh = std::make_shared<RaytracingSubMesh>();
			raySubMesh;

			for (uint32_t j = 0; j < shaderCount; ++j)
			{
				ShaderRecord* record = raySubMesh->GetShaderRecord(j);

				// �}�e���A��������������
				ConstantBuffer* constantBuffer = material->GetConstantBuffer();
				record->AddResource(constantBuffer);

				VertexBuffer* normalBuffer = mesh->GetVertexBuffer(1);
				record->AddResource(normalBuffer);

				VertexBuffer* uvBuffer = mesh->GetVertexBuffer(2);
				record->AddResource(uvBuffer);

				auto texture = material->GetDecalTexture();
				if (texture)
				{
					record->AddResourceView(texture->GetShaderResourceView());
				}
				else
				{
					// �e�N�X�`���Ȃ��̃O���[�v�ɏ�������K�v������
				}
			}

			rayMesh->AddSubMesh(raySubMesh);

			return RaytracingMeshPtr();
		}

		RaytracingMesh::RaytracingMeshPtr RaytracingMesh::Create(ProceduralMeshPtr mesh, uint32_t shaderCount, bool isReBuild)
		{
			auto rayMesh = std::make_shared<RaytracingMesh>();
			rayMesh->m_proceduralMesh = mesh;
			rayMesh->m_isProcedural = true;

			auto& subMeshes = mesh->GetSubMeshes();
			uint32_t count = (uint32_t)subMeshes.size();

			for (uint32_t i = 0; i < count; ++i)
			{
				auto subMesh = subMeshes[i];
				auto material = subMesh->GetMaterial();

				//auto rayGeometry = std::make_shared<RaytracingGeometry>();
				//rayGeometry->AddProceduralGeometry(mesh->GetBuffer());

				//rayGeometry->Create();

				//auto raySubMesh = std::make_shared<RaytracingSubMesh>();

				//raySubMesh->CreateShaderRecord(shaderCount);

				//for (uint32_t j = 0; j < shaderCount; ++j)
				//{
				//	ShaderRecord* record = raySubMesh->GetShaderRecord(j);

				//	// AABB��񏑂�����
				//	StructuredBuffer* structuredBuffer = mesh->GetBuffer();
				//	if (structuredBuffer)
				//	{
				//		record->AddResource(structuredBuffer);
				//	}

				//	// �}�e���A����񏑂�����
				//	ConstantBuffer* constantBuffer = material->GetConstantBuffer();
				//	if (constantBuffer)
				//	{
				//		record->AddResource(constantBuffer);
				//	}
				//}

				//rayMesh->AddSubMesh(raySubMesh);
			}
			return rayMesh;
		}

		RaytracingMesh::RaytracingMeshPtr RaytracingMesh::Create(ProceduralMeshPtr mesh, MaterialPtr material, uint32_t shaderCount, bool isReBuild)
		{
			return RaytracingMeshPtr();
		}

		void RaytracingMesh::AddSubMesh(SubMeshPtr subMesh)
		{
			m_subMeshes.push_back(subMesh);
		}

		RaytracingMesh::SubMeshes& RaytracingMesh::GetSubMeshes()
		{
			return m_subMeshes;
		}

		RaytracingMesh::SubMeshPtr RaytracingMesh::GetSubMesh(uint32_t index) const
		{
			return m_subMeshes[index];
		}

		uint32_t RaytracingMesh::GetSubMeshCount() const
		{
			return (uint32_t)m_subMeshes.size();
		}

		void RaytracingMesh::SetTransformMatrix(const Matrix4x4& matrix)
		{
			for (auto& subMesh : m_subMeshes)
			{
				subMesh->SetTransformMatrix(matrix);
			}

		}

		void RaytracingMesh::SetMask(uint32_t mask)
		{
			for (auto& subMesh : m_subMeshes)
			{
				subMesh->SetMask(mask);
			}
		}

		void RaytracingMesh::AddShader(void* identifier)
		{
			m_identifiers.push_back(identifier);
		}

		void RaytracingMesh::SetShader(ShaderTable* hitGroupTable)
		{
			// �{����������T�u���b�V���e���ꂼ��ŃV�F�[�_�[������������
			uint32_t shaderCount = (uint32_t)m_identifiers.size();
			// �����ŃT�u���b�V���ƕ`�揈���Ɏg�p����V�F�[�_�[�̊֘A�Â����s��
			for (auto subMesh : m_subMeshes)
			{
				for (uint32_t i = 0; i < shaderCount; ++i)
				{
					const auto& identifier = m_identifiers[i];
					ShaderRecord* record = subMesh->GetShaderRecord(i);
					if (!record)
						assert(!"�V�F�[�_�[���R�[�h������܂���");
					record->SetShaderIdentifier(identifier);
					hitGroupTable->RegisterShaderRecord(record);
				}
			}
		}

		void RaytracingMesh::Build(GraphicsCommandList* list)
		{
			for (auto& subMesh : m_subMeshes)
			{
				subMesh->Build(list);
			}
		}

		void RaytracingMesh::ReBuild()
		{
			for (auto& subMesh : m_subMeshes)
			{
				subMesh;
			}
		}

		RaytracingMesh::MeshPtr RaytracingMesh::GetBaseMesh() const
		{
			return m_baseMesh;
		}

		RaytracingMesh::ProceduralMeshPtr RaytracingMesh::GetBaseProceduralMesh() const
		{
			return m_proceduralMesh;
		}
	}
}
