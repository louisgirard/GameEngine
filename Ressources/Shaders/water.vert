#version 330 core

// position des sommets
layout (location = 0) in vec2 in_position;
// Coordonn�es de texture associ�es au sommet
layout (location = 1) in vec2 in_texCoords;
//Varying associ� a la pr�sence dans l'eau
out float var_underWater;
out float var_insideWaterFromRight;
out float var_insideWaterFromLeft;
// Varying associ� aux coordonn�es de texture
out vec2 var_texCoords;

uniform float uni_waterHeight;
uniform float uni_waterLeftLimit;
uniform float uni_waterRightLimit;

void main()
{
	// Position inchang�e
	gl_Position = vec4(in_position, 0.0,1.0);
	// Coordonn�es de texture inchang�es
	var_texCoords = in_texCoords.xy;
	// Check if the position is inside water or not
	var_underWater = in_position.y - uni_waterHeight;
	var_insideWaterFromRight =   in_position.x-uni_waterRightLimit;
	var_insideWaterFromLeft =uni_waterLeftLimit-in_position.x;
}