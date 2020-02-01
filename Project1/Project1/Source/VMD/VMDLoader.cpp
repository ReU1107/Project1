#include "VMDLoader.h"
#include "VMDBinaryReader.h"
#include "VMDDataModel.h"
#include "VMDClipFactory.h"
#include <istream>
#include <fstream>
#include <cassert>

using namespace Engine;

VMDLoader::VMDLoader()
{
}

VMDLoader::~VMDLoader()
{
}

void VMDLoader::Load(const std::string& filePath)
{
	VMDBinaryReader reader(filePath);
	// ヘッダー
	VMDHeader header(reader);

	// モーション
	auto bodyMotions(std::move(LoadBodyMotions(reader)));
	// モーフ
	auto morphMotions(std::move(LoadMorphMotions(reader)));
	// カメラ
	auto cameraMotions(std::move(LoadCameraMotions(reader)));
	// ライト
	auto lightMotions(std::move(LoadLightMotions(reader)));
	// セルフシャドウ
	auto selfShadowMotions(std::move(LoadSelfShadowMotions(reader)));

	uint8_t m_type = reader.GetVMDType();

	const std::string name = header.motionName;

	// アニメーションクリップ作成
	VMDClipFactory factory;
	factory.SetMotionName(name);
	if ((m_type & GetBit(VMDType::Body)) != 0)
	{
		factory.CreateBodyMotion(bodyMotions);
	}
	if ((m_type & GetBit(VMDType::Morph)) != 0) 
	{
		factory.CreateMorphMotion(morphMotions);
	}
	if ((m_type & GetBit(VMDType::Camera)) != 0)
	{
		factory.CreateCameraMotion(cameraMotions);
	}
	if ((m_type & GetBit(VMDType::Light)) != 0)
	{
		factory.CreateLightMotion(lightMotions);
	}
	if ((m_type & GetBit(VMDType::SelfShadow)) != 0)
	{
		factory.CreateSelfShadowMotion(selfShadowMotions);
	}
}

std::vector<VMDBodyMotion> VMDLoader::LoadBodyMotions(VMDBinaryReader& reader)
{
	uint32_t motionCount;
	reader.Read(&motionCount, sizeof(motionCount));
	// 1つのファイルに複数のタイプを動かすモーションありました
	if (motionCount > 0)
		reader.AddVMDType(VMDType::Body);
	std::vector<VMDBodyMotion> motions(motionCount);
	for (auto& motion : motions) 
	{
		reader.Read(motion.boneName, sizeof(motion.boneName));
		reader.Read(&motion.frameIndex, sizeof(motion.frameIndex));
		reader.Read(&motion.position, sizeof(motion.position));
		reader.Read(&motion.rotataion, sizeof(motion.rotataion));
		reader.Read(&motion.bezierControllPoint, sizeof(motion.bezierControllPoint));
	}

	return std::move(motions);
}

std::vector<VMDMorphMotion> VMDLoader::LoadMorphMotions(VMDBinaryReader& reader)
{
	uint32_t motionCount;
	reader.Read(&motionCount, sizeof(motionCount));
	// 1つのファイルに複数のタイプを動かすモーションありました
	if (motionCount > 0)
		reader.AddVMDType(VMDType::Morph);

	std::vector<VMDMorphMotion> motions(motionCount);

	for (auto& morph : motions)
	{
		reader.Read(&morph.name, sizeof(morph.name));
		reader.Read(&morph.frameIndex, sizeof(morph.frameIndex));
		reader.Read(&morph.weight, sizeof(morph.weight));
	}

	return std::move(motions);
}

std::vector<VMDCameraMotion> VMDLoader::LoadCameraMotions(VMDBinaryReader& reader)
{
	uint32_t motionCount;
	reader.Read(&motionCount, sizeof(motionCount));
	// 1つのファイルに複数のタイプを動かすモーションありました
	if (motionCount > 0)
		reader.AddVMDType(VMDType::Camera);

	std::vector<VMDCameraMotion> motions(motionCount);

	for (auto& camera : motions) 
	{
		reader.Read(&camera.frameIndex, sizeof(camera.frameIndex));
		reader.Read(&camera.length, sizeof(camera.length));
		reader.Read(&camera.position, sizeof(camera.position));
		reader.Read(&camera.rotation, sizeof(camera.rotation));
		reader.Read(&camera.interpolation, sizeof(camera.interpolation));
		reader.Read(&camera.angle, sizeof(camera.angle));
		reader.Read(&camera.perspectiveFlag, sizeof(camera.perspectiveFlag));
	}

	return std::move(motions);
}

std::vector<VMDLightMotion> VMDLoader::LoadLightMotions(VMDBinaryReader& reader)
{
	uint32_t motionCount;
	reader.Read(&motionCount, sizeof(motionCount));
	// 1つのファイルに複数のタイプを動かすモーションありました
	if (motionCount > 0)
		reader.AddVMDType(VMDType::Light);

	std::vector<VMDLightMotion> motions(motionCount);

	for (auto& light : motions) 
	{
		reader.Read(&light.frameIndex, sizeof(light.frameIndex));
		reader.Read(&light.color, sizeof(light.color));
		reader.Read(&light.position, sizeof(light.position));
	}

	return std::move(motions);
}

std::vector<VMDSelfShadowMotion> VMDLoader::LoadSelfShadowMotions(VMDBinaryReader& reader)
{
	uint32_t motionCount;
	reader.Read(&motionCount, sizeof(motionCount));
	if (motionCount != 0)
		return std::vector<VMDSelfShadowMotion>();
	// 1つのファイルに複数のタイプを動かすモーションありました
	if (motionCount > 0)
		reader.AddVMDType(VMDType::SelfShadow);

	std::vector<VMDSelfShadowMotion> motions(motionCount);

	for (auto& selfShadow : motions)
	{
		reader.Read(&selfShadow.frameIndex, sizeof(selfShadow.frameIndex));
		reader.Read(&selfShadow.mode, sizeof(selfShadow.mode));
		reader.Read(&selfShadow.distance, sizeof(selfShadow.distance));
	}

	return std::move(motions);
}

