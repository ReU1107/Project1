#include "PMXLoader.h"
#include "PMXDataModel.h"
#include "PMXBinaryReader.h"
#include "PMXMeshFactory.h"
#include "PMXModelFactory.h"

#include "../Engine//String/StringHelper.h"
#include "../Engine/GraphicsSystem/Mesh/Mesh.h"
#include "../Engine/GameObject/Include.h"
#include <istream>
#include <fstream>
#include <cassert>
using namespace Engine;
using namespace Engine::GraphicsSystem;

PMXLoader::PMXLoader()
{
}

PMXLoader::~PMXLoader()
{
}

std::shared_ptr<Engine::GameObject> PMXLoader::LoadModel(const std::string& path, bool skeletal)
{
	PMXBinaryReader reader(path);
	const char* meshPath = CreateBasePath(path.c_str());

	PMXHeader header(reader);
	PMXModelInformation modelInfomation(reader);
	m_addTexcoordCount = header.additionalUVCount;

	// 頂点情報読み込み
	auto vertices(std::move(LoadVertices(reader)));

	// 面情報(インデックス情報)読み込み
	auto indices(std::move(LoadIndices(reader)));

	// テクスチャ情報読み込み
	auto textureTable(std::move(LoadTextureTable(reader)));

	// マテリアル情報読み込み
	auto materials(std::move(LoadMaterials(reader)));

	if (skeletal)
	{
		// ボーン情報読み込み
		auto bones(std::move(LoadBones(reader)));

		// モーフ情報読み込み
		auto morphs(std::move(LoadMorphs(reader)));

		// 表示枠情報読み込み
		auto display(std::move(LoadDisplayFrames(reader)));

		// 剛体情報読み込み
		auto rigidBodies(std::move(LoadRigidBodies(reader)));

		// ジョイント情報読み込み
		auto joints(std::move(LoadJoints(reader)));

		PMXMeshFactory meshFactory(meshPath, modelInfomation, vertices, indices, materials, textureTable);
		auto mesh = meshFactory.Create(morphs);

		PMXModelFactory modelFactory(modelInfomation, bones, rigidBodies, joints);
		return modelFactory.Create(mesh);
	}
	else
	{
		auto modelObject = GameObject::Create(modelInfomation.name);
		PMXMeshFactory meshFactory(meshPath, modelInfomation, vertices, indices, materials, textureTable);
		auto mesh = meshFactory.Create();

		auto renderer = modelObject->AddComponent<MeshRenderer>();
		renderer->SetMesh(mesh);

		return modelObject;
	}

	return nullptr;
}

std::vector<PMXVertex> PMXLoader::LoadVertices(PMXBinaryReader& reader)
{
	// 頂点数
	uint32_t vertexCount = 0;
	reader.Read(&vertexCount, sizeof(vertexCount));
	std::vector<PMXVertex> vertices(vertexCount);

	for (auto& vertex : vertices)
	{
		reader.Read(&vertex.position, sizeof(vertex.position));
		reader.Read(&vertex.normal, sizeof(vertex.normal));
		reader.Read(&vertex.texcoord, sizeof(vertex.texcoord));

		for (uint8_t i = 0; i < m_addTexcoordCount; ++i) 
		{
			reader.Read(&vertex.addTexcoord[i], sizeof(vertex.addTexcoord[i]));
		}
		reader.Read(&vertex.type, sizeof(vertex.type));

		// ボーン情報
		switch (vertex.type)
		{
		case PMXWeightType::BDEF1:
			// ボーン1つのみ
			vertex.boneIndex[0] = reader.ReadIndex(PMXIndexType::Bone);
			vertex.boneWeight[0] = 1.0f;
			break;
		case PMXWeightType::BDEF2:
			// ボーン2つ,ボーン1のウェイト値
			vertex.boneIndex[0] = reader.ReadIndex(PMXIndexType::Bone);
			vertex.boneIndex[1] = reader.ReadIndex(PMXIndexType::Bone);

			reader.Read(&vertex.boneWeight[0], sizeof(vertex.boneWeight[0]));
			vertex.boneWeight[1] = 1.0f - vertex.boneWeight[0];
			break;
		case PMXWeightType::BDEF4:
			// ボーン4つ、ボーンそれぞれのウェイト値
			vertex.boneIndex[0] = reader.ReadIndex(PMXIndexType::Bone);
			vertex.boneIndex[1] = reader.ReadIndex(PMXIndexType::Bone);
			vertex.boneIndex[2] = reader.ReadIndex(PMXIndexType::Bone);
			vertex.boneIndex[3] = reader.ReadIndex(PMXIndexType::Bone);

			reader.Read(&vertex.boneWeight[0], sizeof(vertex.boneWeight[0]));
			reader.Read(&vertex.boneWeight[1], sizeof(vertex.boneWeight[1]));
			reader.Read(&vertex.boneWeight[2], sizeof(vertex.boneWeight[2]));
			reader.Read(&vertex.boneWeight[3], sizeof(vertex.boneWeight[3]));
			break;
		case PMXWeightType::SDEF:
			// BDEF2,SDEF用のfloat3(Vector3)が3つ
			vertex.boneIndex[0] = reader.ReadIndex(PMXIndexType::Bone);
			vertex.boneIndex[1] = reader.ReadIndex(PMXIndexType::Bone);
			reader.Read(&vertex.boneWeight[0], sizeof(vertex.boneWeight[0]));
			vertex.boneWeight[1] = 1.0f - vertex.boneWeight[0];
			reader.Read(&vertex.sdefC, sizeof(vertex.sdefC));
			reader.Read(&vertex.sdefR0, sizeof(vertex.sdefR0));
			reader.Read(&vertex.sdefR1, sizeof(vertex.sdefR1));
			break;
		default:
			assert("PMX頂点より前でずれている可能性があります");
			break;
		}

		// エッジ倍率
		reader.Read(&vertex.edge, sizeof(vertex.edge));
	}

	return std::move(vertices);
}

