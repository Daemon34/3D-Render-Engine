#include "camera.hpp"

ISICG_ISIR::Camera::Camera(const Vec3f& position, const Vec3f& direction, const float& focale, const float& ratio)
	: _position(position), _direction(direction), _focale(focale),
	_ratio(ratio)
{
}

// Returns the direction vector of the camera.
ISICG_ISIR::Vec3f ISICG_ISIR::Camera::getDirection()
{
	return _direction;
}

// Returns the position of the camera.
ISICG_ISIR::Vec3f ISICG_ISIR::Camera::getPosition() {
	return _position;
}

ISICG_ISIR::Ray ISICG_ISIR::Camera::generateRay(Vec3f pixel_pos) {
	// Compute the camera's up vector
	_up = cross(_direction, cross(_direction, Vec3f(0.0, 1.0, 0.0)));

	// Compute the direction vector to the right of the camera
	Vec3f directionDroite = cross(_direction, _up);

	// Compute the center of the camera's image
	Vec3f centreImage = _position + (_direction * _focale);

	// Compute the position of the given pixel on the image
	Vec3f positionPixel = centreImage - (0.5f - pixel_pos.x) * directionDroite - (0.5f - pixel_pos.y) * _up * _ratio;

	// Compute the direction vector of the generated ray
	Vec3f rayDirection = normalize(positionPixel - _position);
	Ray ray = Ray(_position, rayDirection);
	return ray;
};
