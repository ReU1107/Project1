#pragma once
#include "AccelerationStructure.h"
#include <cstdint>
#include <vector>
#include "../Description/SubBottomLevelAccelerationStructureDesc.h"
#include "../../Math/Matrix4x4.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Buffer;
		class VertexBuffer;
		class IndexBuffer;
		class ConstantBuffer;
		class GraphicsCommandList;
		enum class BottomLevelAccelerationStructureFlags : uint8_t;
		enum class BottomLevelAccelerationBuildFlags : uint8_t;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		class BottomLevelAccelerationStructure : public AccelerationStructure
		{
		private:
			using base = AccelerationStructure;
			using Descs = std::vector<SubBottomLevelAccelerationStructureDesc>;
			using VertexBuffers = std::vector<VertexBuffer*>;
		private:
			Descs m_descs;					// �f�X�N�z��
			VertexBuffers m_vertexBuffers;	// ���_�o�b�t�@�z��

			uint32_t m_id;					// id
			uint32_t m_mask;				// ���C�g���[�X�}�X�N�l
			uint32_t m_contribution;

			uint32_t m_materialIndex;

			BottomLevelAccelerationStructureFlags m_flags;		// 
			BottomLevelAccelerationBuildFlags m_buildFlags;		// �t���O

			bool m_isDirty;
		public:
			// �R���X�g���N�^
			BottomLevelAccelerationStructure();
			// �f�X�g���N�^
			virtual ~BottomLevelAccelerationStructure();

			void SetMaterialIndex(uint32_t index);
			// 
			void AddSubBottomLevelASDesc(const SubBottomLevelAccelerationStructureDesc& desc);
			// �O�p�`�|���S��
			void AddTraianglesGeometry(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer = nullptr, ConstantBuffer* constantBuffer = nullptr);
			// �葱���^�`��
			void AddProceduralGeometry(Buffer* buffer, ConstantBuffer* constantBuffer = nullptr);
			// �쐬
			virtual void Create() override;
			virtual void Recreate() override;

			const VertexBuffers& GetVertexBuffers() const;

			// �}�e���A���擾
			uint32_t GetMaterialIndex() const;

			// �r���h�t���O�ݒ�
			void SetBuildFlags(BottomLevelAccelerationBuildFlags buildFlags);

			uint32_t GetContribution() const;

			uint32_t GetID() const;

			uint32_t GetMask() const;

			bool IsDirty() const;

			void Dirty(bool dirty);
		};

		using BottomLevelAS = BottomLevelAccelerationStructure;
	}
}