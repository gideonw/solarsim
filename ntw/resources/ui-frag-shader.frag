#version 150

uniform sampler2D tex; //this is the texture
in vec2 fragTexCoord; //this is the texture coord

out vec4 finalColor;

void main() {
    //set every drawn pixel to white
    //finalColor = vec4(1.0, 1.0, 1.0, 0.40);
	
	finalColor = texture(tex, fragTexCoord);
}