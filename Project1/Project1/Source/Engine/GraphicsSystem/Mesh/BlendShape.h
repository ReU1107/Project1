#pragma once
#include "../../Object.h"
#include <vector>

namespace Engine
{
	namespace GraphicsSystem
	{

		// �O���錾
		struct BlendShapeDeltaPosition;
		struct BlendShapeDeltaNormal;
		struct BlendShapeDeltaTangent;

		class BlendShape final : public Object
		{
		private:
			using base = Object;
			using DeltaPositions = std::vector<BlendShapeDeltaPosition>;
			using DeltaNormals = std::vector<BlendShapeDeltaNormal>;
			using DeltaTangents = std::vector<BlendShapeDeltaTangent>;

		private:
			DeltaPositions m_deltaPositions;// ����
			DeltaNormals m_deltaNormals;	// ����
			DeltaTangents m_deltaTangents;	// ����
			mutable float m_weight;			// �e���x(0�`100)
			mutable bool m_weightIsDirty;	// �E�F�C�g�l���ύX������

		public:
			// �R���X�g���N�^
			BlendShape(const std::string& name);
			// �f�X�g���N�^
			virtual ~BlendShape();
		public:
			// �C���X�^���XID
			static const InstanceID ID() { return InstanceID::BlendShape; }
			// �C���X�^���XID�擾
			virtual InstanceID GetInstanceID() const override { return InstanceID::BlendShape; }

			virtual void* GetPropertyAddress(const std::string& name) override;

		public:

			// �E�F�C�g�ݒ�
			void SetWeight(float weight);
		public:
			// �ʒu�����擾
			DeltaPositions& GetDeltaPositions();
			// �@�������擾
			DeltaNormals& GetDeltaNormals();
			// �ڐ������擾
			DeltaTangents& GetDeltaTangetns();
			// �E�F�C�g�擾
			float GetWeight() const;
			// �v�Z���邩
			bool IsCalculated() const;

		};
	}
}

using BlendShapePtr = std::shared_ptr<Engine::GraphicsSystem::BlendShape>;