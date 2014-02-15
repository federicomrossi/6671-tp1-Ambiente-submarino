#version 110

varying vec3 LightIntensity;
varying vec3 Position;
varying vec3 Normal;
varying vec2 TexCoord;

uniform sampler2D Tex1;



void main()
{
	vec4 texColor = texture2D( Tex1, TexCoord );
	gl_FragColor = texColor * vec4(LightIntensity, 1.0);

	// vec3 NormalColor = Normal / vec3(2.0) + vec3(0.5);
	// gl_FragColor = vec4(NormalColor, 1.0);
}