R"zzz(
#version 330 core
uniform vec3 camera_position;
in vec4 vertex_position;
out vec4 vs_camera_direction;
void main() {
	gl_Position = vertex_position;
	vs_camera_direction = vec4(camera_position, 1.0) - gl_Position;
}
)zzz"
