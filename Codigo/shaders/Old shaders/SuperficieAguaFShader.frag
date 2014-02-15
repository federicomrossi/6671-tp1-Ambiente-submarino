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

uniform float FogMaxDist;
uniform float FogMinDist;
uniform vec3 FogColor;

uniform sampler2D Tex1;


vec3 ads()
{
	// vec3 n = normalize(Normal);
	vec3 s = normalize(LightPosition.xyz - Position.xyz);
	vec3 v = normalize(vec3(-Position));
	vec3 h = normalize(v+s);

	vec3 ambient = Ka * LightIntensity;
	vec3 diffuse = LightIntensity * Kd * max(0.0, dot(s, Normal));
	vec3 spec = LightIntensity * Ks * pow(max(0.0, dot(h, Normal)), Shininess);

	return ambient + diffuse + spec;
}

void main()
{
	float dist = abs(Position.z);
	// float dist = length( Position.xyz );
	float fogFactor = (FogMaxDist - dist) / (FogMaxDist - FogMinDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	vec3 shadeColor = ads();
	vec3 color = mix(FogColor, shadeColor, fogFactor);

	vec4 texColor = texture2D(Tex1, TexCoord);
	gl_FragColor =  texColor * vec4(color, 1.0);
}
