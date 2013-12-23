#version 110


varying vec3 LightIntensity;

uniform vec4 LightPosition;		// Light position in eye coords;
uniform vec3 La;				// Ambient light intensity
uniform vec3 Ld;				// Diffuse light intensity
uniform vec3 Ls;				// Specular light intensity


uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Kd;				// Diffuse reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor


varying vec2 TexCoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 Tangent;

void main()
{
	// Convert normal and position to eye coords
	vec3 tnorm = normalize( NormalMatrix * gl_Normal);
	vec4 eyeCoords = ModelMatrix * gl_Vertex;
	vec3 s = normalize(vec3(LightPosition - eyeCoords));
	vec3 v = normalize(-eyeCoords.xyz);
	vec3 r = reflect(-s, tnorm);
	vec3 ambient = La * Ka;
	float sDotN = max(dot(s,tnorm), 0.0);
	vec3 diffuse = Ld * Kd * sDotN;
	vec3 spec = vec3(0.0);

	if(sDotN > 0.0)
		spec = Ls * Ks * pow(max(dot(r,v), 0.0), Shininess);

	LightIntensity = ambient + diffuse + spec;

	// Pasamos las coordenadas de texturas a los FShaders
	TexCoord = gl_MultiTexCoord0.xy;
			
	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * gl_Vertex;
}
