#ifndef __ISICG_ISIR_DAMIER_MATERIAL__
#define __ISICG_ISIR_DAMIER_MATERIAL__

#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	class DamierMaterial : public AMaterial
	{
	public:
		DamierMaterial(const Vec3f& colorA, const Vec3f& colorB, const float& parametreDiffus, const float& parametreAmbiant, const float& parametreSpeculaire,
			const float& reflectivite, const float& refractivite, const float& indiceRefraction);

		Vec3f shade(const Ray& ray, const Intersection& pos, const Light& light);

		float getReflectivite();

		float getRefractivite();

		float getIndiceRefraction();

		void setX(float x);

	private:
		float posX;
		Vec3f _colorA;
		Vec3f _colorB;
		float _parametreDiffus = 0.0f;
		float _parametreAmbiant = 0.0f;
		float _parametreSpeculaire = 0.0f;
		float _reflectivite = 0.0f;
		float _refractivite = 0.0f;
		float _indiceRefraction = 0.0f;
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_DamierMaterial_MATERIAL__