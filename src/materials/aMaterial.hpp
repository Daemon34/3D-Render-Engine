#ifndef __ISICG_ISIR_A_MATERIAL__
#define __ISICG_ISIR_A_MATERIAL__

#include "3D/intersection.hpp"
#include "3D/ray.hpp"
#include "3D/light.hpp"

namespace ISICG_ISIR
{
	// Abstract class defining a generic material
	class AMaterial
	{
		public:
			virtual Vec3f shade(const Ray &ray, const Intersection &pos, const Light &light) = 0;
			virtual float getReflectivite() = 0;
			virtual float getRefractivite() = 0;
			virtual float getIndiceRefraction() = 0;
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_A_MATERIAL__
