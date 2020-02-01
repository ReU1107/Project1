#pragma once
#include "Mesh.h"
#include "BoneWeight.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class BlendShape;
		enum class VertexDirtyFlags : uint16_t
		{
			Positions = 0x01,		// 
			Normals = 0x02,			// 
			Tangents = 0x04,		// 
			BoneWeights = 0x08,		// 
			BasePositions = 0x10,	// 
			DeltaPositions = 0x20,	// 
			DeltaNormals = 0x40,	// 
			DeltaTangents = 0x80,	// 
			Texcoords0 = 0x100,		// 
			Texcoords1 = 0x200,		// 
			Texcoords2 = 0x400,		// 
			Texcoords3 = 0x800,		// 
		};

		class SkeletalMesh : public Mesh
		{
		private:
			using base = Mesh;
			using BoneWeights = std::vector<BoneWeight>;
			using Texcoords = std::vector<float>;
			using Indices = std::vector<uint32_t>;
			using BlendShapePtr = std::shared_ptr<BlendShape>;
			using BlendShapes = std::vector<BlendShapePtr>;
			using DeltaPositions = std::vector<Vector3>;
			using DeltaNormals = std::vector<Vector3>;
			using DeltaTangents = std::vector<Vector3>;
			using Positions = std::vector<Vector3>;

		private:
			BoneWeights m_boneWeights;			// ���_�{�[���E�F�C�g�l�z��
			Texcoords m_texcoords1;				// ���_UV�ʒu�z��
			Texcoords m_texcoords2;				// ���_UV�ʒu�z��
			Texcoords m_texcoords3;				// ���_UV�ʒu�z��
			Positions m_basePositions;			// �ʒu���

			DeltaPositions m_deltaPositions;	// ���_�����ʒu�z��
			DeltaNormals m_deltaNormals;		// ���_�����ʒu�z��
			DeltaTangents m_deltaTangents;		// ���_�����ʒu�z��

			BlendShapes m_blendShapes;			// �u�����h

			VertexDirtyFlags m_dirtyFlags;		// �z��̍X�V����������Ăяo��

			bool m_vertexDataIsDirty;			// ��������̒��_���̒��g���ύX������true

		public:
			// �R���X�g���N�^
			SkeletalMesh(const std::string& name);
			// �f�X�g���N�^
			virtual ~SkeletalMesh();
		public:
			// �C���X�^���XID
			static const InstanceID ID() { return InstanceID::Mesh; }
			// �C���X�^���XID�擾
			virtual InstanceID GetInstanceID() const override { return InstanceID::Mesh; }

			// �u�����h�V�F�C�v�t���[���ǉ�
			void AddBlendShapeFrame(BlendShapePtr blendShape);

			// �u�����h�V�F�C�v���擾
			uint32_t GetBlendShapeFrameCount() const;

			// �u�����h�V�F�C�v�z��擾
			BlendShapes& GetBlendShapes();
			
			// �u�����h�V�F�C�v�擾
			BlendShapePtr GetBlendShapeFrame(const std::string& name) const;
			BlendShapePtr GetBlendShapeFrame(uint32_t index) const;

			// �u�����h�V�F�C�v�ԍ��擾
			int32_t GetBlendShapeIndex(const std::string& name) const;

			void SetDirtyFlags(VertexDirtyFlags flags);

		public:
			// UV�z��擾
			Texcoords& GetTexcoords0();
			// UV�z��擾
			Texcoords& GetTexcoords1();
			// UV�z��擾
			Texcoords& GetTexcoords2();
			// UV�z��擾
			Texcoords& GetTexcoords3();

			Positions& GetBasePositions();

			// �����ʒu�z��擾
			DeltaPositions& GetDeltaPositions();

			// �{�[�����z��擾
			BoneWeights& GetBoneWeights();

			// �o�b�t�@�X�V
			virtual void Update() override;
			
			// ���_�o�b�t�@�쐬
			virtual void CreateVertexBuffes() override;

		};
	}
}

using SkeletalMeshPtr = std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh>;

//// ���_UV�z��ݒ�
//void SetTexcoords1(const Texcoords&& texcoords);
//// ���_UV�z��ݒ�
//void SetTexcoords2(const Texcoords&& texcoords);
//// ���_UV�z��ݒ�
//void SetTexcoords3(const Texcoords&& texcoords);

//// �����ʒu�z��ݒ�
//void SetDeltaPositions(const DeltaPositions&& deltaPositions);

//// ���_�E�F�C�g�z��ݒ�
//void SetBoneWeights(const BoneWeights&& boneWeights);


//// ���_UV�z��ݒ�
//void SetTexcoords4(const Texcoords&& texcoords);
//// ���_UV�z��ݒ�
//void SetTexcoords5(const Texcoords&& texcoords);
//// ���_UV�z��ݒ�
//void SetTexcoords6(const Texcoords&& texcoords);
//// ���_UV�z��ݒ�
//void SetTexcoords7(const Texcoords&& texcoords);

			//// UV�z��擾
			//Texcoords& GetTexcoords4();
			//// UV�z��擾
			//Texcoords& GetTexcoords5();
			//// UV�z��擾
			//Texcoords& GetTexcoords6();
			//// UV�z��擾
			//Texcoords& GetTexcoords7();

			//// �����@���z��擾
			//DeltaNormals & GetDeltaNormals();
			//// �����ڐ��z��擾
			//DeltaTangents & GetDeltaTangents();