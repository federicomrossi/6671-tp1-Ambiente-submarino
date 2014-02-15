#version 110


uniform sampler2D Texture;
uniform sampler2D NormalMapTex;

uniform vec3 LightIntensity;	// A, D, D intensity
uniform vec4 LightPosition;		// Light position in eye coords;

uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor

varying vec2 TexCoord;

varying vec3 Normal;
varying vec3 Tangent;
varying vec3 n;
varying vec3 t;
varying vec3 pos;

vec3 LightDir;
vec3 ViewDir;


// varying vec3 ReflectDir;		// The direction of the reflected ray
// uniform samplerCube CubeMapTex;	// The cube map



vec3 phongModel(vec3 norm, vec3 diffR) {
	vec3 r = reflect(-LightDir, norm);
	vec3 ambient = LightIntensity * Ka;
	float sDotN = max(dot(LightDir, norm), 0.0);
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

	vec3 binormal;
	mat3 toObjectLocal;


	if(gl_FrontFacing) {
		// Compute the binormal
		binormal = normalize(cross(n, t)) * gl_Color.w;

		// Matrix for transformation to tangent space
		toObjectLocal = mat3(t.x, binormal.x, n.x,
							 t.y, binormal.y, n.y,
							 t.z, binormal.z, n.z);
	} else {
		// Compute the binormal
		binormal = normalize(cross(n, t)) * gl_Color.w;

		// Matrix for transformation to tangent space
		toObjectLocal = mat3(t.x, binormal.x, n.x,
							 t.y, binormal.y, n.y,
							 t.z, binormal.z, n.z);
	}
	
	// Transform light dir. and view dir. to tangent space
	LightDir = normalize(toObjectLocal * (LightPosition.xyz - pos));
	ViewDir = toObjectLocal * normalize(-pos);

	gl_FragColor =  vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
	// gl_FragColor = texColor;
	// gl_FragColor = vec4(Tangent, 1.0);
}
