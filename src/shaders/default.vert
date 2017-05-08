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
	float w = 10.0;
	gl_Position.x = floor(gl_Position.x / w) * w;
	gl_Position.y = floor(gl_Position.y / w) * w;
	gl_Position.z = floor(gl_Position.z / w) * w;
	vs_light_direction = light_position - gl_Position;
	vs_camera_direction = vec4(camera_position, 1.0) - gl_Position;
	vec4 light_direction = normalize(light_position - gl_Position);
	vec4 camera_direction = normalize(vec4(camera_position, 1.0) - gl_Position);
	vs_normal = normal;
	vs_uv = uv;
	gl_Position = vertex_position;

	vec3 texcolor = texture(textureSampler, vs_uv).xyz;
	if (length(texcolor) == 0.0) {
		vec3 color = vec3(diffuse);
		float dot_nl = dot(normalize(light_direction), normalize(normal));
		dot_nl = clamp(dot_nl, 0.0, 1.0);
		vec4 spec = specular * pow(max(0.0, dot(reflect(-light_direction, normal), camera_direction)), shininess);
		color = clamp(dot_nl * color + vec3(ambient), 0.0, 1.0);
		float lum = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
		vec4 fc = vec4(vec3(diffuse), alpha);
		if (lum <= 0.2) {
			fc = vec4(0.0, 0.0, 0.0, 1.0);
		} else if (lum <= 0.4) {
			fc = vec4(0.5*fc.r, 0.5*fc.g, 0.5*fc.b, 1.0);
		} else if (lum <= 0.6) {
			//do nothing
		} else if (lum <= 0.8) {
			fc = vec4(1.0-0.5*fc.r, 1.0-0.5*fc.g, 1.0-0.5*fc.b, 1.0);
		} else {
		 	fc = vec4(1.0, 1.0, 1.0, 1.0);
		}
		fragment_color = fc;
		//fragment_color = vec4(color, alpha);
	} else {
		fragment_color = vec4(texcolor.rgb, alpha);
	}
	//fragment_color = vec4(0.2, 0.2, 0.2, 1.0);
}
)zzz"
