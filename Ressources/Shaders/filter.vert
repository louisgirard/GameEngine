#version 330 core

// position des sommets
layout (location = 0) in vec2 in_position;
// Coordonnées de texture associées au sommet
layout (location = 1) in vec2 in_texCoords;
// Varying associé aux coordonnées de texture
out vec2 var_texCoords;

void main()
{
	// Position inchangée
	gl_Position = vec4(in_position, 0.0,1.0);
	// Coordonnées de texture inchangées
	var_texCoords = in_texCoords.xy;
}
