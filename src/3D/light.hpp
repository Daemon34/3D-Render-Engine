/* Classe abstraite définissant une lumière de manière générale */

#ifndef __ISICG_ISIR_LIGHT__
#define __ISICG_ISIR_LIGHT__

#include <vector>
#include "aObject3D.hpp"

namespace ISICG_ISIR
{	
	class Light
	{
	public:
		virtual void setPosition(const Vec3f& position) = 0;
		virtual Vec3f getPosition() const = 0;
		virtual void setColor(const Vec3f& color) = 0;
		virtual Vec3f getColor() const = 0;
	};
} // namespace ISICG_ISIR

#endif