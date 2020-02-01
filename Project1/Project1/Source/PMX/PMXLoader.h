#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

// �O���錾
class PMXBinaryReader;
struct PMXModelInformation;
struct PMXVertex;
struct PMXIndex;
struct PMXTexture;
struct PMXMaterial;
struct PMXBone;
struct PMXMorph;
struct PMXDisplayFrame;
struct PMXRigidBody;
struct PMXJoint;
namespace Engine
{
	class GameObject;

	namespace GraphicsSystem 
	{
		class Mesh;
		class StaticMesh;
		class SkeletalMesh;
	}
}
class PMXLoader final
{
private:
	uint8_t m_addTexcoordCount;			// ���݂̒ǉ�UV��
public:
	// �R���X�g���N�^
	PMXLoader();
	// �f�X�g���N�^
	~PMXLoader();

	std::shared_ptr<Engine::GameObject> LoadModel(const std::string& path, bool skeletal = false);
private:
	// ���_�z��ǂݍ���
	std::vector<PMXVertex> LoadVertices(PMXBinaryReader& reader);

	// �C���f�b�N�X�ǂݍ���
	std::vector<PMXIndex> LoadIndices(PMXBinaryReader& reader);

	// �e�N�X�`���e�[�u���ǂݍ���
	std::vector<PMXTexture> LoadTextureTable(PMXBinaryReader& reader);

	// �}�e���A���z��ǂݍ���
	std::vector<PMXMaterial> LoadMaterials(PMXBinaryReader& reader);

	// �{�[���z��ǂݍ���
	std::vector<PMXBone> LoadBones(PMXBinaryReader& reader);

	// ���[�t�z��ǂݍ���
	std::vector<PMXMorph> LoadMorphs(PMXBinaryReader& reader);

	// �\���g�z��ǂݍ���
	std::vector<PMXDisplayFrame> LoadDisplayFrames(PMXBinaryReader& reader);

	// ���̔z��ǂݍ���
	std::vector<PMXRigidBody> LoadRigidBodies(PMXBinaryReader& reader);

	// �W���C���g�z��ǂݍ���
	std::vector<PMXJoint> LoadJoints(PMXBinaryReader& reader);

};
