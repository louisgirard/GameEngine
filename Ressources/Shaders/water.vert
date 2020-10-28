#version 330 core

// position des sommets
layout (location = 0) in vec2 in_position;
// Coordonnées de texture associées au sommet
layout (location = 1) in vec2 in_texCoords;
//Varying associé a la présence dans l'eau
out float var_underWater;
out float var_insideWaterFromRight;
out float var_insideWaterFromLeft;
// Varying associé aux coordonnées de texture
out vec2 var_texCoords;

uniform float uni_waterHeight;
uniform float uni_waterLeftLimit;
uniform float uni_waterRightLimit;

void main()
{
	// Position inchangée
	gl_Position = vec4(in_position, 0.0,1.0);
	// Coordonnées de texture inchangées
	var_texCoords = in_texCoords.xy;
	// Check if the position is inside water or not
	var_underWater = in_position.y - uni_waterHeight;
	var_insideWaterFromRight =   in_position.x-uni_waterRightLimit;
	var_insideWaterFromLeft =uni_waterLeftLimit-in_position.x;
}