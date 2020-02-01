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
			// コンストラクタ
			ShaderCompiler();
			// デストラクタ
			~ShaderCompiler();
			// レイトレーシング用シェーダーコンパイル
			ShaderLibrary* CompileLibrary(const wchar_t* fileName, const wchar_t* includeFile = nullptr, const wchar_t* entry = L"", const wchar_t* type = L"lib_6_3");
			// ラスタライザー用シェーダーコンパイル
			Shader* Compile(const wchar_t* fileName, const wchar_t* type, const wchar_t* includeFile = nullptr, const wchar_t* entry = L"main");

		};

	}

}