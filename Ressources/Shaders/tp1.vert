#version 330

//Definition des attributes
in vec3 in_position;
in vec3 in_colors;
// Définition des varying
out vec4 var_colors;
// Définition des uniforms
uniform mat4 uni_mat_view;
uniform mat4 uni_mat_model;
uniform mat4 uni_mat_projection;


void main()
{
	gl_Position =  uni_mat_projection *uni_mat_view * uni_mat_model * vec4(in_position,1.0);
	var_colors = vec4(in_colors, 1.0);

}