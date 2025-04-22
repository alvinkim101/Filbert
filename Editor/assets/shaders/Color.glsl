#type vertex
#version 460 core

uniform mat4 u_viewProjection;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

out vec4 v_color;

void main()
{
	gl_Position = u_viewProjection * vec4(a_position, 1.0f);

	v_color = a_color;
}

#type fragment
#version 460 core

in vec4 v_color;

out vec4 f_color;

void main()
{
	f_color = v_color;
}
