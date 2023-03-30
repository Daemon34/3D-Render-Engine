#include "cookTorranceMaterial.hpp"

// Constructor that initializes the material properties
ISICG_ISIR::CookTorranceMaterial::CookTorranceMaterial(const Vec3f& color, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire,
	const float& reflectivite, const float& refractivite, const float& indiceRefraction, const float& rugosite)
	:
	_color(color),
	_parametreDiffus(parametreDiffus),
	_parametreAmbiant(parametreAmbiant),
	_parametreSpeculaire(parametreSpeculaire),
	_reflectivite(reflectivite),
	_refractivite(refractivite),
	_indiceRefraction(indiceRefraction),
	_rugosite(rugosite)
{}

// Function that calculates the color of the material given a ray, intersection, and light source
ISICG_ISIR::Vec3f ISICG_ISIR::CookTorranceMaterial::shade(const Ray & ray, const Intersection & pos, const Light & light)
{
	Vec3f maCouleur = VEC3F_ZERO;
	CookTorrance cookTorrance;
	float alpha = _rugosite * _rugosite;
	for (int i = 0; i < nbRayonSphereLight; i++) {
		Vec3f directionLumiere = normalize(light.getPosition() - (ray.getPosition() + (pos._distance + 0.01f) * ray.getDirection()));
		float coefficientDiffus = _parametreDiffus * __max(dot(normalize(pos._normale), directionLumiere), 0.0f);
		float coefficientSpeculaire = cookTorrance.BRDF(-directionLumiere, ray.getDirection(), alpha, normalize(pos._normale), _indiceRefraction);
		if (coefficientDiffus + coefficientSpeculaire + _parametreAmbiant > 1.0f) {
			maCouleur += Vec3f(1.0f, 1.0f, 1.0f);
		}
		else {
			maCouleur += light.getColor() * _color * (coefficientDiffus + _parametreAmbiant) + light.getColor() * coefficientSpeculaire;
		}
	}
	return maCouleur / nbRayonSphereLight;
}

float ISICG_ISIR::CookTorranceMaterial::getReflectivite()
{
	return _reflectivite;
}

float ISICG_ISIR::CookTorranceMaterial::getRefractivite()
{
	return _refractivite;
}

float ISICG_ISIR::CookTorranceMaterial::getIndiceRefraction()
{
	return _indiceRefraction;
}
