#version 110

varying vec3 Position;
varying vec3 Normal;
varying vec2 TexCoord;

uniform vec3 LightIntensity;
uniform vec4 LightPosition;		// Light position in eye coords;
uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Kd;				// Diffuse reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor

uniform sampler2D Tex1;


vec3 ads()
{
	vec3 n = normalize(Normal);
	vec3 s = normalize(vec3(LightPosition) - Position);
	vec3 v = normalize(vec3(-Position));
	vec3 r = reflect(-s, n);
	return (LightIntensity * (Ka + 
							  Kd * max(dot(s, n), 0.0) +
							  Ks * pow(max(dot(r, v), 0.0), Shininess)));
}

void main()
{
	vec4 texColor = texture2D(Tex1, TexCoord);
	gl_FragColor = texColor * vec4(ads(), 1.0);
}
