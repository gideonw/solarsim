#version 330

in float wireo;

out vec4 finalColor;

void main() {
	if(wireo > 0)
		finalColor = vec4(0.0, 0.0, 0.0, 1.0);
	else
		finalColor = vec4(0.5, 0.8, 1.0, 1.0);
}