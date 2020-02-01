#pragma once
#include <string>
namespace Engine {

	namespace GraphicsSystem {

		class IResource;

		class WICLoader final
		{
		public:
			// コンストラクタ
			WICLoader();

			~WICLoader();

		public:
			IResource* LoadTexture(const std::string& name);
			//Texture* Create(const char* file);
			// 読み込みWindows Imaging Component(WIC) 対応拡張子(jpeg,png,gif,tiff)
			//virtual Object * Load(const char * filePath) override;
		};
	}
}