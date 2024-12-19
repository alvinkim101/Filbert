#type vertex
#version 460 core

uniform mat4 u_model;
uniform mat4 u_viewProjection;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_textureCoordinates;

out vec2 v_textureCoordinates;

void main()
{
	mat4 modelViewProjection = u_viewProjection * u_model;
	gl_Position = modelViewProjection * vec4(a_position, 1.0f);

	v_textureCoordinates = a_textureCoordinates;
}

#type fragment
#version 460 core

uniform sampler2D u_texture;

in vec2 v_textureCoordinates;

out vec4 f_color;

void main()
{
	f_color = texture(u_texture, v_textureCoordinates);
}
