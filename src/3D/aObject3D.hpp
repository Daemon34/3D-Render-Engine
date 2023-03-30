#ifndef __ISICG_ISIR_A_OBJECT_3D__
#define __ISICG_ISIR_A_OBJECT_3D__

#include "3D/intersection.hpp"
#include "defines.hpp"
#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	// Abstract base class for 3D objects in the scene
	class AObject3D
	{
	public:
		
		// Set the material of the object
		void setMaterial(AMaterial *const material)
		{
			_material = material;
		}

		// Get the material of the object
		AMaterial* getMaterial() const {
			return _material;
		}

		// Compute the intersection between a ray and the object.
		// Returns a vector of Intersection objects, containing the intersection 
		// parameter t and the surface normal, if an intersection exists.
		virtual std::vector<Intersection> intersect(const Ray &ray) const
			= 0;

	protected:
		AMaterial *_material = nullptr; // pointer for polymorphism
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_A_OBJECT_3D__
