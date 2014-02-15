#version 110

varying vec3 Position;
varying vec3 Normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

varying vec2 TexCoord;
uniform float TIMEEE;


void main()
{
	Normal = normalize(NormalMatrix * gl_Normal);
	Position = vec3(ModelMatrix * gl_Vertex);

	// Pasamos las coordenadas de texturas a los FShaders
	TexCoord = gl_MultiTexCoord0.xy;

	vec4 aux = gl_Vertex;
	aux.x = aux.x + 0.07 * exp(aux.z) * cos(0.15*TIMEEE) * sin(0.5*aux.z);
	aux.y = aux.y + 0.07 * exp(aux.z) * cos(0.15*TIMEEE) * sin(0.5*aux.z);
			
	// Convert position to clip coordinates and pass along
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aux;
}

