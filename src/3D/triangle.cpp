#include "triangle.hpp"

// Create a new triangle using 3 vertex position
ISICG_ISIR::Triangle::Triangle(const Vec3f& sommet1, const Vec3f& sommet2, const Vec3f& sommet3)

	: _sommet1(sommet1),
	_sommet2(sommet2),
	_sommet3(sommet3)
{
}

// Get the triangle vertex using an index
ISICG_ISIR::Vec3f ISICG_ISIR::Triangle::getSommet(const uint& indSommet) const
{
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
		std::cout << "Invalid vertex index ! Will return null value.";
		return VEC3F_ZERO;
	}
}

// Computes the intersections between a given ray and the triangle
std::vector<ISICG_ISIR::Intersection> ISICG_ISIR::Triangle::intersect(const Ray& ray) const
{
	Intersection monIntersection;
	std::vector<Intersection> mesIntersections = std::vector<Intersection>();
	Vec3f sommet2sommet1 = _sommet2 - _sommet1;
	Vec3f sommet3sommet1 = _sommet3 - _sommet1;
	Vec3f rayonSommet1 = ray.getPosition() - _sommet1;
	Vec3f  n = cross(sommet2sommet1, sommet3sommet1);
	Vec3f q = cross(rayonSommet1, ray.getDirection());
	float d = 1.0 / dot(ray.getDirection(), n);
	float u = d * dot(-q, sommet3sommet1);
	float v = d * dot(q, sommet2sommet1);
	float t = d * dot(-n, rayonSommet1);
	if ((u < 0.0 || u>1.0 || v < 0.0 || (u + v)>1.0) && t > 0.0f) {
		monIntersection._distance = -1.0f;
	}
	else {
		monIntersection._distance = t;
		monIntersection._obj = this;
		monIntersection._normale = n;
	}
	mesIntersections.emplace_back(monIntersection);
	return mesIntersections;
}