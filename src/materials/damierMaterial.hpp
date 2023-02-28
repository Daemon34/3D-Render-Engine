#ifndef __ISICG_ISIR_DAMIER_MATERIAL__
#define __ISICG_ISIR_DAMIER_MATERIAL__

#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	class DamierMaterial : public AMaterial
	{
	public:
		DamierMaterial(const Vec3f& color, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire, const float& reflectivite, const float& refractivite, const float& indiceRefraction) :
			_color(color),
			_parametreDiffus(parametreDiffus),
			_parametreAmbiant(parametreAmbiant),
			_parametreSpeculaire(parametreSpeculaire),
			_reflectivite(reflectivite),
			_refractivite(refractivite),
			_indiceRefraction(indiceRefraction)
		{}

		Vec3f shade(const Ray &ray, const Intersection &pos, const Light &light)
		{
			Vec3f couleurDamier;
			Vec3f pointTouche = ray.getPosition() + (pos._distance) * ray.getDirection();
			if (abs(sin(pointTouche.z / 10)) >= 0.75f) {
				if (sin(pointTouche.x / 10) > 0.0f) {
					couleurDamier = _color;
				}
				else {
					couleurDamier = Vec3f(1.0f - _color.x, 1.0f - _color.y, 1.0f - _color.z);
				}
			}
			else {
				if (sin(pointTouche.x / 10) > 0.0f) {
					couleurDamier = Vec3f(1.0f - _color.x, 1.0f - _color.y, 1.0f - _color.z);
				}
				else {
					couleurDamier = _color;
				}
			}
			Vec3f maCouleur = VEC3F_ZERO;
			//for (int i = 0; i < nbRayonSphereLight; i++) {
				Vec3f directionLumiere = normalize(light.getPosition() - (ray.getPosition() + (pos._distance + 0.01f) * ray.getDirection()));
				float coefficientDiffus = _parametreDiffus * __max(dot(pos._normale, directionLumiere), 0.0f);
				Vec3f refletSphere = normalize(glm::reflect(directionLumiere, pos._normale));
				float coefficientSpeculaire = _parametreSpeculaire * pow(__max(dot(refletSphere, -ray.getDirection()), 0.0f), 100.0f);
				maCouleur = light.getColor() * couleurDamier * (coefficientDiffus + _parametreAmbiant) + light.getColor() * coefficientSpeculaire;
			//}
				return maCouleur;
		}

		float getReflectivite() {
			return _reflectivite;
		}

		float getRefractivite() {
			return _refractivite;
		}

		float getIndiceRefraction() {
			return _indiceRefraction;
		}

		void setX(float x) {
			posX = x;
		}

	private:
		float posX;
		Vec3f _color;
		float _parametreDiffus = 0.0f;
		float _parametreAmbiant = 0.0f;
		float _parametreSpeculaire = 0.0f;
		float _reflectivite = 0.0f;
		float _refractivite = 0.0f;
		float _indiceRefraction = 0.0f;
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_DamierMaterial_MATERIAL__