/*
 * CLASS LIB_MATEMATICA
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

	// Método que calcula el producto vectorial entre dos vectores
	// tridimensionales.
	// PRE: 'u' y 'v' son los dos vectores que se deben multiplicar.
	// POST: se devuelve un vector normal a 'u' y 'v';
	static float* productoVectorial(float u[3], float v[3]);

	// Método que normaliza un vector de 3 dimensiones
	static float* normalizar(float n[3]);

	// Función que devuelve un numero aleatorio entre "min" y "max"
	static float numeroAleatorio(float min, float max);

	// Cálculo de punto en una curva utilizando el método de Bezier
	// (implementación con algoritmo de Berstein).
	// PRE: "n" es el grado de polinomio a utilizar; "t" es un valor entre 0 y
	// 1 que define el parámetro de la curva (dependiendo de cual sea el valor 
	// se devolverá un cierto punto de dicha curva, siendo 0 el punto de 
	// control inicial y 1 el punto de control final); "p" es un puntero a un 
	// arreglo que contiene las coordenadas de los puntos de control.
	// POST: se devuelve el valor de la coordenada del punto sobre la curva.
	static float curvaBezier(float t, float p[4]);

	// Cálculo de los vectores tangente (t), binormal (b) y normal (n)
	// correspondientes a un punto de la curva de Bezier dado por el valor
	// del parámetro t.
	static void curvaBezierVectores(float u, float px[4], float py[4], 
		float pz[4], float t[3], float b[3], float n[3]);

	// Cálculo del vector tangente (t) correspondiente a un punto de la curva
	// de Bezier dado por el valor del parametro u. 
	static void vectorTangenteCurvaBezier(float u, float px[4], float py[4], 
		float pz[4], float t[3]);

	// Cálculo de punto en una superficie utilizando el método de Bezier.
	static float superficieBezier(float u, float v, float p[4][4]);

	// Calculo de punto en una curva utilizando el método de B-Spline 
	// cuadrático uniforme.
	// PRE: "u" es un valor entre 0 y 1 que define el parámetro de la curva 
	// (dependiendo de cual sea el valor se devolverá un cierto punto de dicha 
	// curva); "p" es un puntero a un arreglo que contiene las coordenadas de 
	// los puntos de control.
	// POST: se devuelve el valor de la coordenada del punto sobre la curva.
	static float curvaBSpline(float u, float p[3]);

	// Cálculo de los vectores tangente (t), binormal (b) y normal (n)
	// correspondientes a un punto de la curva BSpline dado por el valor
	// del parámetro u.
	// El valor no se encuentra normalizado.
	static void curvaBSplineVectores(float u, float px[3], float py[3], 
		float pz[3], float t[3], float b[3], float n[3]);

	// Cálculo del vector tangente (t) correspondiente a un punto de la curva
	// B-Spline dado por el valor del parametro u. 
	static void vectorTangenteCurvaBSpline(float u, float px[3], float py[3], 
		float pz[3], float t[3]);

	// Devuelve el float mas cercano al double pasado por parámetro
	static float nextFloat(double a);
};


#endif