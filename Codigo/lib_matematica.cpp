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


// Calculo de punto en una curva utilizando el método de Bezier
// (implementación con algoritmo de Berstein).
// PRE: "t" es un valor entre 0 y 1 que define el parámetro de la curva (
// dependiendo de cual sea el valor se devolverá un cierto punto de dicha 
// curva, siendo 0 el punto de control inicial y 1 el punto de control final); 
// "p" es un puntero a un arreglo que contiene las coordenadas de los puntos 
// de control.
// POST: se devuelve el valor de la coordenada del punto sobre la curva.
float Matematica::bezier(float t, float p[])
{
	float punto = 0;

	punto += (-pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * p[0];
	punto += (3 * pow(t, 3) - 6 * pow(t, 2) + 3 * t) * p[1];
	punto += (-3 * pow(t, 3) + 3 * pow(t, 2)) * p[2];
	punto += (pow(t, 3)) * p[3];

	return punto;
}
