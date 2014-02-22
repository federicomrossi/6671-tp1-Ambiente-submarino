#version 110

varying vec3 Position;
varying vec3 Normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform float Tiempo;

varying vec2 TexCoord;


void main()
{
	Normal = normalize(NormalMatrix * gl_Normal);
	Position = vec3(ModelMatrix * gl_Vertex);

	// Pasamos las coordenadas de texturas a los FShaders
	TexCoord = gl_MultiTexCoord0.xy;

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * gl_Vertex;
}