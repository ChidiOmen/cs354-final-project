#include "procedure_geometry.h"
#include "bone_geometry.h"
#include "config.h"
#include <iostream>
#include <cmath>

void create_floor(std::vector<glm::vec4>& floor_vertices, std::vector<glm::uvec3>& floor_faces)
{
	floor_vertices.push_back(glm::vec4(kFloorXMin, kFloorY, kFloorZMax, 1.0f));
	floor_vertices.push_back(glm::vec4(kFloorXMax, kFloorY, kFloorZMax, 1.0f));
	floor_vertices.push_back(glm::vec4(kFloorXMax, kFloorY, kFloorZMin, 1.0f));
	floor_vertices.push_back(glm::vec4(kFloorXMin, kFloorY, kFloorZMin, 1.0f));
	floor_faces.push_back(glm::uvec3(0, 1, 2));
	floor_faces.push_back(glm::uvec3(2, 3, 0));
}

// FIXME: create cylinders and lines for the bones
// Hints: Generate a lattice in [-0.5, 0, 0] x [0.5, 1, 0] We wrap this
// around in the vertex shader to produce a very smooth cylinder.  We only
// need to send a small number of points.  Controlling the grid size gives a
// nice wireframe.
void create_bone(std::vector<glm::vec4>& bone_vertices, std::vector<glm::uvec3>& bone_faces) {
	bone_vertices.push_back(glm::vec4(-2.0f, 2.0f, 2.0f, 1.0f));
	bone_vertices.push_back(glm::vec4(2.0f, 2.0f, 2.0f, 1.0f));
	bone_vertices.push_back(glm::vec4(2.0f, 2.0f, -2.0f, 1.0f));
	bone_vertices.push_back(glm::vec4(-2.0f, 2.0f, -2.0f, 1.0f));
	bone_faces.push_back(glm::uvec3(0, 1, 2));
	bone_faces.push_back(glm::uvec3(2, 3, 0));

}

void create_bone_lines(std::vector<glm::vec4>& bone_vertices, std::vector<glm::uvec2>& bone_lines) {
	bone_vertices.push_back(glm::vec4(-2.0f, 2.0f, 2.0f, 1.0f));
	bone_vertices.push_back(glm::vec4(2.0f, 2.0f, 2.0f, 1.0f));
	bone_vertices.push_back(glm::vec4(2.0f, 2.0f, -2.0f, 1.0f));
	bone_vertices.push_back(glm::vec4(-2.0f, 2.0f, -2.0f, 1.0f));
	bone_lines.push_back(glm::uvec2(0, 1));
	bone_lines.push_back(glm::uvec2(1, 2));
	bone_lines.push_back(glm::uvec2(2, 3));
	bone_lines.push_back(glm::uvec2(3, 0));
}

void create_skeleton(std::vector<glm::vec4>& bone_vertices, std::vector<glm::uvec2>& bone_lines,
 Mesh mesh) {
 	for (int i = 0; i < mesh.skel.joints.size(); i++) {
 		Joint* j = mesh.skel.joints[i];
 		bone_vertices.push_back(glm::vec4(j->pos[0], j->pos[1], j->pos[2], 1.0f));
 	}
 	for (int i = 0; i < mesh.skel.bones.size(); i++) {
 		Bone* b = mesh.skel.bones[i];
 		bone_lines.push_back(b->joints);
 	}
 	
}

void create_cylinders(std::vector<glm::vec4>& cyl_vertices, std::vector<glm::uvec2>& cyl_lines,
 Mesh mesh) {
 	for (int i = 0; i < mesh.skel.bones.size(); i++) {
 		Bone* b = mesh.skel.bones[i];
 		int s = cyl_vertices.size();
 		for (int j = 0; j < b->cyl_verts.size(); j++) {
 			glm::vec3 a = b->cyl_verts[j];
 			cyl_vertices.push_back(glm::vec4(a[0], a[1], a[2], 1.0f));
 			// std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
 		}
 		for (int j = 0; j < b->cyl_vert_inds.size(); j++) {
 			glm::uvec2 a = b->cyl_vert_inds[j];
 			cyl_lines.push_back(glm::uvec2(a[0]+s, a[1]+s));
 			// std::cout << a[0]+s << " " << a[1]+s << std::endl;
 		}
 	}
}

void create_cylinder(std::vector<glm::vec4>& cyl_verts, std::vector<glm::uvec3>& cyl_faces,
 glm::dvec3 up, glm::dvec3 origin, float r, float l) {
	glm::dvec3 p = glm::dvec3(1.0f, 1.0f, 1.0f);
	p.z = -1.0f * (up.x + up.y) / up.z;
	std::cout << "DOT: " << glm::dot(p, up) << std::endl;
	int n = 10;
	float theta = 2.0f * 3.14159 / n;
	float costh = std::cos(theta);
	float sinth = std::sin(theta);
	glm::dvec3 a = p;
	for (int i = 0; i < n; i++) {
		glm::dvec3 w = glm::normalize(glm::cross(a, up));
		glm::dvec3 b = glm::dvec3(sinth*w.x - costh*a.x , sinth*w.y - costh*a.y , 
			sinth*w.z - costh*a.z );
		b = glm::normalize(b);
		b.x = r * b.x;
		b.y = r * b.y;
		b.z = r * b.z;
		std::cout << b.x << "DOT: " << glm::dot(p, up) << std::endl;
		a = b;

	}
	
}
