#type vertex
#version 460 core

uniform mat4 u_viewProjection;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_textureCoordinates;
layout (location = 3) in int a_textureSlot;

out vec4 v_color;
out vec2 v_textureCoordinates;
out int v_textureSlot;

void main()
{
	gl_Position = u_viewProjection * vec4(a_position, 1.0f);

	v_color = a_color;
	v_textureCoordinates = a_textureCoordinates;
	v_textureSlot = a_textureSlot;
}

#type fragment
#version 460 core

uniform sampler2D u_textures[32];

in vec4 v_color;
in vec2 v_textureCoordinates;
in flat int v_textureSlot;

out vec4 f_color;

void main()
{
	f_color = texture(u_textures[v_textureSlot], v_textureCoordinates) * v_color;
}
