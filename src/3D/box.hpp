#ifndef __ISICG_ISIR_BOX__
#define __ISICG_ISIR_BOX__

#include <vector>

#include "aObject3D.hpp"
#include "triangle.hpp"

namespace ISICG_ISIR
{
	class Box : public AObject3D
	{
	public:
		// Default constructor
		Box() = default;

		// Constructor with min and max corners of the box
		Box(const Vec3f& min, const Vec3f& max);

		// Computes and returns the surface area of the box
		float computeSurfaceArea();
		
		// Computes the bounding box for a list of triangles
		void computeBoundingBox(const std::vector<Triangle>& listeTriangle);

		// Enlarges the box to include a new triangle
		void enlarge(Triangle& triangleInitial, Triangle& nouveauTriangle);

		std::vector<Intersection> intersect(const Ray& ray) const override;

	private:
		Vec3f _min = Vec3f(FLT_MAX, FLT_MAX, FLT_MAX);
		Vec3f _max = Vec3f(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_BOX__