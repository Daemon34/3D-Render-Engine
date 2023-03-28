#ifndef __ISICG_ISIR_PLANE__
#define __ISICG_ISIR_PLANE__

#include <vector>

#include "aObject3D.hpp"

namespace ISICG_ISIR
{
	class Plane : public AObject3D
	{
	public:
		Plane() = default;
		Plane(const Vec3f& normal, const Vec3f& pointPlan)
			: _normal(normalize(normal)),
			_pointPlan(pointPlan),
			_D(normal.x * pointPlan.x + normal.y * pointPlan.y + normal.z * pointPlan.z)
		{
		}

		std::vector<Intersection> intersect(const Ray& ray) const override
		{
			Intersection monIntersection;
			std::vector<Intersection> mesIntersections = std::vector<Intersection>();
			Vec3f positionRayon = ray.getPosition();
			Vec3f directionRayon = ray.getDirection();
			Vec3f XYZ = positionRayon - _pointPlan;
			float numerateur = XYZ.x * _normal.x + XYZ.y * _normal.y + XYZ.z * _normal.z + _D;
			float denominateur = _normal.x * directionRayon.x + _normal.y * directionRayon.y + _normal.z * directionRayon.z;
			monIntersection._distance = -(numerateur / denominateur);
			monIntersection._normale = _normal;
			monIntersection._obj = this;
			mesIntersections.emplace_back(monIntersection);
			return mesIntersections;
		}

	private:
		Vec3f _normal = VEC3F_ZERO;
		Vec3f _pointPlan = VEC3F_ZERO;
		float _D = 0.0f;
	};
} // namespace ISICG_ISIR

#endif
