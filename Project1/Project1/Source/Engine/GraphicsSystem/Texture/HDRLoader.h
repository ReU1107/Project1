#pragma once
namespace Engine {

	class HDRLoader final //:public IResourceLoader
	{
	public:

		HDRLoader();

		~HDRLoader();

	public:
		// �ǂݍ���Radiance RGBE(HDR)
		//virtual Object * Load(const char * filePath) override;
	};
}