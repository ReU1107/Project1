#pragma once
#include <vector>
#include <array>
#include <cstdint>
#include <iostream>
#include "../../Math/Include.h"
#include "../../Utility/AccessObject.h"
#include "../Enumerations/ResourceViewType.h"

namespace Engine 
{
	namespace GraphicsSystem 
	{
		class VertexBuffer;
		class IndexBuffer;
		class ConstantBuffer;
		class Material;
		class SubMesh;
		class ResourceDescriptor;

		enum class VertexLayout : uint16_t
		{
			Positions = 0x01,		// ���_�V�F�[�_�[�ɗ����ʒu���W
			Normals = 0x02,			// �@��
			Tangents = 0x04,		// �ڐ�
			BoneWeights = 0x08,		// �{�[�����
			BasePositions = 0x10,	// ��{�ɂȂ�ʒu���W
			DeltaPositions = 0x20,	// �ړ�������ʒu���W
			DeltaNormals = 0x40,	// 
			DeltaTangents = 0x80,	// 
			Texcoords0 = 0x100,		// �e�N�X�`�����W
			Texcoords1 = 0x200,		// �e�N�X�`�����W
			Texcoords2 = 0x400,		// �e�N�X�`�����W
			Texcoords3 = 0x800,		// �e�N�X�`�����W
		};

		enum class MeshType : uint8_t
		{
			Static,		// 
			Skeletal,	// 
		};

		class Mesh : public AccessObject<Mesh>
		{
		private:
			using base = AccessObject<Mesh>;
			using VertexBufferPtr = VertexBuffer*;
			using VertexBuffers = std::vector<VertexBufferPtr>;

			using Positions = std::vector<Vector3>;
			using Normals = std::vector<Vector3>;
			using Tangents = std::vector<Vector4>;
			using Texcoords = std::vector<float>;
			using Indices = std::vector<uint32_t>;
			using MeshPtr = std::shared_ptr<Mesh>;
			using SubMeshPtr = std::shared_ptr<SubMesh>;
			using SubMeshes = std::vector<SubMeshPtr>;
		protected:
			VertexBuffers m_vertexBuffers;	// ���_�o�b�t�@�z��
			Positions m_positions;			// �ʒu���
			Normals m_normals;				// �@�����
			Texcoords m_texcoords0;			// UV���
			Indices m_indices;				// �C���f�b�N�X���

			SubMeshes m_subMeshes;			// �T�u���b�V���z��

			uint32_t m_vertexBufferCount;	// ���_�o�b�t�@��
			uint32_t m_textureCount;		// ���̃��b�V�������e�N�X�`���̑���
			VertexLayout m_layout;			// ���_���C�A�E�g
			MeshType m_type;				// ���b�V���^�C�v
			bool m_vertexCountIsDirty;		// ���_�����ύX���ꂽ��true
		public:
			// �R���X�g���N�^
			Mesh(const std::string& name, MeshType type);
			// �f�X�g���N�^
			virtual ~Mesh();

		public:
			// ���_���擾
			uint32_t GetVertexCount() const;
			
			// ���_�o�b�t�@���擾
			uint32_t GetVertexBufferCount() const;

			// ���_�o�b�t�@�z��擾
			VertexBuffers& GetVertexBuffers();
			
			// ���_�o�b�t�@�擾
			VertexBuffer* GetVertexBuffer(uint32_t index) const;

			VertexBuffer* GetVertexBuffer(VertexLayout layout) const;

			// �ʒu�z��擾
			Positions& GetPositions();

			// �ʒu�z��擾
			Normals& GetNormals();

			// UV�z��擾
			Texcoords& GetTexcoords0();

			// �C���f�b�N�X�z��擾
			Indices& GetIndices();

			// �}�e���A���z��擾
			//std::vector<Material*>& GetMaterials();
			// �T�u���b�V���J�E���g�擾
			uint32_t GetSubMeshCount() const;
			// �T�u���b�V���z��擾
			SubMeshes& GetSubMeshes();

			// ���b�V���̎��
			MeshType GetMeshType() const;

			// �e�N�X�`�����ݒ�
			void SetTextureCount(uint32_t textureCount);

			// �e�N�X�`�����擾
			uint32_t GetTextureCount() const;

			virtual void Update() = 0;

			virtual void CreateVertexBuffes() = 0;

			void CreateIndexBuffer();

			// ���_���C�A�E�g�ݒ�
			void SetVertexLayout(VertexLayout layout);
			// ���_���C�A�E�g�ǉ�
			void AddVertexLayout(VertexLayout layout);

		protected:
			// ���_�o�b�t�@�쐬
			void CreateVertexBuffer(uint32_t size, uint32_t stride, void* data, bool gpuAccess = false, ResourceViewType type = ResourceViewType::ShaderResource);

			// ���_�o�b�t�@�X�V
			void UpdateVertexBuffer(uint32_t index, void* data);

		};
	}
}

using MeshPtr = std::shared_ptr<Engine::GraphicsSystem::Mesh>;
