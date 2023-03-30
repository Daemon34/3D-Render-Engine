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
		Triangle(const Vec3f& sommet1, const Vec3f& sommet2, const Vec3f& sommet3);

		Vec3f getSommet(const uint& indSommet) const;

		std::vector<Intersection> intersect(const Ray& ray) const override;

	private:
		Vec3f _sommet1 = VEC3F_ZERO;
		Vec3f _sommet2 = VEC3F_ZERO;
		Vec3f _sommet3 = VEC3F_ZERO;
	};
} // namespace ISICG_ISIR

#endif
