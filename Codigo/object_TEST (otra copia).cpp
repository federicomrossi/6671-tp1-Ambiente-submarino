/*  
 *  CLASS CUBE
 */


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "lib_matematica.h"

#include "object_TEST.h"



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
Test::Test()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
Test::~Test() { }


// Crea un objeto cubo
void Test::create(int size)
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// ////////////////// TEST 3


	// CREACIÓN DEL OBJETO

	// Configuración del paso entre un punto y otro.
	float PASO = 0.05;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = 2 * (int(ceil(1.0 / PASO)) + 1);
	int DIMENSIONES = 3;
	this->ESTIRAMIENTO = 3;


	// Puntos de control
	float pc0x = 0.0;
	float pc0y = 1.0;
	float pc0z = 0.0;

	float pc1x = -1.35;
	float pc1y = 1.0;
	float pc1z = 0.0;

	float pc2x = -1.35;
	float pc2y = -1.0;
	float pc2z = 0.0;

	float pc3x = 0.0;
	float pc3y = -1.0;
	float pc3z = 0.0;

	float pcx[] = {pc0x, pc1x, pc2x, pc3x};
	float pcy[] = {pc0y, pc1y, pc2y, pc3y};



	// Puntos de control inversos
	float pc0x_inv = -0.0;
	float pc0y_inv = -1.0;
	float pc0z_inv = 0.0;

	float pc1x_inv = 1.35;
	float pc1y_inv = -1.0;
	float pc1z_inv = 0.0;

	float pc2x_inv = 1.35;
	float pc2y_inv = 1.0;
	float pc2z_inv = 0.0;

	float pc3x_inv = -0.0;
	float pc3y_inv = 1.0;
	float pc3z_inv = 0.0;

	float pcx_inv[] = {pc0x_inv, pc1x_inv, pc2x_inv, pc3x_inv};
	float pcy_inv[] = {pc0y_inv, pc1y_inv, pc2y_inv, pc3y_inv};



	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2* this->CANT_PUNTOS * (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* (this->ESTIRAMIENTO-1);
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	// Unimos los puntos

	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;



	int i = 0;

	for(int q = 0; q < this->ESTIRAMIENTO; q++)
	{
		for(int j = 0; j < this->CANT_PUNTOS/2; j++) 
		{
			float ppx = Matematica::curvaBezier(j * PASO, pcx);
			float ppy = Matematica::curvaBezier(j * PASO, pcy);
			float ppz = 1.0 * q;

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			std::cout << ppx << "," << ppy << "," << ppz << std::endl;
		}


		for(int j = 0; j < this->CANT_PUNTOS/2; j++) 
		{
			float ppx = Matematica::curvaBezier(j * PASO, pcx_inv);
			float ppy = Matematica::curvaBezier(j * PASO, pcy_inv);
			float ppz = 1.0 * q;

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			std::cout << ppx << "," << ppy << "," << ppz << std::endl;
		}

		// for(int k = 0; k < object_index_buffer_size; k++)
		// 	object_index_buffer[k] = k;


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
	}

	// NORMALES
	// this->object_normal_buffer[0] = 0.5f;
	// this->object_normal_buffer[1] = 0.5f;
	// this->object_normal_buffer[2] = 0.2f;

	// this->object_normal_buffer[3] = 0.5f;
	// this->object_normal_buffer[4] = -0.5f;
	// this->object_normal_buffer[5] = 0.2f;

	// this->object_normal_buffer[6] = -0.5f;
	// this->object_normal_buffer[7] = -0.5f;
	// this->object_normal_buffer[8] = 0.2f;

	// this->object_normal_buffer[9] = -0.5f;
	// this->object_normal_buffer[10] = 0.5f;
	// this->object_normal_buffer[11] = 0.2f;

	// this->object_normal_buffer[12] = 0.5f;
	// this->object_normal_buffer[13] = 0.5f;
	// this->object_normal_buffer[14] = 0.2f;
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Test::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{



	// NORMALES

	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;

	int k = 0;

	for(int i=0; i < (this->ESTIRAMIENTO-1); i++) {
		for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
		{
			float u[3], v[3];
			
			// Tomamos vectores adyacentes u y v
			u[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
				this->object_vertex_buffer[malla[i][j] * 3];
			u[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			u[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 2];
			
			v[0] = this->object_vertex_buffer[malla[i][j+1] * 3] -
				this->object_vertex_buffer[malla[i][j] * 3];
			v[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] -
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			v[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] -
				this->object_vertex_buffer[malla[i][j] * 3 + 2];


			// Calculamos la normal a u y v
			float *n = Matematica::productoVectorial(u, v);

			this->object_normal_buffer[k++] = n[0];
			this->object_normal_buffer[k++] = n[1];
			this->object_normal_buffer[k++] = n[2];
		}
	}

	
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
			&model_matrix[0][0]); 

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
