/*  
 *  CLASS CANGREJO_CUERPO
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
#include "object_cangrejo_cuerpo.h"



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
CangrejoCuerpo::CangrejoCuerpo()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
CangrejoCuerpo::~CangrejoCuerpo() { }


// Crea un objeto
void CangrejoCuerpo::create()
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Puntos de control de la CURVA DE ANCHURA
	float ancho_pc0x = 0.0;
	float ancho_pc0y = 0.0;

	float ancho_pc1x = 0.05;
	float ancho_pc1y = 1.3;

	float ancho_pc2x = 7.0;
	float ancho_pc2y = 1.3;

	float ancho_pc3x = 10.0;
	float ancho_pc3y = 0.0;

	float ancho_pcx[] = {ancho_pc0x, ancho_pc1x, ancho_pc2x, ancho_pc3x};
	float ancho_pcy[] = {ancho_pc0y, ancho_pc1y, ancho_pc2y, ancho_pc3y};


	// Puntos de control de la CURVA SUPERIOR
	float sup_pc0x = 0.0;
	float sup_pc0y = 0.2;

	float sup_pc1x = 0.1;
	float sup_pc1y = 0.5;

	float sup_pc2x = 9.0;
	float sup_pc2y = 1.0;

	float sup_pc3x = 10.0;
	float sup_pc3y = 0.3;

	float sup_pcx[] = {sup_pc0x, sup_pc1x, sup_pc2x, sup_pc3x};
	float sup_pcy[] = {sup_pc0y, sup_pc1y, sup_pc2y, sup_pc3y};


	// Puntos de control de la CURVA INFERIOR
	float inf_pc0x = 0.0;
	float inf_pc0y = -0.2;

	float inf_pc1x = 0.1;
	float inf_pc1y = 0.5;

	float inf_pc2x = 9.0;
	float inf_pc2y = 1.5;

	float inf_pc3x = 10.0;
	float inf_pc3y = -0.3;

	float inf_pcx[] = {inf_pc0x, inf_pc1x, inf_pc2x, inf_pc3x};
	float inf_pcy[] = {inf_pc0y, inf_pc1y, inf_pc2y, inf_pc3y};



	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;
	// Cantidad de curvas que compondran la curva general
	int CANT_CURVAS = 4;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = CANT_CURVAS * (int(ceil(1.0 / PASO)) + 1);
	int DIMENSIONES = 3;
	this->ESTIRAMIENTO = 50;

	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2* this->CANT_PUNTOS * (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* (this->ESTIRAMIENTO-1);
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];



	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;

	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;


	int i = 0;

	// Iteramos sobre cada nivel del objeto
	for(int q = 0; q < this->ESTIRAMIENTO; q++)
	{
		// Calculamos la curva de bezier que da forma al esqueleto superior
		float ancho = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	ancho_pcy);

		// Calculamos la curva de bezier que da forma al esqueleto superior
		float superior = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	sup_pcy);

		// Calculamos la curva de bezier que da forma al esqueleto superior
		float inferior = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	inf_pcy);


		// Puntos de control
		float pc0x = 0.0;
		float pc0y = -1.0 * ancho;
		float pc0z = 1.0 * superior;

		float pc1x = 0.0;
		float pc1y = 1.0 * ancho;
		float pc1z = 1.0 * superior;

		float pc2x = 0.0;
		float pc2y = 1.0 * ancho;
		float pc2z = -1.0 * inferior;

		float pc3x = 0.0;
		float pc3y = -1.0 * ancho;
		float pc3z = -1.0 * inferior;


		// Armamos arreglos para los trozos que conforman la curva
		float pcy012[] = {pc0y, pc1y, pc2y};
		float pcy123[] = {pc1y, pc2y, pc3y};
		float pcy230[] = {pc2y, pc3y, pc0y};
		float pcy301[] = {pc3y, pc0y, pc1y};

		float pcz012[] = {pc0z, pc1z, pc2z};
		float pcz123[] = {pc1z, pc2z, pc3z};
		float pcz230[] = {pc2z, pc3z, pc0z};
		float pcz301[] = {pc3z, pc0z, pc1z};


		// Segmento 0-1-2 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = q * 0.05f;
			float ppy = Matematica::curvaBSpline(j * PASO, pcy012);
			float ppz = Matematica::curvaBSpline(j * PASO, pcz012);

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}

		// Segmento 1-2-3 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = q * 0.05f;
			float ppy = Matematica::curvaBSpline(j * PASO, pcy123);
			float ppz = Matematica::curvaBSpline(j * PASO, pcz123);

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}

		// Segmento 2-3-0 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = q * 0.05f;
			float ppy = Matematica::curvaBSpline(j * PASO, pcy230);
			float ppz = Matematica::curvaBSpline(j * PASO, pcz230);

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}

		// Segmento 3-0-1 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = q * 0.05f;
			float ppy = Matematica::curvaBSpline(j * PASO, pcy301);
			float ppz = Matematica::curvaBSpline(j * PASO, pcz301);

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
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

	for(int i=0; i < (this->ESTIRAMIENTO-1); i++) {
		for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
		{
			float u[3], v[3];
			
			// Tomamos vectores adyacentes u y v
			u[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
				this->object_vertex_buffer[malla[i][j] * 3];
			u[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			u[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 2];
			
			v[0] = this->object_vertex_buffer[malla[i][j+1] * 3] -
				this->object_vertex_buffer[malla[i][j] * 3];
			v[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] -
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			v[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] -
				this->object_vertex_buffer[malla[i][j] * 3 + 2];


			// Calculamos la normal a u y v
			float *n = Matematica::productoVectorial(u, v);

			this->object_normal_buffer[k++] = n[0];
			this->object_normal_buffer[k++] = n[1];
			this->object_normal_buffer[k++] = n[2];
		}
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoCuerpo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glUseProgram(this->programHandle);
	
	// Ponemos el objeto en el centro del eje coordenado
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::translate(model_matrix, glm::vec3(-1.25, 0.0, 0.0));

// Damos forma del cuerpo a la esfera y la renderizamos
	// glm::mat4 mCuerpo = glm::mat4(1.0f);
	// mCuerpo = glm::scale(model_matrix, glm::vec3(1.2, 1.1, 0.5));
	// mCuerpo = glm::rotate(mCuerpo, 15.0f, glm::vec3(0.0, 1.0, 0.0));
	// this->spiralSphere.changeObjectColor(157, 243, 232);
	// this->spiralSphere.render(mCuerpo, view_matrix, projection_matrix);


	

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
			&mCuerpo[0][0]); 

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
