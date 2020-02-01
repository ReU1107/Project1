#pragma once
#include <unordered_map>
#include <string>
#include "../Enumerations/HumanBodyBones.h"
#include <memory>

namespace Engine
{
	class GameObject;
	class Transform;

	namespace AnimationSystem
	{
		// 前方宣言
		class Avatar;
		struct HumanDescription;
		struct BodyPart;

		class AvatarBuilder
		{
		private:
			// 本当はこっちで作らないといけないがHumanBodyBonesを決める方法が不明なため文字列で管理
			static void BuildHumanAvatarDesendentID(std::unordered_map<HumanBodyBones, BodyPart>& bones, std::shared_ptr<GameObject> gameObject, const HumanDescription& humanDescription);

			static void BuildHumanAvatarDesendentName(std::unordered_map<std::string, BodyPart>& bones, std::shared_ptr<GameObject> gameObject, const HumanDescription& humanDescription);

		public:
			// ヒューマノイド(人型)アバター作成
			static std::shared_ptr<Avatar> BuildHumanAvatar(std::shared_ptr<GameObject> root, const HumanDescription& humanDescription);

			static void BuildHumanAvatar(std::shared_ptr<Avatar> avatar, std::shared_ptr<GameObject> rootObject);

			static void Test(std::unordered_map<std::string, BodyPart>& bones, std::shared_ptr<GameObject> gameObject);

		};
	}
}