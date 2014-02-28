#version 110

attribute vec3 VertexPosition;

varying vec4 Color;

void main()
{
	Color = gl_Color;
	gl_Position = vec4( VertexPosition, 1.0);
}