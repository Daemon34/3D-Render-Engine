#include "CookTorrance.hpp"
#include "iostream"

namespace ISICG_ISIR
{
	// Fonction de distribution
	float CookTorrance::Distribution_Beckmann(const Vec3f& halfVector, const Vec3f& normal, const float& alpha) {
		float nDoth = std::min(0.0f, dot(normal, halfVector));
		if (nDoth == 0.0f) {
			return 0.0f;
		}
		else {
			float nDothCarre = nDoth * nDoth;
			float alphaCarre = alpha * alpha;
			float facteurExp = (nDothCarre - 1.0f) / (alphaCarre * nDothCarre);
			float denominateur = 3.14f * alphaCarre * (nDothCarre * nDothCarre);
			return (exp(facteurExp) / denominateur);
		}
	}

	// Fonction de géométrie de Schlick_Beckmann
	float Geometry_Schlick_Beckmann(const Vec3f& direction, const Vec3f& halfVector, const float& alpha) {
		float k = alpha * sqrt(2.0f / 3.14f);
		float dDoth = dot(halfVector, direction);
		float denominateur = (dDoth * (1 - k)) + k;
		return (dDoth / denominateur);
	}

	// Fonction de géométrie de CookTorrance
	float CookTorrance::Geometry_CookTorrance(const Vec3f& directionVue, const Vec3f& normal, const Vec3f& directionLumiere, const Vec3f& halfVector) {
		float hdotN = dot(halfVector, normal);
		float vdotN = dot(directionVue, normal);
		float vdotH = dot(directionVue, halfVector);
		float ldotN = dot(directionLumiere, normal);
		float term1 = (2 * hdotN * vdotN) / vdotH;
		float term2 = (2 * hdotN * ldotN) / vdotH;
		return glm::min(1.0f, glm::min(term1, term2));
	}

	// Terme de Fresnel
	float CookTorrance::Fresnel_Smith(const float& f0, const Vec3f& lumiereDirection, const Vec3f& halfVector) {
		float lDoth = dot(lumiereDirection, halfVector);
		float produit = (1.0f - f0) * pow(1.0f - lDoth, 5);
		return (f0 + produit);
	}

	// BRDF à microfacette
	float CookTorrance::BRDF(const Vec3f& directionLumiere, const Vec3f& directionVue, const float& alpha, const Vec3f& normal, const float& ior) {
		Vec3f halfVector = normalize(directionLumiere + directionVue);
		float f0 = abs((1.0f - ior) / (1.0f + ior));
		f0 = f0 * f0;
		float F = Fresnel_Smith(f0, directionLumiere, halfVector); // Fresnel Factor	
		float G = Geometry_CookTorrance(directionVue, normal, directionLumiere, halfVector); // Masking Term
		float D = Distribution_Beckmann(halfVector, normal, alpha); // Distribution
		float denominateur = 4 * (dot(normal, directionLumiere)) * (dot(normal, directionVue));
		return abs((F * G * D) / denominateur);
	}

} // namespace ISICG_ISIR