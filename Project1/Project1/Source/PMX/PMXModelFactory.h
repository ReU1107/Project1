#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "../Engine/AnimationSystem/Avatar/SkeletonBone.h"

// ëOï˚êÈåæ
struct PMXModelInformation;
struct PMXBone;
struct PMXRigidBody;
struct PMXJoint;

namespace Engine
{

	class Bone;
	class GameObject;
	namespace GraphicsSystem
	{
		class Mesh;
		class SkeletalMesh;
	}
}

class PMXModelFactory
{
private:
	using GameObjectPtr = std::shared_ptr<Engine::GameObject>;
	using SkeletalMeshPtr = std::shared_ptr<Engine::GraphicsSystem::SkeletalMesh>;
private:
	const PMXModelInformation& m_pmxInformation;
	const std::vector<PMXBone>& m_pmxBones;
	const std::vector<PMXRigidBody>& m_pmxRigidBodies;
	const std::vector<PMXJoint>& m_pmxJoints;

public:
	PMXModelFactory(const PMXModelInformation& pmxInfo, 
		const std::vector<PMXBone>& bones, 
		const std::vector<PMXRigidBody>& rigidBodies,
		const std::vector<PMXJoint>& joints);

	~PMXModelFactory();

public:
	GameObjectPtr Create(SkeletalMeshPtr mesh);

private:

	GameObjectPtr CreateSkeleton(GameObjectPtr* rigidBodies, std::vector<std::shared_ptr<Engine::Bone>>& skinBones, std::unordered_map<std::string, Engine::AnimationSystem::SkeletonBone>& skeletonBones);

	void CreateRigidBodies(GameObjectPtr* rigidBodies, GameObjectPtr* bones);

	GameObjectPtr CreateJointRoot(GameObjectPtr* rigidBodies);

};
