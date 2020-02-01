#pragma once
#include <string>
namespace Engine {

	namespace GraphicsSystem {
		class IResource;
		class TGALoader final
		{
		public:
			TGALoader();

			~TGALoader();
		public:
			IResource* LoadTexture(const std::string& fileName);
			//Texture* CreateTexture(const char* file);
			// �ǂݍ���Targa Truevision(TGA)
			//virtual Object * Load(const char * filePath) override;
		};
	}

}