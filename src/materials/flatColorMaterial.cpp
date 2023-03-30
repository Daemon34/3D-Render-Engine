#include "flatColorMaterial.hpp"

ISICG_ISIR::FlatColorMaterial::FlatColorMaterial(const Vec3f& color, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire,
	const float& reflectivite, const float& refractivite, const float& indiceRefraction)
	:
	_color(color),
	_parametreDiffus(parametreDiffus),
	_parametreAmbiant(parametreAmbiant),
	_parametreSpeculaire(parametreSpeculaire),
	_reflectivite(reflectivite),
	_refractivite(refractivite),
	_indiceRefraction(indiceRefraction)
{}

ISICG_ISIR::Vec3f ISICG_ISIR::FlatColorMaterial::shade(const Ray & ray, const Intersection & pos, const Light & light)
{
	Vec3f maCouleur = VEC3F_ZERO;
	for (int i = 0; i < nbRayonSphereLight; i++) {
		Vec3f directionLumiere = normalize(light.getPosition() - (ray.getPosition() + (pos._distance + 0.01f) * ray.getDirection()));
		float coefficientDiffus = _parametreDiffus * __max(dot(pos._normale, directionLumiere), 0.0f);
		Vec3f refletSphere = normalize(glm::reflect(directionLumiere, pos._normale));
		float coefficientSpeculaire = _parametreSpeculaire * pow(__max(dot(refletSphere, ray.getDirection()), 0.0f), 100.0f);
		maCouleur = light.getColor() * _color * (coefficientDiffus + _parametreAmbiant) + light.getColor() * coefficientSpeculaire;
	}
	return maCouleur / nbRayonSphereLight;
}

float ISICG_ISIR::FlatColorMaterial::getReflectivite()
{
	return _reflectivite;
}

float ISICG_ISIR::FlatColorMaterial::getRefractivite()
{
	return _refractivite;
}

float ISICG_ISIR::FlatColorMaterial::getIndiceRefraction()
{
	return _indiceRefraction;
}
