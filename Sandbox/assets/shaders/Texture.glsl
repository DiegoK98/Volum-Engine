#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;

uniform mat4 u_viewProjMat;
uniform mat4 u_modelMat;

out vec2 v_texCoords;

void main()
{
	v_texCoords = a_texCoords;
	gl_Position = u_viewProjMat * u_modelMat * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

in vec2 v_texCoords;

uniform vec4 u_color;
uniform float u_tilingFactor;
uniform sampler2D u_texture;

out vec4 color;

void main()
{
	color = texture(u_texture, v_texCoords * u_tilingFactor) * u_color;
}