#ifndef __ISICG_ISIR_SPHERELIGHT__
#define __ISICG_ISIR_SPHERELIGHT__

#include <vector>

#include "AObject3D.hpp"

namespace ISICG_ISIR
{
	// Class defining a sphere light using the center of the sphere, a radius and a light color
	class SphereLight : public Light
	{
	public:
		SphereLight() = default;
		SphereLight(const Vec3f& color, const Vec3f& position, const float& radius)
			: _color(color), _position(position), _radius(radius)
		{
		}

		void setPosition(const Vec3f& position) {
			_position = position;
		}

		// Renvoie la position d'un point aléatoire sur la sphère
		Vec3f getPosition() const {
			// Générateur de nombre aléatoire uniforme
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator(seed);
			std::uniform_real_distribution<double> uniform01(0.0, 1.0);

			double theta = 2 * 3.14 * uniform01(generator);
			double phi = acos(1 - 2 * uniform01(generator));
			double x = _radius * sin(phi) * cos(theta);
			double y = _radius * sin(phi) * sin(theta);
			double z = _radius * cos(phi);
			return (Vec3f(x, y, z) + _position);
		}

		void setColor(const Vec3f& color) {
			_color = color;
		}

		Vec3f getColor() const {
			return _color;
		}


	private:
		Vec3f _color = VEC3F_ZERO; // Couleur de la lumière
		Vec3f _position = VEC3F_ZERO; // Position du centre de la lumière
		float _radius = 0.0f; // Rayon de la lumière
	};
} // namespace ISICG_ISIR

#endif
