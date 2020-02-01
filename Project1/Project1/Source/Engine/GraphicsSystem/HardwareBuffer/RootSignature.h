#pragma once
#include <string>
#include <vector>
#include "../Enumerations/ShaderType.h"

/*
�e�N�X�`����Ranges�ŕK���ݒ肵�Ȃ��Ƃ����Ȃ�
*/
/*
�V�F�[�_�[�Ŏg�p���郊�\�[�X���ǂ̂悤�ɔz�u���Ă��邩�̋L�q
*/

namespace Engine 
{
	namespace GraphicsSystem 
	{
		class IRootSignature;
		struct ShaderResourceLayoutDesc;
		struct ShaderResourceParameterDesc;
		struct ShaderResourceConstantsDesc;
		struct ShaderResourceDescriptorDesc;
		class Shader;
		enum class RootSignatureType : uint8_t;
		enum class RootSignatureFlags : uint8_t;

		class SamplerState;

		struct ShaderResourceRange
		{
			ShaderResourceParameterDesc* parameters;
			uint32_t count;
			uint32_t index;
			ShaderType usedShader;
		};

		class RootSignature
		{
			using Layouts = std::vector<ShaderResourceLayoutDesc>;
			using Ranges = std::vector<ShaderResourceRange>;
			using StaticSamplerStates = std::vector<SamplerState>;
		private:
			Layouts m_layouts;					// ���C�A�E�g�z��
			Ranges m_ranges;					// �p�����[�^�[�z��
			StaticSamplerStates m_staticSampler;// �ÓI�T���v���[�X�e�[�g
			IRootSignature* m_interface;		// 
			Shader* m_shader;					// �V�F�[�_�[����쐬����ꍇ�͂�����
			RootSignatureType m_type;			// �^�C�v
			RootSignatureFlags m_flags;			// �t���O
		public:
			// �R���X�g���N�^
			RootSignature();
			// �f�X�g���N�^
			~RootSignature();
			// �t���O�ݒ�
			void SetFlags(RootSignatureFlags flags);
			// �^�C�v�ݒ�
			void SetType(RootSignatureType type);
			// ���C�A�E�g�ǉ�
			void AddLayout(const ShaderResourceLayoutDesc& layout);

			// �����W�ǉ�
			void AddDescriptorTableLayout(ShaderResourceParameterDesc* parameters, uint32_t count, ShaderType usedShader = ShaderType::All);

			// �R���X�^���c�ǉ�
			void AddConstantsLayout(const ShaderResourceConstantsDesc& constants, ShaderType usedShader = ShaderType::All);

			// �f�X�N���v�^�[�ǉ�
			void AddDescriptorLayout(const ShaderResourceDescriptorDesc& descriptor, ShaderType usedShader = ShaderType::All);

			// �쐬
			void AddRange(uint32_t parameterCount, ShaderType usedShader = ShaderType::All);

			// �萔�o�b�t�@�ǉ�
			void AddConstantBufferView(uint32_t index, uint32_t space = 0, ShaderType usedShader = ShaderType::All);
			void AddConstantBufferViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count = 1, uint32_t space = 0, uint32_t offset = 0xffffffff);

			// �V�F�[�_�[���\�[�X�r���[�ǉ�
			void AddShaderResourceView(uint32_t index, uint32_t space = 0, ShaderType usedShader = ShaderType::All);
			void AddShaderResourceViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count = 1, uint32_t space = 0, uint32_t offset = 0xffffffff);

			// �A���I�[�_�[�h�A�N�Z�X�r���[�ǉ�
			void AddUnorderedAccessView(uint32_t index, uint32_t space = 0, ShaderType usedShader = ShaderType::All);
			void AddUnorderedAccessViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count = 1, uint32_t space = 0, uint32_t offset = 0xffffffff);

			// �ÓI�T���v���[�X�e�[�g�ǉ�
			void AddStaticSamplerState();

			// �V�F�[�_�[�ݒ�
			void SetShader(Shader* shader);

			// �쐬
			void Create();

			// �჌�x���V�O�l�`���擾
			IRootSignature* GetInterface() const;

			// �^�C�v�擾
			RootSignatureType GetType() const;

			void SetName(const std::wstring& name);

		};

	}

}