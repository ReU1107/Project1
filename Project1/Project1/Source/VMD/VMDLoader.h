#pragma once
#include <vector>

// 前方宣言
class VMDBinaryReader;
struct VMDBodyMotion;
struct VMDMorphMotion;
struct VMDCameraMotion;
struct VMDLightMotion;
struct VMDSelfShadowMotion;

// VMDファイル読み込み
class VMDLoader final
{
public:
	// コンストラクタ
	VMDLoader();
	// デストラクタ
	~VMDLoader();

	void Load(const std::string& path);

private:
	// モーション配列読み込み
	std::vector<VMDBodyMotion> LoadBodyMotions(VMDBinaryReader& reader);
	// 表情データ読み込み
	std::vector<VMDMorphMotion> LoadMorphMotions(VMDBinaryReader& reader);
	// カメラデータ読み込み
	std::vector<VMDCameraMotion> LoadCameraMotions(VMDBinaryReader& reader);
	// 照明(ライト)データ読み込み
	std::vector<VMDLightMotion> LoadLightMotions(VMDBinaryReader& reader);
	// セルフシャドウデータ読み込み
	std::vector<VMDSelfShadowMotion> LoadSelfShadowMotions(VMDBinaryReader& reader);

};
