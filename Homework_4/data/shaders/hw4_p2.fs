#version 410 core

uniform sampler2D colorMap;
uniform sampler2D noiseMap;

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

void main(void)
{

	vec4 tex_color =  texture(colorMap, pass_TexCoord);
	
	vec2 noiseVec;
	noiseVec = normalize(texture(noiseMap, pass_TexCoord).xy);
//	noiseVec = (noiseVec * 3.0 - 2.0) * .1;
	noiseVec = (noiseVec * 5.0 - 0.0) * .01;
	color = pass_Color + texture(colorMap, pass_TexCoord + noiseVec);
	
//	color = pass_Color + tex_color;
}