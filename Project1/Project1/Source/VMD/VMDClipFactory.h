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
	// �{�f�B���[�V�����쐬
	void CreateBodyMotion(std::vector<VMDBodyMotion>& motions);
	// ���[�t���[�V�����쐬
	void CreateMorphMotion(const std::vector<VMDMorphMotion>& motions);
	// �J�������[�V�����쐬
	void CreateCameraMotion(const std::vector<VMDCameraMotion>& motions);
	// ���C�g���[�V�����쐬
	void CreateLightMotion(const std::vector<VMDLightMotion>& motions);
	// �Z���t�V���h�E
	void CreateSelfShadowMotion(const std::vector<VMDSelfShadowMotion>& motions);

};