std::vector<PMXIndex> PMXLoader::LoadIndices(PMXBinaryReader& reader)
{
	uint32_t indexCount = 0;
	reader.Read(&indexCount, sizeof(indexCount));
	std::vector<PMXIndex> indices(indexCount / 3);

	for (auto& index : indices)
	{
		index.index[0] = reader.ReadIndex(PMXIndexType::Vertex);
		index.index[1] = reader.ReadIndex(PMXIndexType::Vertex);
		index.index[2] = reader.ReadIndex(PMXIndexType::Vertex);
	}

	return std::move(indices);
}

std::vector<PMXTexture> PMXLoader::LoadTextureTable(PMXBinaryReader& reader)
{
	uint32_t textureCount;
	reader.Read(&textureCount, sizeof(textureCount));
	std::vector<PMXTexture> textureTable(textureCount);

	for (auto& texture : textureTable) 
	{
		texture.textureFileName = std::move(reader.ReadString());
	}
	return std::move(textureTable);
}

std::vector<PMXMaterial> PMXLoader::LoadMaterials(PMXBinaryReader& reader)
{
	uint32_t materialCount;
	reader.Read(&materialCount, sizeof(materialCount));
	std::vector<PMXMaterial> materials(materialCount);

	for (auto& material : materials)
	{
		material.name = std::move(reader.ReadString());
		material.nameEnglish = std::move(reader.ReadString());

		reader.Read(&material.diffuseCoeff, sizeof(material.diffuseCoeff));
		reader.Read(&material.specularCoeff, sizeof(material.specularCoeff));
		reader.Read(&material.specularity, sizeof(material.specularity));
		reader.Read(&material.ambientCoeff, sizeof(material.ambientCoeff));

		reader.Read(&material.renderFlag, sizeof(material.renderFlag));
		reader.Read(&material.edge, sizeof(material.edge));
		reader.Read(&material.edgeSize, sizeof(material.edgeSize));

		material.decalIndex = reader.ReadIndex(PMXIndexType::Texture);
		material.sphereIndex = reader.ReadIndex(PMXIndexType::Texture);

		reader.Read(&material.sphereFlag, sizeof(material.sphereFlag));
		reader.Read(&material.shareToonFlag, sizeof(material.shareToonFlag));

		if (material.shareToonFlag == PMXShareToonFlag::Individual) 
		{
			material.toonIndex = reader.ReadIndex(PMXIndexType::Texture);
		}
		else if (material.shareToonFlag == PMXShareToonFlag::Share) 
		{
			material.shereToonTexture = reader.ReadIndex(PMXIndexType::Texture);
		}
		material.memo = std::move(reader.ReadString());

		reader.Read(&material.indexCount, sizeof(material.indexCount));
	}

	return std::move(materials);
}

