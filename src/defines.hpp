#ifndef ____ISICG_ISIR_DEFINES__
#define ____ISICG_ISIR_DEFINES__

#include "glm/glm.hpp"

namespace ISICG_ISIR
{
	using uint = unsigned int;
	using uchar = unsigned char;

	// glm::vec attributes can be accessed with .x/y/z/w or .r/g/b/a
	// Use the second method for colours :-)
	using Vec3f = glm::vec3;
	using Vec4f = glm::vec4;
	using Vec3u = glm::uvec3;

	const Vec3f VEC3F_ZERO = Vec3f(0.f, 0.f, 0.f);
	const int MAX_RECURSIVE = 10; // Nombre d'appels recursifs Reflexion et Refraction
	const float DIST_EPSILON = 0.0001f; // Decalage imprécision numériques
	const float MAX_DISTANCE = 10000.0f; // Distance maximum d'affichage
	const float nbRayonSphereLight = 32.0f; // Nombre de rayons pour les lumières sphériques
	const float ANTIALLIASING = 32.0f; // Nombre de supersampling pour l'anti-aliassage
	const float FIN_DE_SCENE = 100.0f; // Arrêt du parcours du rayon pour le Sphere Tracing (metaballs)
	const float META_COEFF = 8.0f; // Coefficient pour les metaballs

	const int progressBarWidth = 70;
	 
} // namespace ISICG_ISIR

#endif // ____ISICG_ISIR_DEFINES__
