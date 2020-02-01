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
			// コンストラクタ
			Shader();
			// デストラクタ
			~Shader();
			// シェーダー登録
			static void RegisterShader(const std::wstring& name, Shader* shader);
			// シェーダー取得
			static Shader* Find(const std::wstring& name);

			void SetInterface(IShader* shader);

			IShader* GetInterface() const;
		};
	}
}