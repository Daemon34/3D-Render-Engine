#ifndef __ISICG_ISIR_FLAT_COOKTORRANCE_MATERIAL__
#define __ISICG_ISIR_FLAT_COOKTORRANCE_MATERIAL__

#include "materials/aMaterial.hpp"
#include "BRDF/CookTorrance.hpp"

namespace ISICG_ISIR
{
	class CookTorranceMaterial : public AMaterial
	{
	public:
		// Constructor that initializes the material properties
		CookTorranceMaterial(const Vec3f& color, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire,
			const float& reflectivite, const float& refractivite, const float& indiceRefraction, const float& rugosite);

		// Function that calculates the color of the material given a ray, intersection, and light source
		Vec3f shade(const Ray& ray, const Intersection& pos, const Light& light);

		float getReflectivite();

		float getRefractivite();

		float getIndiceRefraction();

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