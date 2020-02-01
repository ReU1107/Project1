#include "RigidBody.h"
#include "Collider/Collider.h"
#include "Collider/BoxCollider.h"
#include "Collider/SphereCollider.h"
#include "Collider/CapsuleCollider.h"
#include "Transform.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

using namespace DirectX;

namespace Engine
{

	std::vector<RigidBody::RigidBodyPtr> RigidBody::allRigidBodies;

	RigidBody::RigidBody() noexcept
		: base("RigidBody")
		, m_bt(nullptr)
		, m_rotation(Vector4::Identity)
		, m_position(Vector3::Zero)
		, m_linerVelocity(Vector3::Zero)
		, m_angularVelocity(Vector3::Zero)
		, m_mass(0.0f)
		, m_drag(0.0f)
		, m_useGravity(true)
		, m_isKinematic(true)
	{
	}

	RigidBody::~RigidBody() noexcept
	{
		//delete m_bt->getCollisionShape();
		delete m_bt;
	}

	void RigidBody::SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void RigidBody::SetRotation(const Vector4& rotation)
	{
		m_rotation = rotation;
	}

	void RigidBody::SetRotation(const Vector3& euler)
	{
		XMStoreFloat4(&m_rotation, XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&euler)));
	}

	void RigidBody::SetLinerVelocity(const Vector3& velocity)
	{
		m_linerVelocity = velocity;
	}

	void RigidBody::SetAngularVelocity(const Vector3& velocity)
	{
		m_angularVelocity = velocity;
	}

	void RigidBody::SetMass(float mass)
	{
		m_mass = mass;
	}

	void RigidBody::SetDrag(float drag)
	{
		m_drag = drag;
	}

	void RigidBody::Apply()
	{
		if (m_bt)
			assert(!"二回呼ばれています");

		//btCollisionShape* shape = nullptr;
		//auto collider = GetComponent<Collider>();
		//switch (collider->GetShape())
		//{
		//case Engine::ColliderShape::Box:
		//{
		//	btVector3 vec;
		//	auto extens = std::dynamic_pointer_cast<BoxCollider>(collider)->GetHalfExtents();
		//	vec.setX(extens.x);
		//	vec.setY(extens.y);
		//	vec.setZ(extens.z);
		//	shape = new btBoxShape(vec);
		//}	break;
		//case Engine::ColliderShape::Capsule:
		//{
		//	auto capsule = std::dynamic_pointer_cast<CapsuleCollider>(collider);
		//	float radius = capsule->GetLocalRadius();
		//	float height = capsule->GetLocalHeight();
		//	shape = new btCapsuleShape(radius, height);
		//}	break;
		//case Engine::ColliderShape::Sphere:
		//{
		//	float radius = std::dynamic_pointer_cast<SphereCollider>(collider)->GetLocalRadius();
		//	shape = new btSphereShape(radius);
		//}	break;
		//case Engine::ColliderShape::Mesh:
		//	assert(!"");
		//	break;
		//case Engine::ColliderShape::Terrain:
		//	assert(!"");
		//	break;
		//default:
		//	break;
		//}

		auto transform = GetTransform();
		auto pos = transform->GetWorldPosition();
		auto rot = transform->GetWorldRotation();

		//btVector3 v;
		//v.setX(pos.x);
		//v.setY(pos.y);
		//v.setZ(pos.z);

		//btQuaternion q;
		//q.setX(rot.x);
		//q.setY(rot.y);
		//q.setZ(rot.z);
		//q.setW(rot.w);

		//btMotionState* state = new btDefaultMotionState(btTransform(q, v));
		//btRigidBodyDoubleData dl;
		//m_bt = new btRigidBody(m_mass, state, shape);
	}

	void RigidBody::AddForce(const Vector3& force, ForceMode mode)
	{

		switch (mode)
		{
		case Engine::ForceMode::Force:
			// 速度＝初速度＋(加速度×時間)force
			m_linerVelocity = m_linerVelocity + force;		// 速度
			m_position += m_linerVelocity;	// 
			break;
		case Engine::ForceMode::Acceleration:
			break;
		case Engine::ForceMode::VelocityChange:
			break;
		case Engine::ForceMode::Impulse:
			break;
		default:
			break;
		}

	}

	void RigidBody::AddForce(float forceX, float forceY, float forceZ, ForceMode mode)
	{
	}

	const Vector3& RigidBody::GetLinerVelocity() const
	{
		return m_linerVelocity;
	}

	const Vector3& RigidBody::GetAngularVelocity() const
	{
		return m_angularVelocity;
	}

}