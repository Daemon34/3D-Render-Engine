#define GLM_ENABLE_EXPERIMENTAL

#include "triangleMesh.hpp"

#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "triangle.hpp"
#include "materials/flatColorMaterial.hpp"


namespace ISICG_ISIR
{
	// Load a mesh with assimp
	void TriangleMesh::load(const std::string &path)
	{
		Assimp::Importer importer;

		// Read scene and triangulate meshes
		const aiScene *const scene
			= importer.ReadFile(path.c_str(), aiProcess_Triangulate);

		if (scene == nullptr)
		{
			throw std::runtime_error("Cannot import file: " + path);
		}

		const uint nbMeshes = scene->mNumMeshes;
		uint nbTriangles = 0;
		uint nbVertices = 0;

		for (uint i = 0; i < nbMeshes; ++i)
		{
			const aiMesh *const mesh = scene->mMeshes[i];
			nbTriangles += mesh->mNumFaces;
			nbVertices += mesh->mNumVertices;
		}

		_triangles.resize(nbTriangles);
		_vertices.resize(nbVertices);

		uint currentTriangle = 0;
		uint currentVertex = 0;

		for (uint m = 0; m < nbMeshes; ++m)
		{
			const aiMesh *const mesh = scene->mMeshes[m];
			const aiMaterial *const material
				= scene->mMaterials[mesh->mMaterialIndex];

			for (uint f = 0; f < mesh->mNumFaces; ++f, ++currentTriangle)
			{
				const aiFace face = mesh->mFaces[f];

				MeshTriangle &tri = _triangles[currentTriangle];

				// triangulated ! :-)
				for (uint v = 0; v < 3; ++v)
				{
					const uint idV = face.mIndices[v];
					tri._v[v] = idV;
				}
			}

			for (uint v = 0; v < mesh->mNumVertices; ++v, ++currentVertex)
			{
				Vec3f &vertex = _vertices[currentVertex];
				vertex.x = mesh->mVertices[v].x;
				vertex.y = mesh->mVertices[v].y;
				vertex.z = mesh->mVertices[v].z;
			}
		}
		
		std::cout << "Loaded: " << std::endl
				  << "- nb faces: " << _triangles.size() << std::endl
				  << "- nb vertices: " << _vertices.size() << std::endl;
		setListeTriangle();
	}

	std::vector<Intersection> TriangleMesh::intersect(const Ray &ray)
	{
		std::vector<Intersection> mesIntersections;
		for (int i = 0; i < _listeTriangle.size(); i++) {
			Intersection monIntersection;
			std::vector<Intersection> mesIntersectionsTriangle = _listeTriangle[i].intersect(ray);
			float distanceMin = -1.0f;
			for (uint i = 0; i < mesIntersectionsTriangle.size(); i++)
			{
				if (mesIntersectionsTriangle[i]._distance > -1.0f && (distanceMin > mesIntersectionsTriangle[i]._distance || distanceMin == -1.0f))
				{
					distanceMin = mesIntersectionsTriangle[i]._distance;
					monIntersection = mesIntersectionsTriangle[i];
					monIntersection._obj = this;
				}
			}
			mesIntersections.push_back(monIntersection);
		}
		return mesIntersections;
	}

	void TriangleMesh::translate(const Vec3f& direction) {
		for (int i = 0; i < _vertices.size(); i++) {
			_vertices[i] += direction;
		}
		setListeTriangle();
	}

	void TriangleMesh::scale(const Vec3f& facteur) {
		for (int i = 0; i < _vertices.size(); i++) {
			_vertices[i] *= facteur;
		}
		setListeTriangle();
	}

	std::vector<Triangle>& TriangleMesh::getListeTriangle()
	{
		return _listeTriangle;
	}

	void TriangleMesh::setListeTriangle()
	{
		_listeTriangle.clear();
		for (uint i = 0; i < _triangles.size(); i++) {
			Triangle monTriangle = Triangle(_vertices[_triangles[i]._v0], _vertices[_triangles[i]._v1], _vertices[_triangles[i]._v2]);
			monTriangle.setMaterial(this->getMaterial());
			_listeTriangle.push_back(monTriangle);
		}
	}

} // namespace ISICG_ISIR
