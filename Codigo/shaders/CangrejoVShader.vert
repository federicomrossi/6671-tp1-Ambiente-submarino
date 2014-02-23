#version 110

//
// UNIFORMS
//
uniform vec3 LightIntensity;		// A, D, D intensity
uniform vec4 LightPosition;			// Light position in eye coords;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

//
// VARYINGS
//
varying vec3 Position;
varying vec3 Tangent;
varying vec3 Binormal;
varying vec3 Normal;

varying vec2 TexCoord;



void main()
{
	// Transform normal and tangent to eye space
	Normal = normalize(NormalMatrix * gl_Normal);
	Tangent = normalize(NormalMatrix * vec3(gl_Color));
	Binormal = normalize(cross(Normal, Tangent)) * gl_Color.w;

	// Get the position in eye coordinates
	Position = vec3(ModelMatrix * gl_Vertex);

	// Pass along the texture coordinate
	TexCoord = gl_MultiTexCoord0.xy;

	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * gl_Vertex;
}