#ifndef __ISICG_ISIR_METABALLS__
#define __ISICG_ISIR_METABALLS__

#include <vector>

#include "Sphere.hpp"

namespace ISICG_ISIR
{
	class Metaballs : public AObject3D
	{
	public:
		Metaballs() = default;
		Metaballs(const std::vector<Sphere>& listeSphere)
		{
			for (int i = 0; i < listeSphere.size(); i++) {
				_listeSphere.push_back(listeSphere[i]);
			}
		}

		// Fonction de distance signée pour une Sphere
		float calculDistanceSphere(const Vec3f& point, const float& rayon) const {
			float resultat = length(point) - rayon;
			return resultat;
		}

		// Permet le calcul des metaballs
		float smin(const float& a, const float& b, const float& k) const {
			float h = glm::max(k - abs(a - b), 0.0f);
			return glm::min(a, b) - h * h * 0.25f / k;
		}

		// Calcul du champ potentielle pour chaque sphère de la metaball
		float calculDistanceMetaballs(const Vec3f& pointTouche) const {
			float distance = 100.0f;
			for (uint i = 0; i < _listeSphere.size(); i++) {
				distance = smin(distance, calculDistanceSphere(pointTouche - _listeSphere[i].getPosition(), _listeSphere[i].getRadius()), META_COEFF);
			}
			return distance;
		}

		// Estimation de la normal en utilisant la méthode du gradient
		Vec3f estimationDeLaNormale(const Vec3f& pointTouche) const {
			return normalize(Vec3f(
				calculDistanceMetaballs(Vec3f(pointTouche.x + 0.0001f, pointTouche.y, pointTouche.z)) - calculDistanceMetaballs(Vec3f(pointTouche.x - 0.0001f, pointTouche.y, pointTouche.z)),
				calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y + 0.0001f, pointTouche.z)) - calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y - 0.0001f, pointTouche.z)),
				calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y, pointTouche.z + 0.0001f)) - calculDistanceMetaballs(Vec3f(pointTouche.x, pointTouche.y, pointTouche.z - 0.0001f))
			));
		}

		// Sphere Tracing
		std::vector<Intersection> intersect(const Ray& ray) const override
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

	protected:
		std::vector<Sphere> _listeSphere = std::vector<Sphere>();
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_METABALLS__
