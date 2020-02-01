#pragma once
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IShader;
		class Shader
		{
		private:
			static std::unordered_map<std::wstring, Shader*> s_allShaders;
			static std::mutex s_shaderAccess;
		private:
			IShader* m_interface;
		public:
			// �R���X�g���N�^
			Shader();
			// �f�X�g���N�^
			~Shader();
			// �V�F�[�_�[�o�^
			static void RegisterShader(const std::wstring& name, Shader* shader);
			// �V�F�[�_�[�擾
			static Shader* Find(const std::wstring& name);

			void SetInterface(IShader* shader);

			IShader* GetInterface() const;
		};
	}
}