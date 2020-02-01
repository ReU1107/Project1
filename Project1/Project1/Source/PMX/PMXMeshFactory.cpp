#include "PMXMeshFactory.h"
#include "PMXDataModel.h"

#include "../Engine/Include.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

PMXMeshFactory::PMXMeshFactory(const char* meshPath, const PMXModelInformation& modelInfomation, const std::vector<PMXVertex>& vertices, const std::vector<PMXIndex>& indices, const std::vector<PMXMaterial>& materials, const std::vector<PMXTexture>& textureTable)
	: m_meshPath(meshPath)
	, m_pmxInformation(modelInfomation)
	, m_pmxVertices(vertices)
	, m_pmxIndices(indices)
	, m_pmxMaterials(materials)
	, m_pmxTextureTable(textureTable)
{
}

PMXMeshFactory::~PMXMeshFactory()
{
	delete m_meshPath;
}

std::shared_ptr<Engine::GraphicsSystem::StaticMesh> PMXMeshFactory::Create()
{
	auto mesh = Mesh::Create<StaticMesh>(m_pmxInformation.name);

	// 頂点情報設定
	SetVertices(mesh);
	// 頂点インデックス情報設定
	SetIndices(mesh);
	// ジオメトリ情報設定
	SetGeometries(mesh);

	mesh->CreateVertexBuffes();
	mesh->CreateIndexBuffer();

	return mesh;
}

std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh> PMXMeshFactory::Create(const std::vector<PMXMorph>& morphs)
{
	auto mesh = Mesh::Create<SkeletalMesh>(m_pmxInformation.name);

	// 頂点情報設定
	SetVertices(mesh);
	// 頂点インデックス情報設定
	SetIndices(mesh);
	// ジオメトリ情報設定
	SetGeometries(mesh);
	// モーフ情報設定
	SetBlendShapes(mesh, morphs);

	mesh->CreateVertexBuffes();
	mesh->CreateIndexBuffer();

	return mesh;
}

void PMXMeshFactory::SetVertices(std::shared_ptr<Engine::GraphicsSystem::StaticMesh> mesh)
{
	uint32_t vertexCount = m_pmxVertices.size();

	auto& positions = mesh->GetPositions();
	positions.resize(vertexCount);
	auto& normals = mesh->GetNormals();
	normals.resize(vertexCount);
	auto & texcoords = mesh->GetTexcoords0();
	texcoords.resize(vertexCount * 2);
	uint32_t texIndex = 0;

	for (uint32_t i = 0; i < vertexCount; ++i)
	{
		auto& vertex = m_pmxVertices[i];
		positions[i] = vertex.position;

		normals[i] = vertex.normal;

		texIndex = i * 2;
		texcoords[texIndex] = vertex.texcoord.x;
		texcoords[texIndex + 1] = vertex.texcoord.y;

	}
}

void PMXMeshFactory::SetVertices(std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh> mesh)
{
	uint32_t vertexCount = m_pmxVertices.size();

	auto& positions = mesh->GetPositions();
	positions.resize(vertexCount);

	auto& basePositions = mesh->GetBasePositions();
	basePositions.resize(vertexCount);

	auto& normals = mesh->GetNormals();
	normals.resize(vertexCount);

	auto& texcoords = mesh->GetTexcoords0();
	texcoords.resize(vertexCount * 2);

	auto& boneWeights = mesh->GetBoneWeights();
	boneWeights.resize(vertexCount);

	uint32_t texIndex = 0;

	for (uint32_t i = 0; i < vertexCount; ++i)
	{
		auto& vertex = m_pmxVertices[i];
		positions[i] = vertex.position;

		basePositions[i] = vertex.position;

		normals[i] = vertex.normal;

		texIndex = i * 2;
		texcoords[texIndex] = vertex.texcoord.x;
		texcoords[texIndex + 1] = vertex.texcoord.y;

		boneWeights[i].boneIndex0 = vertex.boneIndex[0];
		boneWeights[i].boneIndex1 = vertex.boneIndex[1];
		boneWeights[i].boneIndex2 = vertex.boneIndex[2];
		boneWeights[i].boneIndex3 = vertex.boneIndex[3];
		boneWeights[i].weight0 = vertex.boneWeight[0];
		boneWeights[i].weight1 = vertex.boneWeight[1];
		boneWeights[i].weight2 = vertex.boneWeight[2];
		boneWeights[i].weight3 = vertex.boneWeight[3];
	}

	mesh->AddVertexLayout(VertexLayout::BasePositions);
	mesh->AddVertexLayout(VertexLayout::BoneWeights);
}

