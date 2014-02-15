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

uniform float Tiempo;

//
// VARYINGS
//
varying vec3 Position;
varying vec3 Tangent;
varying vec3 Normal;
varying vec4 GlColor;
varying vec2 TexCoord;



void main()
{
	// Transform normal and tangent to eye space
	Normal = normalize(NormalMatrix * gl_Normal);
	Tangent = normalize(NormalMatrix * vec3(gl_Color));
	GlColor = gl_Color;

	// Get the position in eye coordinates
	Position = vec3(ModelMatrix * gl_Vertex);

	// Pass along the texture coordinate
	TexCoord = gl_MultiTexCoord0.xy;

	// Calculamos para dar movimiento
	vec4 aux = gl_Vertex;
	aux.x = aux.x + 0.07 * exp(aux.z) * cos(0.15 * Tiempo) * sin(0.5*aux.z);
	aux.y = aux.y + 0.07 * exp(aux.z) * cos(0.15 * Tiempo) * sin(0.5*aux.z);
			
	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aux;
}