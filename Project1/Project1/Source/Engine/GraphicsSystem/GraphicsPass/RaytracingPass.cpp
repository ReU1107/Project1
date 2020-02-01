#include "RaytracingPass.h"
#include "../HardwareBuffer/RootSignature.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Description/Include.h"
#include "../../Utility/EnumOperator.h"

#include "..//Shader/ShaderTable.h"
#include "..//HardwareBuffer//ResourceDescriptor.h"
#include "..//HardwareBuffer//ResourceView.h"
#include "..//Enumerations/Include.h"
#include "..//Mesh/Include.h"
#include "..//HardwareCommand/GraphicsCommandList.h"
#include "../Shader/ShaderRecord.h"
#include "../Texture/Texture.h"

#include "../HardwareBuffer/TopLevelAccelerationStructure.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		RaytracingPass::RaytracingPass()
			: base()
			, m_pipeline(nullptr)
			, m_globalRootSignature(nullptr)
			, m_rayRecord(nullptr)
			, m_active(false)
		{
			m_topLevelAS = std::make_shared<TopLevelAS>();
		}

		RaytracingPass::~RaytracingPass()
		{
			for (auto& rootSignature : m_localRootSignatures)
			{
				delete rootSignature;
			}

			for (auto& record : m_missRecords)
			{
				delete record;
			}

			delete m_globalRootSignature;
			delete m_pipeline;
			delete m_rayRecord;

		}

		void RaytracingPass::CreateShaderTable(bool share)
		{
			if (share)
			{
				m_tables.isShare = true;
				m_tables.share.table = new ShaderTable();
			}
			else
			{
				m_tables.isShare = false;
				m_tables.each.rayGenerateTable = new ShaderTable();
				m_tables.each.hitGroupTable = new ShaderTable();
				m_tables.each.missTable = new ShaderTable();
			}
		}

		void RaytracingPass::RegisterRayGenerateRecord(void* identifier)
		{
			ShaderRecord* record = new ShaderRecord();
			record->SetShaderIdentifier(identifier);
			m_rayRecord = record;
			GetRayGenerateTable()->RegisterShaderRecord(record);
		}

		void RaytracingPass::RegisterMissRecord(void* identifier)
		{
			ShaderRecord* record = new ShaderRecord();
			record->SetShaderIdentifier(identifier);
			m_missRecords.push_back(record);
			GetMissTable()->RegisterShaderRecord(record);
		}

		ShaderTable* RaytracingPass::GetHitGroupTable() const
		{
			ShaderTable* table = (m_tables.isShare) ? m_tables.share.table : m_tables.each.hitGroupTable;
			return table;
		}

		ShaderTable* RaytracingPass::GetRayGenerateTable() const
		{
			ShaderTable* table = (m_tables.isShare) ? m_tables.share.table : m_tables.each.rayGenerateTable;
			return table;
		}

		ShaderTable* RaytracingPass::GetMissTable() const
		{
			ShaderTable* table = (m_tables.isShare) ? m_tables.share.table : m_tables.each.missTable;
			return table;
		}

		void RaytracingPass::SetName(const std::wstring& name)
		{
		}

	}
}
