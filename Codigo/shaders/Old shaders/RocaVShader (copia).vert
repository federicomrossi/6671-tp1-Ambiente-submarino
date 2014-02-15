#version 110

uniform vec3 LightIntensity;	// A, D, D intensity
uniform vec4 LightPosition;		// Light position in eye coords;

varying vec2 TexCoord;
varying vec3 LightDir;
varying vec3 ViewDir;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;



void main()
{
	// Transform normal and tangent to eye space
	vec3 norm = normalize(NormalMatrix * gl_Normal);
	vec3 tang = normalize(NormalMatrix * vec3(gl_Color));

	// Compute the binormal
	vec3 binormal = normalize(cross(norm, tang));

	// Matrix for transformation to tangent space
	mat3 toObjectLocal = mat3(tang.x, binormal.x, norm.x,
							  tang.y, binormal.y, norm.y,
							  tang.z, binormal.z, norm.z);

	// Get the position in eye coordinates
	vec3 pos = vec3(ModelMatrix * gl_Vertex);

	// Transform light dir. and view dir. to tangent space
	LightDir = normalize(toObjectLocal * (LightPosition.xyz - pos));
	ViewDir = toObjectLocal * normalize(-pos);

	// Pass along the texture coordinate
	TexCoord = gl_MultiTexCoord0.xy;
			
	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * gl_Vertex;
}


