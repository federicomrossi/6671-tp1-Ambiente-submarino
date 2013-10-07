/*
 * CLASS LIB_FACTORIAL
 */


#ifndef LIB_MATEMATICA_H
#define LIB_MATEMATICA_H


class Matematica
{
public:
	
	// Método que calcula el factorial del número n.
	static int factorial(int n);

	// Cálculo de la cantidad de combinaciones de m elementos tomados de a n.
	static int combinaciones(int m, int n);

	// Calculo de punto en una curva utilizando el método de Bezier
	// (implementación con algoritmo de Berstein).
	// PRE: "n" es el grado de polinomio a utilizar; "t" es un valor entre 0 y
	// 1 que define el parámetro de la curva (dependiendo de cual sea el valor 
	// se devolverá un cierto punto de dicha curva, siendo 0 el punto de 
	// control inicial y 1 el punto de control final); "p" es un puntero a un 
	// arreglo que contiene las coordenadas de los puntos de control.
	// POST: se devuelve el valor de la coordenada del punto sobre la curva.
	static float bezier(float t, float *p);
};


#endif