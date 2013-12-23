#version 110

varying vec3 Position;
varying vec3 Normal;
uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Kd;				// Diffuse reflectivity
uniform vec3 Ks;				// Specular reflectivity

uniform vec3 LightIntensity;
uniform vec4 LightPosition;		// Light position in eye coords;

uniform float Shininess;		// Specular shininess factor

varying vec2 TexCoord;
uniform sampler2D Tex1;

void main()
{
	vec4 texColor = texture2D( Tex1, TexCoord );

	vec3 n = normalize(Normal);
	vec3 s = normalize(vec3(LightPosition) - Position);
	vec3 v = normalize(vec3(-Position));
	vec3 r = reflect(-s, n);

	vec3 ads = LightIntensity * (Ka +
								 Kd * max(dot(s,n), 0.0) +
								 Ks * pow(max(dot(r,v), 0.0), Shininess));


	gl_FragColor = texColor * vec4(ads, 1.0);
	// gl_FragColor = vec4(((Normal / vec3(2.0)) + vec3(0.5)), 1.0);
}
