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
	this->loadShaderPrograms("DiffuseShadingVShader.vert",
							 "DiffuseShadingFShader.frag");

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
void Grid::render(glm::mat4 model_matrix, glm::mat4 &view_matrix)
{
	// Normal Matrix
	glm::mat3 normal_matrix = glm::mat3 ( 1.0f );

	// Bind Normal MAtrix
	GLuint location_normal_matrix = glGetUniformLocation(this->programHandle, "NormalMatrix"); 
	if( location_normal_matrix >= 0 ) 
		glUniformMatrix3fv( location_normal_matrix, 1, GL_FALSE, &normal_matrix[0][0]); 

	// Bind Model Matrix
	GLuint location_model_matrix = glGetUniformLocation(this->programHandle, "ModelMatrix"); 
	if(location_model_matrix >= 0)
		glUniformMatrix4fv( location_model_matrix, 1, GL_FALSE, &model_matrix[0][0]); 

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->grid_vertex_buffer);

	glDrawElements(GL_LINES, this->grid_index_buffer_size, GL_UNSIGNED_INT, this->grid_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
}
