#include "BlendShape.h"
#include "BlendShapeDeltaValue.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		BlendShape::BlendShape(const std::string& name)
			: base(name)
			, m_weight(0.0f)
			, m_weightIsDirty(false)
		{
		}

		BlendShape::~BlendShape()
		{
			m_deltaPositions.clear();
			m_deltaNormals.clear();
			m_deltaTangents.clear();
		}

		void* BlendShape::GetPropertyAddress(const std::string& name)
		{
			if (name == "weight")
			{
				m_weightIsDirty = true;
				return &m_weight;
			}

			return nullptr;
		}

		void BlendShape::SetWeight(float weight)
		{
			// 0�`100
			weight = MathF::Clamp(weight, 100.0f, 0.0f);
			m_weight = weight;
			m_weightIsDirty = true;
		}

		BlendShape::DeltaPositions& BlendShape::GetDeltaPositions()
		{
			return m_deltaPositions;
		}

		BlendShape::DeltaNormals& BlendShape::GetDeltaNormals()
		{
			return m_deltaNormals;
		}

		BlendShape::DeltaTangents& BlendShape::GetDeltaTangetns()
		{
			return m_deltaTangents;
		}

		float BlendShape::GetWeight() const
		{
			if (m_weightIsDirty)
			{
				m_weight /= 100.0f;
				m_weightIsDirty = false;
			}
			return m_weight;
		}

		bool BlendShape::IsCalculated() const
		{
			// �E�F�C�g�l������Ȃ�0�ɋ߂��Ȃ�v�Z���Ȃ�
			if (m_weight < MathF::Epsilon)
			{
				return false;
			}
			// �O�t���[���ƃE�F�C�g�l���ς��Ȃ��Ȃ�v�Z���Ȃ�
			if (!m_weightIsDirty) 
			{
				return false;
			}
			return true;
		}

	}
}