#ifndef BONE_GEOMETRY_H
#define BONE_GEOMETRY_H

#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <glm/glm.hpp>
#include <mmdadapter.h>

struct BoundingBox {
	BoundingBox()
		: min(glm::vec3(-std::numeric_limits<float>::max())),
		max(glm::vec3(std::numeric_limits<float>::max())) {}
	glm::vec3 min;
	glm::vec3 max;
};

struct Joint {
	// FIXME: Implement your Joint data structure.
	// Note: PMD represents weights on joints, but you need weights on
	//       bones to calculate the actual animation.

	Joint();
	Joint(bool _root, glm::vec3 _offset, int _parent) {
		root = _root;
		offset = _offset;
		parent = _parent;
		length = glm::length(offset);
	}
	~Joint();
	void addChild(int c);
	void calcVectors();

	bool root;
	glm::vec3 offset;
	glm::vec3 pos;
	int parent;
	std::vector<int> children;
	glm::vec3 t;
	glm::vec3 n;
	glm::vec3 b;
	float length;
};

struct Bone
{
	Bone() {};
	Bone (Joint* p, Joint* c) {
		parent = p;
		child = c;
	}
	Bone (int p, int c) {
		joints = glm::uvec2(p, c);
	}
	~Bone() {};
	void createCylinder(glm::vec3 start, glm::vec3 end, int s);

	Joint* parent;
	Joint* child;
	glm::uvec2 joints;
	std::vector<glm::vec3> cyl_verts;
	std::vector<glm::uvec2> cyl_vert_inds;
};


struct Skeleton {
	// FIXME: create skeleton and bone data structures
	Skeleton() {};
	~Skeleton() {};

	std::vector<Bone*> bones;
	std::vector<Joint*> joints;

};

struct Mesh {
	Mesh();
	~Mesh();
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec4> animated_vertices;
	std::vector<glm::uvec3> faces;
	std::vector<glm::vec4> vertex_normals;
	std::vector<glm::vec4> face_normals;
	std::vector<glm::vec2> uv_coordinates;
	std::vector<Material> materials;
	BoundingBox bounds;
	Skeleton skel;

	void loadpmd(const std::string& fn);
	void updateAnimation();
	int getNumberOfBones() const 
	{ 
		return 0;
		// FIXME: return number of bones in skeleton
	}
	glm::vec3 getCenter() const { return 0.5f * glm::vec3(bounds.min + bounds.max); }
private:
	void computeBounds();
	void computeNormals();
};

#endif
