#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoords;
layout(location = 3) in float a_texIndex;
layout(location = 4) in float a_texTilingFactor;

uniform mat4 u_viewProjMat;

out vec4 v_color;
out vec2 v_texCoords;
out float v_texIndex;
out float v_texTilingFactor;

void main()
{
	v_color = a_color;
	v_texCoords = a_texCoords;
	v_texIndex = a_texIndex;
	v_texTilingFactor = a_texTilingFactor;
	gl_Position = u_viewProjMat * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

in vec4 v_color;
in vec2 v_texCoords;
in float v_texIndex;
in float v_texTilingFactor;

uniform sampler2D u_textures[32];

out vec4 color;

void main()
{
	color = texture(u_textures[int(v_texIndex)], v_texCoords * v_texTilingFactor) * v_color;
}