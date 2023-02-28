#ifndef __ISICG_ISIR_TRIANGLE__
#define __ISICG_ISIR_TRIANGLE__

#include <vector>
#include <iostream>
#include "aObject3D.hpp"

namespace ISICG_ISIR
{
	class Triangle : public AObject3D
	{
	public:
		Triangle() = default;
		Triangle(const Vec3f& sommet1, const Vec3f& sommet2, const Vec3f& sommet3)
			: _sommet1(sommet1),
			_sommet2(sommet2),
			_sommet3(sommet3)
		{
		}



		Vec3f getSommet(const uint& indSommet) const {
			if (indSommet == 0) {
				return _sommet1;
			}
			else if (indSommet == 1) {
				return _sommet2;
			}
			else if (indSommet == 2) {
				return _sommet3;
			}
			else {
				std::cout << "Indice du sommet invalide ! Renvoie d'une valeur nulle.";
				return VEC3F_ZERO;
			}
		}

		std::vector<Intersection> intersect(const Ray& ray) override
		{
			Intersection monIntersection;
			std::vector<Intersection> mesIntersections = std::vector<Intersection>();
			Vec3f sommet2sommet1 = _sommet2 - _sommet1;
			Vec3f sommet3sommet1 = _sommet3 - _sommet1;
			Vec3f rayonSommet1 = ray.getPosition() - _sommet1;
			Vec3f  n = cross(sommet2sommet1, sommet3sommet1);
			Vec3f q = cross(rayonSommet1, ray.getDirection());
			float d = 1.0 / dot(ray.getDirection() , n);
			float u = d * dot(-q, sommet3sommet1);
			float v = d * dot(q, sommet2sommet1);
			float t = d * dot(-n, rayonSommet1);
			if ((u < 0.0 || u>1.0 || v < 0.0 || (u + v)>1.0) && t > 0.0f) {
				monIntersection._distance = -1.0f;
			}
			else{
				monIntersection._distance = t;
				monIntersection._obj = this;
				monIntersection._normale = n;
			}
			mesIntersections.emplace_back(monIntersection);
			return mesIntersections;
		}

	private:
		Vec3f _sommet1 = VEC3F_ZERO;
		Vec3f _sommet2 = VEC3F_ZERO;
		Vec3f _sommet3 = VEC3F_ZERO;
	};
} // namespace ISICG_ISIR

#endif
