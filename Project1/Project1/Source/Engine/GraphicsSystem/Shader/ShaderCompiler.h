#pragma once

struct IDxcCompiler;
struct IDxcLibrary;

namespace Engine 
{

	namespace GraphicsSystem
	{

		class IShader;
		class ShaderLibrary;
		class Shader;

		class ShaderCompiler
		{
		private:
			IDxcLibrary* m_library;
			IDxcCompiler* m_compiler;

		public:
			// �R���X�g���N�^
			ShaderCompiler();
			// �f�X�g���N�^
			~ShaderCompiler();
			// ���C�g���[�V���O�p�V�F�[�_�[�R���p�C��
			ShaderLibrary* CompileLibrary(const wchar_t* fileName, const wchar_t* includeFile = nullptr, const wchar_t* entry = L"", const wchar_t* type = L"lib_6_3");
			// ���X�^���C�U�[�p�V�F�[�_�[�R���p�C��
			Shader* Compile(const wchar_t* fileName, const wchar_t* type, const wchar_t* includeFile = nullptr, const wchar_t* entry = L"main");

		};

	}

}