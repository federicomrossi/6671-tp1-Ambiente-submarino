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

#include "object_cube.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Cube::Cube()
{
	this->cube_index_buffer = NULL;
	this->cube_vertex_buffer = NULL;
	this->cube_normal_buffer = NULL;
}


// Destructor
Cube::~Cube() { }


// Crea un objeto cubo
void Cube::create()
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms("DiffuseShadingVShader.vert",
							 "DiffuseShadingFShader.frag");

	// Creamos el objeto

	if (this->cube_vertex_buffer != NULL)
		delete this->cube_vertex_buffer;

	this->cube_vertex_buffer_size = 3*8;
	this->cube_vertex_buffer = new GLfloat[this->cube_vertex_buffer_size];

	if (this->cube_normal_buffer != NULL)
		delete this->cube_normal_buffer;

	this->cube_normal_buffer_size = 3*8;
	this->cube_normal_buffer = new GLfloat[this->cube_normal_buffer_size];

	if (this->cube_index_buffer != NULL)
		delete this->cube_index_buffer;

	this->cube_index_buffer_size = 4 * 6;
	this->cube_index_buffer = new GLuint[this->cube_index_buffer_size];

	// Vertex 1
	this->cube_vertex_buffer[0] = 0.5f;
	this->cube_vertex_buffer[1] = 0.5f;
	this->cube_vertex_buffer[2] = -0.5f;

	// Vertex 2
	this->cube_vertex_buffer[3] = 0.5f;
	this->cube_vertex_buffer[4] = -0.5f;
	this->cube_vertex_buffer[5] = -0.5f;

	// Vertex 3
	this->cube_vertex_buffer[6] = -0.5f;
	this->cube_vertex_buffer[7] = -0.5f;
	this->cube_vertex_buffer[8] = -0.5f;

	// Vertex 4
	this->cube_vertex_buffer[9] = -0.5f;
	this->cube_vertex_buffer[10] = 0.5f;
	this->cube_vertex_buffer[11] = -0.5f;

	// Vertex 5
	this->cube_vertex_buffer[12] = 0.5f;
	this->cube_vertex_buffer[13] = 0.5f;
	this->cube_vertex_buffer[14] = 0.5f;

	// Vertex 6
	this->cube_vertex_buffer[15] = 0.5f;
	this->cube_vertex_buffer[16] = -0.5f;
	this->cube_vertex_buffer[17] = 0.5f;

	// Vertex 7
	this->cube_vertex_buffer[18] = -0.5f;
	this->cube_vertex_buffer[19] = -0.5f;
	this->cube_vertex_buffer[20] = 0.5f;

	// Vertex 8
	this->cube_vertex_buffer[21] = -0.5f;
	this->cube_vertex_buffer[22] = 0.5f;
	this->cube_vertex_buffer[23] = 0.5f;

	this->cube_index_buffer[0] = 0;
	this->cube_index_buffer[1] = 1;
	this->cube_index_buffer[2] = 2;
	this->cube_index_buffer[3] = 3;

	this->cube_index_buffer[4] = 4;
	this->cube_index_buffer[5] = 5;
	this->cube_index_buffer[6] = 6;
	this->cube_index_buffer[7] = 7;

	this->cube_index_buffer[8] = 0;
	this->cube_index_buffer[9] = 4;
	this->cube_index_buffer[10] = 5;
	this->cube_index_buffer[11] = 1;

	this->cube_index_buffer[12] = 1;
	this->cube_index_buffer[13] = 5;
	this->cube_index_buffer[14] = 6;
	this->cube_index_buffer[15] = 2;

	this->cube_index_buffer[16] = 2;
	this->cube_index_buffer[17] = 6;
	this->cube_index_buffer[18] = 7;
	this->cube_index_buffer[19] = 3;

	this->cube_index_buffer[20] = 3;
	this->cube_index_buffer[21] = 7;
	this->cube_index_buffer[22] = 4;
	this->cube_index_buffer[23] = 0;

	this->cube_normal_buffer[0] = 0.5f;
	this->cube_normal_buffer[1] = 0.5f;
	this->cube_normal_buffer[2] = 0.2f;

	this->cube_normal_buffer[3] = 0.5f;
	this->cube_normal_buffer[4] = -0.5f;
	this->cube_normal_buffer[5] = 0.2f;

	this->cube_normal_buffer[6] = -0.5f;
	this->cube_normal_buffer[7] = -0.5f;
	this->cube_normal_buffer[8] = 0.2f;

	this->cube_normal_buffer[9] = -0.5f;
	this->cube_normal_buffer[10] = 0.5f;
	this->cube_normal_buffer[11] = 0.2f;

	this->cube_normal_buffer[12] = 0.5f;
	this->cube_normal_buffer[13] = 0.5f;
	this->cube_normal_buffer[14] = 0.2f;

	this->cube_normal_buffer[15] = 0.5f;
	this->cube_normal_buffer[16] = -0.5f;
	this->cube_normal_buffer[17] = 0.2f;

	this->cube_normal_buffer[18] = -0.5f;
	this->cube_normal_buffer[19] = -0.5f;
	this->cube_normal_buffer[20] = 0.2f;

	this->cube_normal_buffer[21] = -0.5f;
	this->cube_normal_buffer[22] = 0.5f;
	this->cube_normal_buffer[23] = 0.2f;
}


// Renderiza el cubo (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Cube::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
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
	if( location_model_matrix >= 0 ) 
		glUniformMatrix4fv( location_model_matrix, 1, GL_FALSE, 
			&model_matrix[0][0]); 

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, cube_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, cube_normal_buffer);

	glDrawElements(GL_QUADS, this->cube_index_buffer_size, GL_UNSIGNED_INT, 
		this->cube_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
