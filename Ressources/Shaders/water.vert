#version 330 core

// position des sommets
layout (location = 0) in vec2 in_position;
// Coordonn�es de texture associ�es au sommet
layout (location = 1) in vec2 in_texCoords;
//Varying associ� a la pr�sence dans l'eau
out float var_insideWater;
// Varying associ� aux coordonn�es de texture
out vec2 var_texCoords;

uniform float uni_waterHeight;
/*uniform float uni_waterLeftLimit;
uniform float uni_waterRightLimit;*/

void main()
{
	// Position inchang�e
	gl_Position = vec4(in_position, 0.0,1.0);
	// Coordonn�es de texture inchang�es
	var_texCoords = in_texCoords.xy;
	// Check if the position is inside water or not
	/*&& (in_position.x-uni_waterLeftLimit <0)  && (in_position.x-uni_waterLeftLimit > 0)*/
	if( (in_position.y - uni_waterHeight) <0){
		var_insideWater = 1;
	}


	
	
}