#pragma once
#include <cstdint>
#include <string>
#include <iostream>

namespace Engine 
{
	namespace GraphicsSystem
	{
		class IndexBuffer;
		class Material;

		class SubMesh
		{
		private:
			using MaterialPtr = std::shared_ptr<Material>;
		private:
			std::string m_name;				// �f�o�b�O�p���O
			MaterialPtr m_material;			// �}�e���A��
			IndexBuffer* m_indexBuffer;		// �C���f�b�N�X�o�b�t�@�݂̂𕪊�����
			uint32_t m_startIndexLocation;	// ���_�C���f�b�N�X�J�n�ʒu
			uint32_t m_useIndexCount;		// ���g���g�p���钸�_�C���f�b�N�X��
		public:
			// �R���X�g���N�^
			SubMesh(const std::string& name = "");
			// �f�X�g���N�^
			~SubMesh();
		public:
			// �}�e���A���ݒ�
			void SetMaterial(MaterialPtr material);
			// �C���f�b�N�X�o�b�t�@�ݒ�
			void SetIndexBuffer(IndexBuffer* indexBuffer);

			// �C���f�b�N�X�J�n�ʒu�ݒ�
			void SetStartIndexLocation(uint32_t startLocation);
			// �g�p���钸�_�C���f�b�N�X���ݒ�
			void SetUseIndexCount(uint32_t indexCount);

			// �}�e���A���擾
			MaterialPtr GetMaterial() const;

			IndexBuffer* GetIndexBuffer() const;

			// �C���f�b�N�X�J�n�ʒu�擾
			uint32_t GetStartIndexLocation() const;
			// �g�p�C���f�b�N�X���擾
			uint32_t GetUseIndexCount() const;
		};

		// ���b�V�����\�����镔�i(���b�V���̕���)
		//class SubMesh final// : public Object
		//{
		//private:
		//	//using base = Object;
		//private:
		//	uint32_t m_startIndexLocation;	// ���_�C���f�b�N�X�J�n�ʒu
		//	uint32_t m_useIndexCount;		// ���g���g�p���钸�_�C���f�b�N�X��

		//public:
		//	// �R���X�g���N�^
		//	SubMesh(const std::string& name);
		//	// �f�X�g���N�^
		//	~SubMesh();
		////public:
		////	// �C���X�^���XID
		////	static const InstanceID ID() { return InstanceID::SubMesh; }
		////	// �C���X�^���XID�擾
		////	virtual InstanceID GetInstanceID() const override { return InstanceID::SubMesh; }

		//public:
		//	// �C���f�b�N�X�J�n�ʒu�ݒ�
		//	void SetStartIndexLocation(uint32_t startLocation);
		//	// �g�p���钸�_�C���f�b�N�X���ݒ�
		//	void SetUseIndexCount(uint32_t indexCount);
		//public:
		//	// �C���f�b�N�X�J�n�ʒu�擾
		//	uint32_t GetStartIndexLocation() const;
		//	// �g�p�C���f�b�N�X���擾
		//	uint32_t GetUseIndexCount() const;
		//};
	}
}

using SubMeshPtr = std::shared_ptr<Engine::GraphicsSystem::SubMesh>;
