/*  
 *  CLASS SUPERFICIE
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

#include "object_superficie.h"



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
Superficie::Superficie()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
Superficie::~Superficie() { }


// Crea un objeto
void Superficie::create()
{
	// Creamos el eje coordenado
	// this->ejeCoordenado.create(3);

	// TAMAÑO DE LA SUPERFICIE
	float TAMANIO = 16.0;


	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Creamos el objeto
	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	int DIMENSIONES = 3;
	int ESTIRAMIENTO = 1;
	int CANT_PUNTOS = 5;

	// Configuración de la normal
	this->object_normal_buffer_size = DIMENSIONES * CANT_PUNTOS;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];

	this->object_normal_buffer[0] = 0.1f;
	this->object_normal_buffer[1] = 0.1f;
	this->object_normal_buffer[2] = 0.2f;

	this->object_normal_buffer[3] = 0.1f;
	this->object_normal_buffer[4] = 0.1f;
	this->object_normal_buffer[5] = 0.2f;

	this->object_normal_buffer[6] = 0.1f;
	this->object_normal_buffer[7] = 0.1f;
	this->object_normal_buffer[8] = 0.2f;

	this->object_normal_buffer[9] = 0.1f;
	this->object_normal_buffer[10] = 0.1f;
	this->object_normal_buffer[11] = 0.2f;

	this->object_normal_buffer[12] = 0.1f;
	this->object_normal_buffer[13] = 0.1f;
	this->object_normal_buffer[14] = 0.2f;

	// Puntos
	float centroX = 0.0;
	float centroY = 0.0;

	float pc0x = centroX + TAMANIO;
	float pc0y = centroY + TAMANIO;

	float pc1x = centroX - TAMANIO;
	float pc1y = centroY + TAMANIO;

	float pc2x = centroX - TAMANIO;
	float pc2y = centroY - TAMANIO;

	float pc3x = centroX + TAMANIO;
	float pc3y = centroY - TAMANIO;

	this->object_vertex_buffer_size = DIMENSIONES * CANT_PUNTOS  * ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_index_buffer_size = CANT_PUNTOS + 1;
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_vertex_buffer[0] = centroX;
	this->object_vertex_buffer[1] = centroY;
	this->object_vertex_buffer[2] = 0.0;

	this->object_vertex_buffer[3] = pc0x;
	this->object_vertex_buffer[4] = pc0y;
	this->object_vertex_buffer[5] = 0.0;

	this->object_vertex_buffer[6] = pc1x;
	this->object_vertex_buffer[7] = pc1y;
	this->object_vertex_buffer[8] = 0.0;

	this->object_vertex_buffer[9] = pc2x;
	this->object_vertex_buffer[10] = pc2y;
	this->object_vertex_buffer[11] = 0.0;

	this->object_vertex_buffer[12] = pc3x;
	this->object_vertex_buffer[13] = pc3y;
	this->object_vertex_buffer[14] = 0.0;


	for(unsigned int i=0; i< this->object_index_buffer_size; i++) {
		this->object_index_buffer[i] = i;
	}
	this->object_index_buffer[this->object_index_buffer_size - 1] = 1;
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Superficie::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, 
	// 	projection_matrix);
	
	// Seteamos el color de la superficie
	this->changeObjectColor(251, 202, 150);


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

	glDrawElements(GL_TRIANGLE_FAN, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
