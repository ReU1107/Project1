#include "ShaderLibrary.h"
#include "../Interface/IShader.h"
#include <d3d12.h>

namespace Engine
{

	namespace GraphicsSystem 
	{

		ShaderLibrary::ShaderLibrary()
			: m_interface(nullptr)
		{

		}

		ShaderLibrary::~ShaderLibrary()
		{
			
		}

		void ShaderLibrary::SetShader(IShader* shader)
		{
			m_interface = shader;
		}

		void ShaderLibrary::AddFunctionName(const wchar_t* functionName, const wchar_t* anotherName)
		{
			m_functionNames.PushBack(functionName);
			m_functionAnotherNames.PushBack(anotherName);
		}

		void ShaderLibrary::AddFunctionNames(const wchar_t** functionNames, const wchar_t** anotherNames, uint32_t functionCount)
		{
			for (uint32_t i = 0; i < functionCount; ++i)
			{
				const wchar_t* functionName = functionNames[i];
				const wchar_t* anotherName = nullptr;
				if (anotherNames)
				{
					anotherName = anotherNames[i];
				}
				AddFunctionName(functionName, anotherName);
			}
		}

		uint32_t ShaderLibrary::GetShaderFunctionCount() const
		{
			return m_functionNames.GetSize();
		}

		IShader* ShaderLibrary::GetInterface() const
		{
			return m_interface;
		}

		const wchar_t** ShaderLibrary::GetFunctionNames() const
		{
			return m_functionNames.GetArray();
		}

		void ShaderLibrary::SetName(const std::wstring& name)
		{

		}
	}
}

