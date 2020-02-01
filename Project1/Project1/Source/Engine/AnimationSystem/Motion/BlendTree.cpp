#include "BlendTree.h"
#include "ChildMotion.h"

namespace Engine
{
	namespace AnimationSystem
	{

		BlendTree::BlendTree(const std::string& name) noexcept
			: base(name)
			, m_type(BlendTreeType::Direct)
			, m_isActive(true)
		{
		}

		BlendTree::~BlendTree() noexcept
		{
			m_childMotions.clear();
		}

		void BlendTree::Clear()
		{
			for (auto& child : m_childMotions)
			{
				
			}
		}

		void BlendTree::AddChild(MotionPtr motion)
		{
			ChildMotion child(motion);
			m_childMotions.push_back(child);
		}

		void BlendTree::AddChild(const ChildMotion& child)
		{
			m_childMotions.push_back(child);
		}

		void BlendTree::RemoveChild(uint32_t index)
		{
		}

		void BlendTree::Update(AvatarPtr avatar, AvatarMaskPtr mask, float localTime, float weight)
		{
			float totalWeight = 0.0f;
			for (auto& child : m_childMotions)
			{
				totalWeight += child.weight;
			}

			for (auto& child : m_childMotions)
			{
				child.motion->Update(avatar, mask, localTime, (child.weight / totalWeight) * weight);
			}

		}

	}
}
