#include "ShaderCompiler.h"
#include <Windows.h>
#include <dxcapi.h>
#include <d3dcompiler.h>
#include "../D3D12/D3D12Shader.h"
#include "ShaderLibrary.h"
#include "Shader.h"

#pragma comment(lib,"dxcompiler.lib")

namespace Engine
{

	namespace GraphicsSystem
	{

		ShaderCompiler::ShaderCompiler()
		{
			HRESULT hr = {};
			IDxcLibrary* library = nullptr;
			hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&library));
			IDxcCompiler* compiler = nullptr;
			hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
			m_library = library;
			m_compiler = compiler;
		}

		ShaderCompiler::~ShaderCompiler()
		{
			m_library->Release();
			m_compiler->Release();
		}

		ShaderLibrary* ShaderCompiler::CompileLibrary(const wchar_t* fileName, const wchar_t* includeFile, const wchar_t* entry, const wchar_t* type)
		{
			HRESULT hr;

			IDxcIncludeHandler* handler = nullptr;
			if (includeFile)
			{
				hr = m_library->CreateIncludeHandler(&handler);
				IDxcBlob* incBlob = nullptr;
				hr = handler->LoadSource(includeFile, &incBlob);
				incBlob->Release();
			}

			IDxcBlobEncoding* source = nullptr;
			hr = m_library->CreateBlobFromFile(fileName, nullptr, &source);
			IDxcOperationResult* result = nullptr;
			hr = m_compiler->Compile(source, fileName, entry,
				type,
				nullptr, 0, nullptr, 0, handler, &result);

			result->GetStatus(&hr);

			if (FAILED(hr))
			{
				IDxcBlobEncoding* error = nullptr;
				result->GetErrorBuffer(&error);
				const char* a = (const char*)error->GetBufferPointer();
				error->Release();
			}

			handler->Release();

			IDxcBlob* blob = nullptr;
			result->GetResult(&blob);
			ID3DBlob* b = nullptr;
			blob->QueryInterface(IID_PPV_ARGS(&b));

			D3D12Shader* shader = new D3D12Shader();
			shader->m_blob = b;

			ShaderLibrary* library = new ShaderLibrary();
			library->SetShader(shader);

			return library;
		}

		Shader* ShaderCompiler::Compile(const wchar_t* fileName, const wchar_t* type, const wchar_t* includeFile, const wchar_t* entry)
		{
			HRESULT hr;

			IDxcIncludeHandler* handler = nullptr;
			if (includeFile)
			{
				hr = m_library->CreateIncludeHandler(&handler);
				IDxcBlob* incBlob = nullptr;
				hr = handler->LoadSource(includeFile, &incBlob);
				
				incBlob->Release();
			}

			IDxcBlobEncoding* source = nullptr;
			hr = m_library->CreateBlobFromFile(fileName, nullptr, &source);
			IDxcOperationResult* result = nullptr;
			hr = m_compiler->Compile(source, fileName, entry,
				type,
				nullptr, 0, nullptr, 0, handler, &result);

			result->GetStatus(&hr);

			if (FAILED(hr))
			{
				IDxcBlobEncoding* error = nullptr;
				result->GetErrorBuffer(&error);
				const char* a = (const char*)error->GetBufferPointer();
				assert(!"");
				error->Release();
			}

			IDxcBlob* blob = nullptr;
			hr = result->GetResult(&blob);
			ID3DBlob* b = nullptr;
			hr = blob->QueryInterface(IID_PPV_ARGS(&b));

			if (handler)
				handler->Release();

			D3D12Shader* native = new D3D12Shader();
			native->m_blob = b;

			Shader* shader = new Shader();
			shader->SetInterface(native);
			Shader::RegisterShader(fileName, shader);

			return shader;
		}

	}

}

