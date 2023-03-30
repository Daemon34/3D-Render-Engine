#ifndef __ISICG_ISIR_METABALLS__
#define __ISICG_ISIR_METABALLS__

#include <vector>

#include "Sphere.hpp"

namespace ISICG_ISIR
{
	class Metaballs : public AObject3D
	{
	public:
		// Default constructor
		Metaballs() = default;
		// Constructor that initializes the Metaballs object with a list of spheres
		Metaballs(const std::vector<Sphere>& listeSphere);

		// Calculates the distance between a given point and a sphere with a given radius
		float calculDistanceSphere(const Vec3f& point, const float& rayon) const;

		// Smooth minimum function that blends two values based on a given factor k
		float smin(const float& a, const float& b, const float& k) const;

		// Calculates the distance between a given point and the metaballs surface
		float calculDistanceMetaballs(const Vec3f& pointTouche) const;

		// Estimates the normal vector at a given point on the metaballs surface
		Vec3f estimationDeLaNormale(const Vec3f& pointTouche) const;

		// Computes the intersections between a given ray and the metaballs surface using Sphere Tracing
		std::vector<Intersection> intersect(const Ray& ray) const override;

	protected:
		std::vector<Sphere> _listeSphere = std::vector<Sphere>();
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_METABALLS__
