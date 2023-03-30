#ifndef __ISICG_ISIR_COOKTORRANCE__
#define __ISICG_ISIR_COOKTORRANCE__

#include "defines.hpp"

namespace ISICG_ISIR
{
	class CookTorrance
	{
	public:
		float Distribution_Beckmann(const Vec3f& halfVector, const Vec3f& normal, const float& alpha);
		float Geometry_CookTorrance(const Vec3f& directionVue, const Vec3f& normal, const Vec3f& directionLumiere, const Vec3f& halfVector);
		float Fresnel_Smith(const float& f0, const Vec3f& lumiereDirection, const Vec3f& halfVector);
		float BRDF(const Vec3f& directionLumiere, const Vec3f& directionVue, const float& alpha, const Vec3f& normal, const float& ior);

	private:

	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_COOKTORRANCE__
