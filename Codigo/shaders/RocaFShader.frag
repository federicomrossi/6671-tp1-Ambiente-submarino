#version 110

varying vec2 TexCoord;
varying vec3 LightDir;
varying vec3 ViewDir;

uniform sampler2D Texture;
uniform sampler2D NormalMapTex;

uniform vec3 LightIntensity;	// A, D, D intensity
uniform vec4 LightPosition;		// Light position in eye coords;

uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor



vec3 phongModel(vec3 norm, vec3 diffR) {
	vec3 r = reflect(-LightDir, norm);
	vec3 ambient = LightIntensity * Ka;
	float sDotN = max(dot(LightDir, norm), 1.0);
	vec3 diffuse = LightIntensity * diffR * sDotN;
	vec3 spec = vec3(0.0);

	if(sDotN > 0.0)
		spec = LightIntensity * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess);

	return ambient + diffuse + spec;
}



void main()
{
	// Lookup the normal from the normal map
	vec4 normal = texture2D(NormalMapTex, TexCoord);

	// The color texture is used as diffuse reflectivity
	vec4 texColor = texture2D(Texture, TexCoord);

	gl_FragColor =  vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
	// gl_FragColor = texColor;
	// gl_FragColor = normal;
	// gl_FragColor = vec4(LightIntensity, 1.0);
}
