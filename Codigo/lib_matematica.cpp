/*
 * CLASS LIB_FACTORIAL
 */

#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#include "lib_matematica.h"
#include <algorithm> 			// For std::copy



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

	n[0] = u[1] * v[2] - (v[1] * u[2]);
	n[1] = -(u[0] * v[2] - v[0] * u[2]);
	n[2] = u[0] * v[1] - v[0] * u[1];

	std::copy(n, n+3, n);

	return n;
}


// Método que normaliza un vector de 3 dimensiones
float* Matematica::normalizar(float v[3])
{
	static float n[3];

	float norma = sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));


	n[0] = v[0] / norma;
	n[1] = v[1] / norma;
	n[2] = v[2] / norma;

	static float a[3];
	std::copy(n, n+3, a);

	return a;
}


// Función que devuelve un numero aleatorio entre "min" y "max"
float Matematica::numeroAleatorio(float min, float max)
{
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}


// Calculo de punto en una curva utilizando el método de Bezier
// (implementación con algoritmo de Berstein).
// PRE: "t" es un valor entre 0 y 1 que define el parámetro de la curva
// (dependiendo de cual sea el valor se devolverá un cierto punto de dicha 
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


// Cálculo de los vectores tangente (t), binormal (b) y normal (n)
// correspondientes a un punto de la curva de Bezier dado por el valor
// del parámetro t.
// El valor no se encuentra normalizado.
void Matematica::curvaBezierVectores(float u, float px[4], float py[4], float pz[4], float t[3], float b[3], float n[3])
{
	// Primer derivada de las bases de bezier
	float b00 = (-3.0 * pow(u, 2) + 6.0 * u - 3.0);
	float b01 = (9.0 * pow(u, 2) - 12.0 * u + 3.0);
	float b02 = (-9.0 * pow(u, 2) + 6.0 * u);
	float b03 = (3.0 * pow(u, 2));

	if((b00 == 0 && b01 == 0 && b02 == 0  && b03 == 0) || u == 0) {
		// Primer derivada de las bases de bezier
		b00 = (-3.0 * pow(u+0.01, 2) + 6.0 * (u+0.01) - 3.0);
		b01 = (9.0 * pow(u+0.01, 2) - 12.0 * (u+0.01) + 3.0);
		b02 = (-9.0 * pow(u+0.01, 2) + 6.0 * (u+0.01));
		b03 = (3.0 * pow(u+0.01, 2));		
	}
	else if ((b00 == 0 && b01 == 0 && b02 == 0  && b03 == 0) || u == 1) {
		// Primer derivada de las bases de bezier
		b00 = (-3.0 * pow(u-0.01, 2) + 6.0 * (u-0.01) - 3.0);
		b01 = (9.0 * pow(u-0.01, 2) - 12.0 * (u-0.01) + 3.0);
		b02 = (-9.0 * pow(u-0.01, 2) + 6.0 * (u-0.01));
		b03 = (3.0 * pow(u-0.01, 2));
	}


	// Segunda derivada de las bases de bezier
	float b10 = (-6.0 * u + 6.0);
	float b11 = (18.0 * u - 12.0);
	float b12 = (-18.0 * u + 6.0);
	float b13 = (6.0 * u);

	if((b10 == 0 && b11 == 0 && b12 == 0  && b13 == 0) || u == 0) {
		// Primer derivada de las bases de bezier
		b10 = (-6.0 * (u+0.01) + 6.0);
		b11 = (18.0 * (u+0.01) - 12.0);
		b12 = (-18.0 * (u+0.01) + 6.0);
		b13 = (6.0 * (u+0.01));
	}
	else if ((b10 == 0 && b11 == 0 && b12 == 0  && b13 == 0) || u == 1) {
		// Primer derivada de las bases de bezier
		b10 = (-6.0 * (u-0.01) + 6.0);
		b11 = (18.0 * (u-0.01) - 12.0);
		b12 = (-18.0 * (u-0.01) + 6.0);
		b13 = (6.0 * (u-0.01));
	}

	// Tangente
	float tx = 0;
	float ty = 0;
	float tz = 0;

	tx += b00 * px[0];
	tx += b01 * px[1];
	tx += b02 * px[2];
	tx += b03 * px[3];
	
	ty += b00 * py[0];
	ty += b01 * py[1];
	ty += b02 * py[2];
	ty += b03 * py[3];

	tz += b00 * pz[0];
	tz += b01 * pz[1];
	tz += b02 * pz[2];
	tz += b03 * pz[3];

	float tTemp[3];
	tTemp[0] = tx;
	tTemp[1] = ty;
	tTemp[2] = tz;

	float *a;
	a = Matematica::normalizar(tTemp);
	std::copy(a, a+3, t);

	// Binormal
	float bx = 0;
	float by = 0;
	float bz = 0;

	bx += b10 * px[0];
	bx += b11 * px[1];
	bx += b12 * px[2];
	bx += b13 * px[3];

	by += b10 * py[0];
	by += b11 * py[1];
	by += b12 * py[2];
	by += b13 * py[3];

	bz += b10 * pz[0];
	bz += b11 * pz[1];
	bz += b12 * pz[2];
	bz += b13 * pz[3];


	float bTemp[3];
	bTemp[0] = bx;
	bTemp[1] = by;
	bTemp[2] = bz;


	float *temp = Matematica::productoVectorial(tTemp, bTemp);
	
	float *y;
	y = Matematica::normalizar(temp);
	std::copy(y, y+3, b);

	// Normal
	float *k;
	k = Matematica::productoVectorial(t, b);

	k = Matematica::normalizar(k);
	std::copy(k, k+3, n);
}


