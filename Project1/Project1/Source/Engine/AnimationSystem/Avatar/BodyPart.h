#pragma once
#include <string>
#include <memory>
#include "../../InstanceID.h"
#include "../../Math/Include.h"

namespace Engine
{
	// 前方宣言
	class Object;
	namespace AnimationSystem
	{
		// アバターを構成する部品
		struct BodyPart
		{
			std::string name;		// 名前

			//Vector4 bindRotation;	// 回転
			//Vector3 bindPosition;	// 位置
			//Vector3 bindScale;		// スケール

			std::shared_ptr<Object> targetObject;
			InstanceID id;				// アニメーションするオブジェクトID

			BodyPart() noexcept;
		};

	}
}