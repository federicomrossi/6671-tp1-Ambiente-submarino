/*  
 *  CLASS CANGREJO_PINZA_MUNIECA
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

#include "config.h"
#include "object_cangrejo_pinza_munieca.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/CangrejoVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/CangrejoFShader.frag";
}





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
CangrejoPinzaMunieca::CangrejoPinzaMunieca()
{
	this->sphere_vertex_buffer = NULL;
	this->sphere_index_buffer = NULL;
	this->sphere_tangent_buffer = NULL;
	this->sphere_texture_buffer = NULL;

	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_tangent_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
CangrejoPinzaMunieca::~CangrejoPinzaMunieca() { }


// Crea un objeto.
// PRE: 'radius' es el radio de la esfera; 'loops' ...; 'segmentsPerLoop' ....
// [Completar documentacion]
void CangrejoPinzaMunieca::create(const float radius, const unsigned int loops, 
	const unsigned int segmentsPerLoop)
{
	// Cargamos la textura
	this->loadAndInitTexture("textures/cangrejo-textura-01.jpg", 
		"textures/cangrejo-normailmap-textura-01.png");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());



	// Creamos el objeto

	if (this->vertex_buffer.size() > 0)
		this->vertex_buffer.clear();

	if (this->index_buffer.size() > 0)
		this->index_buffer.clear();

	if (this->tangent_buffer.size() > 0)
		this->tangent_buffer.clear();

	if (this->texture_buffer.size() > 0)
		this->texture_buffer.clear();


	// Valor constante para el número Pi
	float PI = 3.1415f;

	// Vector tangente correspondiente al barrido
	float t_barrido[3];
	t_barrido[0] = 0.0;
	t_barrido[1] = 0.0;
	t_barrido[2] = 1.0;


	for(unsigned int loopSegmentNumber = 0; 
		loopSegmentNumber < segmentsPerLoop; ++loopSegmentNumber)
	{
		float theta = 0.0001;
		float phi = loopSegmentNumber * 2 * PI / segmentsPerLoop;
		float sinTheta = std::sin(theta);
		float sinPhi = std::sin(phi);
		float cosTheta = std::cos(theta);
		float cosPhi = std::cos(phi);

		float vx = radius * cosPhi * sinTheta;
		float vy = radius * sinPhi * sinTheta;
		float vz = radius * cosTheta;

		this->vertex_buffer.push_back(vx); // Vx
		this->vertex_buffer.push_back(vy); // Vy
		this->vertex_buffer.push_back(vz); // Vz

		// Vector normal del vértice
		float n[3];
		n[0] = vx;
		n[1] = vy;
		n[2] = vz;
		float *nn = Matematica::normalizar(n);

		// Calculamos la tangente al vértice
		float *temp = Matematica::productoVectorial(nn, t_barrido);
		float *t = Matematica::normalizar(temp);

		this->tangent_buffer.push_back(t[0]);
		this->tangent_buffer.push_back(t[1]);
		this->tangent_buffer.push_back(t[2]);

		this->texture_buffer.push_back(0.0);
		this->texture_buffer.push_back(loopSegmentNumber * 1.0 / (segmentsPerLoop-1));
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

			float vx = radius * cosPhi * sinTheta;
			float vy = radius * sinPhi * sinTheta;
			float vz = radius * cosTheta;

			this->vertex_buffer.push_back(vx); // Vx
			this->vertex_buffer.push_back(vy); // Vy
			this->vertex_buffer.push_back(vz); // Vz

			// Vector normal del vértice
			float n[3];
			n[0] = vx;
			n[1] = vy;
			n[2] = vz;
			float *nn = Matematica::normalizar(n);

			// Calculamos la tangente al vértice
			float *temp = Matematica::productoVectorial(nn, t_barrido);
			float *t = Matematica::normalizar(temp);

			this->tangent_buffer.push_back(t[0]);
			this->tangent_buffer.push_back(t[1]);
			this->tangent_buffer.push_back(t[2]);


			this->texture_buffer.push_back(loopNumber * 1.0 / loops);
			this->texture_buffer.push_back(loopSegmentNumber * 1.0 / (segmentsPerLoop-1));
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

	if (this->sphere_tangent_buffer != NULL)
		delete[] this->sphere_tangent_buffer;
	this->sphere_tangent_buffer = new float[this->tangent_buffer.size()];

	if (this->sphere_texture_buffer != NULL)
		delete[] this->sphere_texture_buffer;
	this->sphere_texture_buffer = new float[this->texture_buffer.size()];



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

	std::vector<float>::iterator tangent_it;
	i = 0;

	for (tangent_it = this->tangent_buffer.begin(); 
		tangent_it != this->tangent_buffer.end(); tangent_it++)
	{
		this->sphere_tangent_buffer[i] = *tangent_it;
		i++;
	}

	std::vector<float>::iterator texture_it;
	i = 0;

	for (texture_it = this->texture_buffer.begin(); 
		texture_it != this->texture_buffer.end(); texture_it++)
	{
		this->sphere_texture_buffer[i] = *texture_it;
		i++;
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPinzaMunieca::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);
	
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

	glm::vec3 light_intensity = LIGHT_INTENSITY;
	glm::vec4 light_position = LIGHT_POSITION;
	glm::vec3 La = glm::vec3(0.1f, 0.1f, 0.2f);
	glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ls = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ka = glm::vec3(100/ 255.0f,
							 0 / 255.0f, 
							 0 / 255.0f);
	this->changeObjectColor(255, 0, 0);
	glm::vec3 Kd = glm::vec3(this->R / 255.0f,
							 this->G / 255.0f, 
							 this->B / 255.0f);
	glm::vec3 Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	float Shininess = 20.0;

	// Fog
	GLfloat FogMinDist = FOG_MIN_DISTANCE;
	GLfloat FogMaxDist = FOG_MAX_DISTANCE;
	glm::vec3 FogColor = FOG_COLOR;
	

	// Light Intensity
	GLuint location_light_intensity = glGetUniformLocation(this->programHandle, 
		"LightIntensity");

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
	
	// Kd
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


	// FogMaxDist
	GLfloat location_fogMaxDist = glGetUniformLocation(this->programHandle,
		"FogMaxDist");

	if(location_fogMaxDist >= 0)
		glUniform1f(location_fogMaxDist, FogMaxDist);


	// FogMinDist
	GLfloat location_fogMinDist = glGetUniformLocation(this->programHandle,
		"FogMinDist");

	if(location_fogMinDist >= 0)
		glUniform1f(location_fogMinDist, FogMinDist); 


	// FogColor
	GLuint location_FogColor = glGetUniformLocation(
		this->programHandle, "FogColor");

	if(location_FogColor >= 0) 
		glUniform3fv(location_FogColor, 1, &FogColor[0]);  
	//
	///////////////////////////////////////////


	// Normal Matrix
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model_matrix)));


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


	// Set the Texture sampler uniform to refer to texture unit 0
	int loc = glGetUniformLocation(this->programHandle, "Texture");
	if(loc >= 0) glUniform1i(loc, 0);
	else fprintf(stderr, "Uniform variable TexCangrejoCuerpo not found!\n");


	// Set the NormalMapTex sampler uniform to refer to texture unit 1
	int locNM = glGetUniformLocation(this->programHandle, "NormalMapTex");
	if(locNM >= 0) glUniform1i(locNM, 1);
	else fprintf(stderr, "Uniform variable NormalMapTexCangrejoCuerpo not found!\n");


	// Activamos textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);

	// Activamos normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalmap_id);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, sphere_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, sphere_vertex_buffer);
	glTexCoordPointer(2, GL_FLOAT, 0, this->sphere_texture_buffer);
	glColorPointer(3, GL_FLOAT, 0, this->sphere_tangent_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, index_buffer.size(), GL_UNSIGNED_INT, sphere_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
