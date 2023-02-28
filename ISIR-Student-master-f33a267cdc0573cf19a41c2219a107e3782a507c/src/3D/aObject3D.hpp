#ifndef __ISICG_ISIR_A_OBJECT_3D__
#define __ISICG_ISIR_A_OBJECT_3D__

#include "3D/intersection.hpp"
#include "defines.hpp"
#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	class AObject3D
	{
	public:
		
		void setMaterial(AMaterial *const material)
		{
			_material = material;
		}

		// Compute ray/object intersection 
		// return parameter t and set normal if intersection exists
		virtual std::vector<Intersection> intersect(const Ray &ray)
			= 0;

	protected:
		AMaterial *_material = nullptr; // pointer for polymorphism
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_A_OBJECT_3D__
