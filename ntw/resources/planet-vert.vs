#version 330

uniform mat4 camera;
uniform mat4 model;

uniform float wire;

out float wireo;

in vec3 vert;

void main() {
	
	gl_PointSize = 10.0f;
	wireo = wire;
	
	mat4 window_scale = mat4(
							 vec4( 150, 0.0, 0.0, 0.0),
							 vec4( 0.0, 150, 0.0, 0.0),
							 vec4( 0.0, 0.0, 150, 0.0),
							 vec4( 0.0, 0.0, 0.0, 1.0)
							 );
	
    // Apply all matrix transformations to vert
    gl_Position = camera * model * vec4(vert, 1);
	//gl_Position = camera * window_scale * model * vec4(vert, 1);
}