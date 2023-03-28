#ifndef __ISICG_ISIR_SPHERE__
#define __ISICG_ISIR_SPHERE__

#include <vector>

#include "aObject3D.hpp"

namespace ISICG_ISIR
{
	class Sphere : public AObject3D
	{
	public:
		Sphere() = default;
		Sphere(const Vec3f &center, const float radius)
			: _center(center), _radius(radius)
		{
		}

		std::vector<Intersection> intersect(const Ray &ray) const override
		{
			Intersection monIntersection;
			std::vector<Intersection> mesIntersections = std::vector<Intersection>();
			Vec3f oc = ray.getPosition() - _center;
			float a = dot(ray.getDirection(), ray.getDirection());
			float b = 2 * dot(oc, ray.getDirection());
			float c = dot(oc, oc) - (_radius * _radius);
			float delta = b * b - 4 * a * c;
			monIntersection._distance = -1.0f;
			// Si le rayon touche la sphere
			if (delta >= 0)
			{
				float t = (-b - sqrt(delta)) / (2 * a);
				if (t > 0)
				{
					monIntersection._normale =  normalize((ray.getPosition() + (t + 0.01f) * ray.getDirection()) - _center);
					monIntersection._distance = t;
					monIntersection._obj = this;
				}
			}
			mesIntersections.emplace_back(monIntersection);
			return mesIntersections;
		}

		Vec3f getPosition() const {
			return _center;
		}

		float getRadius() const {
			return _radius;
		}

	protected:
		Vec3f _center = VEC3F_ZERO;
		float _radius = 1.f;
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_SPHERE__
