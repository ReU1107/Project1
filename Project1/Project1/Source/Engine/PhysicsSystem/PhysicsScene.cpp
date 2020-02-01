#include "PhysicsScene.h"
#include "../GameObject/Include.h"
#include "PhysicsMaterial.h"
#include "Physics.h"
#include "Collision.h"
#include "Sphere.h"
#include "Capsule.h"
#include "../../../Library/bullet/Include/btBulletCollisionCommon.h"
#include "../../../Library/bullet/Include/btBulletDynamicsCommon.h"

#if _DEBUG
#pragma comment(lib,"BulletCollision_vs2010_x64_debug.lib")
#pragma comment(lib,"BulletDynamics_vs2010_x64_debug.lib")
#pragma comment(lib,"BulletSoftBody_vs2010_x64_debug.lib")
#pragma comment(lib,"LinearMath_vs2010_x64_debug.lib")
#else
#pragma comment(lib,"Library/bullet/x64/Release/BulletCollision_vs2010_x64_release.lib")
#pragma comment(lib,"Library/bullet/x64/Release/BulletDynamics_vs2010_x64_release.lib")
#pragma comment(lib,"Library/bullet/x64/Release/BulletSoftBody_vs2010_x64_release.lib")
#pragma comment(lib,"Library/bullet/x64/Release/LinearMath_vs2010_x64_release.lib")
#endif

namespace Engine
{
	namespace PhysicsSystem
	{
		PhysicsScene::PhysicsScene(BloadPhaseType bloadPhaseType)
			: m_world(nullptr)
		{
			// 衝突検出方法の選択(デフォルトを選択)
			//btDefaultCollisionConfiguration* config = new btDefaultCollisionConfiguration();
			//btCollisionDispatcher* dispatcher = new btCollisionDispatcher(config);

			//btBroadphaseInterface* broadphase = nullptr;
			//switch (bloadPhaseType)
			//{
			//case Engine::PhysicsSystem::BloadPhaseType::AABBTree:
			//	broadphase = new btDbvtBroadphase();
			//	break;
			//case Engine::PhysicsSystem::BloadPhaseType::Sweep:
			//	//btBroadphaseInterface* broadphase = new btAxisSweep3();
			//	break;
			//default:
			//	break;
			//}

			//// 拘束(剛体間リンク)のソルバ設定
			//btConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

			//// Bulletのワールド作成
			//btDynamicsWorld* world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
			//world->setGravity(btVector3(Physics::Gravity.x, Physics::Gravity.y, Physics::Gravity.z));

			//m_world = world;
		}
		
		PhysicsScene::~PhysicsScene()
		{
			delete m_world->getBroadphase();
			delete m_world->getDispatcher();
			//btCollisionShape* shape = nullptr;
			//shape = new btBoxShape(btVector3());
			////btCollisionShape* shape = new btCompoundShape(1.0f);
			////btRigidBody;
			////btTriangleMeshShape;
			////btConvexHullShape;
			////shape = new btBoxShape();
			////btCapsuleShape;
			////btMotionState;
			////btSphereShape* s = new btSphereShape(2.0f);
			////btQuaternion q;
			////btVector3 p;
			////btTransform(q, p);
			//btDefaultMotionState* state = new btDefaultMotionState();
			////btMotionState;
			//btRigidBody* rigid = new btRigidBody(1.0f, state, shape);
			//
			////btRigidBody::getWorldTransform();
			////btTransform::getBasis
		}

		void PhysicsScene::Simulate(float step)
		{
			m_world->stepSimulation(step);
		}

	}
}