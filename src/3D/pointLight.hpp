#ifndef __ISICG_ISIR_POINTLIGHT__
#define __ISICG_ISIR_POINTLIGHT__

#include <vector>
#include "light.hpp"

namespace ISICG_ISIR
{
	class PointLight : public Light
	{
	public:
		PointLight() = default;
		PointLight(const Vec3f& color, const Vec3f& position)
			: _color(color), _position(position)
		{
		}

		void setPosition(const Vec3f& position) {
			_position = position;
		}

		Vec3f getPosition() const {
			return _position;
		}

		void setColor(const Vec3f& color) {
			_color = color;
		}

		Vec3f getColor() const {
			return _color;
		}


	private:
		Vec3f _color = VEC3F_ZERO;
		Vec3f _position = VEC3F_ZERO;
	};
} // namespace ISICG_ISIR

#endif
