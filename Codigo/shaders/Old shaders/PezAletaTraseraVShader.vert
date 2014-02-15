#version 110

uniform vec3 LightIntensity;		// A, D, D intensity
uniform vec4 LightPosition;			// Light position in eye coords;

varying vec2 TexCoord;
varying vec3 LightDir;
varying vec3 ViewDir;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

varying vec3 Normal;
varying vec3 Tangent;
varying vec3 n;
varying vec3 t;
varying vec3 pos;

uniform float Tiempo;

// varying vec3 ReflectDir;			// The direction of the reflected ray


void main()
{
	// Normal = gl_Normal;
	Tangent = vec3(gl_Color);

	// Transform normal and tangent to eye space
	n = normalize(NormalMatrix * gl_Normal);
	t = normalize(NormalMatrix * vec3(gl_Color));
	Normal = n;

	// Get the position in eye coordinates
	pos = vec3(ModelMatrix * gl_Vertex);

	// Pass along the texture coordinate
	TexCoord = gl_MultiTexCoord0.xy;

	vec4 aux = gl_Vertex;
	aux.x = aux.x + 0.2 * exp(aux.y) * cos(25.0*Tiempo) * sin(aux.y);
			
	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aux;
}

