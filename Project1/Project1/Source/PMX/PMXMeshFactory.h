#pragma once
#include <vector>
#include <iostream>

struct PMXModelInformation;
struct PMXVertex;
struct PMXIndex;
struct PMXMaterial;
struct PMXTexture;
struct PMXMorph;
namespace Engine 
{

	namespace GraphicsSystem
	{
		class Mesh;
		class Texture;
		class StaticMesh;
		class SkeletalMesh;
	}
}
class PMXMeshFactory final
{
private:
	const char* m_meshPath;

	const PMXModelInformation& m_pmxInformation;
	const std::vector<PMXVertex>& m_pmxVertices;
	const std::vector<PMXIndex>& m_pmxIndices;
	const std::vector<PMXMaterial>& m_pmxMaterials;
	const std::vector<PMXTexture>& m_pmxTextureTable;

public:
	PMXMeshFactory(
		const char* meshPath,
		const PMXModelInformation& modelInfomation,
		const std::vector<PMXVertex>& vertices,
		const std::vector<PMXIndex>& indices,
		const std::vector<PMXMaterial>& materials,
		const std::vector<PMXTexture>& textureTable
	);
	~PMXMeshFactory();

public:
	std::shared_ptr<Engine::GraphicsSystem::StaticMesh> Create();

	std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh> Create(const std::vector<PMXMorph>& morphs);

private:
	// メッシュに頂点情報設定
	void SetVertices(std::shared_ptr<Engine::GraphicsSystem::StaticMesh> mesh);
	void SetVertices(std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh> mesh);
	// メッシュに頂点インデックス情報設定
	void SetIndices(std::shared_ptr<Engine::GraphicsSystem::Mesh> mesh);
	// テクスチャテーブル作成
	void CreateTextureTable(std::vector<std::shared_ptr<Engine::GraphicsSystem::Texture>>& textureTable, uint32_t textureCount);
	// メッシュに形状に関する情報設定
	void SetGeometries(std::shared_ptr<Engine::GraphicsSystem::Mesh> mesh);
	// メッシュにモーフィングデータ設定
	void SetBlendShapes(std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh> mesh, const std::vector<PMXMorph>& morphs);

};
