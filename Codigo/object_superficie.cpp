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
#include "lib_matematica.h"
#include "object_superficie.h"


// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/SuperficieVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/SuperficieFShader.frag";
	
}




/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Superficie::Superficie()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
Superficie::~Superficie() { }


// Crea un objeto
void Superficie::create(int ancho)
{
	// Cargamos la textura
	this->loadAndInitTexture("textures/sand-texture-04.jpg");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());
	


	// Almacenamos el ancho que debe tener la superficie
	this->ESTIRAMIENTO = ancho;


	// Puntos de control de la CURVA DE DEFORMACIÓN EN X
	float deformacionX_pc0x = 0.0;
	float deformacionX_pc0y = 0.0;

	float deformacionX_pc1x = 3.0;
	float deformacionX_pc1y = 5.0;

	float deformacionX_pc2x = 9.0;
	float deformacionX_pc2y = -2.0;

	float deformacionX_pc3x = 10.0;
	float deformacionX_pc3y = 0.0;

	float deformacionX_pcx[] = {deformacionX_pc0x, deformacionX_pc1x,
		deformacionX_pc2x, deformacionX_pc3x};
	float deformacionX_pcy[] = {deformacionX_pc0y, deformacionX_pc1y,
		deformacionX_pc2y, deformacionX_pc3y};


	// Puntos de control de la CURVA DE DEFORMACIÓN EN Y
	float deformacionY_pc0x = 0.0;
	float deformacionY_pc0y = 0.0;

	float deformacionY_pc1x = 2.0;
	float deformacionY_pc1y = -1.4;

	float deformacionY_pc2x = 8.5;
	float deformacionY_pc2y = 6.0;

	float deformacionY_pc3x = 10.0;
	float deformacionY_pc3y = 0.0;

	float deformacionY_pcx[] = {deformacionY_pc0x, deformacionY_pc1x,
		deformacionY_pc2x, deformacionY_pc3x};
	float deformacionY_pcy[] = {deformacionY_pc0y, deformacionY_pc1y,
		deformacionY_pc2y, deformacionY_pc3y};



	// CREACIÓN DEL OBJETO

	// Configuración del paso entre un punto y otro.
	float PASO = 0.25;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = int(ceil(1.0 / PASO)) + 1;
	int DIMENSIONES = 3;
	int DIMENSIONES_TEXTURA = 2;


	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_texture_buffer_size = DIMENSIONES_TEXTURA * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO; 
	this->object_texture_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2 * this->CANT_PUNTOS 
		* (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];


	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	// Unimos los puntos

	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;


	int i = 0;
	int y = 0;
	int w = 0;


	for(int k = -(this->ESTIRAMIENTO / 2); k < (this->ESTIRAMIENTO / 2); k++)
	{
		// Puntos de control
		float pc0x = (this->ESTIRAMIENTO / 2);
		float pc0y = k;
		float pc0z = 0.0;

		float pc1x = (this->ESTIRAMIENTO / 4);
		float pc1y = k;
		float pc1z = 0.5 * cos(k);

		float pc2x = -(this->ESTIRAMIENTO / 4);
		float pc2y = k;
		float pc2z = 0.6 * sin(k);

		float pc3x = -(this->ESTIRAMIENTO / 2);
		float pc3y = k;
		float pc3z = 0.0;

		float pcx[] = {pc0x, pc1x, pc2x, pc3x};
		float pcy[] = {pc0y, pc1y, pc2y, pc3y};
		float pcz[] = {pc0z, pc1z, pc2z, pc3z};


		for(int j = 0; j < this->CANT_PUNTOS; j++) 
		{
			float ppx = Matematica::curvaBezier(j * PASO, pcx);
			float ppy = Matematica::curvaBezier(j * PASO, pcy);
			float ppz = Matematica::curvaBezier(j * PASO, pcz);

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			this->object_texture_buffer[y++] = (j * PASO) 
				* (this->ESTIRAMIENTO / 5);
			this->object_texture_buffer[y++] = ((k * 1.0) 
				/ (this->ESTIRAMIENTO-1)) * (this->ESTIRAMIENTO / 5);


			// Calculamos los vectores tangente, binormal y normal en el punto
			float t[3], b[3], n[3];
			Matematica::curvaBezierVectores(j * PASO, pcx, pcy, pcz, t, b, n);

			// Cargamos las coordenadas del vector normal en el buffer
			// this->object_normal_buffer[w++] = n[0];
			// this->object_normal_buffer[w++] = n[1];
			// this->object_normal_buffer[w++] = n[2];
		}
	}


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



	// NORMALES

	k = 0;

	for(int i=0; i <= (this->ESTIRAMIENTO-1); i++) {
		for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
		{
			

			// Cargamos las coordenadas en el buffer
			this->object_normal_buffer[k++] = 1.0;
			this->object_normal_buffer[k++] = 1.0;
			this->object_normal_buffer[k++] = 1.0;
		}
	}
}




// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Superficie::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{	
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);

	this->changeObjectColor(199, 215, 126);

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


	// Set the Tex1 sampler uniform to refer to texture unit 0
	int loc = glGetUniformLocation(this->programHandle, "Tex1");

	if( loc >= 0 )
		glUniform1i(loc, 0);
	else
		fprintf(stderr, "Uniform variable Tex1 not found!\n");


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, this->object_normal_buffer);
	glTexCoordPointer(2, GL_FLOAT, 0, this->object_texture_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
