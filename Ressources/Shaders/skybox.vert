#version 330 core

// ----------
// The inputs
// ----------

// Vertex in local coordinate system
layout (location=0) in vec3 in_position;

// -----------
// The outputs
// -----------

// Texture coordinates
out vec3 var_textureCoordinates;


// ------------
// The uniforms
// ------------

// Projection Matrix
uniform mat4 uni_mat_projection;
// View Matrix
uniform mat4 uni_mat_view;

void main()
{

	gl_Position = uni_mat_projection * uni_mat_view * vec4(in_position, 1.0);

	// position = direction = Texture Coordinate
	var_textureCoordinates = in_position;
}