#version 110

varying vec3 LightIntensity;
varying vec3 Position;
varying vec3 Normal;
varying vec2 TexCoord;

// vec4 tLightPosition;
// vec3 tLightIntensity;
// float fogMaxDist;
// float fogMinDist;
// vec3 fogColor;



uniform sampler2D Tex1;



void main()
{
	vec4 texColor = texture2D( Tex1, TexCoord );
	gl_FragColor = texColor * vec4(LightIntensity, 1.0);

	// vec3 NormalColor = Normal / vec3(2.0) + vec3(0.5);
	// gl_FragColor = vec4(NormalColor, 1.0);



	// float dist = abs(Position.z);
	// float fogFactor = (fogMaxDist - dist) / (fogMaxDist - fogMinDist);
	// fogFactor = clamp(fogFactor, 0.0, 1.0);

	// vec3 s = normalize(tLightPosition.xyz - Position.xyz);
	// vec3 v = normalize(vec3(-Position));
	// vec3 h = normalize(v+s);
	// vec3 diffuse = tLightIntensity * Kd * max(0.0, dot(s, Normal));
	// vec3 spec = tLightIntensity * Ks * pow(max(0.0, dot(h, Normal)), Shininess)

	// vec3 shadeColor = 
	// vec3 color = mix(fogColor, shadeColor, fogFactor);
	// gl_FragColor = vec4(color, 1.0);



}