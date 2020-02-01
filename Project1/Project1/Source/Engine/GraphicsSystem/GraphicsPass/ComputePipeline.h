#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class IComputePipeline;
		class Shader;
		class RootSignature;

		class ComputePipeline
		{
		private:
			IComputePipeline* m_interface;
			RootSignature* m_rootSignature;	// ���[�g�V�O�l�`��
			Shader* m_computeShader;		// �R���s���[�g�V�F�[�_�[
		public:
			// �R���X�g���N�^
			ComputePipeline();
			// �f�X�g���N�^
			~ComputePipeline();

			// ���[�g�V�O�l�`���ݒ�
			void SetRootSignature(RootSignature* rootSignature);

			// �R���s���[�g�V�F�[�_�[�ݒ�
			void SetComputeShader(Shader* shader);

			void Create();

			// �C���^�[�t�F�C�X�擾
			IComputePipeline* GetInterface() const;

			// ���[�g�V�O�l�`���擾
			RootSignature* GetRootSignature() const;

		};
	}
}