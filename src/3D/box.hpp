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
		Box(const Vec3f& min, const Vec3f& max)
			: _min(min), _max(max)
		{
		}

		// Computes and returns the surface area of the box
		float computeSurfaceArea() {
			// Calculate length, width, and height of the box
			float l = abs(_max.x - _min.x);
			float L = abs(_max.y - _min.y);
			float h = abs(_max.z - _min.z);
			// Return the surface area of the box
			return (2 * l * L + 2 * l * h + 2 * L * h);
		}
		
		// Computes the bounding box for a list of triangles
		void computeBoundingBox(const std::vector<Triangle>& listeTriangle) {
			for (uint i = 0; i < listeTriangle.size(); i++) {
				for (uint indSommet = 0; indSommet < 3; indSommet++) {
					// Get the position of the vertex
					Triangle tri = listeTriangle[i];
					Vec3f positionSommet = listeTriangle[i].getSommet(indSommet);

					// Update minimum and maximum corners of the box
					if (positionSommet.x < _min.x) {
						_min.x = positionSommet.x;
					}
					if (positionSommet.y < _min.y) {
						_min.y = positionSommet.y;
					}
					if (positionSommet.z < _min.z) {
						_min.z = positionSommet.z;
					}
					if (positionSommet.x > _max.x) {
						_max.x = positionSommet.x;
					}
					if (positionSommet.y > _max.y) {
						_max.y = positionSommet.y;
					}
					if (positionSommet.z > _max.z) {
						_max.z = positionSommet.z;
					}
				}
			}
		}

		// Enlarges the box to include a new triangle
		void enlarge(Triangle& triangleInitial, Triangle& nouveauTriangle) {
			// Update the minimum and maximum corners of the box using the vertices of the initial and new triangles
			for (uint indSommet = 0; indSommet < 3; indSommet++) {
				Vec3f positionSommet = triangleInitial.getSommet(indSommet);

				if (positionSommet.x < _min.x) {
					_min.x = positionSommet.x;
				}
				if (positionSommet.y < _min.y) {
					_min.y = positionSommet.y;
				}
				if (positionSommet.z < _min.z) {
					_min.z = positionSommet.z;
				}
				if (positionSommet.x > _max.x) {
					_max.x = positionSommet.x;
				}
				if (positionSommet.y > _max.y) {
					_max.y = positionSommet.y;
				}
				if (positionSommet.z > _max.z) {
					_max.z = positionSommet.z;
				}
			}
			for (uint indSommet = 0; indSommet < 3; indSommet++) {
				Vec3f positionSommet = nouveauTriangle.getSommet(indSommet);

				if (positionSommet.x < _min.x) {
					_min.x = positionSommet.x;
				}
				if (positionSommet.y < _min.y) {
					_min.y = positionSommet.y;
				}
				if (positionSommet.z < _min.z) {
					_min.z = positionSommet.z;
				}
				if (positionSommet.x > _max.x) {
					_max.x = positionSommet.x;
				}
				if (positionSommet.y > _max.y) {
					_max.y = positionSommet.y;
				}
				if (positionSommet.z > _max.z) {
					_max.z = positionSommet.z;
				}
			}
		}

		std::vector<Intersection> intersect(const Ray& ray) const override
		{
			Intersection monIntersection;
			monIntersection._normale = VEC3F_ZERO;
			monIntersection._obj = nullptr;
			std::vector<Intersection> mesIntersections = std::vector<Intersection>();
			float tmin = (_min.x - ray.getPosition().x) / ray.getDirection().x;
			float tmax = (_max.x - ray.getPosition().x) / ray.getDirection().x;
			if (tmin > tmax) {
				std::swap(tmin, tmax);
			}
			float tymin = (_min.y - ray.getPosition().y) / ray.getDirection().y;
			float tymax = (_max.y - ray.getPosition().y) / ray.getDirection().y;
			if (tymin > tymax) {
				std::swap(tymin, tymax);
			}
			if ((tmin > tymax) || (tymin > tmax)) {
				monIntersection._distance = -1.0f;
				mesIntersections.emplace_back(monIntersection);
				return mesIntersections;
			}
			if (tymin > tmin) {
				tmin = tymin;
			}
			if (tymax < tmax) {
				tmax = tymax;
			}
			float tzmin = (_min.z - ray.getPosition().z) / ray.getDirection().z;
			float tzmax = (_max.z - ray.getPosition().z) / ray.getDirection().z;

			if (tzmin > tzmax) {
				std::swap(tzmin, tzmax);
			}
			if ((tmin > tzmax) || (tzmin > tmax)) {
				monIntersection._distance = -1.0f;
				mesIntersections.emplace_back(monIntersection);
				return mesIntersections;
			}
			if (tzmin > tmin) {
				tmin = tzmin;
			}
			if (tzmax < tmax) {
				tmax = tzmax;
			}
			monIntersection._distance = 1.0f;
			monIntersection._obj = this;
			mesIntersections.emplace_back(monIntersection);
			return mesIntersections;
		}

	private:
		Vec3f _min = Vec3f(FLT_MAX, FLT_MAX, FLT_MAX);
		Vec3f _max = Vec3f(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_BOX__