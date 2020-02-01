#pragma once
#include <string>
#include "..//../Utility/Vector.h"
namespace Engine
{

	namespace GraphicsSystem 
	{

		// �O���錾
		class IShader;

		class ShaderLibrary
		{
		private:
			using FunctionNames = Vector<const wchar_t*>;
			using FunctionAnotherNames = Vector<const wchar_t*>;
		private:
			FunctionNames m_functionNames;					// �֐����z��
			FunctionAnotherNames m_functionAnotherNames;	// �֐��ʖ��z��
			IShader* m_interface;
		public:
			// �R���X�g���N�^
			ShaderLibrary();
			// �f�X�g���N�^
			~ShaderLibrary();
		public:
			// �V�F�[�_�[�ݒ�
			void SetShader(IShader* shader);

			// �V�F�[�_�[���C�u�������̊֐����ǉ�
			void AddFunctionName(const wchar_t* functionName, const wchar_t* anotherName = nullptr);
			void AddFunctionNames(const wchar_t** functionNames, const wchar_t** anotherNames, uint32_t functionCount);

			// �V�F�[�_�[�֐������擾
			uint32_t GetShaderFunctionCount() const;
			// �V�F�[�_�[�I�u�W�F�N�g�擾
			IShader* GetInterface() const;
			// �V�F�[�_�[�֐����z��擾
			const wchar_t** GetFunctionNames() const;

			void SetName(const std::wstring& name);
		};

	}

}