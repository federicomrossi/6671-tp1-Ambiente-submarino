/*
 * CLASS LIB_FACTORIAL
 */

#include <iostream>
#include <math.h>
#include "lib_matematica.h"




// Método que calcula el factorial del número n.
int Matematica::factorial(int n)
{
	// Caso base
	if(n <= 1) return 1;

	// Caso recursivo
	return(n * Matematica::factorial(n-1));
}


// Cálculo de la cantidad de combinaciones de m elementos tomados de a n.
int Matematica::combinaciones(int m, int n)
{
	return(Matematica::factorial(m) / (Matematica::factorial(m-n) * 
		Matematica::factorial(n)));
}


// Método que calcula el producto vectorial entre dos vectores
// tridimensionales.
// PRE: 'u' y 'v' son los dos vectores que se deben multiplicar.
// POST: se devuelve un vector normal a 'u' y 'v';
float* Matematica::productoVectorial(float u[3], float v[3])
{
	static float n[3];

	n[0] = u[1] * v[2] - v[1] * u[2];
	n[1] = -(u[0] * v[2] - v[0] * u[2]);
	n[2] = u[0] * v[1] - v[0] * u[1];

	return n;
}


// Calculo de punto en una curva utilizando el método de Bezier
// (implementación con algoritmo de Berstein).
// PRE: "t" es un valor entre 0 y 1 que define el parámetro de la curva (
// dependiendo de cual sea el valor se devolverá un cierto punto de dicha 
// curva, siendo 0 el punto de control inicial y 1 el punto de control final); 
// "p" es un puntero a un arreglo que contiene las coordenadas de los puntos 
// de control.
// POST: se devuelve el valor de la coordenada del punto sobre la curva.
float Matematica::curvaBezier(float t, float p[4])
{
	float punto = 0;

	punto += (-pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * p[0];
	punto += (3 * pow(t, 3) - 6 * pow(t, 2) + 3 * t) * p[1];
	punto += (-3 * pow(t, 3) + 3 * pow(t, 2)) * p[2];
	punto += (pow(t, 3)) * p[3];

	return punto;
}


// Cálculo de punto en una superficie utilizando el método de Bezier.
float Matematica::superficieBezier(float u, float v, float p[4][4])
{
	float Bu[4];
	float Bv[4];

	Bu[0] = -pow(u, 3) + 3 * pow(u, 2) - 3 * u + 1;
	Bu[1] = 3 * pow(u, 3) - 6 * pow(u, 2) + 3 * u;
	Bu[2] = -3 * pow(u, 3) + 3 * pow(u, 2);
	Bu[3] = pow(u, 3);

	Bv[0] = -pow(v, 3) + 3 * pow(v, 2) - 3 * v + 1;
	Bv[1] = 3 * pow(v, 3) - 6 * pow(v, 2) + 3 * v;
	Bv[2] = -3 * pow(v, 3) + 3 * pow(v, 2);
	Bv[3] = pow(v, 3);

	float punto = 0;
	
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 3; j++)
		{
			punto += Bu[i] * Bv[j] * p[i][j];
		}
	}

	return punto;
}


// 
float Matematica::curvaBSpline(float u, float p[3])
{
	float punto = 0;

	punto += (0.5 * pow(1-u, 2)) * p[0];
	punto += (0.5 * (1-u) * u) * p[1];
	punto += (0.5 * pow(u, 2)) * p[2];

	return punto;	
}
