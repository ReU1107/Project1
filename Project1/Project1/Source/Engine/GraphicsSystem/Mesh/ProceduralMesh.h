#pragma once
#include <DirectXMath.h>
#include <vector>

namespace Engine
{
	namespace GraphicsSystem
	{
		/*
		�����̌`��̓V�F�[�_�[���Ō��肵�Ă�������
		*/
		// 
		struct AxisAlignedBoundingBox
		{
			float minX;
			float minY;
			float minZ;
			float maxX;
			float maxY;
			float maxZ;
		};
		class StructuredBuffer;
		class Material;
		class SubMesh;

		class ProceduralMesh
		{
			using AxisAlignedBoundingBoxes = std::vector<AxisAlignedBoundingBox>;
			using SubMeshes = std::vector<SubMesh*>;
		private:
			AxisAlignedBoundingBoxes m_aabbs;	// AABB�z��
			SubMeshes m_subMeshes;				// �T�u���b�V���z��
			StructuredBuffer* m_buffer;

		public:
			// �R���X�g���N�^
			ProceduralMesh();
			// �f�X�g���N�^
			~ProceduralMesh();
			// AABB�ǉ�
			void AddAABB(const DirectX::XMFLOAT3& min, const DirectX::XMFLOAT3& max);
			void AddSphere(const DirectX::XMFLOAT3& center, float radius);
			// �T�u���b�V���ǉ�
			void AddSubMesh(SubMesh* subMesh);

			// �T�u���b�V���z��擾
			SubMeshes& GetSubMeshes();
			// �쐬
			void Create();

			StructuredBuffer* GetBuffer() const;
		};

	}
}