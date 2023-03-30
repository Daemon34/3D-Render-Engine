#ifndef __ISICG_ISIR_FLAT_COLOR_MATERIAL__
#define __ISICG_ISIR_FLAT_COLOR_MATERIAL__

#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	class FlatColorMaterial : public AMaterial
	{
	public:
		FlatColorMaterial(const Vec3f& color, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire,
			const float& reflectivite, const float& refractivite, const float& indiceRefraction);

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
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_FLAT_COLOR_MATERIAL__
