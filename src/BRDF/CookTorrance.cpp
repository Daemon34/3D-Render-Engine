#include "CookTorrance.hpp"
#include "iostream"

namespace ISICG_ISIR
{
	// Beckmann distribution function
	float CookTorrance::Distribution_Beckmann(const Vec3f& halfVector, const Vec3f& normal, const float& alpha) {
		// Calculate dot product between normal and half vector
		float nDoth = std::min(0.0f, dot(normal, halfVector));
		if (nDoth == 0.0f) {
			return 0.0f;
		}
		else {
			// Calculate squared dot product and alpha values
			float nDothCarre = nDoth * nDoth;
			float alphaCarre = alpha * alpha;
			// Calculate the exponential term
			float facteurExp = (nDothCarre - 1.0f) / (alphaCarre * nDothCarre);
			// Calculate the denominator term
			float denominateur = 3.14f * alphaCarre * (nDothCarre * nDothCarre);
			// Calculate the final value of the distribution function
			return (exp(facteurExp) / denominateur);
		}
	}

	// Schlick-Beckmann geometry function
	float Geometry_Schlick_Beckmann(const Vec3f& direction, const Vec3f& halfVector, const float& alpha) {
		// Calculate k and dot product between half vector and direction
		float k = alpha * sqrt(2.0f / 3.14f);
		float dDoth = dot(halfVector, direction);
		// Calculate the denominator term
		float denominateur = (dDoth * (1 - k)) + k;
		// Calculate the final value of the geometry function
		return (dDoth / denominateur);
	}

	// Cook-Torrance geometry function
	float CookTorrance::Geometry_CookTorrance(const Vec3f& directionVue, const Vec3f& normal, const Vec3f& directionLumiere, const Vec3f& halfVector) {
		// Calculate dot products between vectors
		float hdotN = dot(halfVector, normal);
		float vdotN = dot(directionVue, normal);
		float vdotH = dot(directionVue, halfVector);
		float ldotN = dot(directionLumiere, normal);
		// Calculate the first and second terms
		float term1 = (2 * hdotN * vdotN) / vdotH;
		float term2 = (2 * hdotN * ldotN) / vdotH;
		// Calculate the final value of the geometry function
		return glm::min(1.0f, glm::min(term1, term2));
	}

	// Smith's shadowing-masking function (Fresnel factor)
	float CookTorrance::Fresnel_Smith(const float& f0, const Vec3f& lumiereDirection, const Vec3f& halfVector) {
		// Calculate the dot product between light direction and half vector
		float lDoth = dot(lumiereDirection, halfVector);
		// Calculate the product term
		float product = (1.0f - f0) * pow(1.0f - lDoth, 5);
		// Calculate the final value of the Fresnel factor
		return (f0 + product);
	}

	// Microfacet BRDF
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