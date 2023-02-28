#ifndef __ISICG_ISIR_FLAT_COOKTORRANCE_MATERIAL__
#define __ISICG_ISIR_FLAT_COOKTORRANCE_MATERIAL__

#include "materials/aMaterial.hpp"
#include "BRDF/CookTorrance.hpp"

namespace ISICG_ISIR
{
	class CookTorranceMaterial : public AMaterial
	{
	public:
		CookTorranceMaterial(const Vec3f& color, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire, const float& reflectivite, const float& refractivite, const float& indiceRefraction, const float& rugosite) :
			_color(color),
			_parametreDiffus(parametreDiffus),
			_parametreAmbiant(parametreAmbiant),
			_parametreSpeculaire(parametreSpeculaire),
			_reflectivite(reflectivite),
			_refractivite(refractivite),
			_indiceRefraction(indiceRefraction),
			_rugosite(rugosite)
		{}

		Vec3f shade(const Ray& ray, const Intersection& pos, const Light& light)
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

		float getReflectivite() {
			return _reflectivite;
		}

		float getRefractivite() {
			return _refractivite;
		}

		float getIndiceRefraction() {
			return _indiceRefraction;
		}

	private:
		Vec3f _color = VEC3F_ZERO;
		float _parametreDiffus = 0.0f;
		float _parametreAmbiant = 0.0f;
		float _parametreSpeculaire = 0.0f;
		float _reflectivite = 0.0f;
		float _refractivite = 0.0f;
		float _indiceRefraction = 0.0f;
		float _rugosite = 0.0f;
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_COOKTORRANCE_MATERIAL__