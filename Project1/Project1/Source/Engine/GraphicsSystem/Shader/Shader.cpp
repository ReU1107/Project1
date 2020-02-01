#include "Shader.h"
#include <cassert>

namespace Engine
{
	namespace GraphicsSystem
	{
		std::unordered_map<std::wstring, Shader*>Shader::s_allShaders;
		std::mutex Shader::s_shaderAccess;

		Shader::Shader()
			: m_interface(nullptr)
		{
		}

		Shader::~Shader()
		{
		}

		void Shader::RegisterShader(const std::wstring& name, Shader* shader)
		{
			std::lock_guard<std::mutex> lock(s_shaderAccess);
			const auto& it = s_allShaders.find(name);
			if (it != s_allShaders.cend())
				assert(!"シェーダーの名前が被っています");
			s_allShaders.insert({ name,shader });
		}

		Shader* Shader::Find(const std::wstring& name)
		{
			std::lock_guard<std::mutex> lock(s_shaderAccess);
			const auto& it = s_allShaders.find(name);
			if (it == s_allShaders.cend())
				return nullptr;
			
			return (*it).second;
		}

		void Shader::SetInterface(IShader* shader)
		{
			m_interface = shader;
		}

		IShader* Shader::GetInterface() const
		{
			return m_interface;
		}
	}
}