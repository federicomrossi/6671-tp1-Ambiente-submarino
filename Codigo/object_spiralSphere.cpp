/*  
 *  CLASS SPIRALSPHERE
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

#include "object_spiralSphere.h"



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
SpiralSphere::SpiralSphere()
{
	this->sphere_vertex_buffer = NULL;
	this->sphere_index_buffer = NULL;
}


// Destructor
SpiralSphere::~SpiralSphere() { }


// Crea un objeto.
// PRE: 'radius' es el radio de la esfera; 'loops' ...; 'segmentsPerLoop' ....
// [Completar documentacion]
void SpiralSphere::create(const float radius, const unsigned int loops, 
	const unsigned int segmentsPerLoop)
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());

	// Creamos el objeto

	if (this->vertex_buffer.size() > 0)
		this->vertex_buffer.clear();

	if (this->index_buffer.size() > 0)
		this->index_buffer.clear();

	float PI = 3.1415f;

	for(unsigned int loopSegmentNumber = 0; 
		loopSegmentNumber < segmentsPerLoop; ++loopSegmentNumber)
	{
		float theta = 0;
		float phi = loopSegmentNumber * 2 * PI / segmentsPerLoop;
		float sinTheta = std::sin(theta);
		float sinPhi = std::sin(phi);
		float cosTheta = std::cos(theta);
		float cosPhi = std::cos(phi);

		this->vertex_buffer.push_back(radius * cosPhi * sinTheta); // Vx
		this->vertex_buffer.push_back(radius * sinPhi * sinTheta); // Vy
		this->vertex_buffer.push_back(radius * cosTheta);          // Vz
	}

	for (unsigned int loopNumber = 0; loopNumber <= loops; ++loopNumber)
	{
		for (unsigned int loopSegmentNumber = 0; 
			loopSegmentNumber < segmentsPerLoop; ++loopSegmentNumber)
		{
			float theta = (loopNumber * PI / loops) + 
				((PI * loopSegmentNumber) / (segmentsPerLoop * loops));
			
			if (loopNumber == loops)
				theta = PI;

			float phi = loopSegmentNumber * 2 * PI / segmentsPerLoop;
			float sinTheta = std::sin(theta);
			float sinPhi = std::sin(phi);
			float cosTheta = std::cos(theta);
			float cosPhi = std::cos(phi);

			this->vertex_buffer.push_back(radius * cosPhi * sinTheta);
			this->vertex_buffer.push_back(radius * sinPhi * sinTheta);
			this->vertex_buffer.push_back(radius * cosTheta);
		}
	}

	for (unsigned int loopSegmentNumber = 0; 
		loopSegmentNumber < segmentsPerLoop; ++loopSegmentNumber)
	{
		this->index_buffer.push_back(loopSegmentNumber);
		this->index_buffer.push_back(segmentsPerLoop + loopSegmentNumber);
	}

	for (unsigned int loopNumber = 0; loopNumber < loops; ++loopNumber)
	{
		for (unsigned int loopSegmentNumber = 0; 
			loopSegmentNumber < segmentsPerLoop; ++loopSegmentNumber)
		{
			this->index_buffer.push_back(((loopNumber + 1) * segmentsPerLoop) 
				+ loopSegmentNumber);
			this->index_buffer.push_back(((loopNumber + 2) * segmentsPerLoop) 
				+ loopSegmentNumber);
		}
	}

	if (this->sphere_vertex_buffer != NULL)
		delete[] this->sphere_vertex_buffer;

	this->sphere_vertex_buffer = new float[this->vertex_buffer.size()];

	if ( this->sphere_index_buffer != NULL)
		delete[] this->sphere_index_buffer;

	this->sphere_index_buffer = new unsigned int[this->index_buffer.size()];

	std::vector<float>::iterator vertex_it;
	unsigned int v = 0;

	for (vertex_it = this->vertex_buffer.begin(); 
		vertex_it != this->vertex_buffer.end(); vertex_it++)
	{
		this->sphere_vertex_buffer[v] = *vertex_it;
		v++;
	}

	std::vector<unsigned int>::iterator index_it;
	unsigned int i = 0;

	for (index_it = this->index_buffer.begin(); 
		index_it != this->index_buffer.end(); index_it++)
	{
		this->sphere_index_buffer[i] = *index_it;
		i++;
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void SpiralSphere::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glUseProgram(this->programHandle);

	this->changeObjectColor(255, 255, 255);
	
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
	glm::mat4 aux = view_matrix * model_matrix;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			normal_matrix[i][j] = aux[i][j];

	// Bind Normal Matrix
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

	glVertexPointer(3, GL_FLOAT, 0, sphere_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, sphere_vertex_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, index_buffer.size(), GL_UNSIGNED_INT, 
		sphere_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
