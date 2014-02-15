#version 110

//
// UNIFORMS
//
uniform sampler2D Texture;
uniform sampler2D NormalMapTex;

uniform vec3 LightIntensity;	// A, D, D intensity
uniform vec4 LightPosition;		// Light position in eye coords;

uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor

uniform float FogMaxDist;
uniform float FogMinDist;
uniform vec3 FogColor;

//
// VARYINGS
//
varying vec3 Position;
varying vec3 Tangent;
varying vec3 Binormal;
varying vec3 Normal;
varying mat3 toObjectLocal;

varying vec2 TexCoord;

//
// GLOBAL VARIABLES
//
vec3 LightDir;
vec3 ViewDir;



vec3 phongModel(vec3 norm, vec3 diffR) {
	vec3 r = reflect(-LightDir, norm);
	vec3 ambient = LightIntensity * Ka;
	float sDotN = max(dot(LightDir, norm), 0.0);
	vec3 diffuse = LightIntensity * diffR * sDotN;
	vec3 spec = vec3(0.0);

	if(sDotN > 0.0)
		spec = LightIntensity * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess);

	return spec + diffuse + ambient;
}



void main()
{
	// Calcule of the fog factors to apply 
	// float dist = abs(Position.z);
	float dist = length( Position.xyz );
	float fogFactor = (FogMaxDist - dist) / (FogMaxDist - FogMinDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	// Lookup the normal from the normal map
	vec4 nm = texture2D(NormalMapTex, TexCoord);

	// The color texture is used as diffuse reflectivity
	vec4 texColor = texture2D(Texture, TexCoord);

	// Pass coordinates (0,2) to (-1,1)
	nm = nm * 2.0 - 1.0;
	texColor = texColor * 2.0 - 1.0;

	// Pass the normal of normal map texture to tangent space (TBN)
	vec3 nmToTBN;
	nmToTBN.x = Tangent.x * nm.y + Binormal.x * nm.x + Normal.x * nm.z;
	nmToTBN.y = Tangent.y * nm.y + Binormal.y * nm.x + Normal.y * nm.z;
	nmToTBN.z = Tangent.z * nm.y + Binormal.z * nm.x + Normal.z * nm.z;

	// Transform light dir. and view dir. to tangent space
	LightDir = normalize(LightPosition.xyz - Position);
	ViewDir = toObjectLocal * normalize(-Position);

	vec3 shadeColor = phongModel(nmToTBN, texColor.rgb);
	vec3 color = mix(FogColor, shadeColor, fogFactor);

	gl_FragColor =  vec4(color, 1.0);

	// # DEBUG
	// gl_FragColor =  vec4(phongModel(Normal.xyz, texColor.rgb), 1.0);
	// gl_FragColor = texColor;
	// gl_FragColor = vec4(Normal, 1.0);
	// # END DEBUG
}
