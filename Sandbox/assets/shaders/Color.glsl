#type vertex
#version 460 core

uniform mat4 u_model;
uniform mat4 u_viewProjection;

layout (location = 0) in vec3 a_position;

void main()
{
	mat4 modelViewProjection = u_viewProjection * u_model;
	gl_Position = modelViewProjection * vec4(a_position, 1.0f);
}

#type fragment
#version 460 core

uniform vec4 u_color;

out vec4 f_color;

void main()
{
	f_color = u_color;
}
