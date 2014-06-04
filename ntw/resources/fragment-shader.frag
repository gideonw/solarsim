#version 150

in float starTypeOut;

out vec4 finalColor;

void main() {
    //note: the texture function was called texture2D in older versions of GLSL
    //finalColor = texture(tex, fragTexCoord);
	
	if(starTypeOut == 1 || starTypeOut == 2 ){
		//class O
		finalColor = vec4(0.33, 0.65, 0.9, 1.0);
	} else if(starTypeOut == 3 || starTypeOut == 4 ){
		//class B
		finalColor = vec4(0.42, 0.43, 0.66, 1.0);
	} else if(starTypeOut == 5 || starTypeOut == 6){
		//class A
		finalColor = vec4(0.81, 0.97, 1.0, 1.0);
	} else if(starTypeOut == 7 || starTypeOut == 8){
		//class F
		finalColor = vec4(1.0, 1.0, 0.89, 1.0);
	} else if(starTypeOut == 9 || starTypeOut == 10){
		//class G
		finalColor = vec4(1.0, 0.95, 0.68, 1.0);
	} else if(starTypeOut == 11 || starTypeOut == 12){
		//class K
		finalColor = vec4(1.0, 0.8, 0.5, 1.0);
	} else if(starTypeOut == 13 || starTypeOut == 14){
		//class M
		finalColor = vec4(0.95, 0.47, 0.31, 1.0);
	} else {
		//orange filler
		finalColor = vec4(1.0, 0.64, 0.41, 1.0);
	}

}