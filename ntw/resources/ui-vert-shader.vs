#version 330

in vec3 vert;
in vec2 vertTexCoord;
out vec2 fragTexCoord;

void main() {
	// Pass the tex coord straight through to the fragment shader
    fragTexCoord = vertTexCoord;
	
	vec3 disp = vec3(vert.x, vert.y, vert.z);
	
	//disp.xy *= 2;
	disp.x = (disp.x - 1024)/1024;
	disp.y = (768 - disp.y)/768;
	
    gl_Position = vec4(disp, 1);
}