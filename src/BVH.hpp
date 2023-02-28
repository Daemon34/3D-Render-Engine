/* Classe définissant une hiérarchie de volumes englobants.
	Attention, ce BVH ne prend en compte que l'axe des x pour le calcul du SAH.
	De plus, il ne prend en compte que les triangles et pas les autres primitives.
	Consulter le rapport pour plus d'informations.*/

#ifndef __ISICG_ISIR_BVH__
#define __ISICG_ISIR_BVH__

#include "3D/box.hpp"
#include <algorithm>
#include "defines.hpp"
#include "materials/flatColorMaterial.hpp"

namespace ISICG_ISIR
{
	class BVH
	{

	public:
		struct {
			bool operator()(Triangle& a, Triangle& b) const
			{
				return ((a.getSommet(0) + a.getSommet(1) + a.getSommet(2)) / 3.0f).x < ((b.getSommet(0) + b.getSommet(1) + b.getSommet(2)) / 3.0f).x;
			}
		} comparateurX;

		void creationBVH(std::vector<Triangle>& listeTriangle) {
			_boundingBox.trouverVolumeEnglobant(listeTriangle);
			if (listeTriangle.size() < 8) {
				_enfantDroite = nullptr;
				_enfantGauche = nullptr;
				for (int i = 0; i < listeTriangle.size(); i++) {
					_listeTriangle.push_back(listeTriangle[i]);
				}
				
			}
			else {
				std::sort(listeTriangle.begin() , listeTriangle.end(), comparateurX);
				std::vector<Box> boitesGauche(listeTriangle.size());
				std::vector<Box> boitesDroite(listeTriangle.size());
				std::vector<float> SAH(listeTriangle.size());
				for (uint i = 1; i < listeTriangle.size(); i++) {
					boitesGauche[i].enlarge(listeTriangle[0], listeTriangle[i]);
				}
				for (int i = listeTriangle.size() - 2; i >= 0; i--) {
					boitesDroite[i].enlarge(listeTriangle[listeTriangle.size() - 1], listeTriangle[i]);
				}
				float minSAH = FLT_MAX;
				int idSAH = -1;
				for (uint i = 0; i < listeTriangle.size(); i++) {
					int nbTriangleGauche = i;
					int nbTriangleDroite = listeTriangle.size() - nbTriangleGauche;
					float aireGauche = boitesGauche[i].calculerAire();
					float aireDroite = boitesDroite[i].calculerAire();
					SAH[i] = (aireGauche * nbTriangleGauche + aireDroite * nbTriangleDroite) / _boundingBox.calculerAire();
					if (SAH[i] < minSAH) {
						minSAH = SAH[i];
						idSAH = i;
					}
				}
				std::vector<Triangle> listeTriangleGauche = std::vector<Triangle>(idSAH);
				for (int i = 0; i < idSAH; i++) {
					listeTriangleGauche[i] = listeTriangle[i];
				}
				std::vector<Triangle> listeTriangleDroite = std::vector<Triangle>(listeTriangle.size() - idSAH);
				for (int i = idSAH; i < listeTriangle.size(); i++) {
					listeTriangleDroite[i - idSAH] = listeTriangle[i];
				}
				BVH* enfantDroite = new BVH();
				BVH* enfantGauche = new BVH();
				enfantDroite->creationBVH(listeTriangleDroite);
				enfantGauche->creationBVH(listeTriangleGauche);
				_enfantDroite = enfantDroite;
				_enfantGauche = enfantGauche;
			}
		}

		Intersection parcoursBVH(const Ray& rayon) {
			Intersection monIntersection;
			monIntersection._obj = nullptr;
			float distanceMin = -1.0f;
			std::vector<Intersection> mesIntersections = _boundingBox.intersect(rayon);
			for (uint i = 0; i < mesIntersections.size(); i++)
			{
				if (mesIntersections[i]._distance > DIST_EPSILON && (distanceMin > mesIntersections[i]._distance || distanceMin == -1.0f) && mesIntersections[i]._distance < MAX_DISTANCE)
				{
					distanceMin = mesIntersections[i]._distance;
					monIntersection = mesIntersections[i];
				}
			}
			if (monIntersection._obj == nullptr) {
				return monIntersection;
			} else {
				// Si on est dans une feuille
				if (_enfantDroite == nullptr && _enfantGauche == nullptr) {
					monIntersection._obj = nullptr;
					distanceMin = -1.0f;
					for (uint o = 0; o < _listeTriangle.size(); o++){
						std::vector<Intersection> mesIntersections = _listeTriangle[o].intersect(rayon);
						for (uint i = 0; i < mesIntersections.size(); i++){
							if (mesIntersections[i]._distance > DIST_EPSILON && (distanceMin > mesIntersections[i]._distance || distanceMin == -1.0f) && mesIntersections[i]._distance < MAX_DISTANCE)
							{
								distanceMin = mesIntersections[i]._distance;
								monIntersection = mesIntersections[i];
							}
						}
					}
					return monIntersection;
				// Sinon on relance sur les enfants
				} else {
					Intersection intersectionDroite = _enfantDroite->parcoursBVH(rayon);
					Intersection intersectionGauche = _enfantGauche->parcoursBVH(rayon);
					if (intersectionDroite._obj == nullptr) {
						if (intersectionGauche._obj == nullptr) {
							return intersectionDroite;
						}
						else {
							return intersectionGauche;
						}
					}
					else {
						if (intersectionGauche._obj == nullptr) {
							return intersectionDroite;
						}
						else {
							if ((intersectionDroite._distance < intersectionGauche._distance)) {
								return intersectionDroite;
							}
							else {
								return intersectionGauche;
							}
						}
					}
				}
			}
		}
		Box _boundingBox = Box();
		BVH* _enfantDroite = nullptr;
		BVH* _enfantGauche = nullptr;
		std::vector<Triangle> _listeTriangle = std::vector<Triangle>(0);
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_BVH__