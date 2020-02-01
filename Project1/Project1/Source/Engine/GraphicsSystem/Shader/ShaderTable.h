#pragma once
#include <cstdint>
#include <vector>
#include <string>

/*
�ł��邱�ƂȂ�
���[�g�V�O�l�`���̃��C�A�E�g�����Ȃ���
����ɐݒ肵�Ă����悤�ɂ͂�����
*/

namespace Engine 
{
	namespace GraphicsSystem 
	{
		class IResource;
		enum class ShaderTableType;
		class ShaderRecord;
		class StructuredBuffer;

		class ShaderTable
		{
		private:
			using ShaderRecords = std::vector<ShaderRecord*>;
		private:
			ShaderRecords m_records;	// �V�F�[�_�[���R�[�h�z��
			StructuredBuffer* m_buffer;	// �o�b�t�@
			ShaderTableType m_type;		// �^�C�v
		public:
			// �R���X�g���N�^
			ShaderTable();
			// �f�X�g���N�^
			~ShaderTable();
		public:
			// ���\�[�X�擾
			IResource* GetInterface() const;
			// ��̃V�F�[�_�[���R�[�h�̃T�C�Y�擾
			uint32_t GetStride() const;
			// �V�F�[�_�[���R�[�h������o�b�t�@�̃T�C�Y�擾
			uint32_t GetSize() const;
			// �V�F�[�_�[���R�[�h�o�^
			void RegisterShaderRecord(ShaderRecord* record);

			void Create();

			void SetName(const std::wstring& name);

		};
	}
}

/*
�ő�
4096byte��������?
*/