#pragma once
#include <string>
#include "..//../Utility/Vector.h"
namespace Engine
{

	namespace GraphicsSystem 
	{

		// 前方宣言
		class IShader;

		class ShaderLibrary
		{
		private:
			using FunctionNames = Vector<const wchar_t*>;
			using FunctionAnotherNames = Vector<const wchar_t*>;
		private:
			FunctionNames m_functionNames;					// 関数名配列
			FunctionAnotherNames m_functionAnotherNames;	// 関数別名配列
			IShader* m_interface;
		public:
			// コンストラクタ
			ShaderLibrary();
			// デストラクタ
			~ShaderLibrary();
		public:
			// シェーダー設定
			void SetShader(IShader* shader);

			// シェーダーライブラリ内の関数名追加
			void AddFunctionName(const wchar_t* functionName, const wchar_t* anotherName = nullptr);
			void AddFunctionNames(const wchar_t** functionNames, const wchar_t** anotherNames, uint32_t functionCount);

			// シェーダー関数名数取得
			uint32_t GetShaderFunctionCount() const;
			// シェーダーオブジェクト取得
			IShader* GetInterface() const;
			// シェーダー関数名配列取得
			const wchar_t** GetFunctionNames() const;

			void SetName(const std::wstring& name);
		};

	}

}