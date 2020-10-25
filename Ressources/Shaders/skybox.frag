#version 330 core

// ----------
// The inputs
// ----------

// Texture coordinates
in vec3  var_textureCoordinates;


// -----------
// The outputs
// -----------

layout (location=0)  out vec4 out_Fragcolor;


// ------------
// The uniforms
// ------------

//Skybox
uniform samplerCube uni_skybox;

void main()
{	
	out_Fragcolor = texture(uni_skybox, normalize(var_textureCoordinates));
}
