#pragma once

namespace Engine
{
	namespace PhysicsSystem
	{
		struct Capsule;
		struct Plane;
		struct Ray;
		struct Sphere;
		struct AABB;
		struct LineSegment;

		bool Intersect(const AABB& lhs, const AABB& rhs);
		bool Intersect(const AABB& aabb, const Sphere& sphere);
		bool Intersect(const AABB& aabb, const LineSegment& segment);

		bool Intersect(const LineSegment& segment, const Plane& plane);
		bool Intersect(const LineSegment& segment, const Sphere& sphere);

		bool Intersect(const Capsule& lhs, const Capsule& rhs);
		bool Intersect(const Capsule& capsule, const Plane& plane);
		bool Intersect(const Capsule& capsule, const Ray& ray);
		bool Intersect(const Capsule& capsule, const Sphere& sphere);

		bool Intersect(const Plane& lhs, const Plane& rhs);
		bool Intersect(const Plane& plane, const Ray& ray);
		bool Intersect(const Plane& plane, const Sphere& sphere);

		bool Intersect(const Ray& lhs, const Ray& rhs);
		bool Intersect(const Ray& ray, const Sphere& sphere);

		bool Intersect(const Sphere& lhs, const Sphere& rhs);

	}

}