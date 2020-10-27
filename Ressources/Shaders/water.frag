#version 330 core

// Declaration des varyings
in vec2 var_texCoords;
in float var_insideWater;
// La sortie correspondant à la couleur du fragment
layout (location = 0) out vec4 out_fragColor;
// Declaration des uniforms
uniform sampler2D uni_texture; // La texture rendue à la passe précédente
uniform vec3 uni_waterColor; // Color of the water
uniform float uni_blendCoefficient; // How much color will be added, takes its value in[0,1] 

// Programme principal
vec3 blendWater(){
	vec3 initCol =  vec3(texture(uni_texture, var_texCoords));
	if(var_insideWater > 0){
		vec3 coeff = vec3(uni_blendCoefficient,uni_blendCoefficient,uni_blendCoefficient);
		return initCol*(uni_waterColor*coeff); 
	}
	return initCol;
}

void main()
{
	out_fragColor = vec4(blendWater(),1.0);
}