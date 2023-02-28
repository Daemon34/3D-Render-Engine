#ifndef __ISICG_ISIR_CAMERA__
#define __ISICG_ISIR_CAMERA__

#include "3D/ray.hpp"

namespace ISICG_ISIR
{
	class Camera
	{
	public:
		Camera();
		Camera(const Vec3f &position, const Vec3f &direction, const float &focale, const float &ratio)
			: _position(position), _direction(direction), _focale(focale),
			  _ratio(ratio)
		{
		}

		Vec3f getDirection() {
			return _direction;
		}

		Vec3f getPosition() {
			return _position;
		}

		Ray generateRay(Vec3f pixel_pos){
			_up = cross(_direction, cross(_direction, Vec3f(0.0, 1.0, 0.0)));
			Vec3f directionDroite = cross(_direction, _up);
			Vec3f centreImage = _position + (_direction * _focale);
			Vec3f positionPixel = centreImage - (0.5f - pixel_pos.x) * directionDroite - (0.5f - pixel_pos.y) * _up * _ratio;
			Vec3f directionRayon = normalize(positionPixel - _position);
			Ray rayon = Ray(_position, directionRayon);
			return rayon;
		};

	private:
		Vec3f _position = VEC3F_ZERO;
		Vec3f _direction = Vec3f(0.0f, 0.0f, 1.0f);
		Vec3f _up = Vec3f(0.0f, 1.0f, 0.0f);
		float _focale = 0.0f;
		float _ratio = 0.0f;
	};
} // namespace ISICG_ISIR

#endif //__ISICG_ISIR_CAMERA__