void PMXMeshFactory::SetIndices(std::shared_ptr<Engine::GraphicsSystem::Mesh> mesh)
{
	// *3   PMXのデータ構造体が3つのインデックス情報を格納している為
	uint64_t indexCount = (uint64_t)m_pmxIndices.size();
	auto& indices = mesh->GetIndices();
	indices.resize(indexCount * 3);
	for (uint64_t i = 0; i < indexCount; ++i) 
	{
		uint64_t index = i * 3;
		indices[index] = m_pmxIndices[i].index[0];
		indices[index + 1] = m_pmxIndices[i].index[1];
		indices[index + 2] = m_pmxIndices[i].index[2];
	}
}

void PMXMeshFactory::CreateTextureTable(std::vector<std::shared_ptr<Texture>>& textureTable, uint32_t textureCount)
{
	textureTable.resize(textureCount);
	for (uint32_t i = 0; i < textureCount; ++i)
	{
		char texturePath[256];
		strcpy_s(texturePath, 255, m_meshPath);
		strcat_s(texturePath, 255, m_pmxTextureTable[i].textureFileName.c_str());

		char* place = strrchr(texturePath, '*');
		if (place)
		{
			*place = '\0';
		}

		textureTable[i] = Texture::Create(texturePath);
	}
}

void PMXMeshFactory::SetGeometries(std::shared_ptr<Engine::GraphicsSystem::Mesh> mesh)
{
	// テクスチャテーブル作成
	std::vector<std::shared_ptr<Texture>> textureTable;
	uint32_t textureCount = m_pmxTextureTable.size();
	CreateTextureTable(textureTable, textureCount);
	
	mesh->SetTextureCount(textureCount);

	uint32_t materialCount = m_pmxMaterials.size();

	auto& subMeshes = mesh->GetSubMeshes();
	subMeshes.resize(materialCount);

	uint32_t startIndexLocation = 0;
	for (uint32_t i = 0; i < materialCount; ++i) 
	{
		auto& pmxMaterial = m_pmxMaterials[i];
		auto material = std::make_shared<Material>(pmxMaterial.name);
		material->SetAmbientCoeff(pmxMaterial.ambientCoeff);
		material->SetDiffuseCoeff(Color3(pmxMaterial.diffuseCoeff.r, pmxMaterial.diffuseCoeff.g, pmxMaterial.diffuseCoeff.b));
		material->SetSpecularCoeff(pmxMaterial.specularCoeff);
		material->SetOpacity(pmxMaterial.diffuseCoeff.a);

		material->SetSpecularity(pmxMaterial.specularity);
		uint32_t decalIndex = pmxMaterial.decalIndex;
		if (decalIndex < textureCount) 
		{
			material->SetDecalTexture(textureTable[decalIndex]);
		}

		//if (pmxMaterial.sphereFlag != PMXSphereMode::None) {
		//	BlendType type = pmxMaterial.sphereFlag == PMXSphereMode::Spa ? BlendType::Addition : BlendType::Multiplication;
		//	uint32_t sphereIndex = pmxMaterial.sphereIndex;
		//	if (sphereIndex < textureCount) {
		//		material->AddBlendTexture(textureTable[sphereIndex], type);
		//	}
		//}

		auto subMesh = std::make_shared<SubMesh>(pmxMaterial.name);
		subMesh->SetStartIndexLocation(startIndexLocation);
		subMesh->SetUseIndexCount(pmxMaterial.indexCount);
		startIndexLocation += pmxMaterial.indexCount;
		subMesh->SetMaterial(material);
		subMeshes[i] = subMesh;

	}

	textureTable.clear();
}

void PMXMeshFactory::SetBlendShapes(std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh> mesh, const std::vector<PMXMorph>& morphs)
{
	uint32_t morphCount = morphs.size();
	// (モーフ情報がないなら無視)
	if (morphCount <= 0) 
	{
		return;
	}
	uint32_t vertexCount = mesh->GetVertexCount();
	auto& deltaPositions = mesh->GetDeltaPositions();
	// 差分位置配列作成
	deltaPositions.resize(vertexCount);
	mesh->AddVertexLayout(VertexLayout::DeltaPositions);

	// 仮でVertexのみ作成
	for (auto& morph : morphs)
	{
		switch (morph.type)
		{
		case PMXMorphType::Vertex:
		{
			const uint32_t deltaCount = morph.offsetCount;
			auto blendShape = std::make_shared<BlendShape>(morph.name);

			auto& deltaPositions = blendShape->GetDeltaPositions();
			deltaPositions.resize(deltaCount);
			for (uint32_t i = 0; i < deltaCount; ++i)
			{
				deltaPositions[i].index = morph.vertexData[i].index;
				deltaPositions[i].value = morph.vertexData[i].offset;
			}

			mesh->AddBlendShapeFrame(blendShape);
		} break;
		case PMXMorphType::Texcoord:

			break;
		default:
			break;
		}
	}
}

