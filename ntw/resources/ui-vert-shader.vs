#version 150

in vec3 vert;

void main() {
    // does not alter the vertices at all
	mat4 window_scale = mat4(
							 vec4( 0.000975, 0.0, 0.0, 0.0),
							 vec4( 0.0, 0.000975, 0.0, 0.0),
							 vec4( 0.0, 0.0, 0.000975, 0.0),
							 vec4( 0.0, 0.0, 0.0, 1.0)
							 );
	
    gl_Position = window_scale * vec4(vert, 1);
}