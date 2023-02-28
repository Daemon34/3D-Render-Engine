#include "defines.hpp"

using namespace ISICG_ISIR;

// Fonction permettant de calculer les intersection entre un rayon et les objets
// puis qui renvoie l'intersection la plus proche.
Intersection calculIntersections(const std::vector<AObject3D*>& objects, const Ray& rayon, const Light& lumiere, float distanceMax, float distanceEpsilon, BVH& monBVH) {
	Intersection monIntersectionMeshs = monBVH.parcoursBVH(rayon);
	Intersection monIntersectionPrimitives;
	monIntersectionPrimitives._obj = nullptr;
	float distanceMin = -1.0f;
	for (uint o = 0; o < objects.size(); o++)
	{
		std::vector<Intersection> mesIntersections = objects[o]->intersect(rayon);
		for (uint i = 0; i < mesIntersections.size(); i++)
		{
			if (mesIntersections[i]._distance > distanceEpsilon && (distanceMin > mesIntersections[i]._distance || distanceMin == -1.0f) && mesIntersections[i]._distance < distanceMax)
			{
				distanceMin = mesIntersections[i]._distance;
				monIntersectionPrimitives = mesIntersections[i];
			}
		}
	}
	if (monIntersectionPrimitives._obj == nullptr && monIntersectionMeshs._obj == nullptr) {
		Intersection monIntersection;
		monIntersection._obj = nullptr;
		return monIntersection;
	}
	else if (monIntersectionMeshs._obj == nullptr) {
		return monIntersectionPrimitives;
	}
	else if (monIntersectionPrimitives._obj == nullptr) {
		return monIntersectionMeshs;
	}
	else {
		if (monIntersectionMeshs._distance < monIntersectionPrimitives._distance) {
			return monIntersectionMeshs;
		}
		else {
			return monIntersectionPrimitives;
		}
	}
}

// Fonction qui renvoie la couleur obtenue à partir d'un rayon
Vec3f couleur(const Ray& rayon, uint nbRecursive, const Light& lumiere, std::vector<AObject3D*> objects, BVH monBVH) {
	Intersection intersection = calculIntersections(objects, rayon, lumiere, 10000.0f, 0.0001f, monBVH);
	Vec3f maCouleur = Vec3f(0.36f, 0.6f, 0.96f);
	if (intersection._obj == nullptr) {
		return maCouleur;
	}
	else {
		float reflectiviteObjet = intersection._obj->getMaterial()->getReflectivite();
		float refractiviteObjet = intersection._obj->getMaterial()->getRefractivite();

		Vec3f couleurReflectivite = VEC3F_ZERO;
		Vec3f couleurRefractivite = VEC3F_ZERO;

		if (reflectiviteObjet > 0.0f && nbRecursive < MAX_RECURSIVE) {
			Ray rayonReflectivite = Ray(rayon.getPosition() + (intersection._distance) * rayon.getDirection(), normalize(glm::reflect(rayon.getDirection(), intersection._normale)));
			couleurReflectivite = couleur(rayonReflectivite, nbRecursive + 1, lumiere, objects, monBVH);
		}

		if (refractiviteObjet > 0.0f && nbRecursive < MAX_RECURSIVE) {
			bool interieur = (dot(rayon.getDirection(), intersection._normale) > 0.0f);
			float eta;
			if (interieur) {
				eta = intersection._obj->getMaterial()->getIndiceRefraction() / 1.0f;
				intersection._normale = -intersection._normale;

			}
			else {
				eta = 1.0f / intersection._obj->getMaterial()->getIndiceRefraction();
			}
			Vec3f directionRefraction = glm::refract(rayon.getDirection(), intersection._normale, eta);
			if (directionRefraction == VEC3F_ZERO) {
				directionRefraction = normalize(glm::reflect(rayon.getDirection(), intersection._normale));
				return Vec3f(1.0f);
			}
			Ray rayonRefractivite = Ray(rayon.getPosition() + (intersection._distance) * rayon.getDirection(), directionRefraction);
			couleurRefractivite = couleur(rayonRefractivite, nbRecursive + 1, lumiere, objects, monBVH);
		}
		Vec3f couleurBase = intersection._obj->getMaterial()->shade(rayon, intersection, lumiere);
		maCouleur = (1.0f - (reflectiviteObjet + refractiviteObjet)) * couleurBase + reflectiviteObjet * couleurReflectivite + refractiviteObjet * couleurRefractivite;
		Vec3f positionIntersection = rayon.getPosition() + (intersection._distance) * rayon.getDirection();
		float nbIntersectionsOmbres = 0.0f;
		for (int i = 0; i < nbRayonSphereLight; i++) {
			Ray rayonOmbre = Ray(positionIntersection, lumiere.getPosition() - positionIntersection);
			Intersection intersectionOmbre = calculIntersections(objects, rayonOmbre, lumiere, MAX_DISTANCE, DIST_EPSILON, monBVH);
			if (intersectionOmbre._obj != nullptr) {
				nbIntersectionsOmbres += 1;
			}
		}
		if (nbIntersectionsOmbres > 0.0f) {
			float coeffOmbre = nbIntersectionsOmbres / nbRayonSphereLight;
			maCouleur = (0.6f * (1.0f - coeffOmbre)) * maCouleur;
		}
	}
	return maCouleur;
}