// Cálculo del vector tangente (t) correspondiente a un punto de la curva
	// de Bezier dado por el valor del parametro u. 
void Matematica::vectorTangenteCurvaBezier(float u, float px[4], float py[4], 
	float pz[4], float t[3])
{
	// Primer derivada de las bases de bezier
	float b00 = (-3.0 * pow(u, 2) + 6.0 * u - 3.0);
	float b01 = (9.0 * pow(u, 2) - 12.0 * u + 3.0);
	float b02 = (-9.0 * pow(u, 2) + 6.0 * u);
	float b03 = (3.0 * pow(u, 2));

	if((b00 == 0 && b01 == 0 && b02 == 0  && b03 == 0) || u == 0) {
		// Primer derivada de las bases de bezier
		b00 = (-3.0 * pow(u+0.01, 2) + 6.0 * (u+0.01) - 3.0);
		b01 = (9.0 * pow(u+0.01, 2) - 12.0 * (u+0.01) + 3.0);
		b02 = (-9.0 * pow(u+0.01, 2) + 6.0 * (u+0.01));
		b03 = (3.0 * pow(u+0.01, 2));		
	}
	else if ((b00 == 0 && b01 == 0 && b02 == 0  && b03 == 0) || u == 1) {
		// Primer derivada de las bases de bezier
		b00 = (-3.0 * pow(u-0.01, 2) + 6.0 * (u-0.01) - 3.0);
		b01 = (9.0 * pow(u-0.01, 2) - 12.0 * (u-0.01) + 3.0);
		b02 = (-9.0 * pow(u-0.01, 2) + 6.0 * (u-0.01));
		b03 = (3.0 * pow(u-0.01, 2));
	}

	// Tangente
	float tx = 0;
	float ty = 0;
	float tz = 0;

	tx += b00 * px[0];
	tx += b01 * px[1];
	tx += b02 * px[2];
	tx += b03 * px[3];
	
	ty += b00 * py[0];
	ty += b01 * py[1];
	ty += b02 * py[2];
	ty += b03 * py[3];

	tz += b00 * pz[0];
	tz += b01 * pz[1];
	tz += b02 * pz[2];
	tz += b03 * pz[3];

	float tTemp[3];
	tTemp[0] = tx;
	tTemp[1] = ty;
	tTemp[2] = tz;

	float *a;
	a = Matematica::normalizar(tTemp);
	std::copy(a, a+3, t);
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


// Calculo de punto en una curva utilizando el método de B-Spline 
// cuadrático uniforme.
// PRE: "u" es un valor entre 0 y 1 que define el parámetro de la curva 
// (dependiendo de cual sea el valor se devolverá un cierto punto de dicha 
// curva); "p" es un puntero a un arreglo que contiene las coordenadas de 
// los puntos de control.
// POST: se devuelve el valor de la coordenada del punto sobre la curva.
float Matematica::curvaBSpline(float u, float p[3])
{
	float punto = 0;

	punto += (0.5 * pow(1-u, 2)) * p[0];
	punto += (-pow(u, 2) + u + 0.5) * p[1];
	punto += (0.5 * pow(u, 2)) * p[2];

	return punto;
}


// Cálculo de los vectores tangente (t), binormal (b) y normal (n)
// correspondientes a un punto de la curva BSpline dado por el valor
// del parámetro u.
// El valor no se encuentra normalizado.
void Matematica::curvaBSplineVectores(float u, float px[3], float py[3], 
		float pz[3], float t[3], float b[3], float n[3])
{
	// Primer derivada de las bases de bezier
	float b00 = (u - 1);
	float b01 = (-2 * u + 1);
	float b02 = u;

	// Segunda derivada de las bases de bezier
	float b10 = 1;
	float b11 = -2;
	float b12 = 1;


	// Tangente
	float tx = 0;
	float ty = 0;
	float tz = 0;

	tx += b00 * px[0];
	tx += b01 * px[1];
	tx += b02 * px[2];

	ty += b00 * py[0];
	ty += b01 * py[1];
	ty += b02 * py[2];

	tz += b00 * pz[0];
	tz += b01 * pz[1];
	tz += b02 * pz[2];

	float tTemp[3];
	tTemp[0] = tx;
	tTemp[1] = ty;
	tTemp[2] = tz;

	float *a;
	a = Matematica::normalizar(tTemp);
	std::copy(a, a+3, t);

	// Binormal
	float bx = 0;
	float by = 0;
	float bz = 0;

	bx += b10 * px[0];
	bx += b11 * px[1];
	bx += b12 * px[2];

	by += b10 * py[0];
	by += b11 * py[1];
	by += b12 * py[2];

	bz += b10 * pz[0];
	bz += b11 * pz[1];
	bz += b12 * pz[2];

	float bTemp[3];
	bTemp[0] = bx;
	bTemp[1] = by;
	bTemp[2] = bz;

	float *temp = Matematica::productoVectorial(tTemp, bTemp);

	float *y;
	y = Matematica::normalizar(temp);
	std::copy(y, y+3, b);

	// Normal
	float *k;
	k = Matematica::productoVectorial(b, t);
	k = Matematica::normalizar(k);
	std::copy(k, k+3, n);
}


// Cálculo del vector tangente (t) correspondiente a un punto de la curva
// B-Spline dado por el valor del parametro u. 
void Matematica::vectorTangenteCurvaBSpline(float u, float px[3], float py[3], 
	float pz[3], float t[3])
{
	// Primer derivada de las bases de bspline
	float b00 = (u - 1);
	float b01 = (-2 * u + 1);
	float b02 = u;

	if((b00 == 0 && b01 == 0 && b02 == 0) || u == 0) {
		// Primer derivada de las bases de bspline
		b00 = ((u+0.01) - 1);
		b01 = (-2 * (u+0.01) + 1);
		b02 = (u+0.01);
	}
	else if ((b00 == 0 && b01 == 0 && b02 == 0) || u == 1) {
		// Primer derivada de las bases de bspline
		b00 = ((u-0.01) - 1);
		b01 = (-2 * (u-0.01) + 1);
		b02 = (u-0.01);
	}

	// Tangente
	float tx = 0;
	float ty = 0;
	float tz = 0;

	tx += b00 * px[0];
	tx += b01 * px[1];
	tx += b02 * px[2];
	
	ty += b00 * py[0];
	ty += b01 * py[1];
	ty += b02 * py[2];

	tz += b00 * pz[0];
	tz += b01 * pz[1];
	tz += b02 * pz[2];

	float tTemp[3];
	tTemp[0] = tx;
	tTemp[1] = ty;
	tTemp[2] = tz;

	float *a;
	a = Matematica::normalizar(tTemp);
	std::copy(a, a+3, t);
}
