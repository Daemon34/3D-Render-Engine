#ifndef __ISICG_ISIR_A_MATERIAL__
#define __ISICG_ISIR_A_MATERIAL__

#include "3D/intersection.hpp"
#include "3D/ray.hpp"

namespace ISICG_ISIR
{
	class AMaterial
	{
	public:
		virtual Vec3f shade(const Ray &ray, const Intersection &pos) = 0;
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_A_MATERIAL__
