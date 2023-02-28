#include <iostream>
#include <random>

#include "3D/sphere.hpp"
#include "3D/triangleMesh.hpp"
#include "camera.hpp"
#include "chrono.hpp"
#include "defines.hpp"
#include "image.hpp"
#include "materials/flatColorMaterial.hpp"

namespace ISICG_ISIR
{
	int main(int argc, char **argv)
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

		FlatColorMaterial mtl(Vec3f(1.0, 0.0, 0.0));

		Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 3.0f), 1.0f);
		sphere.setMaterial(&mtl);

		std::vector<AObject3D *> objects;
		objects.emplace_back(&sphere);

		// random
		std::random_device rd;
		std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<float> dis(0.f, 1.f);

		Chrono chrono;
		Camera maCamera = Camera(VEC3F_ZERO, Vec3f(0.0f, 0.0f, 1.0f), 0.5f, float(height) / float(width));
		Vec3f positionLumiere = Vec3f(VEC3F_ZERO);
		Vec4f couleurLumiere = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

		Vec4f maCouleur;
		std::cout << "Rendering..." << std::endl;
		chrono.start();
		// rendering loop
		for (uint h = 0; h < height; ++h)
		{
			for (uint w = 0; w < width; ++w)
			{
				Ray rayon = maCamera.generateRay(Vec3f(float(w) / float(width), float(h) / float(height), 0.0f));
				maCouleur = Vec4f(0.4f, 0.4f, 0.4f, 1.0f) * (float(h) / float(height)) * (float(w) / float(width));
				for (uint o = 0; o < objects.size(); o++)
				{
					std::vector<Intersection> mesIntersections
						= objects[o]->intersect(rayon);
					for (int i = 0; i < mesIntersections.size(); i++)
					{
						if (mesIntersections[i]._distance > -1.0f)
						{
							Vec3f directionLumiere = normalize(positionLumiere - (rayon.getPosition() + (mesIntersections[i]._distance + 0.01f) * rayon.getDirection()));
							float coefficientDiffus = 0.5f * __max(dot(mesIntersections[i]._normale, directionLumiere), 0.0f);
							float coefficientAmbiant = 0.1f;
							Vec3f refletSphere = normalize(glm::reflect(-directionLumiere, mesIntersections[i]._normale));
							float coefficientSpeculaire = 0.4f * pow(__max(dot(refletSphere, -rayon.getDirection()), 0.0f), 100.0f);
							maCouleur = couleurLumiere * Vec4f(0.0f, 1.0f, 0.0f, 1.0f) * (coefficientDiffus + coefficientAmbiant) + couleurLumiere * coefficientSpeculaire;
						}
					}
				}
				image.setPixel(w, h, maCouleur);
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

int main(int argc, char **argv)
{
	try
	{
		return ISICG_ISIR::main(argc, argv);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception caught !" << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
