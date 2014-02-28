#version 110

varying vec3 LightIntensity;
varying vec3 Position;
varying vec3 Normal;
varying vec2 TexCoord;

uniform vec4 LightPosition; // Light position in eye coords.
uniform vec3 Kd; // Diffuse reflectivity
uniform vec3 Ld; // Light source intensity

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	// Convert normal and position to eye coords
	vec3 tnorm = normalize( NormalMatrix * gl_Normal);
	vec4 eyeCoords = ViewMatrix * ModelMatrix * gl_Vertex;
	vec3 s = normalize(vec3(LightPosition - eyeCoords));
	
	// Pasamos las coordenadas de texturas a los FShaders
	TexCoord = gl_MultiTexCoord0.xy;

	// The diffuse shading equation
	LightIntensity =  Ld * Kd * max( dot( s, tnorm ), 0.0 );
			
	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * gl_Vertex;
}
