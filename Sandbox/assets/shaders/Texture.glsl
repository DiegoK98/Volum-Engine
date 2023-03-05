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
	// This awful thing is here because, in some devices, indexing can only be done with a dynamically uniform integral expression.
	// Not doing so results in quads rendering black instead of rendering textures
	vec4 texColor = v_color;
	switch (int(v_texIndex))
	{
		case 0: texColor *= texture(u_textures[0], v_texCoords * v_texTilingFactor); break;
		case 1: texColor *= texture(u_textures[1], v_texCoords * v_texTilingFactor); break;
		case 2: texColor *= texture(u_textures[2], v_texCoords * v_texTilingFactor); break;
		case 3: texColor *= texture(u_textures[3], v_texCoords * v_texTilingFactor); break;
		case 5: texColor *= texture(u_textures[5], v_texCoords * v_texTilingFactor); break;
		case 6: texColor *= texture(u_textures[6], v_texCoords * v_texTilingFactor); break;
		case 7: texColor *= texture(u_textures[7], v_texCoords * v_texTilingFactor); break;
		case 8: texColor *= texture(u_textures[8], v_texCoords * v_texTilingFactor); break;
		case 9: texColor *= texture(u_textures[9], v_texCoords * v_texTilingFactor); break;
		case 10: texColor *= texture(u_textures[10], v_texCoords * v_texTilingFactor); break;
		case 11: texColor *= texture(u_textures[11], v_texCoords * v_texTilingFactor); break;
		case 12: texColor *= texture(u_textures[12], v_texCoords * v_texTilingFactor); break;
		case 13: texColor *= texture(u_textures[13], v_texCoords * v_texTilingFactor); break;
		case 14: texColor *= texture(u_textures[14], v_texCoords * v_texTilingFactor); break;
		case 15: texColor *= texture(u_textures[15], v_texCoords * v_texTilingFactor); break;
		case 16: texColor *= texture(u_textures[16], v_texCoords * v_texTilingFactor); break;
		case 17: texColor *= texture(u_textures[17], v_texCoords * v_texTilingFactor); break;
		case 18: texColor *= texture(u_textures[18], v_texCoords * v_texTilingFactor); break;
		case 19: texColor *= texture(u_textures[19], v_texCoords * v_texTilingFactor); break;
		case 20: texColor *= texture(u_textures[20], v_texCoords * v_texTilingFactor); break;
		case 21: texColor *= texture(u_textures[21], v_texCoords * v_texTilingFactor); break;
		case 22: texColor *= texture(u_textures[22], v_texCoords * v_texTilingFactor); break;
		case 23: texColor *= texture(u_textures[23], v_texCoords * v_texTilingFactor); break;
		case 24: texColor *= texture(u_textures[24], v_texCoords * v_texTilingFactor); break;
		case 25: texColor *= texture(u_textures[25], v_texCoords * v_texTilingFactor); break;
		case 26: texColor *= texture(u_textures[26], v_texCoords * v_texTilingFactor); break;
		case 27: texColor *= texture(u_textures[27], v_texCoords * v_texTilingFactor); break;
		case 28: texColor *= texture(u_textures[28], v_texCoords * v_texTilingFactor); break;
		case 29: texColor *= texture(u_textures[29], v_texCoords * v_texTilingFactor); break;
		case 30: texColor *= texture(u_textures[30], v_texCoords * v_texTilingFactor); break;
		case 31: texColor *= texture(u_textures[31], v_texCoords * v_texTilingFactor); break;
	}
	color = texColor;
}