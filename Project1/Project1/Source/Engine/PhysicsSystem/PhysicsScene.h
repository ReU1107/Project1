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

		// このクラスのみ外部とのアクセスをすることができる
		// (GameObjectのコンポーネント等)
		class PhysicsScene
		{
		private:
			btDynamicsWorld* m_world;
			//bool m_async;						// 別スレッドで処理するか
		public:
			// コンストラクタ
			PhysicsScene(BloadPhaseType bloadPhaseType);
			// デストラクタ
			virtual ~PhysicsScene();

			// シミュレーション
			void Simulate(float step);

			// 非同期で行うか
			//bool IsAsync() const { return m_async; }

		};
	}
}