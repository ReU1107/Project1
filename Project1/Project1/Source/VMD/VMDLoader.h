#pragma once
#include <vector>

// �O���錾
class VMDBinaryReader;
struct VMDBodyMotion;
struct VMDMorphMotion;
struct VMDCameraMotion;
struct VMDLightMotion;
struct VMDSelfShadowMotion;

// VMD�t�@�C���ǂݍ���
class VMDLoader final
{
public:
	// �R���X�g���N�^
	VMDLoader();
	// �f�X�g���N�^
	~VMDLoader();

	void Load(const std::string& path);

private:
	// ���[�V�����z��ǂݍ���
	std::vector<VMDBodyMotion> LoadBodyMotions(VMDBinaryReader& reader);
	// �\��f�[�^�ǂݍ���
	std::vector<VMDMorphMotion> LoadMorphMotions(VMDBinaryReader& reader);
	// �J�����f�[�^�ǂݍ���
	std::vector<VMDCameraMotion> LoadCameraMotions(VMDBinaryReader& reader);
	// �Ɩ�(���C�g)�f�[�^�ǂݍ���
	std::vector<VMDLightMotion> LoadLightMotions(VMDBinaryReader& reader);
	// �Z���t�V���h�E�f�[�^�ǂݍ���
	std::vector<VMDSelfShadowMotion> LoadSelfShadowMotions(VMDBinaryReader& reader);

};
