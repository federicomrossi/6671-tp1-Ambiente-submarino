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
	
	// Creamos el objeto

	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	// this->object_vertex_buffer_size = 27;
	// this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_normal_buffer_size = 21;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	// this->object_index_buffer_size = 7;
	// this->object_index_buffer = new GLuint[this->object_index_buffer_size];


	// this->object_vertex_buffer[0] = 2;
	// this->object_vertex_buffer[1] = 0;
	// this->object_vertex_buffer[2] = 0;

	// this->object_vertex_buffer[3] = 1;
	// this->object_vertex_buffer[4] = 1;
	// this->object_vertex_buffer[5] = 2;

	// this->object_vertex_buffer[6] = 2;
	// this->object_vertex_buffer[7] = 2;
	// this->object_vertex_buffer[8] = 0;

	// this->object_vertex_buffer[9] = 0;
	// this->object_vertex_buffer[10] = 2;
	// this->object_vertex_buffer[11] = 0;

	// this->object_vertex_buffer[12] = 0;
	// this->object_vertex_buffer[13] = 0;
	// this->object_vertex_buffer[14] = 0;

	// this->object_vertex_buffer[15] = 1;
	// this->object_vertex_buffer[16] = 1;
	// this->object_vertex_buffer[17] = 2;

	// this->object_vertex_buffer[18] = 2;
	// this->object_vertex_buffer[19] = 0;
	// this->object_vertex_buffer[20] = 0;


	///////////////////////////////////////////////////////////////

	// int paso = 45;
	// int grado = 0;

	// this->object_vertex_buffer_size = 360/paso;
	// this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	// this->object_index_buffer_size = 360/paso;
	// this->object_index_buffer = new GLuint[this->object_index_buffer_size];


	// this->object_vertex_buffer[0] = 0;
	// this->object_vertex_buffer[1] = 0;
	// this->object_vertex_buffer[2] = 0;

	// for(int i = 3; grado < 360; i++)
	// {
	// 	// std::cout << "Grado: " << grado << std::endl;
	// 	this->object_vertex_buffer[i] = std::sin(grado);
	// 	this->object_vertex_buffer[++i] = std::cos(grado);
	// 	this->object_vertex_buffer[++i] = 0;

	// 	grado += paso;
	// }

	// unsigned int i;

	// for(i=0; i< this->object_index_buffer_size; i++)
	// 	this->object_index_buffer[i] = i;

	// Puntos de control
	float pc0x = 0.0;
	float pc0y = 0.0;

	float pc1x = 0.0;
	float pc1y = 2.0;

	float pc2x = 2.0;
	float pc2y = 2.0;

	float pc3x = 2.0;
	float pc3y = 0.0;

	// float pc4x = 2.0;
	// float pc4y = -2.0;

	// float pc5x = 0.0;
	// float pc5y = -2.0;

	float centroX = 1.0;
	float centroY = 0.0;

	float pcx[] = {pc0x, pc1x, pc2x, pc3x};
	float pcy[] = {pc0y, pc1y, pc2y, pc3y};

	// float pcx[] = {pc0x, pc1x, pc2x, pc3x, pc4x, pc5x};
	// float pcy[] = {pc0y, pc1y, pc2y, pc3y, pc4y, pc5y};



	int DIMENSIONS = 3;
	int ESTIRAMIENTO = 2;

	this->object_vertex_buffer_size = DIMENSIONS * 21 * ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_index_buffer_size = 42;
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	int i = 0;
	double PASO = 0.05;

	for(float t = 0.0; t <= (1.0 + PASO); t += PASO)
	{
		float ppx = Matematica::bezier(t, pcx);
		float ppy = Matematica::bezier(t, pcy);

		std::cout << t << " - " << ppx << "," << ppy << std::endl;

		this->object_vertex_buffer[i++] = ppx;
		this->object_vertex_buffer[i++] = ppy;
		this->object_vertex_buffer[i++] = 0.0;

		this->object_vertex_buffer[i++] = ppx;
		this->object_vertex_buffer[i++] = ppy;
		this->object_vertex_buffer[i++] = 1.0;
	}

	// float ppx = Matematica::bezier(0.99999, pcx);
	// float ppy = Matematica::bezier(0.99999, pcy);

	// this->object_vertex_buffer[i++] = ppx;
	// this->object_vertex_buffer[i++] = ppy;
	// this->object_vertex_buffer[i++] = 0.0;

	// this->object_vertex_buffer[i++] = ppx;
	// this->object_vertex_buffer[i++] = ppy;
	// this->object_vertex_buffer[i++] = 1.0;


	for(unsigned int i=0; i< this->object_index_buffer_size; i++) {
		this->object_index_buffer[i] = i;
	}


	/////////////////////////////////////////////////////////////

	// float p1x = 0.0;
	// float p1y = 0.0;

	// float p2x = 3.0;
	// float p2y = 12.0;

	// float p3x = 12.0;
	// float p3y = 1.0;

	// float p4x = 15.0;
	// float p4y = 15.0;

	// float px[] = {p1x, p2x, p3x, p4x};
	// float py[] = {p1y, p2y, p3y, p4y};

	// for(float t = 0.0; t <= 1.0; t += 0.1)
	// {
	// 	float ppx = Matematica::bezier(3, t, px);
	// 	float ppy = Matematica::bezier(3, t, py);
	// 	// std::cout << ppx << "," << ppy << std::endl;
	// }


	///////////////////////////////////////////////////////////////////

	// this->object_vertex_buffer[0] = std::sin(0);
	// this->object_vertex_buffer[1] = std::cos(0);
	// this->object_vertex_buffer[2] = 0;

	// this->object_vertex_buffer[3] = std::sin(45);
	// this->object_vertex_buffer[4] = std::cos(45);
	// this->object_vertex_buffer[5] = 0;

	// this->object_vertex_buffer[6] = std::sin(90);
	// this->object_vertex_buffer[7] = std::cos(90);
	// this->object_vertex_buffer[8] = 0;

	// this->object_vertex_buffer[9] = std::sin(135);
	// this->object_vertex_buffer[10] = std::cos(135);
	// this->object_vertex_buffer[11] = 0;

	// this->object_vertex_buffer[12] = std::sin(180);
	// this->object_vertex_buffer[13] = std::cos(180);
	// this->object_vertex_buffer[14] = 0;

	// this->object_vertex_buffer[15] = std::sin(225);
	// this->object_vertex_buffer[16] = std::cos(225);
	// this->object_vertex_buffer[17] = 0;

	// this->object_vertex_buffer[18] = std::sin(270);
	// this->object_vertex_buffer[19] = std::cos(270);
	// this->object_vertex_buffer[20] = 0;

	// this->object_vertex_buffer[21] = std::sin(270);
	// this->object_vertex_buffer[22] = std::cos(270);
	// this->object_vertex_buffer[23] = 0;

	// this->object_vertex_buffer[24] = 0;
	// this->object_vertex_buffer[25] = 0;
	// this->object_vertex_buffer[26] = 0;



	///////////////////////////////////////////////////////////////

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




	// for (unsigned int i=0; i< this->object_index_buffer_size; i++)
	// 	this->object_index_buffer[i] = i;
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
