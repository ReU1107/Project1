#pragma once
#include <string>
namespace Engine {

	namespace GraphicsSystem {
		class IResource;

		class DDSLoader final
		{
		public:
			DDSLoader();

			~DDSLoader();

		public:
			// ì«Ç›çûÇ›Direct Draw Surface(DDS)
			//virtual Object * Load(const char * filePath) override;

			IResource* LoadTexture(const std::string& name);

		};
	}
}