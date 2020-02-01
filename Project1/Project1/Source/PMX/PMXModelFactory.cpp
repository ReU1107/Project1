#include "PMXModelFactory.h"
#include "PMXDataModel.h"
#include "../Engine/Include.h"
#include "../Script/PMXBoneController.h"

using namespace DirectX;
using namespace Engine;
using namespace Engine::GraphicsSystem;
using namespace Engine::AnimationSystem;
using namespace Engine::PhysicsSystem;

PMXModelFactory::PMXModelFactory(const PMXModelInformation& pmxInfo, const std::vector<PMXBone>& bones, const std::vector<PMXRigidBody>& rigidBodies, const std::vector<PMXJoint>& joints)
	: m_pmxInformation(pmxInfo)
	, m_pmxBones(bones)
	, m_pmxRigidBodies(rigidBodies)
	, m_pmxJoints(joints)
{
}

PMXModelFactory::~PMXModelFactory()
{
}

PMXModelFactory::GameObjectPtr PMXModelFactory::Create(SkeletalMeshPtr mesh)
{
	// モデルオブジェクト
	auto model = GameObject::Create(m_pmxInformation.name);

	uint32_t boneCount = m_pmxBones.size();
	std::unordered_map<std::string, SkeletonBone> skeletonBones;

	uint32_t rigiBodyCount = m_pmxRigidBodies.size();
	// 剛体配列 (ジョイント作成時のindexがRigidBody単位になっている為)
	GameObjectPtr* rigidBodyObjects(new GameObjectPtr[rigiBodyCount]);

	auto avatar = std::make_shared<Avatar>();

	auto& parts = avatar->GetBodyParts();
	auto& blendShapes = mesh->GetBlendShapes();
	for (auto& blendShape : blendShapes)
	{
		BodyPart part;
		part.targetObject = blendShape;
		part.id = InstanceID::BlendShape;
		part.name = blendShape->GetName();

		parts.insert({ part.name,part });
	}
	auto renderer = model->AddComponent<SkinnedMeshRenderer>();
	renderer->SetMesh(mesh);
	auto& skinBones = renderer->GetSkinBones();

	// スケルトンオブジェクト
	auto skeleton = CreateSkeleton(rigidBodyObjects, skinBones, skeletonBones);
	model->AddChild(skeleton);
	AvatarBuilder::BuildHumanAvatar(avatar, skeleton);

	auto animator = model->AddComponent<Animator>();
	animator->SetAvatar(avatar);

	return model;
}

PMXModelFactory::GameObjectPtr PMXModelFactory::CreateSkeleton(GameObjectPtr* rigidBodies, std::vector<std::shared_ptr<Engine::Bone>>& skinBones, std::unordered_map<std::string, Engine::AnimationSystem::SkeletonBone>& skeletonBones)
{
	auto skeleton = GameObject::Create(m_pmxInformation.name + "スケルトン", false);
	uint32_t boneCount = m_pmxBones.size();
	skinBones.resize(boneCount);

	// ボーン配列
	GameObjectPtr* bones(new GameObjectPtr[boneCount]);

	// スケーリング行列
	const XMMATRIX scalingMatrix = XMMatrixScalingFromVector(XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f));
	// 回転行列
	const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&Vector4::Identity));

	// 一度全てのボーンオブジェクトを作成
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		auto& pmxBone = m_pmxBones[i];
		auto& name = pmxBone.name;
		bones[i] = GameObject::Create(name, false);
		std::shared_ptr<Bone> bone = nullptr;

		if ((pmxBone.boneFlag & PMXBoneFlag::IK) != 0)
		{
			bone = bones[i]->AddComponent<IKBone>();
		}
		else
		{
			bone = bones[i]->AddComponent<FKBone>();
		}
		if ((pmxBone.boneFlag & PMXBoneFlag::FixedAxis) != 0)
		{
			bone->SetFixedAxis(pmxBone.axisVector);
		}

	}
	// 親がいないときは8,16bitの最大数が入っている
	const static uint8_t parentNone8 = 0xff;
	const static uint16_t parentNone16 = 0xffff;
	// ボーン数によって読み込み情報のbitサイズが違う為最大値も違う
	uint32_t parentNone = 0;
	if (boneCount < parentNone8)
	{
		parentNone = parentNone8;
	}
	else if (boneCount < parentNone16)
	{
		parentNone = parentNone16;
	}

	// 親子関係作成
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		auto& pmxBone = m_pmxBones[i];
		auto boneObject = bones[i];
		auto& name = pmxBone.name;
		// 回転値,スケール値は入っていない為デフォルト
		SkeletonBone skeletonBone;
		skeletonBone.position.x = pmxBone.position.x;
		skeletonBone.position.y = pmxBone.position.y;
		skeletonBone.position.z = pmxBone.position.z;

		// 移動行列
		const XMMATRIX translationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&skeletonBone.position));

		const XMMATRIX bindMatrix = XMMatrixMultiply(XMMatrixMultiply(scalingMatrix, rotationMatrix), translationMatrix);

		Matrix4x4 offsetMatrix = Matrix4x4::Identity;
		XMStoreFloat4x4(&offsetMatrix, XMMatrixInverse(nullptr, bindMatrix));

		const uint16_t parentIndex = pmxBone.parentIndex;

		auto transform = boneObject->GetTransform();
		// 親がいない
		if (parentIndex == parentNone)
		{
			// スケルトンオブジェクトの子として追加
			skeleton->AddChild(boneObject);
			transform->SetLocalPosition(pmxBone.position);
		}
		else
		{
			auto& pmxParentBone = m_pmxBones[parentIndex];
			auto parentBone = bones[parentIndex];
			parentBone->AddChild(boneObject);

			// 親から見た相対位置
			Vector3 localPosition = pmxBone.position - pmxParentBone.position;
			transform->SetLocalPosition(localPosition);
		}

		auto bone = boneObject->GetComponent<Bone>();

		skinBones[i] = bone;
		skinBones[i]->SetOffsetMatrix(offsetMatrix);

		if (skinBones[i]->GetType() == BoneType::InverseKinematics)
		{
			std::shared_ptr<IKBone> ik = std::dynamic_pointer_cast<IKBone>(bone);

			ik->SetEffectorBone(bones[pmxBone.ikTargetIndex]->GetComponent<Bone>());
			
			ik->SetIterationCount(pmxBone.ikLoopCount);

			ik->SetIterationLimitAngle(pmxBone.ikLimitAngle);

			for (auto& pmxLink : pmxBone.ikLink)
			{
				IKLink ikLink;
				ikLink.bone = bones[pmxLink.linkIndex]->GetComponent<Bone>();
				ikLink.isLimit = pmxLink.limitFlag == PMXLimitFlag::ON ? true : false;
				ikLink.lowerLimitAngle = pmxLink.lowerLimitAngle;
				ikLink.upperLimitAngle = pmxLink.upperLimitAngle;

				ik->AddLink(ikLink);
			}

			ik->AddComponent<PMXBoneController>();
		}

		skeletonBones.insert({ name,skeletonBone });
	}

	// 剛体情報
	CreateRigidBodies(rigidBodies, bones);

	return skeleton;
}

