#ifndef __ISICG_ISIR_TRIANGLE_MESH__
#define __ISICG_ISIR_TRIANGLE_MESH__

#include <vector>

#include "glm/gtx/transform.hpp"
#include "assimp/mesh.h"

#include "triangle.hpp"

namespace ISICG_ISIR
{
	struct MeshTriangle
	{
		// vertices ids in TriangleMesh::_vertices
		union
		{
			struct
			{
				uint _v0, _v1, _v2;
			};
			uint _v[3];
		};
	};

	class TriangleMesh : public AObject3D
	{
	public:
		TriangleMesh() = default;
		void load(const std::string &path);

		std::vector<Intersection> intersect(const Ray &ray) override;
		void translate(const Vec3f& direction);
		void scale(const Vec3f& facteur);
		std::vector<Triangle>& getListeTriangle();
		void setListeTriangle();

	private:
		std::vector<MeshTriangle> _triangles;
		std::vector<Vec3f> _vertices;
		std::vector<Triangle> _listeTriangle = std::vector<Triangle>(0);
	};
} // namespace ISICG_ISIR

#endif // __ISICG_ISIR_TRIANGLE_MESH__
