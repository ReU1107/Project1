#pragma once
#include <string>
namespace Engine {

	namespace GraphicsSystem {

		class IResource;

		class WICLoader final
		{
		public:
			// �R���X�g���N�^
			WICLoader();

			~WICLoader();

		public:
			IResource* LoadTexture(const std::string& name);
			//Texture* Create(const char* file);
			// �ǂݍ���Windows Imaging Component(WIC) �Ή��g���q(jpeg,png,gif,tiff)
			//virtual Object * Load(const char * filePath) override;
		};
	}
}