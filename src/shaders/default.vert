R"zzz(
#version 330 core
uniform vec4 light_position;
uniform vec3 camera_position;
in vec4 vertex_position;
in vec4 normal;
in vec2 uv;
out vec4 vs_light_direction;
out vec4 vs_normal;
out vec2 vs_uv;
out vec4 vs_camera_direction;
void main() {
	gl_Position = vertex_position;
	//gl_Position.x = floor(1.0 * gl_Position.x) / 1.0;
	//gl_Position.y = floor(1.0 * gl_Position.y) / 1.0;
	//gl_Position.z = floor(1.0 * gl_Position.z) / 1.0;
	vs_light_direction = light_position - gl_Position;
	vs_camera_direction = vec4(camera_position, 1.0) - gl_Position;
	vs_normal = normal;
	vs_uv = uv;
}
)zzz"
