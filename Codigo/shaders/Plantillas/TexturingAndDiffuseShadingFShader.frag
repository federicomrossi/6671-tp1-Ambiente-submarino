#version 110

varying vec3 LightIntensity;
varying vec3 Position;
varying vec3 Normal;
varying vec2 TexCoord;

uniform sampler2D Tex1;

void main() 
{
	// gl_FragColor = texture2D( Tex1, TexCoord );

	vec4 texColor = texture2D( Tex1, TexCoord );
	gl_FragColor  = texColor * vec4 (LightIntensity, 1.0);
}
