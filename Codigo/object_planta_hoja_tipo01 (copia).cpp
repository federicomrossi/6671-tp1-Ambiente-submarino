/*  
 *  CLASS PEZ_ALETA_DORSAL
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "lib_matematica.h"
#include "object_planta_hoja_tipo01.h"



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
PlantaHojaTipo01::PlantaHojaTipo01() 
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
PlantaHojaTipo01::~PlantaHojaTipo01() { }


// Crea un objeto
void PlantaHojaTipo01::create()
{
	// // DEBUG
	// // Creamos la esfera
	// this->cube.create();
	// // END DEBUG


	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Creamos el objeto

	// Puntos de control
	float pc0x = 0.0;
	float pc0y = 0.0;

	float pc1x = -1.0;
	float pc1y = 2.0;

	float pc2x = -1.0;
	float pc2y = 4.0;

	float pc3x = 0.0;
	float pc3y = 6.0;

	float pcx[] = {pc0x, pc1x, pc2x, pc3x};
	float pcy[] = {pc0y, pc1y, pc2y, pc3y};

	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;

	// Valores para cálculos (no modificar)
	int CANT_PUNTOS = int(ceil(1.0 / PASO)) + 1;
	int DIMENSIONES = 3;
	int ESTIRAMIENTO = 3;


	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * CANT_PUNTOS * ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2 * CANT_PUNTOS * (ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = 2 * CANT_PUNTOS * (ESTIRAMIENTO-1);
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	std::cout << "PUNTOS: " << 2 * CANT_PUNTOS * (ESTIRAMIENTO-1) << std::endl;



	// Unimos los puntos
	
	int malla[ESTIRAMIENTO][CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < ESTIRAMIENTO; m++)
		for(int n = 0; n < CANT_PUNTOS; n++)
			malla[m][n] = e++;


	int i = 0;

	for(int k = 0; k < ESTIRAMIENTO; k++) {
		for(int j = 0; j < CANT_PUNTOS; j++) {

			float ppx = Matematica::curvaBezier(j * PASO, pcx);
			float ppy = Matematica::curvaBezier(j * PASO, pcy);
			float ppz = k * 0.5f;

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}
	}


	int sentido = 1;
	int k = 0;

	for(int i=0; i < (ESTIRAMIENTO-1); i++)
	{
		if(sentido == 1)
		{
			for(int j=0; j <= (CANT_PUNTOS-1); j++) {
				std::cout << i << j << ", ";
				std::cout << i+1 << j << std::endl;
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = -1;
		}
		else if(sentido == -1)
		{
			for(int j=(CANT_PUNTOS-1); j >= 0; j--) {
				std::cout << i << j << ", ";
				std::cout << i+1 << j << std::endl;
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = 1;
		}

		std::cout << std::endl;
	}

	std::cout << "K: " << k << std::endl;




	// for(unsigned int i=0; i< this->object_index_buffer_size; i++) {
	// 	this->object_index_buffer[i] = i;
	// }


	// NORMALES

	for(int j = 0; j < this->object_normal_buffer_size; j++)
		this->object_normal_buffer[i] = 0.0f;

	std::cout << "PASOO" << std::endl;
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PlantaHojaTipo01::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Bind View Matrix
	// ################
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



	// Bind Light Settings
	// ###################

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



	// // DEBUG
	// // Damos forma y la renderizamos
	// this->cube.changeObjectColor(20, 143, 4);
	// glm::mat4 m = glm::mat4(1.0f);
	// m = glm::scale(model_matrix, glm::vec3(0.01, 0.2, 3.0));
	// this->cube.render(m, view_matrix, projection_matrix);
	// // END DEBUG
}
