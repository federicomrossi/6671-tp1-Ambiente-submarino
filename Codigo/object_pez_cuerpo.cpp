/*  
 *  CLASS PEZ
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

#include "object_pez_cuerpo.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/DiffuseShadingVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/DiffuseShadingFShader.frag";
}







/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
PezCuerpo::PezCuerpo()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
PezCuerpo::~PezCuerpo() { }


// Crea un objeto
void PezCuerpo::create()
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Puntos de control de la CURVA DE ESQUELETO SUPERIOR

	float superior_pc0x = 0.0;
	float superior_pc0y = 0.15;

	float superior_pc1x = 9.0;
	float superior_pc1y = 1.0;

	float superior_pc2x = 10.0;
	float superior_pc2y = 1.5;

	float superior_pc3x = 10.0;
	float superior_pc3y = 0.0;

	float superior_pcx[] = {superior_pc0x, superior_pc1x, superior_pc2x, superior_pc3x};
	float superior_pcy[] = {superior_pc0y, superior_pc1y, superior_pc2y, superior_pc3y};


	// Puntos de control de la CURVA DE ESQUELETO INFERIOR

	float inferior_pc0x = 10.0;
	float inferior_pc0y = 0.15;

	float inferior_pc1x = 9.0;
	float inferior_pc1y = 0.5;

	float inferior_pc2x = 0.1;
	float inferior_pc2y = 1.0;

	float inferior_pc3x = 0.0;
	float inferior_pc3y = 0.0;

	float inferior_pcx[] = {inferior_pc0x, inferior_pc1x, inferior_pc2x, inferior_pc3x};
	float inferior_pcy[] = {inferior_pc0y, inferior_pc1y, inferior_pc2y, inferior_pc3y};



	// Puntos de control de la CURVA DE ANCHO DEL ESQUELETO

	float ancho_pc0x = 0.0;
	float ancho_pc0y = 0.0;

	float ancho_pc1x = 2.0;
	float ancho_pc1y = 0.3;

	float ancho_pc2x = 8.0;
	float ancho_pc2y = 0.3;

	float ancho_pc3x = 10.0;
	float ancho_pc3y = 0.0;

	float ancho_pcx[] = {ancho_pc0x, ancho_pc1x, ancho_pc2x, ancho_pc3x};
	float ancho_pcy[] = {ancho_pc0y, ancho_pc1y, ancho_pc2y, ancho_pc3y};




	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;
	// Cantidad de curvas que compondran la curva general
	int CANT_CURVAS = 4;

	// Valores para cálculos (no modificar)
	this->ESTIRAMIENTO = 16;
	this->CANT_PUNTOS = CANT_CURVAS * (int(ceil(1.0 / PASO)) + 1);
	int DIMENSIONES = 3;
	this->ESPACIADO_ESTIRAMIENTO = 0.2;




	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2* this->CANT_PUNTOS * (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;



	int i = 0;

	// Iteramos sobre cada nivel del objeto
	for(int q = 0; q < this->ESTIRAMIENTO; q++)
	{
		// Calculamos la curva de bezier que da forma al esqueleto superior
		float distancia_sup = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	superior_pcy);

		// Calculamos la curva de bezier que da forma al esqueleto inferior
		float distancia_inf = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	inferior_pcy);

		// Calculamos la curva de bezier que da el ancho del cuerpo
		float ancho = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1), ancho_pcy);


		// Puntos de control
		float pc0x = 1.0  * distancia_inf;
		float pc0y = -1.0 * ancho;
		float pc0z = 0.0;

		float pc1x = -1.0 * distancia_sup;
		float pc1y = -1.0 * ancho;
		float pc1z = 0.0;

		float pc2x = -1.0 * distancia_sup;
		float pc2y = 1.0 * ancho;
		float pc2z = 0.0;

		float pc3x = 1.0  * distancia_inf;
		float pc3y = 1.0 * ancho;
		float pc3z = 0.0;

		// Armamos arreglos para los trozos que conforman la curva
		float pcx012[] = {pc0x, pc1x, pc2x};
		float pcx123[] = {pc1x, pc2x, pc3x};
		float pcx230[] = {pc2x, pc3x, pc0x};
		float pcx301[] = {pc3x, pc0x, pc1x};

		float pcy012[] = {pc0y, pc1y, pc2y};
		float pcy123[] = {pc1y, pc2y, pc3y};
		float pcy230[] = {pc2y, pc3y, pc0y};
		float pcy301[] = {pc3y, pc0y, pc1y};

		float punto_cierre_x;
		float punto_cierre_y;
		float punto_cierre_z;



		// Segmento 0-1-2 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx012);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy012);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			// DEBUG
			// if(j == 0)
			// 	std::cout << "012: " << ppx << "," << ppy << "," << ppz << std::endl;
			// else if(j == (this->CANT_PUNTOS / CANT_CURVAS)-1)
			// 	std::cout << "012: " << ppx << "," << ppy << "," << ppz << std::endl;
		}

		// Segmento 1-2-3 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx123);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy123);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			// DEBUG
			// if(j == 0)
			// 	std::cout << "123: " << ppx << "," << ppy << "," << ppz << std::endl;
			// else if(j == (this->CANT_PUNTOS / CANT_CURVAS)-1)
			// 	std::cout << "123: " << ppx << "," << ppy << "," << ppz << std::endl;
		}

		// Segmento 2-3-0 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx230);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy230);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			// DEBUG
			// if(j == 0)
			// 	std::cout << "230: " << ppx << "," << ppy << "," << ppz << std::endl;
			// else if(j == (this->CANT_PUNTOS / CANT_CURVAS)-1)
			// 	std::cout << "230: " << ppx << "," << ppy << "," << ppz << std::endl;
		}

		// Segmento 3-0-1 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx301);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy301);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			// DEBUG
			// std::cout;
			// if(j == 0)
			// 	std::cout << "301: " << ppx << "," << ppy << "," << ppz << std::endl;
			// else if(j == (this->CANT_PUNTOS / CANT_CURVAS)-1)
			// 	std::cout << "301: " << ppx << "," << ppy << "," << ppz << std::endl;
		}
		
		// DEBUG
		// std::string a;
		// std::cin >> a; 
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

	k = 0;

	for(int i=0; i <= (this->ESTIRAMIENTO-1); i++) {
		for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
		{
			float t1[3], t2[3], t3[3], t4[3];
			float *n1, *n2, *n3, *n4;
			float n[3];

			int w = (this->ESTIRAMIENTO-1);
			int z = (this->CANT_PUNTOS-1);

			// Caso 1: i=0 y j=0
			if((i == 0) && (j == 0))
			{
				// Vector tg para w-1
				t1[0] = this->object_vertex_buffer[malla[w-1][j] * 3] - 
					this->object_vertex_buffer[malla[w][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[w-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[w][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[w-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[w][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para z-1
				t4[0] = this->object_vertex_buffer[malla[i][z-1] * 3] - 
					this->object_vertex_buffer[malla[i][z] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][z-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][z] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][z-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][z] * 3 + 2];
			}
			// Caso 2: i=max y j=0
			else if((i == this->ESTIRAMIENTO-1) && (j == 0))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[1][j] * 3] - 
					this->object_vertex_buffer[malla[0][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[0][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[0][j] * 3 + 2];

				// Vector tg para z-1
				t4[0] = this->object_vertex_buffer[malla[i][z-1] * 3] - 
					this->object_vertex_buffer[malla[i][z] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][z-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][z] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][z-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][z] * 3 + 2];
			}
			// Caso 3: i=max y j=max
			else if((i == this->ESTIRAMIENTO-1) && (j == this->CANT_PUNTOS-1))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][1] * 3] - 
					this->object_vertex_buffer[malla[i][0] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][0] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][0] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[1][j] * 3] - 
					this->object_vertex_buffer[malla[0][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[0][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[0][j] * 3 + 2];

				// Vector tg para j-1
				t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];
			}
			// Caso 4: i=0 y j=max
			else if((i == this->ESTIRAMIENTO-1) && (j == this->CANT_PUNTOS-1))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[w-1][j] * 3] - 
					this->object_vertex_buffer[malla[w][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[w-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[w][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[w-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[w][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][1] * 3] - 
					this->object_vertex_buffer[malla[i][0] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][0] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][0] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j-1
				t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];
			}
			// Caso 5: i=0 y 0<j<max
			else if((i==0) && (j>0) && (j<(this->CANT_PUNTOS-1)))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[w-1][j] * 3] - 
					this->object_vertex_buffer[malla[w][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[w-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[w][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[w-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[w][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j-1
				t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];
			}
			// Caso 6: 0<i<max y j=0
			else if((i>0) && (i<(this->ESTIRAMIENTO-1)) && (j==0))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

					// Vector tg para z-1
				t4[0] = this->object_vertex_buffer[malla[i][z-1] * 3] - 
					this->object_vertex_buffer[malla[i][z] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][z-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][z] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][z-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][z] * 3 + 2];
			}
			// Caso 7: i=max y 0 < j < max
			else if((i==(this->ESTIRAMIENTO-1)) && (j>0) && (j<(this->CANT_PUNTOS-1)))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[1][j] * 3] - 
					this->object_vertex_buffer[malla[0][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[0][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[0][j] * 3 + 2];

				// Vector tg para j-1
				t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];
			}
			// Caso 8: 0 < i < max y j=max
			else if((i>0) && (i<(this->ESTIRAMIENTO-1)) && (j==(this->CANT_PUNTOS-1)))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][1] * 3] - 
					this->object_vertex_buffer[malla[i][0] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][0] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][0] * 3 + 2];
					
				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j-1
				t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];
			}
			// Caso 9: 0 < i < max y 0 < j < max
			else if((i>0) && (i<(this->ESTIRAMIENTO-1)) && (j>0) && (j<(this->CANT_PUNTOS-1)))
			{
				// Vector tg para i-1
				t1[0] = this->object_vertex_buffer[malla[i-1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t1[1] = this->object_vertex_buffer[malla[i-1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t1[2] = this->object_vertex_buffer[malla[i-1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j+1
				t2[0] = this->object_vertex_buffer[malla[i][j+1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t2[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t2[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para i+1
				t3[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t3[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t3[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];

				// Vector tg para j-1
				t4[0] = this->object_vertex_buffer[malla[i][j-1] * 3] - 
					this->object_vertex_buffer[malla[i][j] * 3];
				t4[1] = this->object_vertex_buffer[malla[i][j-1] * 3 + 1] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 1];
				t4[2] = this->object_vertex_buffer[malla[i][j-1] * 3 + 2] - 
					this->object_vertex_buffer[malla[i][j] * 3 + 2];
			}

			// if(j <= (this->CANT_PUNTOS-1)/4) {
			// 	// Calculamos la normal para cada sentido
			// 	n1 = Matematica::productoVectorial(t1, t2);
			// 	n2 = Matematica::productoVectorial(t2, t3);
			// 	n3 = Matematica::productoVectorial(t3, t4);
			// 	n4 = Matematica::productoVectorial(t4, t1);
			// }
			// else if((j > (this->CANT_PUNTOS-1)/4) && (j <= (this->CANT_PUNTOS-1)/2)) {
			// 	// Calculamos la normal para cada sentido
			// 	n1 = Matematica::productoVectorial(t2, t1);
			// 	n2 = Matematica::productoVectorial(t3, t2);
			// 	n3 = Matematica::productoVectorial(t4, t3);
			// 	n4 = Matematica::productoVectorial(t1, t4);
			// }
			// else if((j > (this->CANT_PUNTOS-1)/2) && (j <= (this->CANT_PUNTOS-1) * 3/4)) {
			// 	// Calculamos la normal para cada sentido
			// 	n1 = Matematica::productoVectorial(t2, t1);
			// 	n2 = Matematica::productoVectorial(t3, t2);
			// 	n3 = Matematica::productoVectorial(t3, t4);
			// 	n4 = Matematica::productoVectorial(t1, t1);
			// }
			// else {
			// 	// Calculamos la normal para cada sentido
			// 	n1 = Matematica::productoVectorial(t1, t2);
			// 	n2 = Matematica::productoVectorial(t2, t3);
			// 	n3 = Matematica::productoVectorial(t3, t4);
			// 	n4 = Matematica::productoVectorial(t4, t1);
			// }


			// Calculamos la normal para cada sentido
			n1 = Matematica::productoVectorial(t1, t2);
			n2 = Matematica::productoVectorial(t2, t3);
			n3 = Matematica::productoVectorial(t3, t4);
			n4 = Matematica::productoVectorial(t4, t1);


			// Obtenemos la normal tomando el promedio de normales
			n[0] = n1[0] + n2[0] + n3[0] + n4[0];
			n[1] = n1[1] + n2[1] + n3[1] + n4[1];
			n[2] = n1[2] + n2[2] + n3[2] + n4[2];

			// Normalizamos la normal obtenida
			float *normal = Matematica::normalizar(n);

			// Cargamos las coordenadas en el buffer
			this->object_normal_buffer[k++] = normal[0];
			this->object_normal_buffer[k++] = normal[1];
			this->object_normal_buffer[k++] = normal[2];
		}
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezCuerpo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glUseProgram(this->programHandle);

	this->changeObjectColor(166, 214, 38);
	
	// Ponemos el objeto en el centro del eje coordenado
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::translate(model_matrix, glm::vec3(-1.5, 0.0, 0.0));
	mCuerpo = glm::rotate(mCuerpo, 90.0f, glm::vec3(0.0, 1.0, 0.0));


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
	glm::vec4 light_position = glm::vec4(8.0f, 8.0f, 2.0f, 1.0f);
	glm::vec3 light_intensity = glm::vec3(1.0f, 1.0f, 1.0f);
	   
	GLuint location_light_position = glGetUniformLocation(this->programHandle, 
		"LightPosition");

	if(location_light_position >= 0) 
		glUniform4fv( location_light_position, 1, &light_position[0]); 

	GLuint location_light_intensity = glGetUniformLocation(
		this->programHandle, "Ld");

	if(location_light_intensity >= 0) 
		glUniform3fv( location_light_intensity, 1, &light_intensity[0]); 
	//
	///////////////////////////////////////////


	// Normal Matrix
	glm::mat3 normal_matrix = glm::mat3 ( 1.0f );

	// Bind Normal MAtrix
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
			&mCuerpo[0][0]); 

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
