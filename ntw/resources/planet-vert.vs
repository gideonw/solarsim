#version 330

uniform mat4 camera;
uniform mat4 model;

in vec3 vert;

void main() {
	mat4 window_scale = mat4(
							 vec4( 0.15, 0.0, 0.0, 0.0),
							 vec4( 0.0, 0.15, 0.0, 0.0),
							 vec4( 0.0, 0.0, 0.15, 0.0),
							 vec4( 0.0, 0.0, 0.0, 1.0)
							 );
	
    // Apply all matrix transformations to vert
    gl_Position = camera * window_scale * model * vec4(vert, 1);
}