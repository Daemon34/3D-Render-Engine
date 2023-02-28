#ifndef __ISICG_ISIR_RAY__
#define __ISICG_ISIR_RAY__

#include "defines.hpp"

namespace ISICG_ISIR
{
	class Ray
	{
	public:
		Ray(const Vec3f &position, const Vec3f &direction)
			: _position(position), _direction(direction)
		{
		}

		Vec3f getPosition() const 
		{
			return _position;
		}

		void setPosition(const Vec3f& position) {
			_position = position;
		}

		Vec3f getDirection() const
		{
			return _direction;
		}

		void setDirection(const Vec3f& direction) {
			_direction = direction;
		}




	private:
		Vec3f _position;
		Vec3f _direction;
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_RAY__