void PMXModelFactory::CreateRigidBodies(GameObjectPtr* rigidBodies, GameObjectPtr* bones)
{

	uint32_t rigidBodyCount = m_pmxRigidBodies.size();
	int32_t index;
	for (uint32_t i = 0; i < rigidBodyCount; ++i) 
	{
		auto& pmxRigidBody = m_pmxRigidBodies[i];
		index = pmxRigidBody.index;
		auto bone = bones[index];
		rigidBodies[i] = bone;
		auto rigidBody = bone->AddComponent<RigidBody>();

		rigidBody->SetPosition(pmxRigidBody.position);
		rigidBody->SetRotation(pmxRigidBody.rotation);

		std::shared_ptr<PhysicsMaterial> material = nullptr;
		uint32_t mask = 0;
		mask |= (UINT16_MAX - pmxRigidBody.collisionGroup);
		if (pmxRigidBody.shape == PMXShape::Sphere)
		{
			auto sphereCollider = bones[index]->AddComponent<SphereCollider>();
			sphereCollider->SetLocalCenter(pmxRigidBody.position);
			sphereCollider->SetLocalRadius(pmxRigidBody.size.x);
			sphereCollider->SetMask(mask);

			sphereCollider->SetRigidBody(rigidBody);
			material = sphereCollider->GetPhysicMaterial();
		}
		else if (pmxRigidBody.shape == PMXShape::Box) 
		{
			auto boxCollider = bones[index]->AddComponent<BoxCollider>();
			boxCollider->SetLocalCenter(pmxRigidBody.position);
			boxCollider->SetLocalSize(pmxRigidBody.size);
			boxCollider->SetMask(mask);
			boxCollider->SetRigidBody(rigidBody);

			material = boxCollider->GetPhysicMaterial();
		}
		else if (pmxRigidBody.shape == PMXShape::Capsule) 
		{
			auto capsuleCollider = bones[index]->AddComponent<CapsuleCollider>();
			capsuleCollider->SetLocalCenter(pmxRigidBody.position);
			capsuleCollider->SetLocalDirection(Vector3(0.0f, 1.0f, 0.0f));
			capsuleCollider->SetLocalHeight(pmxRigidBody.size.x);
			capsuleCollider->SetLocalRadius(pmxRigidBody.size.y);
			capsuleCollider->SetMask(mask);
			capsuleCollider->SetRigidBody(rigidBody);
			material = capsuleCollider->GetPhysicMaterial();
		}
		//material->SetReflection(pmxRigidBody.repulsive);
		material->SetMass(pmxRigidBody.mass);
		material->SetStaticFriction(pmxRigidBody.friction);
		material->SetDynamicFriction(pmxRigidBody.translationAtten);
	}
}

PMXModelFactory::GameObjectPtr PMXModelFactory::CreateJointRoot(GameObjectPtr* rigidBodies)
{
	auto jointRoot = GameObject::Create("JointRoot");

	for (auto& joint : m_pmxJoints)
	{
		auto object = GameObject::Create(joint.name);

		if (joint.type == PMXJointType::Spring)
		{
			auto springJoint = object->AddComponent<SpringJoint>();

			if (joint.indexA != UINT32_MAX)
			{
				springJoint->AddConnectBone(rigidBodies[joint.indexA]);
			}
			if (joint.indexB != UINT32_MAX)
			{
				springJoint->AddConnectBone(rigidBodies[joint.indexB]);
			}

		}

		jointRoot->AddChild(object);

	}

	return jointRoot;
}
