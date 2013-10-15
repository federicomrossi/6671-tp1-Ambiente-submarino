/*  
 *  CLASS CUBE
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

#include "object_grid.h"



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
Grid::Grid()
{
	this->grid_index_buffer = NULL;
	this->grid_vertex_buffer = NULL;
}


// Destructor
Grid::~Grid() { }


// Crea un objeto cubo
void Grid::create(int size)
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());
	
	// Creamos el objeto

	if (this->grid_vertex_buffer != NULL)
		delete this->grid_vertex_buffer;

	this->grid_vertex_buffer_size = 12*(2*size +1);
	this->grid_vertex_buffer = new GLfloat[this->grid_vertex_buffer_size];


	if (this->grid_index_buffer != NULL)
		delete this->grid_index_buffer;

	this->grid_index_buffer_size = 4*(2*size +1);
	this->grid_index_buffer = new GLuint[this->grid_index_buffer_size];

	int offset;

	for (int i=0; i<size; i++)
	{
		offset = 24*i;
		this->grid_vertex_buffer[offset++] = -size;
		this->grid_vertex_buffer[offset++] = i+1;
		this->grid_vertex_buffer[offset++] = 0;

		this->grid_vertex_buffer[offset++] = size;
		this->grid_vertex_buffer[offset++] = i+1;
		this->grid_vertex_buffer[offset++] = 0;

		this->grid_vertex_buffer[offset++] = -size;
		this->grid_vertex_buffer[offset++] = -(i+1);
		this->grid_vertex_buffer[offset++] = 0;

		this->grid_vertex_buffer[offset++] = size;
		this->grid_vertex_buffer[offset++] = -(i+1);
		this->grid_vertex_buffer[offset++] = 0;


		this->grid_vertex_buffer[offset++] = i+1;
		this->grid_vertex_buffer[offset++] = -size;
		this->grid_vertex_buffer[offset++] = 0;

		this->grid_vertex_buffer[offset++] = i+1;
		this->grid_vertex_buffer[offset++] = size;
		this->grid_vertex_buffer[offset++] = 0;

		this->grid_vertex_buffer[offset++] = -(i+1);
		this->grid_vertex_buffer[offset++] = -size;
		this->grid_vertex_buffer[offset++] = 0;

		this->grid_vertex_buffer[offset++] = -(i+1);
		this->grid_vertex_buffer[offset++] = size;
		this->grid_vertex_buffer[offset++] = 0;
	}

	offset = 24 * size;
	this->grid_vertex_buffer[offset++]   = -size;
	this->grid_vertex_buffer[offset++] = 0;
	this->grid_vertex_buffer[offset++] = 0;

	this->grid_vertex_buffer[offset++] = size;
	this->grid_vertex_buffer[offset++] = 0;
	this->grid_vertex_buffer[offset++] = 0;

	this->grid_vertex_buffer[offset++] = 0;
	this->grid_vertex_buffer[offset++] = -size;
	this->grid_vertex_buffer[offset++] = 0;

	this->grid_vertex_buffer[offset++] = 0;
	this->grid_vertex_buffer[offset++] = size;
	this->grid_vertex_buffer[offset++] = 0;

	for (unsigned int i=0; i< this->grid_index_buffer_size; i++)
		this->grid_index_buffer[i] = i;
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Grid::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
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

	/*struct FogInfo {
		float maxDist;
		float minDist;
		vec3 color;
	};

	GLuint fog;
	GLuint location_fog = glGetUniformLocation(fog, "FogInfo"); 

	fog.maxDist = 5.0f;
	fog.minDist = 1.0f;
	fog.color = glm::vec3(0.0f, 0.0f, 0.0f);
	*/


	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->grid_vertex_buffer);

	glDrawElements(GL_LINES, this->grid_index_buffer_size, GL_UNSIGNED_INT, 
		this->grid_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
