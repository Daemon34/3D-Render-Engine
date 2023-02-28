#ifndef __ISICG_ISIR_INTERSECTION__
#define __ISICG_ISIR_INTERSECTION__

#include "defines.hpp"

namespace ISICG_ISIR
{
	class AObject3D;

	struct Intersection
	{
		Intersection() = default;

		Vec3f _normale = VEC3F_ZERO;
		float _distance = -1.f;
		AObject3D *_obj = nullptr;
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_INTERSECTION__
