#version 330

out vec4 out_Color;
in vec4 var_colors;

vec3 color_red()
{
	return vec3(1.0, 0, 0);
}

void main()
{
	//out_Color = vec4(color_red(), 1.0);
	out_Color = var_colors;
}