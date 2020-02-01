#pragma once
#include <vector>
#include <string>

struct VMDBodyMotion;
struct VMDMorphMotion;
struct VMDCameraMotion;
struct VMDLightMotion;
struct VMDSelfShadowMotion;

class VMDClipFactory
{
private:
	std::string m_motionName;

public:
	void SetMotionName(const std::string& name) { m_motionName = name; }

public:
	// ボディモーション作成
	void CreateBodyMotion(std::vector<VMDBodyMotion>& motions);
	// モーフモーション作成
	void CreateMorphMotion(const std::vector<VMDMorphMotion>& motions);
	// カメラモーション作成
	void CreateCameraMotion(const std::vector<VMDCameraMotion>& motions);
	// ライトモーション作成
	void CreateLightMotion(const std::vector<VMDLightMotion>& motions);
	// セルフシャドウ
	void CreateSelfShadowMotion(const std::vector<VMDSelfShadowMotion>& motions);

};