std::vector<PMXBone> PMXLoader::LoadBones(PMXBinaryReader& reader)
{
	uint32_t boneCount;
	reader.Read(&boneCount, sizeof(boneCount));
	std::vector<PMXBone> bones(boneCount);

	for (auto& bone : bones)
	{
		bone.name = std::move(reader.ReadString());
		bone.nameEnglish = std::move(reader.ReadString());

		reader.Read(&bone.position, sizeof(bone.position));

		bone.parentIndex = reader.ReadIndex(PMXIndexType::Bone);
		reader.Read(&bone.transformHierarchy, sizeof(bone.transformHierarchy));

		reader.Read(&bone.boneFlag, sizeof(bone.boneFlag));
		// 接続先1
		if (((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::AccessShowMode) == 0) 
		{
			reader.Read(&bone.offsetPosition, sizeof(bone.offsetPosition));
		}
		else
		{
			bone.connectIndex = reader.ReadIndex(PMXIndexType::Bone);
		}

		// 回転付与, 移動付与1
		if (((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::TranlateAppend) ||
			((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::RotateAppend))
		{
			bone.influenceTargetIndex = reader.ReadIndex(PMXIndexType::Bone);
			reader.Read(&bone.influenceCoeff, sizeof(bone.influenceCoeff));
		}
		// 軸固定1
		if (((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::FixedAxis)) 
		{
			reader.Read(&bone.axisVector, sizeof(bone.axisVector));
		}

		// ローカル軸1
		if (((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::LocalAxis)) 
		{
			reader.Read(&bone.xAxis, sizeof(bone.xAxis));
			reader.Read(&bone.zAxis, sizeof(bone.zAxis));
		}

		// 外部親変形1
		if (((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::DeformOuterParent)) 
		{
			reader.Read(&bone.key, sizeof(bone.key));
		}

		// IK1
		if (((uint16_t)bone.boneFlag & (uint16_t)PMXBoneFlag::IK)) 
		{
			bone.ikTargetIndex = reader.ReadIndex(PMXIndexType::Bone);
			reader.Read(&bone.ikLoopCount, sizeof(bone.ikLoopCount));
			reader.Read(&bone.ikLimitAngle, sizeof(bone.ikLimitAngle));
			reader.Read(&bone.ikLinkCount, sizeof(bone.ikLinkCount));

			bone.ikLink.resize(bone.ikLinkCount);

			for (auto& ikLink : bone.ikLink) 
			{
				ikLink.linkIndex = reader.ReadIndex(PMXIndexType::Bone);
				reader.Read(&ikLink.limitFlag, sizeof(ikLink.limitFlag));

				// IKリンク1
				if (((uint8_t)ikLink.limitFlag & (uint8_t)PMXLimitFlag::ON)) 
				{
					reader.Read(&ikLink.lowerLimitAngle, sizeof(ikLink.lowerLimitAngle));
					reader.Read(&ikLink.upperLimitAngle, sizeof(ikLink.upperLimitAngle));
				}
			}
		}
	}

	return std::move(bones);
}

std::vector<PMXMorph> PMXLoader::LoadMorphs(PMXBinaryReader& reader)
{
	uint32_t morphCount;
	reader.Read(&morphCount, sizeof(morphCount));
	std::vector<PMXMorph> morphs(morphCount);

	for (auto& morph : morphs) 
	{
		morph.name = std::move(reader.ReadString());
		morph.nameEnglish = std::move(reader.ReadString());

		reader.Read(&morph.operation, sizeof(morph.operation));
		reader.Read(&morph.type, sizeof(morph.type));
		reader.Read(&morph.offsetCount, sizeof(morph.offsetCount));

		if (morph.type == PMXMorphType::Vertex) 
		{
			morph.vertexData.resize(morph.offsetCount);
			for (auto& vertex : morph.vertexData) 
			{
				vertex.index = reader.ReadIndex(PMXIndexType::Vertex);
				reader.Read(&vertex.offset, sizeof(vertex.offset));
			}
		}
		else if (morph.type == PMXMorphType::Texcoord || morph.type == PMXMorphType::AddTexcoord1 ||
			morph.type == PMXMorphType::AddTexcoord2 || morph.type == PMXMorphType::AddTexcoord3 ||
			morph.type == PMXMorphType::AddTexcoord4) {
			morph.texcoordData.resize(morph.offsetCount);
			for (auto& texcoord : morph.texcoordData) 
			{
				texcoord.index = reader.ReadIndex(PMXIndexType::Vertex);
				reader.Read(&texcoord.offset, sizeof(texcoord.offset));
			}
		}
		else if (morph.type == PMXMorphType::Bone) 
		{
			morph.boneData.resize(morph.offsetCount);
			for (auto& bone : morph.boneData) 
			{
				bone.index = reader.ReadIndex(PMXIndexType::Bone);

				reader.Read(&bone.displacement, sizeof(bone.displacement));
				reader.Read(&bone.rotation, sizeof(bone.rotation));
			}
		}
		else if (morph.type == PMXMorphType::Material)
		{
			morph.materialData.resize(morph.offsetCount);
			for (auto& material : morph.materialData) 
			{
				material.index = reader.ReadIndex(PMXIndexType::Material);
				reader.Read(&material.operation, sizeof(material.operation));
				reader.Read(&material.diffuse, sizeof(material.diffuse));
				reader.Read(&material.specular, sizeof(material.specular));
				reader.Read(&material.specularity, sizeof(material.specularity));
				reader.Read(&material.ambient, sizeof(material.ambient));
				reader.Read(&material.edge, sizeof(material.edge));
				reader.Read(&material.edgeSize, sizeof(material.edgeSize));
				reader.Read(&material.textureCoeff, sizeof(material.textureCoeff));
				reader.Read(&material.sphereTexCoeff, sizeof(material.sphereTexCoeff));
				reader.Read(&material.toonTexCoeff, sizeof(material.toonTexCoeff));
			}
		}
		else if (morph.type == PMXMorphType::Group) 
		{
			morph.groupData.resize(morph.offsetCount);
			for (auto& group : morph.groupData)
			{
				group.index = reader.ReadIndex(PMXIndexType::Morph);
				reader.Read(&group.coeff, sizeof(group.coeff));
			}
		}
		else {
			assert(!"");
		}
	}
	return std::move(morphs);
}

std::vector<PMXDisplayFrame> PMXLoader::LoadDisplayFrames(PMXBinaryReader& reader)
{
	uint32_t frameCount;
	reader.Read(&frameCount, sizeof(frameCount));
	std::vector<PMXDisplayFrame> frames(frameCount);

	for (auto& frame : frames)
	{
		frame.name = std::move(reader.ReadString());
		frame.nameEnglish = std::move(reader.ReadString());
		reader.Read(&frame.flag, sizeof(frame.flag));
		reader.Read(&frame.elementCount, sizeof(frame.elementCount));

		frame.elements.resize(frame.elementCount);

		for (auto& element : frame.elements) 
		{
			reader.Read(&element.target, sizeof(element.target));
			if (element.target == PMXFrameTarget::Bone) 
			{
				element.index = reader.ReadIndex(PMXIndexType::Bone);
			}
			else if (element.target == PMXFrameTarget::Morph) 
			{
				element.index = reader.ReadIndex(PMXIndexType::Morph);
			}
		}
	}

	return std::move(frames);
}

std::vector<PMXRigidBody> PMXLoader::LoadRigidBodies(PMXBinaryReader& reader)
{
	uint32_t rigidBodyCount;
	reader.Read(&rigidBodyCount, sizeof(rigidBodyCount));
	std::vector<PMXRigidBody> rigidBodies(rigidBodyCount);

	for (auto& rigidBody : rigidBodies) 
	{
		rigidBody.name = std::move(reader.ReadString());
		rigidBody.nameEnglish = std::move(reader.ReadString());

		rigidBody.index = reader.ReadIndex(PMXIndexType::Bone);

		reader.Read(&rigidBody.group, sizeof(rigidBody.group));
		reader.Read(&rigidBody.collisionGroup, sizeof(rigidBody.collisionGroup));
		reader.Read(&rigidBody.shape, sizeof(rigidBody.shape));

		reader.Read(&rigidBody.size, sizeof(rigidBody.size));
		reader.Read(&rigidBody.position, sizeof(rigidBody.position));
		reader.Read(&rigidBody.rotation, sizeof(rigidBody.rotation));

		reader.Read(&rigidBody.mass, sizeof(rigidBody.mass));
		reader.Read(&rigidBody.translationAtten, sizeof(rigidBody.translationAtten));
		reader.Read(&rigidBody.rotationAtten, sizeof(rigidBody.rotationAtten));
		reader.Read(&rigidBody.repulsive, sizeof(rigidBody.repulsive));
		reader.Read(&rigidBody.friction, sizeof(rigidBody.friction));

		reader.Read(&rigidBody.operation, sizeof(rigidBody.operation));
	}

	return std::move(rigidBodies);
}

std::vector<PMXJoint> PMXLoader::LoadJoints(PMXBinaryReader& reader)
{
	uint32_t jointCount;
	reader.Read(&jointCount, sizeof(jointCount));
	std::vector<PMXJoint> joints(jointCount);

	for (auto& joint : joints)
	{
		joint.name = std::move(reader.ReadString());
		joint.nameEnglish = std::move(reader.ReadString());


		reader.Read(&joint.type, sizeof(joint.type));

		if (joint.type == PMXJointType::Spring)
		{
			joint.indexA = reader.ReadIndex(PMXIndexType::RigidBody);
			joint.indexB = reader.ReadIndex(PMXIndexType::RigidBody);

			reader.Read(&joint.position, sizeof(joint.position));
			reader.Read(&joint.rotation, sizeof(joint.rotation));

			reader.Read(&joint.lowerTranslation, sizeof(joint.lowerTranslation));
			reader.Read(&joint.upperTranslation, sizeof(joint.upperTranslation));
			reader.Read(&joint.lowerRotation, sizeof(joint.lowerRotation));
			reader.Read(&joint.upperRotation, sizeof(joint.upperRotation));

			reader.Read(&joint.constantTranslatin, sizeof(joint.constantTranslatin));
			reader.Read(&joint.constantRotation, sizeof(joint.constantRotation));

		}
	}

	return std::move(joints);
}


