#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;


uniform sampler2D ourTexture;
void main()
{
	//FragColor = texture(ourTexture,TexCoord);
	FragColor = mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.5);
}