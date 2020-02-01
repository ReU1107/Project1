#include "AvatarBuilder.h"
#include "Avatar.h"
#include "BodyPart.h"
#include "../../GameObject/Include.h"
#include "HumanDescription.h"

namespace Engine
{
	namespace AnimationSystem
	{
		//void AvatarBuilder::BuildHumanAvatarDesendentID(std::unordered_map<HumanBodyBones, BodyPart>& bones, std::shared_ptr<Engine::Transform> transform, const HumanDescription& humanDescription)
		//{
		//	//const auto& name = transform->GetOwner()->GetName();
		//	//const auto& skeletonBones = humanDescription.skeletonBones;
		//	//const auto& it = skeletonBones.find(name);
		//	//if (it != skeletonBones.cend())
		//	//{
		//	//	auto& skeletonBone = (*it).second;

		//	//	BodyPart part(transform, skeletonBone.classID);
		//	//	part.name = name;
		//	//	//part.bindPosition = skeletonBone.position;
		//	//	//part.bindRotation = skeletonBone.rotation;
		//	//	//part.bindScale = skeletonBone.scale;
		//	//	HumanBodyBones humanBoneID = HumanBoneID(name);
		//	//	bones.insert({ humanBoneID,part });
		//	//}

		//	//auto nextSibling = transform->GetNextSibling();
		//	//if (nextSibling)
		//	//{
		//	//	BuildHumanAvatarDesendentID(bones, nextSibling, humanDescription);
		//	//}
		//	//auto oldestChild = transform->GetOldestChild();
		//	//if (oldestChild)
		//	//{
		//	//	BuildHumanAvatarDesendentID(bones, oldestChild, humanDescription);
		//	//}
		//}

		void AvatarBuilder::BuildHumanAvatarDesendentName(std::unordered_map<std::string, BodyPart>& bones, std::shared_ptr<GameObject> gameObject, const HumanDescription& humanDescription)
		{
			const auto& name = gameObject->GetName();
			const auto& skeletonBones = humanDescription.skeletonBones;
			const auto& it = skeletonBones.find(name);
			if (it != skeletonBones.cend()) 
			{
				auto& skeletonBone = (*it).second;

				BodyPart part;
				part.name = name;
				if (skeletonBone.id == InstanceID::Transform)
				{
					part.targetObject = gameObject->GetTransform();
				}
				else if (skeletonBone.id == InstanceID::BlendShape)
				{
				//	part.targetObject = gameObject->GetComponent<SkinnedMeshRenderer>()->GetMesh();
					
				}

				
				bones.insert({ name,part });
			}

			auto nextSibling = gameObject->GetNextSibling();
			if (nextSibling) 
			{
				BuildHumanAvatarDesendentName(bones, nextSibling, humanDescription);
			}
			auto oldestChild = gameObject->GetOldestChild();
			if (oldestChild)
			{
				BuildHumanAvatarDesendentName(bones, oldestChild, humanDescription);
			}
		}

		std::shared_ptr<Avatar> AvatarBuilder::BuildHumanAvatar(std::shared_ptr<GameObject> root, const HumanDescription& humanDescription)
		{
			auto avatar = std::make_shared<Avatar>();
			auto& bones = avatar->GetBodyParts();
			BuildHumanAvatarDesendentName(bones, root, humanDescription);

			return avatar;
		}

		void AvatarBuilder::BuildHumanAvatar(std::shared_ptr<Avatar> avatar, std::shared_ptr<GameObject> rootObject)
		{
			auto& bones = avatar->GetBodyParts();
			Test(bones, rootObject);
		}

		void AvatarBuilder::Test(std::unordered_map<std::string, BodyPart>& parts, std::shared_ptr<GameObject> gameObject)
		{
			BodyPart part;
			part.targetObject = gameObject->GetComponent<Bone>();
			part.id = InstanceID::Bone;
			part.name = gameObject->GetName();

			parts.insert({ part.name,part });

			auto next = gameObject->GetNextSibling();
			if (next)
			{
				Test(parts, next);
			}
			auto child = gameObject->GetOldestChild();
			if (child)
			{
				Test(parts, child);
			}

		}

		//Avatar * AvatarBuilder::BuildHumanAvatar(const HumanDescription & humanDescription)
		//{
		//	Avatar * avatar = new Avatar();

		//	std::vector<SkinBone> bones(humanDescription.skeletonCount);
		//	for (uint32_t i = 0; i < humanDescription.skeletonCount; ++i) {
		//		auto & skeleton = humanDescription.skeletonBones[i];
		//		bones[i].transform = skeleton.transform;

		//		// スケーリング行列
		//		const XMMATRIX scalingMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&skeleton.scale));
		//		// 回転行列
		//		const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&skeleton.rotation));
		//		// 移動行列
		//		const XMMATRIX translationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&skeleton.position));

		//		XMStoreFloat4x4(&bones[i].bindMatrix, XMMatrixMultiply(XMMatrixMultiply(scalingMatrix, rotationMatrix), translationMatrix));

		//		XMStoreFloat4x4(&bones[i].offsetMatrix, XMMatrixInverse(nullptr, XMLoadFloat4x4(&bones[i].bindMatrix)));
		//	}
		//	avatar->SetBones(std::move(bones));

		//	return avatar;
		//}
	}
}