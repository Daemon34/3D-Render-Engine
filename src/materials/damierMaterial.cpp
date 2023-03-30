#include "damierMaterial.hpp"

ISICG_ISIR::DamierMaterial::DamierMaterial(const Vec3f& colorA, const Vec3f& colorB, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire, 
	const float& reflectivite, const float& refractivite, const float& indiceRefraction)
	:
	_colorA(colorA),
	_colorB(colorB),
	_parametreDiffus(parametreDiffus),
	_parametreAmbiant(parametreAmbiant),
	_parametreSpeculaire(parametreSpeculaire),
	_reflectivite(reflectivite),
	_refractivite(refractivite),
	_indiceRefraction(indiceRefraction)
{}

ISICG_ISIR::Vec3f ISICG_ISIR::DamierMaterial::shade(const Ray & ray, const Intersection & pos, const Light & light)
{
	Vec3f couleurDamier;
	Vec3f pointTouche = ray.getPosition() + (pos._distance) * ray.getDirection();
	if (abs(sin(pointTouche.z / 10)) >= 0.75f) {
		if (sin(pointTouche.x / 10) > 0.0f) {
			couleurDamier = _colorA;
		}
		else {
			couleurDamier = _colorB;
		}
	}
	else {
		if (sin(pointTouche.x / 10) > 0.0f) {
			couleurDamier = _colorB;
		}
		else {
			couleurDamier = _colorA;
		}
	}
	Vec3f maCouleur = VEC3F_ZERO;
	Vec3f directionLumiere = normalize(light.getPosition() - (ray.getPosition() + (pos._distance + 0.01f) * ray.getDirection()));
	float coefficientDiffus = _parametreDiffus * __max(dot(pos._normale, directionLumiere), 0.0f);
	Vec3f refletSphere = normalize(glm::reflect(directionLumiere, pos._normale));
	float coefficientSpeculaire = _parametreSpeculaire * pow(__max(dot(refletSphere, -ray.getDirection()), 0.0f), 100.0f);
	maCouleur = light.getColor() * couleurDamier * (coefficientDiffus + _parametreAmbiant) + light.getColor() * coefficientSpeculaire;
	return maCouleur;
}

float ISICG_ISIR::DamierMaterial::getReflectivite()
{
	return _reflectivite;
}

float ISICG_ISIR::DamierMaterial::getRefractivite()
{
	return _refractivite;
}

float ISICG_ISIR::DamierMaterial::getIndiceRefraction()
{
	return _indiceRefraction;
}

void ISICG_ISIR::DamierMaterial::setX(float x)
{
	posX = x;
}