#include "metaballs.hpp"

// Constructor that initializes the Metaballs object with a list of spheres
ISICG_ISIR::Metaballs::Metaballs(const std::vector<Sphere>& listeSphere)
{
	// Adds each sphere from the input list to the internal _listeSphere vector
	for (int i = 0; i < listeSphere.size(); i++) {
		_listeSphere.push_back(listeSphere[i]);
	}
}

// Calculates the distance between a given point and a sphere with a given radius
float ISICG_ISIR::Metaballs::calculDistanceSphere(const Vec3f& point, const float& rayon) const
{
	// Calculates the distance between the point and the sphere center and subtracts the sphere radius
	float resultat = length(point) - rayon;
	return resultat;
}

// Smooth minimum function that blends two values based on a given factor k
float ISICG_ISIR::Metaballs::smin(const float& a, const float& b, const float& k) const
{
	// Calculates the difference between a and b and takes its absolute value
	float h = glm::max(k - abs(a - b), 0.0f);
	// Interpolates between a and b based on h and k
	return glm::min(a, b) - h * h * 0.25f / k;
}

// Calculates the distance between a given point and the metaballs surface
float ISICG_ISIR::Metaballs::calculDistanceMetaballs(const Vec3f& pointTouche) const
{
	// Initializes the distance as a high value
	float distance = 100.0f;
	// Iterates over all the spheres in _listeSphere
	for (uint i = 0; i < _listeSphere.size(); i++) {
		// Calculates the distance between the point and the current sphere and updates the distance value using smin
		distance = smin(distance, calculDistanceSphere(pointTouche - _listeSphere[i].getPosition(), _listeSphere[i].getRadius()), META_COEFF);
	}
	return distance;
}

// Estimates the normal vector at a given point on the metaballs surface
ISICG_ISIR::Vec3f ISICG_ISIR::Metaballs::estimationDeLaNormale(const Vec3f& pointTouche) const
{
	// Calculates the gradient using finite differences and normalizes it
	return normalize(Vec3f(
		calculDistanceMetaballs(Vec3f(pointTouche.x + 0.0001f, pointTouche.y, pointTouche.z)) - calculDistanceMetaballs(Vec3f(pointTouche.x - 0.0001f, pointTouche.y, pointTouche.z)),
		calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y + 0.0001f, pointTouche.z)) - calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y - 0.0001f, pointTouche.z)),
		calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y, pointTouche.z + 0.0001f)) - calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y, pointTouche.z - 0.0001f))
	));
}

// Computes the intersections between a given ray and the metaballs surface using Sphere Tracing
std::vector<ISICG_ISIR::Intersection> ISICG_ISIR::Metaballs::intersect(const Ray& ray) const
{
	Intersection monIntersection;
	monIntersection._distance = 0.0f;
	monIntersection._obj = nullptr;
	std::vector<Intersection> mesIntersections = std::vector<Intersection>();
	float depth = 0.0f;
	while (depth < FIN_DE_SCENE) {
		Vec3f positionRayon = (ray.getPosition() + depth * ray.getDirection());
		float dist = calculDistanceMetaballs(positionRayon);
		if (dist < 0.001f) {
			monIntersection._distance = depth;
			monIntersection._normale = estimationDeLaNormale(positionRayon);
			monIntersection._obj = this;
			mesIntersections.emplace_back(monIntersection);
			return mesIntersections;
		}
		depth += dist;
	}

	mesIntersections.emplace_back(monIntersection);
	return mesIntersections;
}
