#pragma once
#include "ComputePass.h"
#include <vector>
#include <iostream>

namespace Engine
{
	namespace SceneManagement
	{
		class Scene;
	}

	namespace GraphicsSystem
	{
		class RenderTexture;
		class RaytracingPipeline;
		class RaytracingMesh;
		class RaytracingSubMesh;
		class RootSignature;
		class ShaderTable;
		class ShaderRecord;
		class CommandList;
		class GraphicsCommandList;
		class TopLevelAccelerationStructure;
		struct SubTopLevelAccelerationStructureDesc;

		struct ShaderTables
		{
			union
			{
				struct
				{
					ShaderTable* rayGenerateTable;	// ���C�����p�e�[�u��
					ShaderTable* hitGroupTable;		// �q�b�g�O���[�v�e�[�u��
					ShaderTable* missTable;			// �~�X�e�[�u��
				}each;
				struct
				{
					ShaderTable* table;				// ���L�e�[�u��
					uint64_t hitGroupCount;			// �q�b�g�O���[�v�̐�
					uint64_t missCount;				// �~�X�̐�
				}share;
			};
			bool isShare;
			ShaderTables()
				: each()
				, isShare(false)
			{
			}
		};

		// ���C�g���[�V���O�̏������s��
		class RaytracingPass : public ComputePass
		{
		private:
			using base = ComputePass;
			using TopLevelASPtr = std::shared_ptr<TopLevelAccelerationStructure>;
			using RenderTextures = std::vector<RenderTexture*>;
			using RootSignatures = std::vector<RootSignature*>;
			using ShaderRecords = std::vector<ShaderRecord*>;
			using SubDescs = std::vector<SubTopLevelAccelerationStructureDesc>;

		protected:
			ShaderRecord* m_rayRecord;
			ShaderRecords m_missRecords;
			SubDescs m_subDescs;

			TopLevelASPtr m_topLevelAS;
			ShaderTables m_tables;
			SceneManagement::Scene* m_belongScene;					// �����V�[��

			RaytracingPipeline* m_pipeline;			// �p�C�v���C��
			RootSignature* m_globalRootSignature;	// �O���[�o���V�O�l�`�������ʂɂ����Ă���
			RootSignatures m_localRootSignatures;	// ���[�g�V�O�l�`���z��

			uint32_t m_subMeshCount;				// �T�u���b�V������
			bool m_active;							// 
		public:
			// �R���X�g���N�^
			RaytracingPass();
			// �f�X�g���N�^
			virtual ~RaytracingPass();

			void SetScene(SceneManagement::Scene* scene) { m_belongScene = scene; }

			// �V�F�[�_�[�e�[�u���쐬
			void CreateShaderTable(bool share = false);
			// ���C�쐬�V�F�[�_�[�o�^
			void RegisterRayGenerateRecord(void* identifier);
			// �~�X�V�F�[�_�[�o�^
			void RegisterMissRecord(void* identifier);

			// �q�b�g�O���[�v�e�[�u���擾
			ShaderTable* GetHitGroupTable() const;
			// ���C�����p�e�[�u���擾
			ShaderTable* GetRayGenerateTable() const;
			// �~�X�V�F�[�_�[�e�[�u���擾
			ShaderTable* GetMissTable() const;

			void SetName(const std::wstring& name);
		};
	}
}