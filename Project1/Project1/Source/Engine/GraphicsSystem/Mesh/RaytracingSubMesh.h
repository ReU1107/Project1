#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include "../../Math/Matrix4x4.h"

namespace Engine
{

	namespace GraphicsSystem
	{

		// �O���錾
		class IRaytracingGeometry;
		class BottomLevelAccelerationStructure;
		class ShaderRecord;
		class GraphicsCommandList;
		class Material;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		class RaytracingSubMesh
		{
		private:
			using ShaderRecords = std::vector<ShaderRecord*>;
			using MaterialPtr = std::shared_ptr<Material>;
			using BottomLevelASPtr = std::shared_ptr<BottomLevelAccelerationStructure>;

		private:
			BottomLevelASPtr m_bottomLevelAS;
			MaterialPtr m_sharedMaterial;
			ShaderRecords m_shaderRecords;					// �V�F�[�_�[���R�[�h
			Matrix4x4 m_matrix;								// �ϊ��s��
			uint32_t m_id;									// id
			uint32_t m_mask;								// ���C�g���[�X�}�X�N�l

			SubTopLevelAccelerationStructureFlags m_flags;
			bool m_dirty;									// �ύX����������

		public:
			// �R���X�g���N�^
			RaytracingSubMesh();
			// �f�X�g���N�^
			~RaytracingSubMesh();
		public:

			void CreateShaderRecord(uint32_t recordCount = 1);

			// �\������`��ݒ�
			void SetBottomLevelAS(BottomLevelASPtr bottomLevelAS);

			// 
			void SetSharedMaterial(MaterialPtr material);

			void SetFlags(SubTopLevelAccelerationStructureFlags flags);

			// �}�X�N�l�ݒ�
			void SetMask(uint32_t mask = 0xff);

			// �ϊ��s��ݒ�
			void SetTransformMatrix(const Matrix4x4& matrix);

		public:
			// �`��擾
			BottomLevelASPtr GetBottomLevelAS() const { return m_bottomLevelAS; };

			// �V�F�[�_�[���R�[�h�擾
			ShaderRecord* GetShaderRecord(uint32_t index = 0) const;

			// �V�F�[�_�[���R�[�h�z��ԍ��擾
			uint32_t GetShaderRecordIndex(uint32_t index = 0)const;

			SubTopLevelAccelerationStructureFlags GetFlags() const;

			// ID�擾
			uint32_t GetID() const;

			// �}�X�N�l�擾
			uint32_t GetMask() const;

			// �ϊ��s��擾
			const Matrix4x4& GetTransformMatrix() const;
			// �l�̕ύX����������
			bool IsDirty() const { return m_dirty; }

			void Build(GraphicsCommandList* list) {};

			void SetName(const std::wstring& name);
		};

	}

}
/*
m_shaderRecordIndex
���̃C���X�^���X�Ɏg�p���郊�\�[�X�Ȃǂ��������z��̔ԍ�

*/