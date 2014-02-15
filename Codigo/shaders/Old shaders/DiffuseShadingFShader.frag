#version 110

varying vec3 LightIntensity;
varying vec3 Normal;

void main()
{
	gl_FragColor = vec4(LightIntensity, 1.0);
	// float z = (gl_FragCoord.z /gl_FragCoord.w) / 100000.0;
	// float fogFactor = exp2(-1.0 * z * z);
	// fogFactor = clamp(fogFactor, 0.0, 1.0);
	// gl_FragColor = mix(vec4(0.1,0.1,0.2,1.0), gl_FragColor, fogFactor);
	// gl_FragColor = vec4(((Normal / vec3(2.0)) + vec3(0.5)), 1.0);
}