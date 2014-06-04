#version 150

uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in float starType;

out float starTypeOut;

void main() {
    // Pass the starType straight through to the fragment shader
    starTypeOut = starType;
	if(starType < 12)
	{
		gl_PointSize = 1.0f;
	} else
	{
		gl_PointSize = 3.0f;
	}
	mat4 window_scale = mat4(
							  vec4( 0.15, 0.0, 0.0, 0.0),
							  vec4( 0.0, 0.15, 0.0, 0.0),
							  vec4( 0.0, 0.0, 0.15, 0.0),
							  vec4( 0.0, 0.0, 0.0, 1.0)
							  );
    
    // Apply all matrix transformations to vert
    gl_Position = camera * window_scale * model * vec4(vert, 1);
}