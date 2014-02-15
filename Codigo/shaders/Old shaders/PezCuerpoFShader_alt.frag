#version 110


varying vec3 LightIntensity;
varying vec3 Position;
varying vec3 Normal;
varying vec3 Tangent;
varying vec2 TexCoord;
varying vec2 NormalMapTexCoord;

uniform sampler2D Texture;
uniform sampler2D NormalMapTex;

void main()
{
	vec4 texColor = texture2D(Texture, TexCoord);
	vec4 texNM = texture2D(NormalMapTex, NormalMapTexCoord);
	// gl_FragColor = texColor * vec4(LightIntensity, 1.0);
	// gl_FragColor = texNM * vec4(LightIntensity, 1.0);
	gl_FragColor = mix(texColor, texNM, texNM.a) * vec4(LightIntensity, 1.0);
	// gl_FragColor = texColor * vec4(Color, 1.0);
	// gl_FragColor = vec4(((Normal / vec3(2.0)) + vec3(0.5)), 1.0);
}

