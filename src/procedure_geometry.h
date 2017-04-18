#ifndef PROCEDURE_GEOMETRY_H
#define PROCEDURE_GEOMETRY_H

#include <vector>
#include <glm/glm.hpp>
#include "bone_geometry.h"

class LineMesh;

void create_floor(std::vector<glm::vec4>& floor_vertices,
 std::vector<glm::uvec3>& floor_faces);
// FIXME: Add functions to generate the bone mesh.
void create_bone(std::vector<glm::vec4>& bone_vertices,
 std::vector<glm::uvec3>& bone_faces);
void create_bone_lines(std::vector<glm::vec4>& bone_vertices,
 std::vector<glm::uvec2>& bone_lines);
void create_skeleton(std::vector<glm::vec4>& bone_vertices,
 std::vector<glm::uvec2>& bone_lines, Mesh mesh);
void create_cylinder(std::vector<glm::vec4>& cyl_verts,
 std::vector<glm::uvec3>& cyl_faces, glm::dvec3 up, glm::dvec3 origin,
  float r, float l);
void create_cylinders(std::vector<glm::vec4>& cyl_vertices, std::vector<glm::uvec2>& cyl_lines,
 Mesh mesh);

#endif
