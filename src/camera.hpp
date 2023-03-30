#ifndef __ISICG_ISIR_CAMERA__
#define __ISICG_ISIR_CAMERA__

#include "3D/ray.hpp"

namespace ISICG_ISIR
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const Vec3f& position, const Vec3f& direction, const float& focale, const float& ratio);

		Vec3f getDirection();

		Vec3f getPosition();

		Ray generateRay(Vec3f pixel_pos);

	private:
		Vec3f _position = VEC3F_ZERO;
		Vec3f _direction = Vec3f(0.0f, 0.0f, 1.0f);
		Vec3f _up = Vec3f(0.0f, 1.0f, 0.0f);
		float _focale = 0.0f;
		float _ratio = 0.0f;
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_CAMERA__
