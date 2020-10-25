#version 330 core
#define M_PI 3.1415926535897932384626433832795

// Declaration des varyings
in vec2 var_texCoords;
// La sortie correspondant à la couleur du fragment
layout (location = 0) out vec4 out_fragColor;
// Declaration des uniforms
uniform sampler2D uni_texture; // La texture rendue à la passe précédente
uniform sampler2D uni_depthTexture; 
uniform int uni_width; // Largeur de la gaussienne

void main(){

	vec4 result = vec4(0.0, 0.0, 0.0, 0.0);
	vec2 sizeText = textureSize(uni_texture,0);
	float gaussCoeff = 0;
	float sommeCoeff = 0;
	int xCorr = 0;
	int yCorr = 0;
	float newX = 0;
	float newY = 0;
	vec2 newCoordinate = vec2(0.0);
	float near = texture(uni_depthTexture, vec2(0.5, 0.5)).z;
	float depth = texture(uni_depthTexture, var_texCoords).z;

	float width = uni_width* clamp((depth-near) / (1.0-near),0.0,1.0) ;
	if(depth>near){
		for(int x=0; x<width; ++x) {
			for(int y=0; y<width; ++y) {
				xCorr =x-int(width/2);
				yCorr =y-int(width/2);
				gaussCoeff=exp((pow(xCorr,2)+pow(y,2))/ pow(width,2))/(2*M_PI*width);
				sommeCoeff += gaussCoeff;
				newX = var_texCoords.x + xCorr/sizeText.x;
				newY = var_texCoords.y + yCorr/sizeText.y;
				newCoordinate = vec2(newX, newY); 
				result += gaussCoeff*texture(uni_texture, newCoordinate);
			}
		}
		out_fragColor = result/sommeCoeff;
		//out_fragColor = texture(uni_depthTexture, var_texCoords);
	}
	else{
		out_fragColor = texture(uni_texture, var_texCoords);
	}
	
}