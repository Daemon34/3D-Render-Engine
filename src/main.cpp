#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <random>
#include <algorithm>

#include "3D/sphere.hpp"
#include "3D/plane.hpp"
#include "3D/triangleMesh.hpp"
#include "3D/triangle.hpp"
#include "3D/metaballs.hpp"
#include "BVH.hpp"
#include "camera.hpp"
#include "chrono.hpp"
#include "defines.hpp"
#include "image.hpp"
#include "materials/flatColorMaterial.hpp"
#include "materials/damierMaterial.hpp"
#include "materials/cookTorranceMaterial.hpp"
#include "3D/sphereLight.hpp"
#include "3D/pointLight.hpp"
#include "raytracer.hpp"

namespace ISICG_ISIR
{
	int main(int argc, char** argv)
	{
		if (argc != 4)
		{
			throw std::runtime_error(
				"Invalid program argument: must be launched with <imageWidth> "
				"<imageHeight> <imageName>\n e.g. 800 600 results.jpg");
		}

		// get arguments
		const std::string name(argv[1]);
		const uint width = atoi(argv[2]);
		const uint height = atoi(argv[3]);

		ImageJPG image(width, height);

		// G�n�rateur nombre al�atoire
		std::random_device rd;
		std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

		// -------------- CREATION DES OBJETS DANS LA SCENE --------------------------------------------------

		// -------------------------- SPHERE ET PLAN --------------------------------------------------------

		Sphere sphereVerte = Sphere(Vec3f(-7.0f, 4.0f, 5.0f), 0.8f);
		FlatColorMaterial materialVert(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.8f, 2.2f);
		CookTorranceMaterial materialCookTorranceVert(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.8f, 2.2f, 0.4f);
		//sphereVerte.setMaterial(&materialVert);
		sphereVerte.setMaterial(&materialCookTorranceVert);

		Sphere sphereRouge = Sphere(Vec3f(5.0f, 7.0f, 5.0f), 1.0f);
		FlatColorMaterial materialRouge(Vec3f(1.0f, 0.0f, 0.0f), 0.7f, 0.1f, 0.2f, 0.5f, 0.0f, 0.0f);
		CookTorranceMaterial materialCookTorranceRouge(Vec3f(1.0f, 0.0f, 0.0f), 0.7f, 0.1f, 0.2f, 0.5f, 0.0f, 0.0f, 0.2f);
		//sphereRouge.setMaterial(&materialRouge);
		sphereRouge.setMaterial(&materialCookTorranceRouge);

		Sphere sphereViolet = Sphere(Vec3f(0.0f, 5.0f, 5.0f), 3.0f);
		FlatColorMaterial materialViolet(Vec3f(1.0f, 0.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.0f, 0.0f);
		CookTorranceMaterial materialCookTorrance(Vec3f(1.0f, 0.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.0f, 0.0f, 1.0f);
		sphereViolet.setMaterial(&materialCookTorrance);
		//sphereViolet.setMaterial(&materialViolet);

		Sphere sphereBleu = Sphere(Vec3f(0.0f, 5.0f, 10.0f), 2.5f);
		FlatColorMaterial materialBleu(Vec3f(0.0f, 0.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.0f, 0.0f);
		sphereBleu.setMaterial(&materialBleu);

		Sphere sphereReflect1 = Sphere(Vec3f(0.0f, 3.0f, 12.0f), 4.0f);
		CookTorranceMaterial materialCookTorranceR(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.0f, 0.0f, 1.0f);
		sphereReflect1.setMaterial(&materialCookTorranceR);
		Sphere sphereReflect2 = Sphere(Vec3f(-10.0f, 3.0f, 10.0f), 3.0f);
		CookTorranceMaterial materialCookTorranceG(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.0f, 0.0f, 0.6f);
		sphereReflect2.setMaterial(&materialCookTorranceG);
		Sphere sphereReflect3 = Sphere(Vec3f(10.0f, 3.0f, 10.0f), 3.0f);
		CookTorranceMaterial materialCookTorranceB(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.0f, 0.0f, 0.2f);
		sphereReflect3.setMaterial(&materialCookTorranceB);

		Sphere sphereReflect4 = Sphere(Vec3f(8.0f, 3.0f, 3.0f), 2.0f);
		CookTorranceMaterial materialCookTorranceRef(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.6f, 0.0f, 0.0f, 0.6f);
		sphereReflect4.setMaterial(&materialCookTorranceRef);

		Sphere sphereReflect5 = Sphere(Vec3f(-8.0f, 3.0f, 3.0f), 2.0f);
		FlatColorMaterial materialCookTorranceRaf(Vec3f(1.0f, 1.0f, 1.0f), 0.7f, 0.1f, 0.2f, 0.0f, 0.6f, 2.2f);
		sphereReflect5.setMaterial(&materialCookTorranceRaf);

		Plane plan = Plane(Vec3f(0.0f, 1.0f, 0.0f), Vec3f(0.0f, -2.0f, 0.0f));
		DamierMaterial materialSol(Vec3f(1.0f, 0.0f, 0.0f), 0.9f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f);
		plan.setMaterial(&materialSol);

		// -----------------------------------------------------------------------------------
		// -------------------------- LUMIERE ------------------------------------------------

		SphereLight lumiere = SphereLight(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(-6.0f, 8.0f, -20.0f), 1.0f);
		//PointLight lumiere = PointLight(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(0.0f, 8.0f, 2.0f));

		// -----------------------------------------------------------------------------------

		// -------------------------- METABALLS -----------------------------------------

		std::vector<Sphere> listeSphereMeta = std::vector<Sphere>();

		listeSphereMeta.push_back(sphereReflect1);
		listeSphereMeta.push_back(sphereReflect2);
		listeSphereMeta.push_back(sphereReflect3);
		Metaballs metaballs = Metaballs(listeSphereMeta);
		metaballs.setMaterial(&materialCookTorranceG);

		// -----------------------------------------------------------------------------------

		// -------------------------- MAILLAGE TRIANGLE ---------------------------------------

		TriangleMesh mesh;
		mesh.setMaterial(&materialCookTorrance);
		mesh.load("data/obj/Bunny.obj");
		mesh.scale(Vec3f(1.5f, 1.5f, 1.5f));
		mesh.translate(Vec3f(0.0f, 3.0f, 3.0f));

		// --------------------------------------------------------------------------------------

		// -------------------------- BVH --------------------------------------------------------

		BVH monBVH;
		std::cout << "Creation BVH..." << std::endl;
		monBVH.creationBVH(mesh.getListeTriangle());
		std::cout << "Fin BVH" << std::endl;

		// -----------------------------------------------------------------------------------------

		// -------------------------- SCENE ------------------------------------------------------

		std::vector<AObject3D*> objects;
		objects.emplace_back(&sphereReflect4);
		objects.emplace_back(&sphereReflect5);
		//objects.emplace_back(&sphereReflect3);
		//objects.emplace_back(&sphereVerte);
		//objects.emplace_back(&sphereRouge);
		//objects.emplace_back(&sphereViolet);
		//objects.emplace_back(&sphereBleu);
		objects.emplace_back(&plan);
		objects.emplace_back(&metaballs);

		Chrono chrono;
		Camera maCamera = Camera(Vec3f(0.0f, 8.0f, -5.0f), Vec3f(0.0f, -0.5f, 1.0f), 0.5f, float(height) / float(width));

		// --------------------------------------------------------------------------------------------


		std::cout << "Rendering..." << std::endl;
		chrono.start();

		// rendering loop
		#pragma omp parallel for
		for (uint h = 0; h < height; ++h)
		{
			for (uint w = 0; w < width; ++w)
			{
				Vec3f sommeCouleur = VEC3F_ZERO;

				// Boucle pour l'antialliasing
				for (int i = 0; i < ANTIALLIASING; i++) {
					// G�n�ration d'un rayon pour un pixel de l'image � partir de la cam�ra
					Ray rayon = maCamera.generateRay(Vec3f(float(w + dis(gen)) / float(width), float(h + dis(gen)) / float(height), 0.0f));
					sommeCouleur += couleur(rayon, 0, lumiere, objects, monBVH); // Ajout de la couleur obtenue par le rayon
				}
				Vec3f couleurFinale = sommeCouleur / ANTIALLIASING; // Moyenne des couleurs de chaque rayon

				image.setPixel(w, h, couleurFinale); // Mise a jour du pixel dans l'image finale
			}
		}
		chrono.stop();
		std::cout << "Rendering done. Image computed in "
			<< chrono.elapsedTime() << "s (" << image.getWidth() << "x"
			<< image.getHeight() << ")" << std::endl;

		std::cout << "Save image as: " << name << std::endl;
		image.save(name);

		return EXIT_SUCCESS;
	}
} // namespace ISICG_ISIR

int main(int argc, char** argv)
{
	try
	{
		return ISICG_ISIR::main(argc, argv);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Exception caught !" << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
