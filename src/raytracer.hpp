#include "defines.hpp"

using namespace ISICG_ISIR;

// Compute all intersections between a ray and all objects in the scene and return the closest one
Intersection calculIntersections(const std::vector<AObject3D*>& objects, const Ray& rayon, const BVH& monBVH) {
	Intersection monIntersectionMeshs = monBVH.parcoursBVH(rayon);
	Intersection monIntersectionPrimitives;
	monIntersectionPrimitives._obj = nullptr;
	float distanceMin = MAX_DISTANCE;
	for (auto& object : objects)
	{
		std::vector<Intersection> intersections = object->intersect(rayon);
		for (auto& intersection : intersections)
		{
			if (intersection._distance > DIST_EPSILON && distanceMin > intersection._distance && intersection._distance < MAX_DISTANCE)
			{
				distanceMin = intersection._distance;
				monIntersectionPrimitives = intersection;
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

// Return the pixel color depending on what the ray will hit
Vec3f couleur(const Ray& rayon, uint nbRecursive, const Light& lumiere, const std::vector<AObject3D*>& objects, const BVH& monBVH) {
	Intersection intersection = calculIntersections(objects, rayon, monBVH);
	Vec3f maCouleur = Vec3f(0.36f, 0.6f, 0.96f);
	if (intersection._obj == nullptr) {
		return maCouleur;
	}
	else {
		Vec3f positionIntersection = rayon.getPosition() + (intersection._distance) * rayon.getDirection();

		float reflectiviteObjet = intersection._obj->getMaterial()->getReflectivite();
		float refractiviteObjet = intersection._obj->getMaterial()->getRefractivite();

		Vec3f couleurReflectivite = VEC3F_ZERO;
		Vec3f couleurRefractivite = VEC3F_ZERO;

		if (reflectiviteObjet > 0.0f && nbRecursive < MAX_RECURSIVE) {
			Ray rayonReflectivite = Ray(positionIntersection, normalize(glm::reflect(rayon.getDirection(), intersection._normale)));
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
			Ray rayonRefractivite = Ray(positionIntersection, directionRefraction);
			couleurRefractivite = couleur(rayonRefractivite, nbRecursive + 1, lumiere, objects, monBVH);
		}
		Vec3f couleurBase = intersection._obj->getMaterial()->shade(rayon, intersection, lumiere);
		maCouleur = (1.0f - (reflectiviteObjet + refractiviteObjet)) * couleurBase + reflectiviteObjet * couleurReflectivite + refractiviteObjet * couleurRefractivite;
		
		int nbIntersectionsOmbres = 0;
		for (int i = 0; i < nbRayonSphereLight; i++) {
			Ray rayonOmbre = Ray(positionIntersection, lumiere.getPosition() - positionIntersection);
			Intersection intersectionOmbre = calculIntersections(objects, rayonOmbre, monBVH);
			if (intersectionOmbre._obj != nullptr) {
				nbIntersectionsOmbres += 1;
			}
		}
		if (nbIntersectionsOmbres > 0) {
			float coeffOmbre = static_cast<float>(nbIntersectionsOmbres) / nbRayonSphereLight;
			maCouleur = (0.6f * (1.0f - coeffOmbre)) * maCouleur;
		}
	}
	return maCouleur;
}

