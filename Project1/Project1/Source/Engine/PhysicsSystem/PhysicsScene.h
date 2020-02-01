#pragma once


class btDynamicsWorld;

namespace Engine
{
	class Collider;

	namespace PhysicsSystem
	{
		enum class BloadPhaseType
		{
			AABBTree,
			Sweep,
		};

		// ���̃N���X�̂݊O���Ƃ̃A�N�Z�X�����邱�Ƃ��ł���
		// (GameObject�̃R���|�[�l���g��)
		class PhysicsScene
		{
		private:
			btDynamicsWorld* m_world;
			//bool m_async;						// �ʃX���b�h�ŏ������邩
		public:
			// �R���X�g���N�^
			PhysicsScene(BloadPhaseType bloadPhaseType);
			// �f�X�g���N�^
			virtual ~PhysicsScene();

			// �V�~�����[�V����
			void Simulate(float step);

			// �񓯊��ōs����
			//bool IsAsync() const { return m_async; }

		};
	}
}