/*  
 *  CLASS PEZ_OJO
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
#include "object_pez_ojo.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/RocaVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/RocaFShader.frag";
}





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
PezOjo::PezOjo() 
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_tangent_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
PezOjo::~PezOjo() { }


// Crea un objeto
void PezOjo::create()
{
	// Cargamos la textura
	this->loadAndInitTexture("textures/rock-texture-01.jpg");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	int DIMENSIONES = 3;
	int DIMENSIONES_TEXTURA = 2;
	float PI = 3.1415f;
	float ro = 1.0f;
	int phi;
	int tita;
	int num_puntos = 9;

	this->ESTIRAMIENTO = (num_puntos / 2) + 1;
	this->CANT_PUNTOS = num_puntos;


	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * 45;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_texture_buffer_size = DIMENSIONES_TEXTURA  * 45;
	this->object_texture_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2 * 45;
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * 45;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];

	this->object_tangent_buffer_size = DIMENSIONES * 45;
	this->object_tangent_buffer = new GLfloat[this->object_tangent_buffer_size];



	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;

	
	int i = 0;
	int y = 0;
	int w = 0;
	int z = 0;
	int cont = 0;

	for(phi = 0; phi < (num_puntos-1)/2 + 1; phi++)
	{
		std::cout << std::endl << "Phi: " << PI / num_puntos * phi << std::endl;

		for(tita = 0; tita < num_puntos; tita++)
		{
			cont++;
			std::cout << "tita: " << 2 * PI / num_puntos * tita << std::endl;

			float vx = ro * std::sin(2 * PI * phi / (num_puntos-1)) * std::cos(2 * PI * tita / (num_puntos-1));
			float vy = ro * std::sin(2 * PI * phi / (num_puntos-1)) * std::sin(2 * PI * tita / (num_puntos-1));
			float vz = ro * std::cos(2 * PI * phi / (num_puntos-1));

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = vx;
			this->object_vertex_buffer[i++] = vy;
			this->object_vertex_buffer[i++] = vz;

			// // Cargamos las coordenadas del vector normal en el buffer
			// this->object_normal_buffer[w++] = 1.0;
			// this->object_normal_buffer[w++] = 1.0;
			// this->object_normal_buffer[w++] = 1.0;

			// // Cargamos las coordenadas del vector tangente en el buffer
			// this->object_tangent_buffer[z++] = 0.0;
			// this->object_tangent_buffer[z++] = 0.0;
			// this->object_tangent_buffer[z++] = 1.0;

			// this->object_texture_buffer[y++] = (std::cos(PI / num_puntos * phi) + 1) / 2;
			// this->object_texture_buffer[y++] = (std::cos(PI / num_puntos * phi) + 1) / 2;
		}
	}
	std::cout << "CONT: " << cont << std::endl;

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


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezOjo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);
	glActiveTexture(GL_TEXTURE0);
	
	this->changeObjectColor(180,180,180);

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

	glm::vec3 light_intensity = glm::vec3(0.7f, 0.7f, 0.7f);
	glm::vec4 light_position = glm::vec4(-8.0f, -8.0f, 2.0f, 1.0f);
	glm::vec3 La = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ls = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ka = glm::vec3(90 / 255.0f,
							 49 / 255.0f, 
							 49 / 255.0f);
	this->changeObjectColor(186, 143, 143);
	glm::vec3 Kd = glm::vec3(this->R / 255.0f,
							 this->G / 255.0f, 
							 this->B / 255.0f);
	glm::vec3 Ks = glm::vec3(0.5f, 0.5f, 0.5f);
	float Shininess = 1.0;

	// Fog
	float FogMinDist = 4.0;
	float FogMaxDist = 10.0;
	glm::vec3 FogColor = glm::vec3(0.0f / 255.0, 
								   36.0f / 255.0,
								   60.0f / 255.0);

	// Light Intensity
	GLuint location_light_intensity = glGetUniformLocation(this->programHandle, "LightIntensity");

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
	
	// // Kd
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




	// FoxMaxDist
	GLfloat location_fogMaxDist = glGetUniformLocation(this->programHandle,
		"FogMaxDist");

	if(location_fogMaxDist >= 0)
		glUniform1f(location_fogMaxDist, FogMaxDist);


	// FoxMinDist
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
	glm::mat3 normal_matrix = glm::mat3 ( 1.0f );

	// Bind Normal Matrix
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



	//  the Texture sampler uniform to refer to texture unit 0
	int loc = glGetUniformLocation(this->programHandle, "Texture");
	if(loc >= 0) glUniform1i(loc, 0);
	else fprintf(stderr, "Uniform variable TexPezOjo not found!\n");



	// Activamos textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);
	glTexCoordPointer(2, GL_FLOAT, 0, this->object_texture_buffer);
	glColorPointer(3, GL_FLOAT, 0, this->object_tangent_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
