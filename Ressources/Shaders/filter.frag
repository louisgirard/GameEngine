#version 330 core

// Declaration des varyings
in vec2 var_texCoords;
// La sortie correspondant à la couleur du fragment
layout (location = 0) out vec4 out_fragColor;
// Declaration des uniforms
uniform sampler2D uni_texture; // La texture rendue à la passe précédente
//uniform mat3 uni_kernel; // Le noyau à appliquer
//uniform vec2 uni_offset; // L’offset utilisé pour le voisinage

uniform float uni_degrade;
uniform float uni_indice;
// Programme principal


vec3 celShading(){
	vec3 ic = vec3(texture(uni_texture, var_texCoords));
	float n = length(ic)/sqrt(3);
	float f = pow(round(pow(n,uni_indice)*uni_degrade)/uni_degrade,1/uni_indice);
	return (ic/n) * f ;
}



void main()
{

	out_fragColor = vec4(celShading(),1.0);
}