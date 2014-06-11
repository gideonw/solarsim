#version 150

in vec3 vert;
in vec2 vertTexCoord;
out vec2 fragTexCoord;


void main() {
    // does not alter the vertices at all
	mat4 window_scale = mat4(
							 vec4( 0.000975, 0.0, 0.0, 0.0),
							 vec4( 0.0, 0.000975, 0.0, 0.0),
							 vec4( 0.0, 0.0, 0.000975, 0.0),
							 vec4( 0.0, 0.0, 0.0, 1.0)
							 );
	
	// Pass the tex coord straight through to the fragment shader
    fragTexCoord = vertTexCoord;
	
    gl_Position = window_scale * vec4(vert, 1);
}