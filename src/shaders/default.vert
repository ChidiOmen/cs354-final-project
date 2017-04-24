R"zzz(
#version 330 core
uniform vec4 light_position;
uniform vec3 camera_position;
in vec4 vertex_position;
in vec4 normal;
in vec2 uv;
uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shininess;
uniform float alpha;
uniform sampler2D textureSampler;
out vec4 vs_light_direction;
out vec4 vs_normal;
out vec2 vs_uv;
out vec4 vs_camera_direction;
out vec4 fragment_color;
void main() {
	gl_Position = vertex_position;
	//gl_Position.x = floor(1.0 * gl_Position.x) / 1.0;
	//gl_Position.y = floor(1.0 * gl_Position.y) / 1.0;
	//gl_Position.z = floor(1.0 * gl_Position.z) / 1.0;
	vs_light_direction = light_position - gl_Position;
	vs_camera_direction = vec4(camera_position, 1.0) - gl_Position;
	vec4 light_direction = normalize(light_position - gl_Position);
	vec4 camera_direction = normalize(vec4(camera_position, 1.0) - gl_Position);
	vs_normal = normal;
	vs_uv = uv;

	vec3 texcolor = texture(textureSampler, vs_uv).xyz;
	if (length(texcolor) == 0.0) {
		vec3 color = vec3(diffuse);
		float dot_nl = dot(normalize(light_direction), normalize(normal));
		dot_nl = clamp(dot_nl, 0.0, 1.0);
		vec4 spec = specular * pow(max(0.0, dot(reflect(-light_direction, normal), camera_direction)), shininess);
		color = clamp(dot_nl * color + vec3(ambient), 0.0, 1.0);
		fragment_color = vec4(color, alpha);
		fragment_color.r = floor(10.0 * fragment_color.r) / 10.0;
		fragment_color.g = floor(10.0 * fragment_color.g) / 10.0;
		fragment_color.b = floor(10.0 * fragment_color.b) / 10.0;
	} else {
		fragment_color = vec4(texcolor.rgb, alpha);
	}
	//fragment_color = vec4(0.2, 0.2, 0.2, 0.5);
}
)zzz"
