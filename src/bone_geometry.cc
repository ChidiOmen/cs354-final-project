#include "config.h"
#include "bone_geometry.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>

/*
 * For debugging purpose.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	size_t count = std::min(v.size(), static_cast<size_t>(10));
	for (size_t i = 0; i < count; ++i) os << i << " " << v[i] << "\n";
	os << "size = " << v.size() << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& bounds)
{
	os << "min = " << bounds.min << " max = " << bounds.max;
	return os;
}



// FIXME: Implement bone animation.


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Joint::addChild(int c) {
	children.push_back(c);
}

void Joint::calcVectors() {
	if(root) {
		t = glm::vec3(1.0f, 0.0f, 0.0f);
		n = glm::vec3(0.0f, 1.0f, 0.0f);
		b = glm::vec3(0.0f, 0.0f, 1.0f);
	} else {
		// t = glm::vec3();
	}
}

void Bone::createCylinder(glm::vec3 start, glm::vec3 end, int s) {
	glm::vec3 dir = end - start;
	glm::vec3 norm = glm::dvec3(1.0f, 1.0f, 1.0f);
	if (dir.z < 0.1f) dir.z = 0.1f;
	norm.z = -1.0f * (dir.x + dir.y) / dir.z;
	int n = 10;
	float radius = 0.4f;
	float theta = 2.0f * 3.14159 / n;
	float costh = std::cos(theta);
	float sinth = std::sin(theta);
	glm::vec3 cur_norm = glm::normalize(norm);
	for (float j = 0.0f; j < 3.0f; j += 1.0f) {
		glm::vec3 p = start + j * dir / 2.0f;
		for (int i = 0; i < n; i++) {
			glm::vec3 w = glm::normalize(glm::cross(cur_norm, dir));
			glm::vec3 b = glm::dvec3(-1*sinth*w.x + costh*cur_norm.x,
			 -1*sinth*w.y + costh*cur_norm.y , -1*sinth*w.z + costh*cur_norm.z );
			b = radius * glm::normalize(b);
			cyl_verts.push_back(b+p);
			// std::cout << "j: " << j << " p: " << p << " B+P: " << b+p << std::endl; //REMOVE
			int q = (int) j;
			// std::cout << "q: " << q << std::endl;
			if (i == n - 1) {
				cyl_vert_inds.push_back(glm::uvec2(n - 1 + 0 + q*n, 0 + q*n));
			}
			else {
				cyl_vert_inds.push_back(glm::uvec2(i + 0 + q*n, i + 1 + 0 + q*n));
			}
			cur_norm = b;
		}
	}
}

void Mesh::loadpmd(const std::string& fn)
{
	MMDReader mr;
	mr.open(fn);
	mr.getMesh(vertices, faces, vertex_normals, uv_coordinates);
	computeBounds();
	mr.getMaterial(materials);

	// FIXME: load skeleton and blend weights from PMD file
	//        also initialize the skeleton as needed
	glm::vec3 offset;
	int parent;
	int id = 0;
	mr.getJoint(id, offset, parent);
	Joint* root = new Joint(true, offset, parent);
	root->pos = root->offset;
	skel.joints.push_back(root);
	id++;
	while (mr.getJoint(id, offset, parent)) {
		Joint* j = new Joint(false, offset, parent);
		skel.joints.push_back(j);
		if (parent != -1) {
			Joint* jp = skel.joints[parent];
			jp->addChild(id);
			for (int i = 0; i < j->pos.size(); i++) {
				j->pos[i] = j->offset[i] + jp->pos[i];
			}
			Bone* b = new Bone(parent, id);
			b->createCylinder(jp->pos, j->pos, b->cyl_verts.size());
			skel.bones.push_back(b);

		}
		else j->pos = j->offset;
		id++;
	}
	// for(int i = 0; i < skel.bones.size(); i++) {
	// 	Bone* b = skel.bones[i];
	// 	b->createCylinder(skel.joints[b->joints[0]]->pos, 
	// 	skel.joints[b->joints[1]]->pos, b->cyl_verts.size());
	// }
}

void Mesh::updateAnimation()
{
	animated_vertices = vertices;
	// FIXME: blend the vertices to animated_vertices, rather than copy
	//        the data directly.
}


void Mesh::computeBounds()
{
	bounds.min = glm::vec3(std::numeric_limits<float>::max());
	bounds.max = glm::vec3(-std::numeric_limits<float>::max());
	for (const auto& vert : vertices) {
		bounds.min = glm::min(glm::vec3(vert), bounds.min);
		bounds.max = glm::max(glm::vec3(vert), bounds.max);
	}
}

