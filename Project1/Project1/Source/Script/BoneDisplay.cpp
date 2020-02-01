#include "BoneDisplay.h"
#include "../Engine/Include.h"


using namespace Engine;

BoneDisplay::BoneDisplay()
{
}

BoneDisplay::~BoneDisplay()
{
}

void BoneDisplay::OnStart()
{
	AddComponent<LineRenderer>();
}

void BoneDisplay::OnUpdate(float deltaTime)
{
	auto renderer = GetComponent<SkinnedMeshRenderer>();
	if (renderer)
	{
		auto lineRenderer = GetComponent<LineRenderer>();
		lineRenderer->Clear();

		//lineRenderer->AddLine3D(Vector3(0, -2, 0), Vector3(100, 2, 0), Color4::Red, Color4::Blue, 2.0f);

		auto bones = renderer->GetSkinBones();

		auto transform = GetTransform();
		for (auto& bone : bones)
		{
			auto parent = bone->GetParent()->GetComponent<Bone>();
			if (!parent)
				continue;
			auto worldPosition = bone->GetWorldPosition();
			auto parentPosition = parent->GetWorldPosition();

			auto startPosition = worldPosition;
			auto endPosition = parentPosition;

			lineRenderer->AddLine3D(startPosition, endPosition, Color4::Red, Color4::Blue, 0.5f);
			//lineRenderer->AddLine3D(endPosition, startPosition, Color4::Red, Color4::Blue, 0.5f);
		}

	}
}
