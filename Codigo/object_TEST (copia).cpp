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


	// ////////////////// TEST 1

	
	// // Creamos el objeto

	// if (this->object_vertex_buffer != NULL)
	// 	delete this->object_vertex_buffer;

	// this->object_normal_buffer_size = 21;
	// this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	// if (this->object_index_buffer != NULL)
	// 	delete this->object_index_buffer;

	// // Puntos de control
	// float pc0x = 0.0;
	// float pc0y = 0.0;

	// float pc1x = 0.0;
	// float pc1y = 2.0;

	// float pc2x = 2.0;
	// float pc2y = 2.0;

	// float pc3x = 2.0;
	// float pc3y = 0.0;

	// float centroX = 1.0;
	// float centroY = 0.0;

	// float pcx[] = {pc0x, pc1x, pc2x, pc3x};
	// float pcy[] = {pc0y, pc1y, pc2y, pc3y};

	// int DIMENSIONS = 3;
	// int ESTIRAMIENTO = 2;

	// this->object_vertex_buffer_size = DIMENSIONS * 21 * ESTIRAMIENTO;
	// this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	// this->object_index_buffer_size = 42;
	// this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	// int i = 0;
	// double PASO = 0.05;

	// for(float t = 0.0; t <= (1.0 + PASO); t += PASO)
	// {
	// 	float ppx = Matematica::curvaBezier(t, pcx);
	// 	float ppy = Matematica::curvaBezier(t, pcy);

	// 	std::cout << t << " - " << ppx << "," << ppy << std::endl;

	// 	this->object_vertex_buffer[i++] = ppx;
	// 	this->object_vertex_buffer[i++] = ppy;
	// 	this->object_vertex_buffer[i++] = 0.0;

	// 	this->object_vertex_buffer[i++] = ppx;
	// 	this->object_vertex_buffer[i++] = ppy;
	// 	this->object_vertex_buffer[i++] = 1.0;
	// }


	// for(unsigned int i=0; i< this->object_index_buffer_size; i++) {
	// 	this->object_index_buffer[i] = i;
	// }



	// ///////////////// TEST 2

	// Creamos el objeto

	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_normal_buffer_size = 21;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	// Puntos de control
	float pcx[4][4];
	float pcy[4][4];
	float pcz[4][4];

	pcx[0][0] = 0;
	pcy[0][0] = 0;
	pcz[0][0] = 1;

	pcx[0][1] = 0;
	pcy[0][1] = 2;
	pcz[0][1] = 2;
	
	pcx[0][2] = 0;
	pcy[0][2] = 3;
	pcz[0][2] = 1.5;

	pcx[0][3] = 0;
	pcy[0][3] = 5;
	pcz[0][3] = 0;



	pcx[1][0] = 1;
	pcy[1][0] = 0;
	pcz[1][0] = 1;

	pcx[1][1] = 1;
	pcy[1][1] = 2;
	pcz[1][1] = 2;

	pcx[1][2] = 1;
	pcy[1][2] = 3;
	pcz[1][2] = 1.5;

	pcx[1][3] = 1;
	pcy[1][3] = 5;
	pcz[1][3] = 0;



	pcx[2][0] = 2;
	pcy[2][0] = 0;
	pcz[2][0] = 1;

	pcx[2][1] = 2;
	pcy[2][1] = 2;
	pcz[2][1] = 2;

	pcx[2][2] = 2;
	pcy[2][2] = 3;
	pcz[2][2] = 1.5;

	pcx[2][3] = 2;
	pcy[2][3] = 5;
	pcz[2][3] = 0;


	pcx[3][0] = 3;
	pcy[3][0] = 0;
	pcz[3][0] = 1;

	pcx[3][1] = 3;
	pcy[3][1] = 2;
	pcz[3][1] = 2;

	pcx[3][2] = 3;
	pcy[3][2] = 3;
	pcz[3][2] = 1.5;

	pcx[3][3] = 3;
	pcy[3][3] = 5;
	pcz[3][3] = 0;




	int DIMENSIONS = 3;
	int ESTIRAMIENTO = 4;

	this->object_vertex_buffer_size = DIMENSIONS * 27 * ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_index_buffer_size = 24 + 2;
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	int i = 0;
	double PASO = 0.5;

	for(float u = 0.0; u <= (1.0); u += PASO)
	{
		for(float v = 0.0; v <= (1.0); v += PASO)
		{
			float ppx = Matematica::superficieBezier(u, v, pcx);
			float ppy = Matematica::superficieBezier(u, v, pcy);
			float ppz = Matematica::superficieBezier(u, v, pcz);

			std::cout << u << " - " << ppx << "," << ppy << "," << ppz << std::endl;

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}
	}


	// for(unsigned int i=0; i< this->object_index_buffer_size; i++) {
	// 	this->object_index_buffer[i] = i;
	// }


	int a = int((1 / PASO) + 1);

	int j = 0;
	int index = 0;

	for(int k = 0; k < (j + (a - 1)); k++)
	{
		for(int i = j; i < a; i++)
		{
			this->object_index_buffer[index++] = i;
			this->object_index_buffer[index++] = i + 3;

			if(i == a - 1)
				this->object_index_buffer[index++] = i + 3;

			j++;
		}

		j += a;
	}



	// this->object_index_buffer[0] = 0;
	// this->object_index_buffer[1] = 1;
	// this->object_index_buffer[2] = 3;

	// this->object_index_buffer[3] = 1;
	// this->object_index_buffer[4] = 3;
	// this->object_index_buffer[5] = 4;

	// this->object_index_buffer[6] = 1;
	// this->object_index_buffer[7] = 4;
	// this->object_index_buffer[8] = 2;

	// this->object_index_buffer[9] = 4;
	// this->object_index_buffer[10] = 2;
	// this->object_index_buffer[11] = 5;


	// this->object_index_buffer[12] = 3;
	// this->object_index_buffer[13] = 4;
	// this->object_index_buffer[14] = 6;

	// this->object_index_buffer[15] = 4;
	// this->object_index_buffer[16] = 6;
	// this->object_index_buffer[17] = 7;

	// this->object_index_buffer[18] = 4;
	// this->object_index_buffer[19] = 5;
	// this->object_index_buffer[20] = 7;

	// this->object_index_buffer[21] = 5;
	// this->object_index_buffer[22] = 7;
	// this->object_index_buffer[23] = 8;
	



	// NORMALES


	this->object_normal_buffer[0] = 0.5f;
	this->object_normal_buffer[1] = 0.5f;
	this->object_normal_buffer[2] = 0.2f;

	this->object_normal_buffer[3] = 0.5f;
	this->object_normal_buffer[4] = -0.5f;
	this->object_normal_buffer[5] = 0.2f;

	this->object_normal_buffer[6] = -0.5f;
	this->object_normal_buffer[7] = -0.5f;
	this->object_normal_buffer[8] = 0.2f;

	this->object_normal_buffer[9] = -0.5f;
	this->object_normal_buffer[10] = 0.5f;
	this->object_normal_buffer[11] = 0.2f;

	this->object_normal_buffer[12] = 0.5f;
	this->object_normal_buffer[13] = 0.5f;
	this->object_normal_buffer[14] = 0.2f;

	this->object_normal_buffer[15] = 0.5f;
	this->object_normal_buffer[16] = -0.5f;
	this->object_normal_buffer[17] = 0.2f;

	this->object_normal_buffer[18] = -0.5f;
	this->object_normal_buffer[19] = -0.5f;
	this->object_normal_buffer[20] = 0.2f;
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Test::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
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
