#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include "../../Math/Matrix4x4.h"
/*
�N���G�C�g�֐���separate�ɂ����Ă̐���
separate�͕��i���Ƃ𕪉����邩���Ȃ��̏���separate��true�̏ꍇ�̓T�u���b�V�����Ƃɕ������s��
false�̏ꍇ�͑S�Ă���ɂ��Ă����Ă������ƂɂȂ�
true�̎g�����Ƃ��ă{�[���A�j���[�V�����̓K�p����ۂɕK�v�s���ɂȂ�
�t�ɃA�j���[�V�������Ȃ����̂�false�ɂ��Ă������ق�������
*/

namespace Engine
{
	namespace GraphicsSystem
	{
		class RaytracingSubMesh;
		class Mesh;
		class Material;
		class ProceduralMesh;
		class ShaderTable;
		class Resource;
		class ResourceView;
		class GraphicsCommandList;
		enum class RaytracingInstanceFlags : uint8_t;

		class RaytracingMesh
		{
		private:
			using SubMeshPtr = std::shared_ptr<RaytracingSubMesh>;
			using SubMeshes = std::vector<SubMeshPtr>;
			using ShaderIdentifiers = std::vector<void*>;
			using RaytracingMeshPtr = std::shared_ptr<RaytracingMesh>;
			using MaterialPtr = std::shared_ptr<Material>;
			using MeshPtr = std::shared_ptr<Mesh>;
			using ProceduralMeshPtr = std::shared_ptr<ProceduralMesh>;
		private:
			SubMeshes m_subMeshes;					// �T�u���b�V���z��
			ShaderIdentifiers m_identifiers;		// �V�F�[�_�[���ʔz��
			MeshPtr m_baseMesh;					// ��{���b�V��
			ProceduralMeshPtr m_proceduralMesh;	// �v���V�[�W�������b�V��
			bool m_isProcedural;		

		public:
			// �R���X�g���N�^
			RaytracingMesh();
			// �f�X�g���N�^
			~RaytracingMesh();

		public:
			static RaytracingMeshPtr Create(MeshPtr mesh, uint32_t shaderCount = 1, bool isReBuild = false);
			static RaytracingMeshPtr Create(MeshPtr mesh, MaterialPtr material, uint32_t shaderCount = 1, bool isReBuild = false);
			static RaytracingMeshPtr Create(ProceduralMeshPtr mesh, uint32_t shaderCount = 1, bool isReBuild = false);
			static RaytracingMeshPtr Create(ProceduralMeshPtr mesh, MaterialPtr material, uint32_t shaderCount = 1, bool isReBuild = false);

		public:
			// �T�u���b�V���ǉ�
			void AddSubMesh(SubMeshPtr subMesh);

			// 
			SubMeshes& GetSubMeshes();

			// �T�u���b�V���擾
			SubMeshPtr GetSubMesh(uint32_t index) const;
			// �T�u���b�V�����擾
			uint32_t GetSubMeshCount() const;

			void SetTransformMatrix(const Matrix4x4& matrix);

			void SetMask(uint32_t mask);

			// �V�F�[�_�[�e�[�u�����ł̎����̔ԍ���o�^���邽��
			void AddShader(void* identifier);
			// AddShader��ɕK���Ă�
			void SetShader(ShaderTable* hitGroupTable);

			void Build(GraphicsCommandList* list);

			// �x�[�X�̃��b�V���̒��_���ɕω�����������ǂ�ł�������
			// ��蒼��
			void ReBuild();

			MeshPtr GetBaseMesh() const;

			ProceduralMeshPtr GetBaseProceduralMesh() const;

		};

	}
}

using RaytracingMeshPtr = std::shared_ptr<Engine::GraphicsSystem::RaytracingMesh>;
