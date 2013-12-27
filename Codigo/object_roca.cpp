/*  
 *  CLASS ROCA
 */


#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>
#include "lib_matematica.h"
#include "object_roca.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/RocaVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/RocaFShader.frag";
}





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Roca::Roca() 
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_tangent_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
Roca::~Roca() { }


// Crea un objeto
void Roca::create()
{
	// Cargamos la textura
	this->loadAndInitTexture("textures/rock-texture-01.jpg",
		"textures/rock-normalmap-texture-01.jpg");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;
	// Cantidad de curvas que compondran la curva general
	int CANT_CURVAS = 4;

	// Valores para cálculos (no modificar)
	this->ESTIRAMIENTO = 10;
	this->CANT_PUNTOS = CANT_CURVAS * (int(ceil(1.0 / PASO)) + 1);
	int DIMENSIONES = 3;
	this->ESPACIADO_ESTIRAMIENTO = 0.1;
	int DIMENSIONES_TEXTURA = 2;



	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_texture_buffer_size = DIMENSIONES_TEXTURA * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO; 
	this->object_texture_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2* this->CANT_PUNTOS * (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];

	this->object_tangent_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_tangent_buffer = new GLfloat[this->object_tangent_buffer_size];



	// Puntos de control de la CURVA DE ESQUELETO INFERIOR

	float radio_pc0x = 10.0;
	float radio_pc0y = 0.0001;

	float radio_pc1x = 5.0;
	float radio_pc1y = 0.9;

	float radio_pc2x = 3.0;
	float radio_pc2y = 1.0;

	float radio_pc3x = 0.0;
	float radio_pc3y = 0.0001;

	float radio_pcx[] = {radio_pc0x, radio_pc1x, radio_pc2x, radio_pc3x};
	float radio_pcy[] = {radio_pc0y, radio_pc1y, radio_pc2y, radio_pc3y};



	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;



	int i = 0;
	int y = 0;
	int w = 0;
	int z = 0;

	// Vector tangente correspondiente al barrido
	float t_barrido[3];
	t_barrido[0] = 0.0;
	t_barrido[1] = 0.0;
	t_barrido[2] = 1.0;


	// Iteramos sobre cada nivel del objeto
	for(int q = 0; q < this->ESTIRAMIENTO; q++)
	{
		// Calculamos la curva de bezier que da forma al esqueleto inferior
		float radio = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	radio_pcy);

		// Puntos de control
		float pc0x = 1.0 * radio;
		float pc0y = -1.0 * radio;
		float pc0z = 0.0;

		float pc1x = -1.0 * radio;
		float pc1y = -1.0 * radio;
		float pc1z = 0.0;

		float pc2x = -1.0 * radio;
		float pc2y = 1.0 * radio;
		float pc2z = 0.0;

		float pc3x = 1.0 * radio;
		float pc3y = 1.0 * radio;
		float pc3z = 0.5;

		// Armamos arreglos para los trozos que conforman la curva
		float pcx012[] = {pc0x, pc1x, pc2x};
		float pcx123[] = {pc1x, pc2x, pc3x};
		float pcx230[] = {pc2x, pc3x, pc0x};
		float pcx301[] = {pc3x, pc0x, pc1x};

		float pcy012[] = {pc0y, pc1y, pc2y};
		float pcy123[] = {pc1y, pc2y, pc3y};
		float pcy230[] = {pc2y, pc3y, pc0y};
		float pcy301[] = {pc3y, pc0y, pc1y};

		float pcz012[] = {pc0z, pc1z, pc2z};
		float pcz123[] = {pc1z, pc2z, pc3z};
		float pcz230[] = {pc2z, pc3z, pc0z};
		float pcz301[] = {pc3z, pc0z, pc1z};


		// Segmento 0-1-2 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			float var = 0.0;
			if(((j%3) == 0 )&& q < this->ESTIRAMIENTO-1 && q > 0 && j > 0)
				var =  Matematica::numeroAleatorio(-0.05, 0.05);

			if(q == this->ESTIRAMIENTO-1) 
				var += -this->ESPACIADO_ESTIRAMIENTO / 2;

			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx012);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy012);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx012, pcy012, pcz012, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t, t_barrido);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx + var;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz + var;

			this->object_texture_buffer[y++] = (j * PASO);
			this->object_texture_buffer[y++] = ((q + (this->ESTIRAMIENTO / 2)) * 1.0) / this->ESTIRAMIENTO;
		}

		// Segmento 1-2-3 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			float var = 0.0;
			if(((j%3) == 0 )&& q < this->ESTIRAMIENTO-1 && q > 0 && j > 0)
				var =  Matematica::numeroAleatorio(-0.05, 0.05);

			if(q == this->ESTIRAMIENTO-1) 
				var += -this->ESPACIADO_ESTIRAMIENTO / 2;

			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx123);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy123);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx123, pcy123, pcz123, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t, t_barrido);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx + var;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz + var;

			this->object_texture_buffer[y++] = (j * PASO);
			this->object_texture_buffer[y++] = ((q + (this->ESTIRAMIENTO / 2)) * 1.0) / this->ESTIRAMIENTO;
		}

		// Segmento 2-3-0 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			float var = 0.0;
			if(((j%3) == 0 )&& q < this->ESTIRAMIENTO-1 && q > 0 && j > 0)
				var =  Matematica::numeroAleatorio(-0.05, 0.05);

			if(q == this->ESTIRAMIENTO-1) 
				var += -this->ESPACIADO_ESTIRAMIENTO / 2;

			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx230);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy230);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx230, pcy230, pcz230, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t, t_barrido);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx + var;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz + var;

			this->object_texture_buffer[y++] = (j * PASO);
			this->object_texture_buffer[y++] = ((q + (this->ESTIRAMIENTO / 2)) * 1.0) / this->ESTIRAMIENTO;
		}

		// Segmento 3-0-1 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			float var = 0.0;
			if(((j%3) == 0 )&& q < this->ESTIRAMIENTO-1 && q > 0 && j > 0 
				&& j < (this->CANT_PUNTOS / CANT_CURVAS)-1)
				var =  Matematica::numeroAleatorio(-0.05, 0.05);

			if(q == this->ESTIRAMIENTO-1) 
				var += -this->ESPACIADO_ESTIRAMIENTO / 2;

			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx301);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy301);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx301, pcy301, pcz301, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t, t_barrido);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx + var;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz + var;

			this->object_texture_buffer[y++] = (j * PASO);
			this->object_texture_buffer[y++] = ((q + (this->ESTIRAMIENTO / 2)) * 1.0) / this->ESTIRAMIENTO;
		}
	}




	int sentido = 1;
	int k = 0;

	for(int i=0; i < (this->ESTIRAMIENTO-1); i++)
	{
		if(sentido == 1)
		{
			for(int j=0; j <= (this->CANT_PUNTOS-1); j++) {
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = -1;
		}
		else if(sentido == -1)
		{
			for(int j=(this->CANT_PUNTOS-1); j >= 0; j--) {
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = 1;
		}
	}



	// NORMALES


	// k = 0;

	// for(int i=0; i <= (this->ESTIRAMIENTO-1); i++) {
	// 	for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
	// 	{
	// 		float t1[3], t2[3], t3[3], t4[3];
	// 		float *n1, *n2, *n3, *n4;
	// 		float n[3];

	// 		int w = (this->ESTIRAMIENTO-1);
	// 		int z = (this->CANT_PUNTOS-1);

	// 		// // Caso 1: i=0 y j=0
	// 		// if((i == 0) && (j == 0))
	// 		// {
	// 		// 	// Vector tg para w-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[w-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[w-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[w-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para z-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][z-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][z-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][z-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3 + 2];
	// 		// }
	// 		// // Caso 2: i=max y j=0
	// 		// else if((i == this->ESTIRAMIENTO-1) && (j == 0))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3 + 2];

	// 		// 	// Vector tg para z-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][z-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][z-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][z-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3 + 2];
	// 		// }
	// 		// // Caso 3: i=max y j=max
	// 		// else if((i == this->ESTIRAMIENTO-1) && (j == this->CANT_PUNTOS-1))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3 + 2];

	// 		// 	// Vector tg para j-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];
	// 		// }
	// 		// // Caso 4: i=0 y j=max
	// 		// else if((i == this->ESTIRAMIENTO-1) && (j == this->CANT_PUNTOS-1))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[w-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[w-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[w-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];
	// 		// }
	// 		// // Caso 5: i=0 y 0<j<max
	// 		// else if((i==0) && (j>0) && (j<(this->CANT_PUNTOS-1)))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[w-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[w-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[w-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[w][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];
	// 		// }
	// 		// // Caso 6: 0<i<max y j=0
	// 		// else if((i>0) && (i<(this->ESTIRAMIENTO-1)) && (j==0))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 		// Vector tg para z-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][z-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][z-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][z-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][z] * 3 + 2];
	// 		// }
	// 		// // Caso 7: i=max y 0 < j < max
	// 		// else if((i==(this->ESTIRAMIENTO-1)) && (j>0) && (j<(this->CANT_PUNTOS-1)))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[0][j] * 3 + 2];

	// 		// 	// Vector tg para j-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];
	// 		// }
	// 		// // Caso 8: 0 < i < max y j=max
	// 		// else if((i>0) && (i<(this->ESTIRAMIENTO-1)) && (j==(this->CANT_PUNTOS-1)))
	// 		// {
	// 		// 	// Vector tg para i-1
	// 		// 	t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j+1
	// 		// 	t2[0] = this->object_vertex_buffer[malla[i][1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3];
	// 		// 	t2[1] = this->object_vertex_buffer[malla[i][1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3 + 1];
	// 		// 	t2[2] = this->object_vertex_buffer[malla[i][1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][0] * 3 + 2];
					
	// 		// 	// Vector tg para i+1
	// 		// 	t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 		// 	// Vector tg para j-1
	// 		// 	t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3];
	// 		// 	t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 		// 	t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
	// 		// 		this->object_vertex_buffer[malla[i][j] * 3 + 2];
	// 		// }

	// 		// Caso 9: 0 < i < max y 0 < j < max
	// 		// if((i>0) && (i<(this->ESTIRAMIENTO-1)) && (j>0) && (j<(this->CANT_PUNTOS-1)))
	// 		if( (j > 0) &&
	// 			(j != ((this->CANT_PUNTOS / 4)-1) * 1) &&
	// 			(j != ((this->CANT_PUNTOS / 4)-1) * 2) &&
	// 			(j != ((this->CANT_PUNTOS / 4)-1) * 3) &&
	// 			(j < this->CANT_PUNTOS-1) && 
	// 			(i > 0) &&
	// 			(i < this->ESTIRAMIENTO-1)
	// 		  )
	// 		{
	// 			// Vector tg para i-1
	// 			t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3];
	// 			t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 			t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 			// Vector tg para j+1
	// 			t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3];
	// 			t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 			t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 			// Vector tg para i+1
	// 			t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3];
	// 			t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 			t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 2];

	// 			// Vector tg para j-1
	// 			t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3];
	// 			t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 1];
	// 			t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
	// 				this->object_vertex_buffer[malla[i][j] * 3 + 2];
	// 		}
	// 		else
	// 		{
	// 			k++;k++;k++;
	// 			continue;
	// 		}

	// 		// Calculamos la normal para cada sentido
	// 		n1 = Matematica::productoVectorial(t1, t2);
	// 		n2 = Matematica::productoVectorial(t2, t3);
	// 		n3 = Matematica::productoVectorial(t3, t4);
	// 		n4 = Matematica::productoVectorial(t4, t1);


	// 		// Obtenemos la normal tomando el promedio de normales
	// 		n[0] = n1[0] + n2[0] + n3[0] + n4[0];
	// 		n[1] = n1[1] + n2[1] + n3[1] + n4[1];
	// 		n[2] = n1[2] + n2[2] + n3[2] + n4[2];

	// 		// Normalizamos la normal obtenida
	// 		float *normal = Matematica::normalizar(n);

	// 		// Cargamos las coordenadas en el buffer
	// 		this->object_normal_buffer[k++] = normal[0];
	// 		this->object_normal_buffer[k++] = normal[1];
	// 		this->object_normal_buffer[k++] = normal[2];
	// 	}
	// }
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Roca::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);
	
	this->changeObjectColor(180,180,180);

	///////////////////////////////////////////
	// Bind View Matrix
	GLuint location_view_matrix = glGetUniformLocation(this->programHandle,
		"ViewMatrix"); 

	if(location_view_matrix >= 0) 
		glUniformMatrix4fv(location_view_matrix, 1, GL_FALSE, 
			&view_matrix[0][0]); 

	// Bind Projection Matrix
	GLuint location_projection_matrix = glGetUniformLocation(
		this->programHandle, "ProjectionMatrix"); 
	
	if(location_projection_matrix >= 0) 
		glUniformMatrix4fv( location_projection_matrix, 1, GL_FALSE,
			&projection_matrix[0][0]); 
	//
	///////////////////////////////////////////


	//////////////////////////////////////
	// Bind Light Settings

	glm::vec3 light_intensity = glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec4 light_position = glm::vec4(-8.0f, -8.0f, 2.0f, 1.0f);
	glm::vec3 La = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ls = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ka = glm::vec3(90 / 255.0f,
							 49 / 255.0f, 
							 49 / 255.0f);
	this->changeObjectColor(186, 143, 143);
	glm::vec3 Kd = glm::vec3(this->R / 255.0f,
							 this->G / 255.0f, 
							 this->B / 255.0f);
	glm::vec3 Ks = glm::vec3(0.5f, 0.5f, 0.5f);
	float Shininess = 1.0;

	// Light Intensity
	GLuint location_light_intensity = glGetUniformLocation(this->programHandle, "LightIntensity");

	if(location_light_intensity >= 0) 
		glUniform3fv( location_light_intensity, 1, &light_intensity[0]); 

	// Light Position
	GLuint location_light_position = glGetUniformLocation(this->programHandle, 
		"LightPosition");

	if(location_light_position >= 0) 
		glUniform4fv( location_light_position, 1, &light_position[0]); 

	// // La
	// GLuint location_la = glGetUniformLocation(
	// 	this->programHandle, "La");

	// if(location_la >= 0) 
	// 	glUniform3fv( location_la, 1, &La[0]); 
	
	// // Ld
	// GLuint location_ld = glGetUniformLocation(
	// 	this->programHandle, "Ld");

	// if(location_ld >= 0) 
	// 	glUniform3fv( location_ld, 1, &Ld[0]); 

	// // Ls
	// GLuint location_ls = glGetUniformLocation(
	// 	this->programHandle, "Ls");

	// if(location_ls >= 0) 
	// 	glUniform3fv( location_ls, 1, &Ls[0]); 


	// Ka
	GLuint location_ka = glGetUniformLocation(
		this->programHandle, "Ka");

	if(location_ka >= 0) 
		glUniform3fv( location_ka, 1, &Ka[0]); 
	
	// // Kd
	// GLuint location_kd = glGetUniformLocation(
	// 	this->programHandle, "Kd");

	// if(location_kd >= 0) 
	// 	glUniform3fv( location_kd, 1, &Kd[0]); 

	// Ks
	GLuint location_ks = glGetUniformLocation(
		this->programHandle, "Ks");

	if(location_ks >= 0) 
		glUniform3fv( location_ks, 1, &Ks[0]); 


	// Shininess
	GLfloat location_shininess = glGetUniformLocation(this->programHandle,
		"Shininess");

	if(location_shininess >= 0)
		glUniform1f(location_shininess, Shininess); 

	//
	///////////////////////////////////////////


	// Normal Matrix
	glm::mat3 normal_matrix = glm::mat3 ( 1.0f );

	// Bind Normal Matrix
	GLuint location_normal_matrix = glGetUniformLocation(this->programHandle, 
		"NormalMatrix"); 
	if( location_normal_matrix >= 0 ) 
		glUniformMatrix3fv( location_normal_matrix, 1, GL_FALSE, 
			&normal_matrix[0][0]); 

	// Bind Model Matrix
	GLuint location_model_matrix = glGetUniformLocation(this->programHandle, 
		"ModelMatrix"); 
	if(location_model_matrix >= 0)
		glUniformMatrix4fv( location_model_matrix, 1, GL_FALSE, 
			&model_matrix[0][0]);



	//  the Texture sampler uniform to refer to texture unit 0
	int loc = glGetUniformLocation(this->programHandle, "Texture");
	if(loc >= 0) glUniform1i(loc, 0);
	else fprintf(stderr, "Uniform variable Tex1 not found!\n");


	// Set the NormalMapTex sampler uniform to refer to texture unit 1
	int locNM = glGetUniformLocation(this->programHandle, "NormalMapTex");
	if(locNM >= 0) glUniform1i(locNM, 1);
	else fprintf(stderr, "Uniform variable NormalMapTex not found!\n");


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);
	glTexCoordPointer(2, GL_FLOAT, 0, this->object_texture_buffer);
	glColorPointer(3, GL_FLOAT, 0, this->object_tangent_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
