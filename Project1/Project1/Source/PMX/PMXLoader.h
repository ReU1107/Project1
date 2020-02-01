#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

// 前方宣言
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
	uint8_t m_addTexcoordCount;			// 現在の追加UV数
public:
	// コンストラクタ
	PMXLoader();
	// デストラクタ
	~PMXLoader();

	std::shared_ptr<Engine::GameObject> LoadModel(const std::string& path, bool skeletal = false);
private:
	// 頂点配列読み込み
	std::vector<PMXVertex> LoadVertices(PMXBinaryReader& reader);

	// インデックス読み込み
	std::vector<PMXIndex> LoadIndices(PMXBinaryReader& reader);

	// テクスチャテーブル読み込み
	std::vector<PMXTexture> LoadTextureTable(PMXBinaryReader& reader);

	// マテリアル配列読み込み
	std::vector<PMXMaterial> LoadMaterials(PMXBinaryReader& reader);

	// ボーン配列読み込み
	std::vector<PMXBone> LoadBones(PMXBinaryReader& reader);

	// モーフ配列読み込み
	std::vector<PMXMorph> LoadMorphs(PMXBinaryReader& reader);

	// 表示枠配列読み込み
	std::vector<PMXDisplayFrame> LoadDisplayFrames(PMXBinaryReader& reader);

	// 剛体配列読み込み
	std::vector<PMXRigidBody> LoadRigidBodies(PMXBinaryReader& reader);

	// ジョイント配列読み込み
	std::vector<PMXJoint> LoadJoints(PMXBinaryReader& reader);

};
